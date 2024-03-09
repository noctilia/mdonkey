#include <SFML/Graphics.hpp>  

#include <array>
#include <cassert>

#include "fonts.hpp"
#include "../core/log.hpp"
#include "../stubs/al_stubs.hpp"

static sf::Font* game_font = nullptr;
static std::array<ALLEGRO_COLOR, TEXT_COLOR_COUNT> text_color_palette;

bool load_fonts()
{
  text_color_palette[TEXT_WHITE] = al_map_rgb(255, 255, 255);
  text_color_palette[TEXT_RED] = al_map_rgb(255, 0, 0);
  text_color_palette[TEXT_BLUE] = al_map_rgb(0, 0, 170);
  text_color_palette[TEXT_GREEN] = al_map_rgb(0, 255, 0);
  text_color_palette[TEXT_YELLOW] = al_map_rgb(255, 184, 0);
  text_color_palette[TEXT_CYAN] = al_map_rgb(0, 255, 255);
  text_color_palette[TEXT_ORANGE] = al_map_rgb(255, 121, 0);
  text_color_palette[TEXT_PINK] = al_map_rgb(255, 33, 85);

  constexpr const char* font_path = "assets/fnt/PressStart2P-Regular.ttf";
  //game_font = al_load_ttf_font(font_path, 8, ALLEGRO_TTF_MONOCHROME);
  assert(game_font == nullptr); // (game_font == nullptr, "game_font already loaded")
  game_font = new sf::Font();
  auto rc = game_font->loadFromFile(font_path);

  if(!rc){
    std::string msg{"failed to load game font '"};
    msg += font_path;
    msg += "'";
    log(log_lvl::fatal, msg);
  }
  return rc;
}

void unload_fonts()
{
  delete game_font;
  game_font = nullptr;
  //if (game_font)
  //al_destroy_font(game_font);
}

void draw_text(int left_px, int bottom_px, const char* text, text_color color)
{
  // TODO: implement draw_text
  //al_draw_text(game_font, text_color_palette[color], left_px, bottom_px, 0, text);
  sf::Text sf_text;
  sf_text.setFont(*game_font);
  sf_text.setCharacterSize(8);
  sf_text.setString(text);  
  sf_text.setFillColor(sf::Color(text_color_palette[color].r, text_color_palette[color].g, text_color_palette[color].b, text_color_palette[color].a));
  sf_text.setPosition(left_px, bottom_px);
  gworld_bitmap->draw(sf_text);
}

void draw_text(int left_px, int bottom_px, std::string text, text_color color)
{
  // TODO: implement draw_text
  //al_draw_text(game_font, text_color_palette[color], left_px, bottom_px, 0, text.c_str());
  sf::Text sf_text;
  sf_text.setFont(*game_font);
  sf_text.setCharacterSize(8);
  sf_text.setString(text);
  sf_text.setFillColor(sf::Color(text_color_palette[color].r, text_color_palette[color].g, text_color_palette[color].b, text_color_palette[color].a));
  sf_text.setPosition(left_px, bottom_px);
  gworld_bitmap->draw(sf_text);
}
