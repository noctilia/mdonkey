#pragma once
#include <SFML/Graphics.hpp>

#ifndef FRAMEWORK_SCREEN_WIDTH
#define FRAMEWORK_SCREEN_WIDTH 320
#endif

#ifndef FRAMEWORK_SCREEN_HEIGHT
#define FRAMEWORK_SCREEN_HEIGHT 200
#endif

#ifndef FRAMEWORK_SCREEN_BITSPERPIXEL
#define FRAMEWORK_SCREEN_BITSPERPIXEL 8
#endif

extern bool demo_config(unsigned& width, unsigned& height, unsigned& bitsPerPixel);
extern bool demo_init(unsigned char* vscreen, size_t width, size_t height);;
extern void demo_update();
extern void demo_shutdown();

/* palette stuff */
namespace Gfx {
  extern unsigned char g_palette[256 * 3];

  void clearPalette();
  
  void setPalette(int col, int r, int g, int b);
  void getPalette(int col, int* r, int* g, int* b);

  void setPalette(size_t first, size_t last, unsigned char* srcpal);
  void getPalette(size_t first, size_t last, unsigned char* dstpal);

  class Fps
  {
  public:
    Fps() {
    }

    void update(sf::RenderWindow& window) {
      auto t1 = m_clock.getElapsedTime().asSeconds();
      float dt = t1 - m_t0;
      m_frame++;
      if (dt >= 1.f) {
        m_fps = m_frame / dt;
        m_fpsAvg = (1 - m_alpha) * m_fpsAvg + m_alpha * m_fps;
        m_t0 = t1;
        m_frame = 0;
      }
    }

    float getFps() const { return m_fps; }
    float getFpsAvg() const { return m_fpsAvg; }

    std::string getFpsString() const { return std::to_string(m_fps); }
    std::string getFpsAvgString() const { return std::to_string(m_fpsAvg); }

  public:
    sf::Clock m_clock;
    float m_lastTime = 0;
    unsigned m_frame = 0;
    float m_t0 = m_clock.getElapsedTime().asSeconds();

    const float m_alpha = 0.3f;
    float m_fpsAvg = 0;
    float m_fps = 0;
  };

  class XMode {
  public:
    XMode()
      : m_width(0)
      , m_height(0)
    {}

    bool init(const char* title, unsigned width = FRAMEWORK_SCREEN_WIDTH, unsigned height = FRAMEWORK_SCREEN_HEIGHT);
    void update();
    void shutdown();

    bool run();

    int width() const { return m_width; } 
    int height() const { return m_height; } 
    unsigned char* vscreen() { return m_vscreen.get(); }  
    
  private:
    void blit_vscreen();

  private:
    sf::RenderWindow m_window;
    sf::Texture m_vtexture;
    sf::Sprite m_vsprite;

    int m_size = 0;
    int m_scanline = 0;
    
    int m_width = FRAMEWORK_SCREEN_WIDTH;
    int m_height = FRAMEWORK_SCREEN_HEIGHT;
    int m_bitsPerPixel = FRAMEWORK_SCREEN_BITSPERPIXEL;

    std::unique_ptr<sf::Uint8> m_screen;
    std::unique_ptr<sf::Uint8> m_vscreen;

    Fps m_fps;
  };

}