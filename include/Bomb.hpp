//
// Bomb.hpp for  in /home/quesne_p//Bomber/Game
// 
// Made by pierre quesnel
// Login   <quesne_p@epitech.net>
// 
// Started on  Fri May 31 05:25:10 2013 pierre quesnel
// Last update Fri Jun  7 17:43:02 2013 pierre quesnel
//

#ifndef			BOMB_HPP_
# define		BOMB_HPP_

# define		BOMB_SCALE		300.0f

#include		"Bomberman.hpp"
#include		"ThemeSound.hpp"
#include		"Clock.hpp"
#include		"Point.hpp"

class			map;

class			Bomb : public AObject
{
private:
  Point			_loc;
  int			_dmg;
  int			_rad;
  gdl::Clock		_timer;
  gdl::Model		_model;
  gdl::Image		_expTxtr;
  bool			_over;
  bool			_explosed;
  unsigned int		_visualTimer;
  Map			*_map;
  ThemeSound		*_sound;

public:
  Bomb(Point const &, int const &, int const &);
  Bomb(Bomb const &);
  ~Bomb(){};

  Bomb const		&operator=(Bomb const &);
public:
  void			initialize(void);
  void			update(gdl::GameClock const &, gdl::Input &);
  void			draw();
  Point const		&getLoc(void) const;
  int const		&getDmg(void) const;
  int const		&getRad(void) const;
  bool const		&getOver(void) const;
  bool const		&getExp(void) const;
  void			setExp(bool const &);
  unsigned int const	&getVisualTimer() const;
  void			setMap(Map *map);
  void			stopSound();
private:
  void			blowUp(void);
  void			drawExp(gdl::Image &txtr, Point const &point);
  void			setVisualTimer(unsigned const &);
};

#endif
