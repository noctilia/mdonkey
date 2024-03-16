#include "debug.hpp"
#include "../assets/fonts.hpp"
#include "../core/input.hpp"
#include "../core/cutscene.hpp"
#include "../assets/cutscenes.hpp"

namespace debug {

  constexpr float wait_period_s = 10.f;
  float clock_s;
  bool is_play_triggered;

  cutscene cutscene_player;

  void on_enter()
  {
    clock_s = 0.f;
    is_play_triggered = false;
    //cutscene_player.initialise(cutscenes::menu_barrel_jump);
  }

  void update(float dt_s)
  {
    clock_s += dt_s;

    if (input::is_action_triggered(input::ACTION_MENU_ENTER))
      is_play_triggered = true;

   /* cutscene_player.update(dt_s);
    if (cutscene_player.is_done()) {
      cutscene_player.initialise(cutscenes::menu_barrel_jump);
      cutscene_player.update(0.001f);
    }*/
  }

  void draw()
  {
    int x = 1;
    int y = 2;  

    //draw_centered_sprite(SID_MARIO_IDLE, vector2f{ float(x) * 8, float(y) * 1 }, false); y++;

    draw_sprite(SID_MARIO_IDLE, vector2f{ float(x) * 16, float(y) * 16 }, false); x++;
    draw_sprite(SID_MARIO_RUN_0, vector2f{ float(x) * 16, float(y) * 16 }, false); x++;
    draw_sprite(SID_MARIO_RUN_1, vector2f{ float(x) * 16, float(y) * 16 }, false); x++;

    draw_sprite(SID_MARIO_CLIMB_OFF_0, vector2f{ float(x) * 16, float(y) * 16 }, false); x++;
    draw_sprite(SID_MARIO_CLIMB_OFF_1, vector2f{ float(x) * 16, float(y) * 16 }, false); x++;
    draw_sprite(SID_MARIO_CLIMB_OFF_2, vector2f{ float(x) * 16, float(y) * 16 }, false); x++;

    
  }

  bool is_done()
  {
    return is_play_triggered;
  }
}
