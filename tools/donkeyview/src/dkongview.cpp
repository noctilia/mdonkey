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
#include <format>

#ifdef WIN32
#include <windows.h>  
#endif

#define RGN_FRAC(num,den)       (0x80000000 | (((num) & 0x0f) << 27) | (((den) & 0x0f) << 23))
#define IS_FRAC(offset)         ((offset) & 0x80000000)
#define FRAC_NUM(offset)        (((offset) >> 27) & 0x0f)
#define FRAC_DEN(offset)        (((offset) >> 23) & 0x0f)
#define FRAC_OFFSET(offset)     ((offset) & 0x007fffff)

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

constexpr u8 MAX_GFX_ELEMENTS = 32;
constexpr u16 MAX_GFX_PLANES = 8;
constexpr u16 MAX_GFX_SIZE = 32;

#define STEP2(START,STEP)       (START),(START)+(STEP)
#define STEP4(START,STEP)       STEP2(START,STEP),STEP2((START)+2*(STEP),STEP)
#define STEP8(START,STEP)       STEP4(START,STEP),STEP4((START)+4*(STEP),STEP)
#define STEP16(START,STEP)      STEP8(START,STEP),STEP8((START)+8*(STEP),STEP)


struct gfx_layout
{
  u32 xoffs(int x) const { return (extxoffs != nullptr) ? extxoffs[x] : xoffset[x]; }
  u32 yoffs(int y) const { return (extyoffs != nullptr) ? extyoffs[y] : yoffset[y]; }

  u16             width;              // pixel width of each element
  u16             height;             // pixel height of each element
  u32             total;              // total number of elements, or RGN_FRAC()
  u16             planes;             // number of bitplanes
  u32             planeoffset[MAX_GFX_PLANES]; // bit offset of each bitplane
  u32             xoffset[MAX_GFX_SIZE]; // bit offset of each horizontal pixel
  u32             yoffset[MAX_GFX_SIZE]; // bit offset of each vertical pixel
  u32             charincrement;      // distance between two consecutive elements (in bits)
  const u32* extxoffs;           // extended X offset array for really big layouts
  const u32* extyoffs;           // extended Y offset array for really big layouts
};

struct gfx_decode_entry
{
  const char* memory_region;      // memory region where the data resides
  u32             start;              // offset of beginning of data to decode
  const gfx_layout* gfxlayout;        // pointer to gfx_layout describing the layout; nullptr marks the end of the array
  u16             color_codes_start;  // offset in the color lookup table where color codes start
  u16             total_color_codes;  // total number of color codes
  u32             flags;              // flags and optional scaling factors
};

static const gfx_layout spritelayout =
{
  16,16,                                  /* 16*16 sprites */
  RGN_FRAC(1,4),                          /* 128 sprites */
  2,                                      /* 2 bits per pixel */
  { RGN_FRAC(1,2), RGN_FRAC(0,2) },       /* the two bitplanes are separated */
  { STEP8(0,1), STEP8(RGN_FRAC(1,4),1) }, /* the two halves of the sprite are separated */
  { STEP16(0,8) },
  16 * 8                                    /* every sprite takes 16 consecutive bytes */
};



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

  void load_charset8x8(const std::string& path, const std::vector<std::uint8_t>& data, sf::Image& image)
  {
    int char_x = 8;
    int char_y = 8;

    int num_bytes_per_char = 8;
    int num_of_chars = data.size() / num_bytes_per_char;

    //sf::Image image;
    image.create(16 * 8 * 2, 16 * 8 * 2, sf::Color(0, 255, 0));

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
    float scale = 2.0f;
    load_charset8x8("charset8x8.png", _data, _image);

    texture.create(_image.getSize().x, _image.getSize().y);
    texture.update(_image);
    sprite.setTexture(texture);

    sprite2.setTexture(texture);
    sprite2.setScale(scale, scale);
    sprite2.setPosition(_image.getSize().x, 0);
    return true;
  }

  void draw(sf::RenderTexture* texture) const
  {
    texture->draw(sprite);
    texture->draw(sprite2);
  }

private:
  sf::Image _image;
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

  void load_spriteset16x16(const std::string& path, const std::vector<std::uint8_t>& data, sf::Image& image, int pagesize = 0x800)
  {
    int sx = 16;
    int sy = 16;

    auto readbit = [](int n, const std::uint8_t* data) -> int
      {
        const std::uint8_t* ptr = &data[n / 8];

        auto offset = ptr - data;
        

        return *ptr & (1 << (n % 8)) ? 1 : 0;
      };

    auto readcolor = [&](int n, const std::uint8_t* data) -> int
      {
        int offset = 0;

        std::cout << std::format("{:x} : {}", n / 8, n / 8) << std::endl;

        int c0 = readbit((n), data + offset);
        int c1 = readbit((n), data + offset + 0x1000);

        int m = 0;
        m = c1 + c0 ? 1 : 0;
        m = (c1 << 1) + c0;

        return m;
      };

    image.create(256*4, 256 * 4, sf::Color(0, 0, 0, 0));

    auto tile = [&](int k, int x, int y, int palette) {
      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          auto c = readcolor(k++, data.data());
          

          std::vector< std::vector<sf::Color>> palette_colors =
          {
          { // mario body 
            sf::Color(10,   10,   10, 255),
            sf::Color(245, 187,   159, 255),    // crema face 
            sf::Color(255,   0, 0, 255),        // red
            sf::Color(3, 1,   220, 255),        // blue
          },
          {// pauline head
            sf::Color(10,   10,  10, 255),
            sf::Color(254, 252, 255, 255),     // white face
            sf::Color(238, 117,  17, 255),     // orange
            sf::Color(240,  87, 232, 255),     // pink cloath
          },
          { // pauline body
            sf::Color( 10,  10,  10, 255),
            sf::Color(  3,   1, 220, 255),     // blue feet
            sf::Color(254, 252, 255, 255),     // white
            sf::Color(240,  87, 232, 255),     // pink cloath 
          },
          { // barrel 
            sf::Color(101,  10,  10, 255),
            sf::Color(  3,   3, 255, 255),     // blue 
            sf::Color(238, 117,  17, 255),     // brown
            sf::Color(245, 187, 159, 255),     // light brown
          }
          };
          image.setPixel(x + j, y + i, palette_colors[palette][c]);
        }
      }
      };

    int m = 32;
    int x = 0;
    int y = 0;
    for (int k = 0; k < 2*256; k+=2)
    {
      //tile( k * (8*8), (k % m) * 16, (k / m) * 16);
     //tile(k * (8 * 8), 0, k * 8);

     //tile(k * (8 * 8), (k % m) * 8, (k / m) * 8);

      int palette = 0;
      if (k >= 32)
        palette = 1;
      if (k >= 34)
        palette = 2;
      if (k >= 42)
        palette = 3;

      tile((0x100 + k) * (8 * 8), x, y, palette);
      tile((0x000 + k) * (8 * 8), x + 8, y, palette);

      tile((0x100 + k+1)* (8 * 8), x, y + 8, palette);
      tile((0x000 + k+1)* (8 * 8), x +8, y + 8, palette);

     x += 16;
     if (x >= 256)
     {
       x = 0;
       y += 16;   
     }  
     
      //tile((0x100 + k) * (8 * 8), 0, k * 8, palette);
      //tile(k * (8 * 8), 8, k * 8, palette);
    }
    image.saveToFile(path);
  }

  bool init() {
    float scale = 4.0f;

    load_spriteset16x16("spriteset16x16.png", _data, _image);

    texture.create(_image.getSize().x, _image.getSize().y);
    texture.update(_image);
    sprite.setTexture(texture);

    sprite2.setTexture(texture);
    sprite2.setScale(scale, scale);
    //sprite2.setPosition(_image.getSize().x, 0);
    return true;
  }

  void draw(sf::RenderTexture* texture) const
  {
    texture->draw(sprite);
    texture->draw(sprite2);
  }

private:
  sf::Image _image;
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

#define p(s) std::cout << #s << " = " << s << std::endl;  
  p(spritelayout.width);
  p(spritelayout.height);
  p(spritelayout.total);
  p(spritelayout.planes);
  p(spritelayout.planeoffset[0]);
  p(spritelayout.planeoffset[1]);
  p(spritelayout.xoffset[0]);
  p(spritelayout.xoffset[1]);
  p(spritelayout.yoffset[0]);
  p(spritelayout.yoffset[1]);
  p(spritelayout.charincrement);
  p(spritelayout.extxoffs);
  p(spritelayout.extyoffs);

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
  KongSpriteset kong_sprites(
    { "assets/roms/l_4m_b.bin",
      "assets/roms/l_4n_b.bin",
      "assets/roms/l_4r_b.bin",
      "assets/roms/l_4s_b.bin"
    });

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

    //kong_tiles.draw(&world_bitmap);
    kong_sprites.draw(&world_bitmap);

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