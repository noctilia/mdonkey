#ifndef DONKEY_KONG_1981_INPUT_HH
#define DONKEY_KONG_1981_INPUT_HH

#include <SFML/Graphics.hpp>
#include <array>

const int ALLEGRO_KEY_N = sf::Keyboard::N;  
const int ALLEGRO_KEY_A = sf::Keyboard::A;  
const int ALLEGRO_KEY_D = sf::Keyboard::D;
const int ALLEGRO_KEY_W = sf::Keyboard::W;
const int ALLEGRO_KEY_S = sf::Keyboard::S;

const int ALLEGRO_KEY_LEFT = sf::Keyboard::Left;
const int ALLEGRO_KEY_RIGHT = sf::Keyboard::Right;
const int ALLEGRO_KEY_UP = sf::Keyboard::Up;
const int ALLEGRO_KEY_DOWN = sf::Keyboard::Down;

const int ALLEGRO_KEY_SPACE = sf::Keyboard::Space;
const int ALLEGRO_KEY_ENTER = sf::Keyboard::Enter;

namespace input
{
  /** All the input actions a user can perform. */
  enum action
  {
    ACTION_FORCE_NEXT_LVL,
    ACTION_MOVE_LEFT,
    ACTION_MOVE_RIGHT,
    ACTION_CLIMB_UP,
    ACTION_CLIMB_DOWN,
    ACTION_JUMP,
    ACTION_MENU_PREV,
    ACTION_MENU_NEXT,
    ACTION_MENU_ENTER,
    ACTION_SKIP_CUTSCENE,
    ACTION_COUNT,
  };

  enum class action_trigger
  {
    on_press,
    while_down,
  };

  /** Defines how each action is triggered. */
  constexpr std::array<action_trigger, ACTION_COUNT> action_triggers {
    action_trigger::on_press, // action_force_next_level
    action_trigger::while_down, // action_move_left
    action_trigger::while_down, // action_move_right
    action_trigger::while_down, // action_climb_up
    action_trigger::while_down, // action_climb_down
    action_trigger::on_press , // action_jump
    action_trigger::while_down, // action_menu_prev
    action_trigger::while_down, // action_menu_next
    action_trigger::on_press, // action_menu_enter
    action_trigger::on_press, // action_skip_cutscene
  };

  using keycode = int;

  using control_scheme = std::array<keycode, ACTION_COUNT>;

  constexpr control_scheme wasd_control_scheme {
    ALLEGRO_KEY_N, // action_force_next_lvl
    ALLEGRO_KEY_A, // action_move_left
    ALLEGRO_KEY_D, // action_move_right
    ALLEGRO_KEY_W, // action_climb_up
    ALLEGRO_KEY_S, // action_climb_down
    ALLEGRO_KEY_W , // action_jump
    ALLEGRO_KEY_LEFT, // action_menu_prev
    ALLEGRO_KEY_RIGHT, // action_menu_next
    ALLEGRO_KEY_ENTER, // action_menu_enter
    ALLEGRO_KEY_SPACE, // action_skip_cutscene
  };

  constexpr control_scheme arrows_control_scheme {
    ALLEGRO_KEY_N, // action_force_next_lvl
    ALLEGRO_KEY_LEFT, // action_move_left
    ALLEGRO_KEY_RIGHT, // action_move_right
    ALLEGRO_KEY_UP, // action_climb_up
    ALLEGRO_KEY_DOWN, // action_climb_down
    ALLEGRO_KEY_SPACE , // action_jump
    ALLEGRO_KEY_LEFT, // action_menu_prev
    ALLEGRO_KEY_RIGHT, // action_menu_next
    ALLEGRO_KEY_ENTER, // action_menu_enter
    ALLEGRO_KEY_SPACE, // action_skip_cutscene
  };

  bool is_action_triggered(action a);
  void record_key_pressed(keycode code);
  void record_key_released(keycode code);
  void set_control_scheme(const control_scheme& scheme);

  /** required to be called every frame to run internal updates. */
  void update_key_states();

} // namespace input

#endif //DONKEY_KONG_1981_INPUT_HH