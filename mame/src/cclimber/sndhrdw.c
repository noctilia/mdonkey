#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mame.h"
#include "driver.h"
#include "osdepend.h"

#define AY8910_CLOCK (1536000000)       /* 1.536000000 MHZ */
//#include "psg.c"

#define SND_CLOCK 3072000	/* 3.072 Mhz */


#define UPDATES_PER_SECOND 60
#define emulation_rate (200*UPDATES_PER_SECOND)
#define buffer_len (emulation_rate/UPDATES_PER_SECOND)

#define SNDCTRL_PORT 0x08
#define SNDWRITE_PORT 0x09
#define SNDREAD_PORT 0x0c


unsigned char samples[0x4000];	/* 16k for samples */
int sample_freq,sample_volume;
int porta;






int cclimber_sh_start(void)
{
	
	return 1;
}



void cclimber_sh_stop(void)
{
	//AYShutdown();
}



void cclimber_sample_rate_w(int offset,int data)
{
	/* calculate the sampling frequency */
	sample_freq = SND_CLOCK / 4 / (256 - data);
}



void cclimber_sample_volume_w(int offset,int data)
{
	sample_volume = data & 0x1f;
	sample_volume = (sample_volume << 3) | (sample_volume >> 2);
}



void cclimber_sample_trigger_w(int offset,int data)
{
	int start,end;


	if (data == 0 || play_sound == 0)
		return;

	start = 64 * porta;
	end = start;

	/* find end of sample */
	while (end < 0x4000 && (samples[end] != 0xf7 || samples[end+1] != 0x80))
		end += 2;

	osd_play_sample(1,samples + start,end - start,sample_freq,sample_volume,0);
}



/***************************************************************************

  Execute an OUT instruction.

***************************************************************************/
int lastreg;	/* AY-3-8910 register currently selected */

void cclimber_sh_out(byte Port,byte Value)
{
	
}



/***************************************************************************

  Read a data port IN.

  The processor needs to be able to read data from the Sound Chip. When
  turning voices on and off it must be able to read the status of other
  voices so it can OR or AND the appropriate bits without affecting the
  others. The CC software doesn't keep its own record of the status of
  the sound chip voices. (Lionel T.)

***************************************************************************/
int cclimber_sh_in(byte Port)
{
	
		return 0;
}



#define BUFFERS 2
void cclimber_sh_update(void)
{
	

	osd_update_audio();
}
