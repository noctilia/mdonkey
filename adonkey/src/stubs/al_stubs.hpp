#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#define ALLEGRO_FLIP_HORIZONTAL 1
#define ALLEGRO_FLIP_VERTICAL 2 

extern sf::RenderWindow* gwindow;
extern sf::RenderTexture* gworld_bitmap;

typedef sf::Texture ALLEGRO_BITMAP;

ALLEGRO_BITMAP* al_load_bitmap(const char* filename); 
int al_draw_bitmap(ALLEGRO_BITMAP* bitmap, float dx, float dy, int flags);  
int al_draw_bitmap_region(ALLEGRO_BITMAP* bitmap, float sx, float sy, float sw, float sh, float dx, float dy, int flags); 
void al_destroy_bitmap(ALLEGRO_BITMAP* bitmap);


typedef struct ALLEGRO_CONFIG ALLEGRO_CONFIG;

ALLEGRO_CONFIG* al_load_config_file(const char* filename);
void al_save_config_file(const char* filename, const ALLEGRO_CONFIG* config);

ALLEGRO_CONFIG* al_create_config(void);
void al_destroy_config(ALLEGRO_CONFIG* config);
const char* al_get_config_value(const ALLEGRO_CONFIG* config, const char* section, const char* key);

char const* al_get_config_value(struct ALLEGRO_CONFIG const*, char const*, char const*);
int al_get_config_value_int(struct ALLEGRO_CONFIG const*, char const*, char const*);

int al_get_config_value_int(const ALLEGRO_CONFIG* config, const char* section, const char* key);

int al_get_config_value (ALLEGRO_CONFIG const* config, char const* section, char const* key, char const* def);
int al_set_config_value (ALLEGRO_CONFIG* config, char const* section, char const* key, char const* value);  

typedef sf::Color ALLEGRO_COLOR;
//struct ALLEGRO_COLOR
//{
//  float r, g, b, a;
//};


void al_draw_rectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness);
void al_draw_filled_rectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color);
void al_draw_line(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness);  

//ALLEGRO_COLOR al_map_rgb_f(float r, float g, float b, float a);
//ALLEGRO_COLOR al_map_rgba_f(float r, float g, float b, float a);
ALLEGRO_COLOR al_map_rgb(float r, float g, float b);
//ALLEGRO_COLOR al_map_rgba(float r, float g, float b, float a);
//void al_unmap_rgb(ALLEGRO_COLOR color, float* r, float* g, float* b);
//void al_unmap_rgba(ALLEGRO_COLOR color, float* r, float* g, float* b, float* a);
//void al_color_hsv_to_rgb(float h, float s, float v, float* r, float* g, float* b);
//void al_color_rgb_to_hsv(float r, float g, float b, float* h, float* s, float* v);



