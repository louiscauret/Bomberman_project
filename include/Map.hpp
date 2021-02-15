//
// map.hpp for  in /home/quesne_p//Bomber
// 
// Made by pierre quesnel
// Login   <quesne_p@epitech.net>
// 
// Started on  Tue May 28 17:46:41 2013 pierre quesnel
// Last update Sun Jun  9 03:36:00 2013 pierre quesnel
//

#ifndef					MAP_HPP_
# define				MAP_HPP_

# define				SCALE	150.0f
# define				C_TXTR	5

# include				<iostream>
# include				<string>
# include				<vector>
# include				<GL/gl.h>
# include				<GL/glu.h>
# include				"AObject.hpp"
# include				"Player.hpp"
# include				"GameClock.hpp"
# include				"Bomb.hpp"
# include				"ThemeSound.hpp"
# include				"Menu.hpp"
# include				"EndMenu.hpp"

class					MyGame;

class					Map : public AObject
{
public:
  enum					LandType
    {
      GRASS				= ' ',
      WALL				= '1',
      BOX				= '2',
      RBONUS				= '3',
      HBONUS				= '4',
      DBONUS				= '5',
    };
    
protected:
  int					_xSize;
  int					_ySize;
  std::vector<std::vector<LandType> >	_map;
  gdl::Image				_GrassTxtr;
  gdl::Image				_WallTxtr;
  gdl::Image				_BoxTxtr;
  gdl::Image				_bloodTxtr;
  gdl::Image				_rBonusTxtr;
  gdl::Image				_hBonusTxtr;
  gdl::Image				_dBonusTxtr;
  gdl::Image				_fondTxtr;
  std::vector<Player *>			_playerList;
  std::vector<Bomb *>			_bombList;
  ThemeSound				*_themeSound;
  ThemeSound				*_endSound;
  bool					_pause;
  MyGame				*_parent;
  EndMenu				*_gameEnd;
  std::string				_currentName;

public:
  Map(MyGame *parent);
  Map(Map const &);
  ~Map();
  Map const				&operator=(Map const &);

public:
  void					initialize(void);
  void					update(gdl::GameClock const &, gdl::Input &);
  void					draw(void);

public:
  void					mapLoad(std::string const &);
  void					setPlayerList(Player &);
  int const 				&getXSize() const;
  int const				&getYSize() const;
  bool					isEmpty(Point const &point);
  void					setBomb(Bomb&);
  int					isBonus(Point const &point) const;
  void					removeBonus(Point const &point);
  bool					isPaused() const;
  void					setPause(bool const &);
  std::vector<Player *> const		&getPlayerList() const;

private:
  void					ClearMap();
  Map::LandType const			&ConvertMapChar(char const &) const;
  Map::LandType				DefineLandType(Point const&) const;
  void					txtrGrass(int const &x, int const &y);
  void					txtrWall(int const &x, int const &y);
  void					txtrBox(int const &x, int const &y);
  void					txtrRB(int const &x, int const &y);
  void					txtrHB(int const &x, int const &y);
  void					txtrDB(int const &x, int const &y);
  void					drawItem(gdl::Image & txtr, Point const &point);
  void					drawItem2(gdl::Image & txtr, Point const &point);
  void					makeExp(Point const &loc, int const &dmg, int const &rad);
  void					cleanExplBomb();
  int					ratioDmg(int dmg, int x, int p, int rad);
  Map::LandType				popBonus(Point const &loc);
  void					checkUpPlayers();
  void					forceExit(gdl::Input &input);
  void					handleWin();
  void					handleBomb(gdl::GameClock const & timer, gdl::Input & input);
  void					handlePlayer(gdl::GameClock const & timer, gdl::Input & input);
  void					handlePause(gdl::Input &input);
  void					handleUnPause(gdl::Input &input);
  bool					saveMap(void);
  void					MakeSave(gdl::Input & input);
  bool					saveConf(void);
};

#endif
