#include "xmode.h"

namespace Gfx {

  /* palette stuff */
  unsigned char g_palette[256 * 3];

  void clearPalette() {
    memset(g_palette, 0, sizeof(g_palette));
  }

  void setPalette(int col, int r, int g, int b) {
    g_palette[col * 3 + 0] = r << 2;
    g_palette[col * 3 + 1] = g << 2;
    g_palette[col * 3 + 2] = b << 2;
  }

  void getPalette(int col, int* r, int* g, int* b) {
    *r = g_palette[col * 3 + 0];
    *g = g_palette[col * 3 + 1];
    *b = g_palette[col * 3 + 2];
  }

  void setPalette(size_t first, size_t last, unsigned char* srcpal) {
    memcpy(g_palette + 3 * first, srcpal + 3 * first, 3 * (last - first));
  }

  void getPalette(size_t first, size_t last, unsigned char* dstpal) {
    memcpy(dstpal + 3 * first, g_palette + 3 * first, 3 * (last - first));
  }


  /*********************************************************************************************************************/

  bool XMode::init(const char* title, unsigned width, unsigned height) {

    unsigned bitsPerPixel = 8;
    /*if (!demo_config(width, height, bitsPerPixel)) 
    {
      return false;
    }*/

    m_window.create(sf::VideoMode(width, height), title);
    m_window.setFramerateLimit(60);

    m_vtexture.create(width, height);

    m_width = width;
    m_height = height;
    m_scanline = 4 * width;
    m_bitsPerPixel = bitsPerPixel;

    m_size = height * m_scanline;
    m_screen.reset(new sf::Uint8[m_size]);

    m_vscreen.reset(new sf::Uint8[m_width * m_height]);
    memset(m_vscreen.get(), 0, m_width * m_height);

    //return demo_init(m_vscreen.get(), m_width, m_height);
    return true;
  }

  void XMode::update() {
    //demo_update();
  };

  void XMode::shutdown() {
    //demo_shutdown();
  }

  bool XMode::run() {
    if (m_window.isOpen())
    {
      sf::Event e;
      while (m_window.pollEvent(e))
      {
        if (e.type == sf::Event::Closed) {
          m_window.close();
        }
        if (e.type == sf::Event::KeyPressed) {
          if (e.key.code == sf::Keyboard::Space) {
          }
        }
      }

      m_fps.update(m_window);

      update();
      blit_vscreen();

      std::string strfps = "fps: " + std::to_string((int)m_fps.getFps()) + ", avg: " + std::to_string((int)m_fps.getFpsAvg());
      m_window.setTitle(strfps);

      m_vtexture.update(m_screen.get());
      m_vsprite.setTexture(m_vtexture);
      m_window.draw(m_vsprite);

      m_window.display();
    }
    return false;
  }

  void XMode::blit_vscreen()
  {
    sf::Uint8* vscreen = m_vscreen.get();
    for (int i = 0; i < m_height; i++) {
      sf::Uint8* p = m_screen.get() + i * m_scanline;
      for (int j = 0; j < m_width; j++) {
        int col = vscreen[i * m_width + j];
        p[0] = Gfx::g_palette[3 * col + 0];
        p[1] = Gfx::g_palette[3 * col + 1];
        p[2] = Gfx::g_palette[3 * col + 2];
        p[3] = 0xff;
        p += 4;
      }
    }
  }

}

