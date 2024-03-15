#include "title.hpp"
#include "../assets/sprites.hpp"
#include "../assets/fonts.hpp"

namespace title {
  constexpr int flash_count = 21;
  constexpr float flash_duration_s = 0.05f;
  constexpr float title_duration_s = 3.f;

  bool flash_state; // true=blue, false=red.
  int flash_counter;
  float clock_s;

  void on_enter()
  {
    clock_s = 0.f;
    flash_state = 0;
    flash_counter = 0;
  }

  void update(float dt_s)
  {
    clock_s += dt_s;
    if(clock_s > flash_duration_s && flash_counter < flash_count){
      flash_state = !flash_state;
      ++flash_counter;
      clock_s = 0.f;
    }
  }

  void draw()
  {
    sprite_id donkey_sid, kong_sid, copy_sid;
    text_color txt_color;
    if(flash_state){
      donkey_sid = SID_BLUE_TITLE_DONKEY;
      kong_sid = SID_BLUE_TITLE_KONG;
      copy_sid = SID_GOLD_COPY;
      txt_color = TEXT_YELLOW;
    }
    else{
      donkey_sid = SID_RED_TITLE_DONKEY;
      kong_sid = SID_RED_TITLE_KONG;
      copy_sid = SID_CYAN_COPY;
      txt_color = TEXT_CYAN;
    }
    draw_sprite(donkey_sid, vector2f{8, 64});
    draw_sprite(kong_sid, vector2f{32, 120});
    draw_sprite(copy_sid, vector2f{90, 216});
    draw_sprite(SID_KONG_BEAT_CHEST, vector2f{90, 175}, true);

    //draw_sprite (SID_MARIO_IDLE, vector2f{8, 175}, true);
    //draw_sprite(SID_MARIO_IDLE, vector2f{ 4*8, 175 }, false);
   
    draw_sprite(SID_MARIO_RUN_0, vector2f{ 4 * 8, 100 + 16 * 0}, false);
    draw_sprite(SID_MARIO_IDLE,  vector2f{ 4 * 8, 100 + 16 * 1 }, false);
    draw_sprite(SID_MARIO_RUN_1, vector2f{ 4 * 8, 100 + 16 * 2}, false);
    draw_sprite(SID_MARIO_JUMPING,  vector2f{ 4 * 8, 100 + 16 * 3 }, false);


    draw_text(100, 216, "1981", txt_color);
    draw_text(16, 226, "NINTENDO OF AMERICA INC.", txt_color);
    draw_text(4, 238, "REMAKE BY IANMURFINXYZ 2021", txt_color);
  }

  bool is_done()
  {
    // todo: return clock_s > title_duration_s;
   return clock_s > title_duration_s;
   //return false;
  }
}
