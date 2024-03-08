#include "math.hpp" 
#include "al_stubs.hpp"


ALLEGRO_BITMAP* al_load_bitmap(const char* filename)
{
  sf::Texture* texture = new sf::Texture();
  texture->loadFromFile(filename);  
  return texture;
}

int al_draw_bitmap_region(ALLEGRO_BITMAP* bitmap, float sx, float sy, float sw, float sh, float dx, float dy, int flags)
{
  return 0;
}

void al_destroy_bitmap(ALLEGRO_BITMAP* bitmap)
{
  delete bitmap;
}

ALLEGRO_CONFIG* al_load_config_file(const char* filename)
{
    return NULL;
}

void al_save_config_file(const char* filename, const ALLEGRO_CONFIG* config)
{
}

ALLEGRO_CONFIG* al_create_config(void)
{
  return nullptr;
}

const char* al_get_config_value(const ALLEGRO_CONFIG* config, const char* section, const char* key)
{
    return NULL;
}


int al_get_config_value_int(ALLEGRO_CONFIG const*, char const*, char const*)
{
  return 0;
}

int al_get_config_value(ALLEGRO_CONFIG const* config, char const* section, char const* key, char const* def)
{
  return 0;
}

int al_set_config_value(ALLEGRO_CONFIG* config, char const* section, char const* key, char const* value)
{
  return 0;
}


void al_destroy_config(ALLEGRO_CONFIG* config)
{

} 

void al_draw_rectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness)
{
}

void al_draw_filled_rectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color)
{
}

void al_draw_line(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness)
{
}

ALLEGRO_COLOR al_map_rgb(float r, float g, float b)
{
  return ALLEGRO_COLOR();
}
