#include <SFML/Graphics.hpp>

#include <exception>
#include <string>
#include <cstring>
#include <sstream>
#include <ctime>
#include <random>
#include <memory>
#include <cassert>
#include <iostream>
#include <fstream>  
#include <vector>   
#include <cstdarg>  
#include <cstdio> 

#ifdef WIN32
#include <windows.h>  
#endif

void fatal_error(const char* format, ...)
{
  va_list arg_ptr;
  va_start(arg_ptr, format);
  vfprintf(stdout, format, arg_ptr);
  _flushall();
  exit(0);
}


namespace global
{
  int window_width_px = 1024;
  int window_height_px = 800;
  bool is_debug_draw = false;
  bool is_debug_enabled = false;
  bool is_jm_invulnerable = false;
  bool is_classic_mode = true;
}

sf::RenderTexture* gworld_bitmap = nullptr;


void run_viewer(sf::RenderTexture* texture)
{

}

class KongSprite
{
public:
  KongSprite(const std::string& path)
  {
    load(path);
    init();
  }

  bool load(const std::string& path)
  { 
    std::ifstream fi(path);
    if (!fi.is_open()) {
      return false;
    }

    fi.seekg(0, std::ios::end);
    std::streampos length = fi.tellg();
    fi.seekg(0, std::ios::beg);

    m_data.resize(length);
    fi.read(reinterpret_cast<char*>(m_data.data()), length);
    fi.close();

    return false;
  }

  bool init() {
    float scale = 2.0f;
    pixbuf.create(224, 256, sf::Color(0, 0, 0));


    int k = 0;

    
    for (int y = 0; y < 256; y++) {
      for (int x = 0; x < 224; x++) {

        if (++k >= m_data.size())
          break;


        int index = (y * 224) + x;
        int r = m_data[index];
        int g = m_data[index];
        int b = m_data[index];
        int a = 0xff;
        pixbuf.setPixel(x, y, sf::Color(r, g, b, a));
      }
    }

    texture.create(pixbuf.getSize().x, pixbuf.getSize().y);
    texture.update(pixbuf);
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);  

    return true;
  }

  void draw(sf::RenderTexture* texture)
  {
    texture->draw(sprite);
  } 

private:
  sf::Image pixbuf;
  sf::Texture texture;
  sf::Sprite sprite;
  std::vector<std::uint8_t> m_data;
};

int main(int argc, char** argv)
{
#ifdef WIN32
  ::AllocConsole();
  freopen("CONOUT$", "w", stdout);
#endif

  float target_fps_hz = 60.f;
  sf::RenderWindow window;

  sf::Event event;
  sf::Clock clock;

  sf::Font debug_font;
  debug_font.loadFromFile("assets/fnt/slkscr.ttf");

  sf::RenderTexture world_bitmap;
  gworld_bitmap = &world_bitmap;

  sf::Sprite world_sprite;

  window.create(sf::VideoMode(global::window_width_px, global::window_height_px), "Donkey Kong Sprite View", sf::Style::Default);

  global::window_width_px = window.getSize().x;
  global::window_height_px = window.getSize().y;

  world_bitmap.create(global::window_width_px, global::window_height_px);

  sf::View view = window.getDefaultView();

  KongSprite kong_sprite("assets/roms/v_5k_b.bin"); 
 
  bool is_running = true;
  while (window.isOpen() && is_running) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        is_running = false;
      }

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          window.close();
        }
        if (event.key.code == sf::Keyboard::Tab) {
          global::is_debug_draw = !global::is_debug_draw;
          auto debug_state_string = global::is_debug_draw ? "on" : "off";
        }
        if (event.key.code == sf::Keyboard::O) {
        }
        if (event.key.code == sf::Keyboard::P) {
        }
      }

      if (event.type == sf::Event::KeyReleased) {
      }

      if (event.type == sf::Event::Resized) {
        view.setSize({ static_cast<float>(event.size.width), static_cast<float>(event.size.height) });
        window.setView(view);
      }
    }

    float tick_delta_s = clock.restart().asSeconds();

    world_bitmap.clear(sf::Color{ 64, 64, 64 });

    kong_sprite.draw(&world_bitmap);
    world_bitmap.display();

    world_sprite.setTexture(world_bitmap.getTexture());
    world_sprite.setPosition(0, 0);

    

    window.clear();

    

    window.draw(world_sprite);

    window.display();
  }

  return 0;
}

#ifdef WIN32
#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  return main(__argc, __argv);
}
#endif  