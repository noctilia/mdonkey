//#include "game.hpp"

#include "SFML/Graphics.hpp"
#include <string>

const int game_width = 224;
const int game_height = 256;

const int scale = 3;

const int screen_width = scale * game_width; 
const int screen_height = scale * game_height;  

int main(int argv, char** argc)
{
  srand(time(0));

  sf::Font font;
  font.loadFromFile("assets/fnt/ModernDOS8x8.ttf");

  sf::Font fontScore;
  fontScore.loadFromFile("assets/fnt/slkscr.ttf");

  sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "MDonkey");
  window.setFramerateLimit(60);

  sf::RenderTexture buffer;
  buffer.create(window.getSize().x, window.getSize().y);

  int windowHeight = window.getSize().x;
  int windowWidth = window.getSize().y;
  
  float sx = windowWidth / float(game_width);
  float sy = windowHeight / float(game_height);
  
  int scale = std::min(sx, sy);

  int scaleW = game_width * scale;
  int scaleH = game_height * scale;
  
  int scaleX = (windowWidth - scaleW) / 2;
  int scaleY = (windowHeight - scaleH) / 2;

  // todo:: use smart pointers
  //Graphics* GraphicManager = new Graphics(&window, &buffer, scaleX, scaleY, scaleW, scaleH, &font, &fontScore);
  //Sounds* SoundManager = new Sounds;
  //Game GameManager(GraphicManager, SoundManager);

  int player_life = 3;
  int player_score = 0;

  int game_state = -1;
  int game_level = 1;
  
  sf::Texture texture;
  texture.loadFromFile("assets/level_#1.png");

  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(3, 3);

#if 1
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear(sf::Color::Black);


    window.draw(sprite);

    sf::Text text;  
    text.setFont(font); 
    text.setString("HIGH SCORE");  
    text.setPosition(40, 10);
    text.setCharacterSize(48);  
    text.setFillColor(sf::Color::Yellow);  
    //text.setStyle(sf::Text::Bold);  
    window.draw(text);

    text.setFont(fontScore);
    text.setString("HIGH SCORE");
    text.setPosition(40, 40);
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::Yellow);

    window.draw(text);  

    window.display();
  }
  return 0; 
#endif

  while (game_state != 0)
  {
    // TODO: use event manager
    //game_state = GameManager.runMenu();
    switch (game_state)
    {
    case 0:
      break;
    case 1:
      player_life = 3;
      player_score = 0;

      game_level = 1;
      
      while (player_life != 0)
      {
        if (game_level == 5)
          break;

        //if (GameManager.runGame(player_life, game_level, player_score) == true)
        //{
        //  if (game_level == 4)
        //    GameManager.runCut(14);        //cutscene
        //  else
        //    GameManager.runCut(0);        //cutscene
        /*  game_level++;
        }*/
      }
      
      /*if (game_level == 5)
        GameManager.runStatic(1);
      else
        GameManager.runStatic(2);*/

      break;

    case 2:
      //GameManager.runOptions();
      break;

    case 3:
      //GameManager.runStatic(0);
      break;
    }
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