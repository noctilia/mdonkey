/***************************************************************************

Crazy Kong memory map

Very similar to Crazy Climber, there is an additional ROM at 5000-5fff.
RAM is at 6000-6bff

*
 * DSW1 (bits NOT inverted)
 * bit 7 : COCKTAIL or UPRIGHT cabinet (1 = UPRIGHT)
 * bit 6 : \ 000 = 1 coin 1 play   001 = 2 coins 1 play  010 = 1 coin 2 plays
 * bit 5 : | 011 = 3 coins 1 play  100 = 1 coin 3 plays  101 = 4 coins 1 play
 * bit 4 : / 110 = 1 coin 4 plays  111 = 5 coins 1 play
 * bit 3 : \bonus at
 * bit 2 : / 00 = 7000  01 = 10000  10 = 15000  11 = 20000
 * bit 1 : \ 00 = 3 lives  01 = 4 lives
 * bit 0 : / 10 = 5 lives  11 = 6 lives
 *
***************************************************************************/

#include "driver.h"
#include "machine.h"
#include "common.h"

int ckong_IN0_r(int offset);
int ckong_IN2_r(int offset);
int ckong_DSW1_r(int offset);

unsigned char *ckong_videoram;
unsigned char *ckong_colorram;
unsigned char *ckong_bsvideoram;
unsigned char *ckong_spriteram;
unsigned char *ckong_bigspriteram;
void ckong_videoram_w(int offset,int data);
void ckong_colorram_w(int offset,int data);
void ckong_bigsprite_videoram_w(int offset,int data);
void ckong_vh_convert_color_prom(unsigned char *palette, unsigned char *colortable,const unsigned char *color_prom);
int ckong_vh_start(void);
void ckong_vh_stop(void);
void ckong_vh_screenrefresh(struct osd_bitmap *bitmap);

void cclimber_sample_trigger_w(int offset,int data);
void cclimber_sample_rate_w(int offset,int data);
void cclimber_sample_volume_w(int offset,int data);
int cclimber_sh_start(void);
void cclimber_sh_stop(void);
void cclimber_sh_out(byte Port,byte Value);
int cclimber_sh_in(byte Port);
void cclimber_sh_update(void);



static struct MemoryReadAddress readmem[] =
{
	{ 0x6000, 0x6bff, MRA_RAM },
	{ 0x0000, 0x5fff, MRA_ROM },
	{ 0xb800, 0xb800, ckong_IN2_r },
	{ 0x9880, 0x989f, MRA_RAM },	/* sprite registers */
	{ 0x98dc, 0x98df, MRA_RAM },	/* bigsprite registers */
	{ 0xb000, 0xb000, ckong_DSW1_r },
	{ 0xa000, 0xa000, ckong_IN0_r },
	{ 0x9000, 0x93ff, MRA_RAM },	/* video RAM */
	{ 0x9c00, 0x9fff, MRA_RAM },	/* color RAM */
	{ 0xa800, 0xa800, MRA_NOP },
	{ -1 }	/* end of table */
};

static struct MemoryWriteAddress writemem[] =
{
	{ 0x6000, 0x6bff, MWA_RAM },
	{ 0x9880, 0x989f, MWA_RAM, &ckong_spriteram },
	{ 0xa000, 0xa000, interrupt_enable_w },
	{ 0x9000, 0x93ff, ckong_videoram_w, &ckong_videoram },
	{ 0x9c00, 0x9fff, ckong_colorram_w, &ckong_colorram },
	{ 0x8800, 0x88ff, ckong_bigsprite_videoram_w, &ckong_bsvideoram },
	{ 0x98dc, 0x98df, MWA_RAM, &ckong_bigspriteram },
	{ 0xa004, 0xa004, cclimber_sample_trigger_w },
	{ 0xb000, 0xb000, cclimber_sample_volume_w },
	{ 0xa800, 0xa800, cclimber_sample_rate_w },
	{ 0xa001, 0xa002, MWA_NOP },
	{ 0x0000, 0x5fff, MWA_ROM },
	{ -1 }	/* end of table */
};



static struct DSW dsw[] =
{
	{ 0, 0x03, "LIVES", { "3", "4", "5", "6" } },
	{ 0, 0x0c, "BONUS", { "7000", "10000", "15000", "20000" } },
	{ -1 }
};



static struct GfxLayout charlayout =
{
	8,8,	/* 8*8 characters */
	512,	/* 512 characters */
	2,	/* 2 bits per pixel */
	512*8*8,	/* the two bitplanes are separated */
	{ 7*8, 6*8, 5*8, 4*8, 3*8, 2*8, 1*8, 0*8 },
	{ 0, 1, 2, 3, 4, 5, 6, 7 },	/* pretty straightforward layout */
	8*8	/* every char takes 8 consecutive bytes */
};
static struct GfxLayout bscharlayout =
{
	8,8,	/* 8*8 characters */
	256,	/* 256 characters */
	2,	/* 2 bits per pixel */
	256*8*8,	/* the two bitplanes are separated */
	{ 7*8, 6*8, 5*8, 4*8, 3*8, 2*8, 1*8, 0*8 },
	{ 0, 1, 2, 3, 4, 5, 6, 7 },	/* pretty straightforward layout */
	8*8	/* every char takes 8 consecutive bytes */
};
static struct GfxLayout spritelayout =
{
	16,16,	/* 16*16 sprites */
	128,	/* 128 sprites */
	2,	/* 2 bits per pixel */
	128*16*16,	/* the two bitplanes are separated */
	{ 23*8, 22*8, 21*8, 20*8, 19*8, 18*8, 17*8, 16*8,
			7*8, 6*8, 5*8, 4*8, 3*8, 2*8, 1*8, 0*8 },
	{ 0, 1, 2, 3, 4, 5, 6, 7,	/* pretty straightforward layout */
			8*8+0, 8*8+1, 8*8+2, 8*8+3, 8*8+4, 8*8+5, 8*8+6, 8*8+7 },
	32*8	/* every sprite takes 32 consecutive bytes */
};



static struct GfxDecodeInfo gfxdecodeinfo[] =
{
	{ 0x10000, &charlayout,   0, 15 },	/* char set #1 */
	{ 0x12000, &charlayout,   0, 15 },	/* char set #2 */
	{ 0x14000, &bscharlayout,  16, 23 },	/* big sprite char set */
	{ 0x10000, &spritelayout, 0, 15 },	/* sprite set #1 */
	{ 0x12000, &spritelayout, 0, 15 },	/* sprite set #2 */
	{ -1 } /* end of array */
};



static unsigned char palette[] =
{
	0x00,0x00,0x00,	/* BLACK */
	0x49,0x00,0x00,	/* DKRED1 */
	0x92,0x00,0x00,	/* DKRED2 */
	0xff,0x00,0x00,	/* RED */
	0x00,0x24,0x00,	/* DKGRN1 */
	0x92,0x24,0x00,	/* DKBRN1 */
	0xb6,0x24,0x00,	/* DKBRN2 */
	0xff,0x24,0x00,	/* LTRED1 */
	0xdb,0x49,0x00,	/* BROWN */
	0x00,0x6c,0x00,	/* DKGRN2 */
	0xff,0x6c,0x00,	/* LTORG1 */
	0x00,0x92,0x00,	/* DKGRN3 */
	0x92,0x92,0x00,	/* DKYEL */
	0xdb,0x92,0x00,	/* DKORG */
	0xff,0x92,0x00,	/* ORANGE */
	0x00,0xdb,0x00,	/* GREEN1 */
	0x6d,0xdb,0x00,	/* LTGRN1 */
	0x00,0xff,0x00,	/* GREEN2 */
	0x49,0xff,0x00,	/* LTGRN2 */
	0xff,0xff,0x00,	/* YELLOW */
	0x00,0x00,0x55,	/* DKBLU1 */
	0xff,0x00,0x55,	/* DKPNK1 */
	0xff,0x24,0x55,	/* DKPNK2 */
	0xff,0x6d,0x55,	/* LTRED2 */
	0xdb,0x92,0x55,	/* LTBRN */
	0xff,0x92,0x55,	/* LTORG2 */
	0x24,0xff,0x55,	/* LTGRN3 */
	0x49,0xff,0x55,	/* LTGRN4 */
	0xff,0xff,0x55,	/* LTYEL */
	0x00,0x00,0xaa,	/* DKBLU2 */
	0xff,0x00,0xaa,	/* PINK1 */
	0x00,0x24,0xaa,	/* DKBLU3 */
	0xff,0x24,0xaa,	/* PINK2 */
	0xdb,0xdb,0xaa,	/* CREAM */
	0xff,0xdb,0xaa,	/* LTORG3 */
	0x00,0x00,0xff,	/* BLUE */
	0xdb,0x00,0xff,	/* PURPLE */
	0x00,0xb6,0xff,	/* LTBLU1 */
	0x92,0xdb,0xff,	/* LTBLU2 */
	0xdb,0xdb,0xff,	/* WHITE1 */
	0xff,0xff,0xff	/* WHITE2 */
};

enum {BLACK,DKRED1,DKRED2,RED,DKGRN1,DKBRN1,DKBRN2,LTRED1,BROWN,DKGRN2,
	LTORG1,DKGRN3,DKYEL,DKORG,ORANGE,GREEN1,LTGRN1,GREEN2,LTGRN2,YELLOW,
	DKBLU1,DKPNK1,DKPNK2,LTRED2,LTBRN,LTORG2,LTGRN3,LTGRN4,LTYEL,DKBLU2,
	PINK1,DKBLU3,PINK2,CREAM,LTORG3,BLUE,PURPLE,LTBLU1,LTBLU2,WHITE1,
	WHITE2};

const unsigned char colortable[] =
{
	/* characters and sprites */
        BLACK,LTYEL,BROWN,WHITE1,      /* hammers, white text */
        BLACK,LTORG1,WHITE1,LTRED1,     /* pauline with kong */
        BLACK,BLUE,LTBLU1,LTYEL,       /* 4th lvl */
        BLACK,LTBRN,BROWN,CREAM,     /* kong */
        BLACK,BLUE,LTYEL,LTBLU1,     /* 2nd level */
        BLACK,RED,CREAM,BLUE,         /* blue text */
        BLACK,PINK1,RED,DKGRN3,      /* 3rd level */
        BLACK,LTBRN,CREAM,LTRED1,     /* pauline */
        BLACK,LTYEL,BLUE,BROWN,      /* barrel */
        BLACK,RED,CREAM,BLUE,      /* mario */
        BLACK,PINK1,RED,DKGRN3,      /* 1st level */
        BLACK,RED,LTRED1,YELLOW,       /* oil flame */
        BLACK,YELLOW,BLUE,RED,       /* small mario, spring */
        BLACK,DKGRN3,LTBLU1,BROWN,      /* scared flame */
        BLACK,LTRED1,YELLOW,BLUE,       /* flame */
        BLACK,CREAM,LTBLU2,BLUE,        /* "oil" barrel */

	/* big sprite */
	BLACK,WHITE2,DKGRN2,BLUE,	/* helicopter */
	BLACK,WHITE2,PURPLE,PINK2,	/* air balloon */
	BLACK,LTRED2,WHITE2,LTORG1,	/* bird */
	BLACK,WHITE2,BLUE,LTORG2,	/* title screen Crazy Climber logo */
	BLACK,DKPNK1,LTYEL,DKBLU2,	/* 2nd level electric sign */
	BLACK,DKBLU3,DKPNK1,LTYEL,	/* 3rd level sign */
	BLACK,LTYEL,DKBLU3,DKPNK1,	/* 2nd level sign */
	BLACK,DKBLU1,DKGRN1,WHITE2	/* 1st level sign */
};



const struct MachineDriver ckong_driver =
{
	/* basic machine hardware */
	3072000,	/* 3.072 Mhz */
	60,
	readmem,
	writemem,
	dsw, { 0x80 },
	0,
	nmi_interrupt,
	0,

	/* video hardware */
	256,256,
	gfxdecodeinfo,
	41,24,
	0,0,palette,colortable,
	0,17,
	0x0a,0x0b,
	8*13,8*16,0x0a,
	0,
	ckong_vh_start,
	ckong_vh_stop,
	ckong_vh_screenrefresh,

	/* sound hardware */
	0,
	0,
	cclimber_sh_start,
	cclimber_sh_stop,
	cclimber_sh_out,
	cclimber_sh_in,
	cclimber_sh_update
};
