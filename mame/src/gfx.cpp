#include "gfx.h"

#include <string>
#include <format>

extern "C" {
#include "common.h"
}

extern "C" void write_gfx(int n, struct GfxElement* g)
{
  printf("write_gfx gfx%d\n", n);
  printf("g->width %d\n", g->width);
  printf("g->height %d\n", g->height);
  printf("g->total_elements %d\n", g->total_elements);
  printf("g->color_granularity %d\n", g->color_granularity);
  printf("g->total_colors %d\n", g->total_colors);

  std::string s = std::format("gfx_{}_{}x{}.raw", n, g->gfxdata->width, g->gfxdata->height);
  FILE* fo = fopen(s.c_str(), "wb");

  int w = g->gfxdata->width;
  int h = g->gfxdata->height;

  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
      unsigned char* line = g->gfxdata->line[y];
      unsigned char color = line[x];
      auto c = g->colortable[color];
      fwrite(&color, 1, 1, fo);
    }
  }
  fclose(fo);

}