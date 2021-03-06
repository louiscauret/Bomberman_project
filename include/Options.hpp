//
// Options.hpp for bomberman in /home/cauret_l//Projets_epi/tek2/C++/Bomberman/BomberV03/Bomber
//
// Made by louis cauret
// Login   <cauret_l@epitech.net>
//
// Started on  Sat Jun  8 16:50:53 2013 louis cauret
// Last update Sun Jun  9 18:14:39 2013 louis cauret
//

#ifndef				OPTIONS_HPP
# define			OPTIONS_HPP

# include			<SFML/Graphics.hpp>
# include			<iostream>
# include			<string>
# include			<sstream>
# include			<iostream>
# include			<fstream>
# include			<vector>
# include			<iomanip>
# include			<unistd.h>
# include			"Menu.hpp"
# include			"ThemeSound.hpp"

class				Options
{
private:
  sf::RenderWindow		*_App;
  sf::Font			*_font;
  sf::String			*_text;
  sf::String			*_text2;
  sf::String			*_text3;
  sf::String			*_text4;
  sf::String			*_text5;
  sf::String			*_text6;
  sf::String			*_text8;
  sf::String			*_text9;
  sf::String			*_text10;
  sf::String			*_text7;
  int				_botNbr;
  int				_indexMap;
  std::ostringstream		_botNbrStream;
  std::string			*_botNbrString;
  bool				_pos;
  bool				_exist;
  std::vector<std::string>	_listMap;

public:
  Options();
  ~Options();

public:
  void				initialize(void);
  void				gameOptions(void);

  std::string const		&getMapName(void) const;
  int				getNbBot(void) const;
  bool				getPreload(void) const;
};




#endif
