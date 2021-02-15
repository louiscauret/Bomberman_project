//
// EndMenu.hpp for  in /home/quesne_p//Bomber/Bomber
//
// Made by pierre quesnel
// Login   <quesne_p@epitech.net>
//
// Started on  Fri Jun  7 21:15:43 2013 pierre quesnel
// Last update Sun Jun  9 18:11:38 2013 louis cauret
//

#ifndef			ENDMENU_HPP
# define		ENDMENU_HPP

# include		<SFML/Graphics.hpp>
# include		<string>
# include		<sstream>
# include		<iostream>
# include		<unistd.h>

class			MyGame;

class			EndMenu
{
private:
  sf::RenderWindow	*_App;
  sf::Image		*_image;
  sf::Font		*_font;
  std::ostringstream	_intScore;
  std::ostringstream	_intBestScore;
  std::string		*_playerScore;
  std::string		*_bestScore;
  sf::String		*_text;
  sf::String		*_text2;
  sf::String		*_text3;
  sf::String		*_text4;
  sf::String		*_text5;
  sf::String		*_text6;
  sf::String		*_text7;
  sf::String		*_text8;
  sf::String		*_text9;
  sf::String		*_text10;
  sf::String		*_text11;
  bool			_pos;
  sf::Image		*_fond;
  sf::Sprite		*_sprite;

public:
  EndMenu(std::string player, int pScore, int bScore);
  ~EndMenu();

public:
  void			endGame(void);
  void			initialize(void);

};

#endif
