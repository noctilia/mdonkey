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

static void fatal_error(const char* format, ...)
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


class KongTileset
{
public:
  KongTileset(const std::string& path)
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

    _data.resize(length);
    fi.read(reinterpret_cast<char*>(_data.data()), length);
    fi.close();

    return false;
  }

  void save_charset8x8(const std::string& path, const std::vector<std::uint8_t>& data)
  {
    int char_x = 8;
    int char_y = 8;

    int num_bytes_per_char = 8;  
    int num_of_chars = data.size() / num_bytes_per_char;

    sf::Image image;
    image.create(16*8, 16*8, sf::Color(0, 255, 0));

    int k = 0;
    int x0 = 0;
    int y0 = 0;

    int n = 0;
    int r = 0;

    int bitspercolor = 1;
    int mask = 0x1;
    for (int s = 0; s < bitspercolor; s++)
    {
      mask |= 1 << s; 
    }

    // 8x8 bit charset --> 8 Bytes per char
    // filesize = 2048 bytes --> 256 chars
    for (int m = 0; m < num_of_chars; m++) {
      if (k >= data.size())
        break;

      int p = 0;
      int r = data[k];
      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          int c = r & mask;
          r >>= bitspercolor;

          int x = x0 + (7 - i);
          int y = y0 + (7 - j);
          if (c != 0) {
            image.setPixel(x, y, sf::Color(255, 255, 255, 255));
          }
          else {
            image.setPixel(x, y, sf::Color(0, 0, 0, 0));
          }
          p += bitspercolor;
          if (p >= 8) {
            p = 0;
            if (++k >= data.size())
              break;
            r = data[k];
          }

        }
      }
      n++;
      x0 += 8;
      if (!(n % 16)) {
        y0 += 8;
        x0 = 0;
      }
    }

    image.saveToFile(path);
  }
  
  bool init() {
    float scale = 4.0f;
    _pixbuf.create(256, 256, sf::Color(0, 255, 0));

    int k = 0;
    int x0 = 0;
    int y0 = 0;
    
    int n = 0;  
    int r = 0;
    // 8x8 bit charset --> 8 Bytes per char
    // filesize = 2048 bytes --> 256 chars
    for (int m = 0; m < 256; m++) {
        if (k >= _data.size())
          break;

        int bitspercolor = 1;
        int mask = 0x1;
        for (int s = 0; s < bitspercolor; s++)
          mask |= 1 << s;

        int p = 0;
        int r = _data[k];
        for (int i = 0; i < 8; i++)
        {
          for (int j = 0; j < 8; j++)
          {
            int c = r & mask;
            r = r >> bitspercolor;

            int x = x0 + (7 - i);
            //int x = x0 + j;
            int y = y0 + (7-j);
            if (c != 0) {            
              _pixbuf.setPixel(x, y, sf::Color(255, 255, 255, 255));
            }            
            else {
              _pixbuf.setPixel(x, y, sf::Color(255, 0, 0, 255));
            }
            p += bitspercolor;
            if (p >= 8) {
              p = 0;
              k++;
              if (k >= _data.size())
                break;
              r = _data[k];
            }
            
          }
        }
        n++;
        x0 += 8;
        if (!(n % 16)) {
          y0 += 8;
          x0 = 0;
        }
    } 

    save_charset8x8("charset8x8.png", _data);

    texture.create(_pixbuf.getSize().x, _pixbuf.getSize().y);
    texture.update(_pixbuf);
    sprite.setTexture(texture);
    
    sprite2.setTexture(texture);
    sprite2.setScale(scale, scale);
    sprite2.setPosition(_pixbuf.getSize().x, 0);
    return true;
  }

  void draw(sf::RenderTexture* texture) const
  {
    texture->draw(sprite);
    texture->draw(sprite2);
  } 

private:
  sf::Image _pixbuf;
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Sprite sprite2;
  std::vector<std::uint8_t> _data;
  std::vector<std::uint8_t> _sprite_data;
};

class KongSpriteset
{
public:
  KongSpriteset(const std::vector<std::string>& vpath)
  {
    load(vpath);
    init();
  }

  bool load(const std::vector<std::string>& vpath)
  {
    _data.resize(0);
    for (auto& p : vpath) 
    {
      std::ifstream fi(p);
      if (!fi.is_open()) {
        return false;
      }

      fi.seekg(0, std::ios::end);
      std::streampos length = fi.tellg();
      fi.seekg(0, std::ios::beg);

      auto ofs = _data.size();
      _data.resize(ofs + length);
      fi.read(reinterpret_cast<char*>(_data.data() + ofs), length);
      fi.close();
    }

    return false;
  }

  void save_spriteset16x16(const std::string& path, const std::vector<std::uint8_t>& data, int pagesize = 0x800)
  {

  }

  bool init() {
    float scale = 4.0f;

    save_spriteset16x16("spriteset16x16.png", _data);

    texture.create(_pixbuf.getSize().x, _pixbuf.getSize().y);
    texture.update(_pixbuf);
    sprite.setTexture(texture);

    sprite2.setTexture(texture);
    sprite2.setScale(scale, scale);
    sprite2.setPosition(_pixbuf.getSize().x, 0);
    return true;
  }

  void draw(sf::RenderTexture* texture) const
  {
    texture->draw(sprite);
    texture->draw(sprite2);
  }

private:
  sf::Image _pixbuf;
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Sprite sprite2;
  std::vector<std::uint8_t> _data;
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

  KongTileset kong_tiles("assets/roms/v_5k_b.bin"); 
  KongSpriteset kong_sprites({ "assets/roms/l_4m_b.bin", "assets/roms/l_4n_b.bin", "assets/roms/l_4r_b.bin", "assets/roms/l_4s_b.bin" });
  
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

    kong_tiles.draw(&world_bitmap);
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