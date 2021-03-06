//
// Player.hpp for  in /home/quesne_p//Bomber
//
// Made by pierre quesnel
// Login   <quesne_p@epitech.net>
//
// Started on  Sun May 26 15:38:05 2013 pierre quesnel
// Last update Sun Jun  9 18:20:41 2013 louis cauret
//

#ifndef			PLAYER_HPP_
# define		PLAYER_HPP_

# include		<iostream>
# include		<string>
# include		<map>
# include		<GL/gl.h>
# include		<GL/glu.h>
# include		"GameClock.hpp"
# include		"Input.hpp"
# include		"Vector3f.hpp"
# include		"Model.hpp"
# include		"GameClock.hpp"
# include		"Point.hpp"
# include		"ThemeSound.hpp"

# define		C_HEAD	4
# define		C_SORT	3

class			Map;
class			Point;

class			Player
{
public:
  enum			Sort
  {
    P1,
    P2,
    BOT,
  };
enum			Dir
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
  };
protected:
  Point			_loc;
  Sort			_sort;
  Dir			_lookAt;
  Point			_ms;
  gdl::Clock		_timer;
  gdl::Clock		_bombTimer;
  gdl::Model		_model;
  bool			_isTired;
  int			_hp;
  bool			_alive;
  int			_x;
  int			_y;
  std::string		_name;
  int			_rad;
  int			_dmg;
  bool			_moving;
  bool			_stoping;
  bool			_running;
  ThemeSound		*_BonusSound;
  int			_nbBonus;
  int			_nbBomb;
  int			_score;
  std::vector<Player *>	_playerList;
  int			_bombUse;
  Point			_bombLoc;
  bool			_botMove;
  Point			_oldPos;

public:
  Player(Sort const &, Point point, std::string id);
  Player(Player const &);
  virtual ~Player();
  Player const		&operator=(Player const &);

public:
  gdl::Color const	randomColor() const;
  void			draw();
  virtual void		update(gdl::GameClock const&, gdl::Input&, Map&);
  Point			getLoc() const;
  void			setDmg(int const&);
  bool			isAlive() const;
  int			getHp() const;
  std::string		getName() const;
  int			getScore() const;

private:
  void			moveUp(void);
  void			moveDown(void);
  void			moveRight(void);
  void			moveLeft(void);
  void			updateP1(gdl::Input & input, Map & map);
  void			updateP2(gdl::Input & input, Map & map);
  void			updateBot(gdl::Input & input, Map & map);
  void			botMoveToPlayer(Point &pLoc, Map &map);
  void			botRunAwayFromBomb(Map &map);
  void			botAleaMove(Map &map);
  void			botGetEnemyLoc(Point &pLoc, Map &map);
  void			botPutBomb(Point &pLoc, Map &map);
  bool			botGetItem(Map &map);
  void			headTracking(void) const;
  void			headUp(void) const;
  void			headDown(void) const;
  void			headLeft(void) const;
  void			headRight(void) const;
  void			setLookAt(Dir const&);
  bool			moving(Dir const&, Map&);
  void			setBonus(int const &b);
  void			handlerTake();
  void			handleScore();
  bool			checkOtherLoc(Map &map);
  bool			oldMove();
};

#endif
