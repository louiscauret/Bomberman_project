//
// Menu.hpp for  in /home/quesne_p//Bomber/Bomber
// 
// Made by pierre quesnel
// Login   <quesne_p@epitech.net>
// 
// Started on  Fri Jun  7 21:25:49 2013 pierre quesnel
// Last update Sun Jun  9 04:53:45 2013 pierre quesnel
//

#ifndef			MENU_HPP
# define		MENU_HPP

# include		<cstdlib>
# include		<SFML/Graphics.hpp>
# include		<iostream>

class			MyGame;
class			Options;

class			MainMenu
{
private:
  sf::RenderWindow	*_App;
  sf::Image		*_image;
  bool			_pos;
  sf::Font		*_font;
  sf::String		*_text;
  sf::String		*_text2;
  sf::String		*_text3;
  sf::String		*_text4;
  sf::String		*_text5;
  sf::String		*_text6;
  sf::String		*_text7;
  sf::String		*_text8;
  sf::String		*_text9;
  sf::Image		*_fond;
  sf::Sprite		*_sprite;

private:
  ////////////////////////////
  //From Options
  ///////////////////////////
  bool			_Preload;
  std::string		_MapName;
  int			_nbBot;
  bool			_multi;

public:
  MainMenu();
  ~MainMenu();

public:
  void			initialize(void);
  bool			menu(void);
  bool			getPreload() const;
  std::string const	&getMapName() const;
  int			getNbBot() const;
  bool			getMultiPlayer() const;
  void			chooseMode();
};

#endif
