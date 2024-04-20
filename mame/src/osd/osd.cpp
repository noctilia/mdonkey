/***************************************************************************

  osdepend.c

  OS dependant stuff (display handling, keyboard scan...)
  This is the only file which should me modified in order to port the
  emulator to a different system.

***************************************************************************/


#include <stdio.h>
#include <string.h>
#include <SFML/Graphics.hpp>

#include "xmode.h"

#include <memory>
std::shared_ptr<Gfx::XMode> xmode;

extern "C" {

#include "osdepend.h"

  typedef struct RGB
  {
    unsigned char r, g, b;
  } RGB;

  RGB palette[256];

  static void set_color(int color, RGB* col)
  {
    palette[color].r = col->r;
    palette[color].g = col->g;
    palette[color].b = col->b;

    Gfx::setPalette(color, col->r, col->g, col->b); 
  }


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_MODE GFX_VESA1


  struct osd_bitmap* bitmap;
  int first_free_pen;
  int use_vesa;
  int play_sound;
  int noscanlines;
  int use_joystick;


  int osd_joy_up, osd_joy_down, osd_joy_left, osd_joy_right;
  int osd_joy_b1, osd_joy_b2, osd_joy_b3, osd_joy_b4;

  /* audio related stuff */
#define NUMVOICES 4
#define SAMPLE_RATE 44100
#define SAMPLE_BUFFER_LENGTH 50000

/* put here anything you need to do when the program is started. Return 0 if */
/* initialization was successful, nonzero otherwise. */
  int osd_init(int argc, char** argv)
  {
    xmode = std::make_shared<Gfx::XMode>();
    return 0;
  }

  void osd_exit(void)
  {
    xmode.reset();
  }

  struct osd_bitmap* osd_create_bitmap(int width, int height)
  {
    struct osd_bitmap* bitmap;

    if ((bitmap = (struct osd_bitmap*)malloc(sizeof(struct osd_bitmap) + (height - 1) * sizeof(unsigned char*))) != 0)
    {
      int i;
      unsigned char* bm;

      bitmap->width = width;
      bitmap->height = height;
      if ((bm = (unsigned char*)malloc(width * height * sizeof(unsigned char))) == 0)
      {
        free(bitmap);
        return 0;
      }

      for (i = 0; i < height; i++) {
        bitmap->line[i] = &bm[i * width];
      }

      bitmap->_private = bm;
    }

    return bitmap;
  }

  void osd_free_bitmap(struct osd_bitmap* bitmap)
  {
    if (bitmap)
    {
      free(bitmap->_private);
      free(bitmap);
    }
  }

  /* Create a display screen, or window, large enough to accomodate a bitmap */
/* of the given dimensions. I don't do any test here (224x288 will just do */
/* for now) but one could e.g. open a window of the exact dimensions */
/* provided. Return a osd_bitmap pointer or 0 in case of error. */
  struct osd_bitmap* osd_create_display(int width, int height)
  {
    xmode->init("mame", width, height);

#if 0
    if (!(width == 224 && height == 288) &&
      !(width == 256 && height == 256))
      use_vesa = 1;

    if (use_vesa)
    {
      if (set_gfx_mode(SCREEN_MODE, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0)
        return 0;
    }
    else
    {
      /* big hack: open a mode 13h screen using Allegro, then load the custom screen */
      /* definition over it. */
      if (set_gfx_mode(GFX_VGA, 320, 200, 0, 0) != 0)
        return 0;

      if (width == 224 && height == 288)
        outRegArray(scr224x288, sizeof(scr224x288) / sizeof(Register));
      else if (width == 256 && height == 256)
      {
        if (noscanlines)
          outRegArray(scr256x256, sizeof(scr256x256) / sizeof(Register));
        else
          outRegArray(scr256x256scanlines, sizeof(scr256x256) / sizeof(Register));
      }
    }
#endif
    bitmap = osd_create_bitmap(width, height);

    return bitmap;
  }



  /* shut up the display */
  void osd_close_display(void)
  {
    //set_gfx_mode(GFX_TEXT,80,25,0,0);
    osd_free_bitmap(bitmap);
  }

  int osd_obtain_pen(unsigned char red, unsigned char green, unsigned char blue)
  {
    RGB rgb;

    rgb.r = red >> 2;
    rgb.g = green >> 2;
    rgb.b = blue >> 2;

    set_color(first_free_pen, &rgb);
    return first_free_pen++;
  }

  /* Update the display. */
  /* As an additional bonus, this function also saves the screen as a PCX file */
  /* when the user presses F5. This is not required for porting. */
  void osd_update_display(void)
  {
    memcpy(xmode->vscreen(), bitmap->_private, bitmap->width * bitmap->height);
    xmode->run();

    //if (use_vesa)
    //{
    //	int y;
    //	int width4 = bitmap->width / 4;
    //	unsigned long *lb = (unsigned long *)bitmap->private;


    //	for (y = 0;y < bitmap->height;y++)
    //	{
    //		unsigned long address;


    //		address = bmp_write_line(screen,y + (SCREEN_HEIGHT - bitmap->height) / 2)
    //				+ (SCREEN_WIDTH - bitmap->width) / 2;
    //		_dosmemputl(lb,width4,address);
    //		lb += width4;
    //	}
    //}
    //else
    //{
    //	/* copy the bitmap to screen memory */
    //	_dosmemputl(bitmap->private,bitmap->width * bitmap->height / 4,0xa0000);
    //}

    ///* if the user pressed F12, save a snapshot of the screen. */
    //if (osd_key_pressed(OSD_KEY_F12))
    //{
    //	BITMAP *bmp;
    //	PALETTE pal;
    //	char name[13];
    //	FILE *f;
    //	static int snapno;
    //	int y;


    //	do
    //	{
    //		sprintf(name,"snap%04d.pcx",snapno);
    //		/* avoid overwriting of existing files */
    //		if ((f = fopen(name,"rb")) != 0)
    //		{
    //			fclose(f);
    //			snapno++;
    //		}
    //	} while (f != 0);

    //	get_palette(pal);
    //	bmp = create_bitmap(bitmap->width,bitmap->height);
    //	for (y = 0;y < bitmap->height;y++)
    //		memcpy(bmp->line[y],bitmap->line[y],bitmap->width);
    //	save_pcx(name,bmp,pal);
    //	destroy_bitmap(bmp);
    //	snapno++;

    //	/* wait for the user to release F12 */
    //	while (osd_key_pressed(OSD_KEY_F12));
    //}
  }



  void osd_update_audio(void)
  {
  }

  void osd_play_sample(int channel, unsigned char* data, int len, int freq, int volume, int loop)
  {
  }

  void osd_play_streamed_sample(int channel, unsigned char* data, int len, int freq, int volume)
  {
  }

  void osd_adjust_sample(int channel, int freq, int volume)
  {
  }

  void osd_stop_sample(int channel)
  {
  }

  /* check if a key is pressed. The keycode is the standard PC keyboard code, as */
  /* defined in osdepend.h. Return 0 if the key is not pressed, nonzero otherwise. */
  int osd_key_pressed(int keycode)
  {
    //return key[keycode];
    return 0;
  }

  /* wait for a key press and return the keycode */
  int osd_read_key(void)
  {
    /*clear_keybuf();
    return readkey() >> 8;*/
    return 0;
  }

  void osd_poll_joystick(void)
  {
  }

} // extern "C"	