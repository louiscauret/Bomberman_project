//
// Map.cpp for  in /home/quesne_p//Bomber
// 
// Made by pierre quesnel
// Login   <quesne_p@epitech.net>
// 
// Started on  Tue May 28 17:50:37 2013 louis cauret
// Last update Sun Jun  9 02:06:48 2013 pierre quesnel
//

#include	<iostream>
#include	<string>
#include	<stdio.h>
#include	<fstream>
#include	<stdexcept>
#include	<vector>
#include	<stdlib.h>
#include	"Map.hpp"
#include	"MyGame.hpp"
#include	"Score.hpp"

Map::Map(MyGame *parent)
{
  _xSize = 0;
  _ySize = 0;
  this->_pause = false;
  this->_parent = parent;
}

Map::Map(Map const &cpy)
{
  this->_xSize = cpy._xSize;
  this->_ySize = cpy._ySize;
  this->_map = cpy._map;
  this->_GrassTxtr = cpy._GrassTxtr;
  this->_WallTxtr = cpy._WallTxtr;
  this->_BoxTxtr = cpy._BoxTxtr;
  this->_bloodTxtr = cpy._bloodTxtr;
  this->_playerList = cpy._playerList;
  this->_bombList = cpy._bombList;
  this->_pause = false;
}

Map const	&Map::operator=(Map const &cpy)
{
  if (this != &cpy)
    {
      this->_xSize = cpy._xSize;
      this->_ySize = cpy._ySize;
      this->_map = cpy._map;
      this->_GrassTxtr = cpy._GrassTxtr;
      this->_WallTxtr = cpy._WallTxtr;
      this->_BoxTxtr = cpy._BoxTxtr;
      this->_bloodTxtr = cpy._bloodTxtr;
      this->_playerList = cpy._playerList;
      this->_bombList = cpy._bombList;
      this->_pause = false;
    }
  return (*this);
}

Map::~Map(){}

void		Map::ClearMap()
{
  _xSize = 0;
  _ySize = 0;
  _map.clear();
}


Map::LandType const		&Map::ConvertMapChar(char const &c) const
{
  std::map<char, LandType>	landMap;
  
  landMap.insert(std::pair<char, LandType>(' ', GRASS));
  landMap.insert(std::pair<char, LandType>('1', WALL));
  landMap.insert(std::pair<char, LandType>('2', BOX));
  landMap.insert(std::pair<char, LandType>('3', RBONUS));
  landMap.insert(std::pair<char, LandType>('4', HBONUS));
  landMap.insert(std::pair<char, LandType>('5', DBONUS));
  for (std::map<char, LandType>::iterator it = landMap.begin(); it!=landMap.end(); ++it)
    {
      if (it->first == c)
	return (it->second);
    }
  throw std::string("Invalid Map.");
}

void		Map::mapLoad(std::string const &file)
{
  std::ifstream iss(file.c_str());
  std::string	mapLine;

  if (iss)
    {
      ClearMap();
      while (std::getline(iss, mapLine))
	{
	  std::vector<LandType>	Line;
	  _ySize++;
	  if (_xSize < (int)mapLine.size())
	    _xSize = (int)mapLine.size();
	  for (std::string::iterator it = mapLine.begin(); it < mapLine.end(); ++it)
	    Line.push_back(ConvertMapChar(*it));
	  _map.push_back(Line);
	}
    }
  else
    {
      std::cerr << "Loading Map failed." << std::endl;
      exit(EXIT_FAILURE);
    }
}

void		Map::initialize(void)
{
  ///////////////////////////////////////////////////
  //Musique de fond
  ///////////////////////////////////////////////////
  this->_themeSound = new ThemeSound("./Sound/theme.ogg");
  _themeSound->initialize();
  ////////////////////////////////////////////////////
  //Atribution des textures
  ////////////////////////////////////////////////////
  _GrassTxtr = gdl::Image::load("Txtr/FloorPortal.png");
  _WallTxtr = gdl::Image::load("Txtr/WallPortal.png");
  _BoxTxtr = gdl::Image::load("Txtr/BoxPortal.png");
  _bloodTxtr = gdl::Image::load("Txtr/DeadPlayer.png");
  _rBonusTxtr = gdl::Image::load("Txtr/RangeBonus.png");
  _hBonusTxtr = gdl::Image::load("Txtr/HealBonus.png");
  _dBonusTxtr = gdl::Image::load("Txtr/DomageBonus.png");
  _fondTxtr = gdl::Image::load("Txtr/fond2.png");
  sleep(1);
}


void		Map::forceExit(gdl::Input &input)
{
  if (input.isKeyDown(gdl::Keys::Escape))
    {
      this->_themeSound->StopTheme();
      this->_themeSound->update();
      for (std::vector<Bomb*>::iterator it =  _bombList.begin(); it !=  _bombList.end(); ++it)
	(*it)->stopSound();
      usleep(500);
      this->_parent->close();
      exit(EXIT_FAILURE);
    }
}

void		Map::handleWin()
{
  int		playerAlive = 0;
  Score		score;
  int		maxScore = 0;
  int		myScore;
  std::string	name;

  for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); ++it)
    if ((*it)->isAlive())
      playerAlive++;
  if (playerAlive == 1)
    {
      for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); ++it)
	if ((*it)->isAlive())
	  {
	    name = (*it)->getName();
	    myScore = (*it)->getScore();
	  }
      this->_themeSound->StopTheme();
      this->_themeSound->update();
      sleep(2);
      usleep(200);
      this->_endSound = new ThemeSound("./Sound/End.ogg");
      this->_endSound->initialize();
      sleep(5);
      score.ScoreStat();
      maxScore = score.getMaxScore();
      score.insertScore(myScore);
      usleep(500);
      this->_parent->close();
      _gameEnd = new EndMenu(name.c_str(), myScore, maxScore);
      _gameEnd->initialize();
      _gameEnd->endGame();      
    }
  else if (playerAlive < 1)
    {
      this->_themeSound->StopTheme();
      this->_themeSound->update();
      sleep(2);
      usleep(500);
      this->_parent->close();
      score.ScoreStat();
      maxScore = score.getMaxScore();
      _gameEnd = new EndMenu("Nobody", 0, maxScore);
      _gameEnd->initialize();
      _gameEnd->endGame();
    }
}


void		Map::handleBomb(gdl::GameClock const & timer, gdl::Input & input)
{
  for (std::vector<Bomb*>::iterator it = _bombList.begin(); it != _bombList.end(); ++it)
    if ((*it)->getOver() && !(*it)->getExp())
      {
	(*it)->setExp(true);
	makeExp((*it)->getLoc(), (*it)->getDmg(), (*it)->getRad());
      }
  for (std::vector<Bomb*>::iterator it = _bombList.begin(); it != _bombList.end(); ++it)
    (*it)->update(timer, input);
}

void		Map::handlePlayer(gdl::GameClock const & timer, gdl::Input & input)
{
  for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); ++it)
    (*it)->update(timer, input, *this);
}

void		Map::handlePause(gdl::Input &input)
{
  if (input.isKeyDown(gdl::Keys::P))
    {
      setPause(true);
      usleep(1000);
    }
}

void		Map::handleUnPause(gdl::Input &input)
{
  if (input.isKeyDown(gdl::Keys::U))
    {
      setPause(false);
      usleep(1000);
    }
}

void		Map::update(gdl::GameClock const & timer, gdl::Input & input)
{
  ///////////////////////////////////////////////////////////////////////////
  //Exit forcé
  ///////////////////////////////////////////////////////////////////////////
  forceExit(input);
  ///////////////////////////////////////////////////////////////////////////
  //Save
  ///////////////////////////////////////////////////////////////////////////
  MakeSave(input);
  ///////////////////////////////////////////////////////////////////////////
  //End game
  ///////////////////////////////////////////////////////////////////////////
  handleWin();    
  ///////////////////////////////////////////////////////////////////////////
  //Pause
  ///////////////////////////////////////////////////////////////////////////
  handlePause(input);
  handleUnPause(input);
  if (isPaused() == false)
    {
      ///////////////////////////////////////////////////////////////////////
      //Bomb
      ///////////////////////////////////////////////////////////////////////
      handleBomb(timer, input);
      ///////////////////////////////////////////////////////////////////////
      //Players
      ///////////////////////////////////////////////////////////////////////
      handlePlayer(timer, input);
    }
  ///////////////////////////////////////////////////////////////////////////
  //Other divers
  ///////////////////////////////////////////////////////////////////////////
  this->_themeSound->update();
  usleep(5000);
}
  
void		Map::cleanExplBomb()
{
  //////////////////////////////////////////////////////////
  //supprime les bombes usagées.
  //////////////////////////////////////////////////////////
  for (std::vector<Bomb*>::iterator it =  _bombList.begin(); it !=  _bombList.end(); )
    {
      if ((*it)->getExp() == true && (*it)->getOver() == true)
	it = _bombList.erase(it);
      else
	++it;
    }
}

int		Map::ratioDmg(int dmg, int x, int p, int rad)
{
  //////////////////////////////////////////////////////////
  //resist chance (25% de chance de reduction des domages 
  //proportionnel a la distance bomb - player et du radius
  //////////////////////////////////////////////////////////
  int chance = rand() % 4;
  
  if (chance == 0)
    {
      int		d;

      if (x >= p)
	d = x - p;
      else
	d = p - x;
      std::cout << this->_currentName << " >> "
		<< "Partial resistance : "
		<< (int)((dmg / (rad)) * ((rad) - d))
		<< " Damages instead of "
		<< dmg
		<< ", damages reduced by "
		<< (dmg - (int)((dmg / (rad)) * ((rad) - d)))
		<< "!"
		<< std::endl;
      return ((int)((dmg / (rad)) * ((rad) - d)));
    }
  else
    {
      std::cout << this->_currentName << " >> "
		<< "No resistance : "
		<< dmg
		<< " Damages !"
		<< std::endl;
      return (dmg);
    }
}

Map::LandType		Map::popBonus(Point const &loc)
{
  (void)loc;
  int			chance;

  if ((chance = rand() % 4) == 0)
    return (Map::RBONUS);
  if ((chance = rand() % 4) == 0)
    return (Map::HBONUS);
  if ((chance = rand() % 5) == 0)
    return (Map::DBONUS);
  else
    return (Map::GRASS);
}

void		Map::makeExp(Point const &loc, int const &dmg, int const &rad)
{
  ////////////////////////////////////////////////////
  //destruction de map
  ////////////////////////////////////////////////////
  for (int v = (loc.x); v <= (loc.x + (rad - 1)); ++v)
    {
      int h = loc.y;
      for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); ++it)
  	{
  	  Point PlayerLoc;
  	  PlayerLoc = (*it)->getLoc();
  	  if (PlayerLoc.x == v && PlayerLoc.y == h)
	    {
	      this->_currentName = (*it)->getName();
	      (*it)->setDmg(ratioDmg(dmg, loc.x, PlayerLoc.x, rad));
	    }
  	}
      Map::LandType Land = DefineLandType(Point(v, h));	  
      if (v >= 0 && h >= 0 && Land != WALL)
  	{	
  	  if ( Land == Map::BOX)
  	    _map.at(h).at(v) = popBonus(loc);
  	}
      else      
  	break;
    }
  for (int v = (loc.x); v >= (loc.x - (rad - 1)); --v)
    {
      int h = loc.y;
      for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); ++it)
  	{
  	  Point PlayerLoc;
  	  PlayerLoc = (*it)->getLoc();
  	  if (PlayerLoc.x == v && PlayerLoc.y == h)
  	    (*it)->setDmg(ratioDmg(dmg, loc.x, PlayerLoc.x, rad));
  	}
      Map::LandType Land = DefineLandType(Point(v, h));	  
      if (v >= 0 && h >= 0 && Land != WALL)
  	{
  	  if ( Land == Map::BOX)
  	    _map.at(h).at(v) = popBonus(loc);
  	}
      else      
  	break;
    }
  for (int h = (loc.y); h <= (loc.y + (rad - 1)); ++h)
    {
      int v = loc.x;
      for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); ++it)
  	{
  	  Point PlayerLoc;
  	  PlayerLoc = (*it)->getLoc();
  	  if (PlayerLoc.x == v && PlayerLoc.y == h)
  	    (*it)->setDmg(ratioDmg(dmg, loc.y, PlayerLoc.y, rad));
  	}
      Map::LandType Land = DefineLandType(Point(v, h));	  
      if (v >= 0 && h >= 0 && Land != WALL)
  	{	
  	  if ( Land == Map::BOX)
  	    _map.at(h).at(v) = popBonus(loc);
  	}
      else      
  	break;
    }
  for (int h = (loc.y); h >= (loc.y - (rad - 1)); --h)
    {
      int v = loc.x;
      for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); ++it)
  	{
  	  Point PlayerLoc;
  	  PlayerLoc = (*it)->getLoc();
  	  if (PlayerLoc.x == v && PlayerLoc.y == h)
  	    (*it)->setDmg(ratioDmg(dmg, loc.y, PlayerLoc.y, rad));
  	}
      Map::LandType Land = DefineLandType(Point(v, h));	  
      if (v >= 0 && h >= 0 && Land != WALL)
  	{	
  	  if ( Land == Map::BOX)
  	    _map.at(h).at(v) = popBonus(loc);
  	}
      else      
  	break;
    }
  checkUpPlayers();
}


void		Map::checkUpPlayers()
{
  std::cout << "//////////////////////////////" << std::endl;
  for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); ++it)
    {
      if ((*it)->getHp() > 0)
	std::cout << "Player "
		  << (*it)->getName().c_str()
		  << " : "
		  <<  (*it)->getHp()
		  << " hp remaining"
		  << std::endl;
    }
  std::cout << "//////////////////////////////" << std::endl;
}

void		Map::drawItem(gdl::Image &txtr, Point const& point)
{
  Point		coor(point.x * 2 * SCALE, point.y * 2 * SCALE);

  txtr.bind();
  glBegin(GL_QUADS);
  //////////////////
  // 4 coté + 1 top
  //////////////////
  glTexCoord2d(0, 0);
  glVertex3f(-SCALE + coor.x, 2 * SCALE, SCALE + coor.y);
  glTexCoord2d(0, 1);
  glVertex3f(-SCALE + coor.x, 0.0f, SCALE + coor.y);
  glTexCoord2d(1, 1);
  glVertex3f(SCALE + coor.x, 0.0f, SCALE + coor.y);
  glTexCoord2d(1, 0);
  glVertex3f(SCALE + coor.x, 2 * SCALE, SCALE + coor.y);
  glTexCoord2d(0, 0);
  glVertex3f(-SCALE + coor.x, 2 * SCALE, -SCALE + coor.y);
  glTexCoord2d(0, 1);
  glVertex3f(-SCALE + coor.x, 0.0f, -SCALE + coor.y);
  glTexCoord2d(1, 1);
  glVertex3f(-SCALE + coor.x, 0.0f, SCALE + coor.y);
  glTexCoord2d(1, 0);
  glVertex3f(-SCALE + coor.x, 2 * SCALE, SCALE + coor.y);
  glTexCoord2d(0, 0);
  glVertex3f(SCALE + coor.x, 2 * SCALE, -SCALE + coor.y);
  glTexCoord2d(0, 1);
  glVertex3f(SCALE + coor.x, 0.0f, -SCALE + coor.y);
  glTexCoord2d(1, 1);
  glVertex3f(-SCALE + coor.x, 0.0f, -SCALE + coor.y);
  glTexCoord2d(1, 0);
  glVertex3f(-SCALE + coor.x, 2 * SCALE, -SCALE + coor.y);
  glTexCoord2d(0, 0);
  glVertex3f(SCALE + coor.x, 2 * SCALE, SCALE + coor.y);
  glTexCoord2d(0, 1);
  glVertex3f(SCALE + coor.x, 0.0f, SCALE + coor.y);
  glTexCoord2d(1, 1);
  glVertex3f(SCALE + coor.x, 0.0f, -SCALE + coor.y);
  glTexCoord2d(1, 0);
  glVertex3f(SCALE + coor.x, 2 * SCALE, -SCALE + coor.y);
  glTexCoord2d(0, 0);
  glVertex3f(-SCALE + coor.x, 2 * SCALE, SCALE + coor.y);
  glTexCoord2d(0, 1);
  glVertex3f(SCALE + coor.x, 2 * SCALE, SCALE + coor.y);
  glTexCoord2d(1, 1);
  glVertex3f(SCALE + coor.x, 2 * SCALE, -SCALE + coor.y);
  glTexCoord2d(1, 0);
  glVertex3f(-SCALE + coor.x, 2 * SCALE, -SCALE + coor.y);
  /////////////////
  glEnd();
}

void		Map::drawItem2(gdl::Image &txtr, Point const &point)
{
  Point		coor(point.x * 2 * SCALE, point.y * 2 * SCALE);

  txtr.bind();
  glBegin(GL_QUADS);
  glTexCoord2d(0, 0);
  glVertex3f(-SCALE + coor.x, 0.0f, SCALE + coor.y);
  glTexCoord2d(0, 1);
  glVertex3f(-SCALE + coor.x, 0.0f, -SCALE + coor.y);
  glTexCoord2d(1, 1);
  glVertex3f(SCALE + coor.x, 0.0f, -SCALE + coor.y);
  glTexCoord2d(1, 0);
  glVertex3f(SCALE + coor.x, 0.0f, SCALE + coor.y);
  glEnd();
}

void		Map::txtrGrass(int const &x, int const &y)
{
  drawItem2(_GrassTxtr, Point(x, y));
}

void		Map::txtrWall(int const &x, int const &y)
{
  drawItem(_WallTxtr, Point(x, y));
}

void		Map::txtrBox(int const &x, int const &y)
{
  drawItem(_BoxTxtr, Point(x, y));
}

void		Map::txtrRB(int const &x, int const &y)
{
  drawItem(_rBonusTxtr, Point(x, y));
}

void		Map::txtrHB(int const &x, int const &y)
{
  drawItem(_hBonusTxtr, Point(x, y));
}

void		Map::txtrDB(int const &x, int const &y)
{
  drawItem(_dBonusTxtr, Point(x, y));
}

void				Map::draw(void)
{
  void				(Map::*ptr_txtr[C_TXTR])(int const &, int const &);
  std::map<LandType, int>	landMap;
  
  landMap.insert(std::pair<LandType, int>(GRASS, 0));
  landMap.insert(std::pair<LandType, int>(WALL, 1));
  landMap.insert(std::pair<LandType, int>(BOX, 2));
  landMap.insert(std::pair<LandType, int>(RBONUS, 3));
  landMap.insert(std::pair<LandType, int>(HBONUS, 4));
  landMap.insert(std::pair<LandType, int>(DBONUS, 5));
  ptr_txtr[0] = &Map::txtrGrass;
  ptr_txtr[1] = &Map::txtrWall;
  ptr_txtr[2] = &Map::txtrBox;
  ptr_txtr[3] = &Map::txtrRB;
  ptr_txtr[4] = &Map::txtrHB;
  ptr_txtr[5] = &Map::txtrDB;
  ///////////////////////
  //0 draw le fond
  ////////////////////////
  _fondTxtr.bind();
  glBegin(GL_QUADS);
  glTexCoord2d(0, 0);
  glVertex3f(-66560.0f, -9000.0f, 45520.0f);
  glTexCoord2d(0, 1);
  glVertex3f(-66560.0f, -4000.0f, -45520.0f);
  glTexCoord2d(1, 1);
  glVertex3f(66560.0f, -4000.0f, -45520.0f);
  glTexCoord2d(1, 0);
  glVertex3f(66560.0f, -9000.0f, 45520.0f);
  glEnd();

  ////////////////////////
  //1 draw la map
  ////////////////////////
  for (int y = 0; y < getYSize(); ++y)
    for (int x = 0; x < getXSize(); ++x)
      {
	Map::LandType Land = DefineLandType(Point(x, y));
	for (std::map<LandType, int>::iterator it = landMap.begin(); it!=landMap.end(); ++it)
	  {
	    if (it->first == Land)
	      (this->*ptr_txtr[it->second])(x, y);
	  }
      }
  ///////////////////////
  //2 draw les Player & Bots
  ///////////////////////
  for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); ++it)
    {
      if ((*it)->isAlive())
	(*it)->draw();
      else
	drawItem2(_bloodTxtr, (*it)->getLoc());
    }
  //////////////////////
  //3 bomb
  //////////////////////
  for (std::vector<Bomb*>::iterator it = _bombList.begin(); it != _bombList.end(); ++it)
    (*it)->draw();
}

int const	&Map::getXSize() const
{
  return (_xSize);
}

int const	&Map::getYSize() const
{
  return (_ySize);
}


void		Map::MakeSave(gdl::Input & input)
{
  if (input.isKeyDown(gdl::Keys::F9))
    {
      ThemeSound	*saved = new ThemeSound("./Sound/Save.ogg");

      setPause(true);
      if (!saveMap())
	std::cerr << "Saving map failed." << std::endl;
      else
	std::cout << "Saving map complete." << std::endl;
      if (!saveConf())
	std::cerr << "Saving players failed." << std::endl;
      else
	std::cout << "Saving players complete." << std::endl;
      this->_themeSound->PauseTheme();
      sleep(1);
      saved->initialize();
      sleep(1);
      this->_themeSound->initialize();
    }
}

bool		Map::saveConf(void)
{
  std::ofstream fichierConf("./Save/save.conf", std::ios::out | std::ios::trunc);

  if(fichierConf)
    {
      for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); ++it)
	{
	  if ((*it)->isAlive())
	    {
	      if ((*it)->getName() == "Joueur 1")
		fichierConf << "0;";
	      else if ((*it)->getName() == "Joueur 2")
		fichierConf << "1;";
	      else
		fichierConf << "2;";
	      fichierConf << (*it)->getLoc().x;
	      fichierConf << ";";
	      fichierConf << (*it)->getLoc().y;
	      fichierConf << ";;";
	      fichierConf << std::endl;
	    }
	}
    }
  else
    return (false);
  return (true);
}

bool		Map::saveMap(void)
{
  std::ofstream fichierMap("./Save/save.bbr", std::ios::out | std::ios::trunc);

  if(fichierMap)
    {
      for (int y = 0; y < getYSize(); ++y)
	{
	  for (int x = 0; x < getXSize(); ++x)
	    fichierMap << (char)DefineLandType(Point(x, y));
	  fichierMap << std::endl;
	}
    }
  else
    return (false);
  return (true);
}

Map::LandType	Map::DefineLandType(Point const & point) const
{
  if (point.x < 0 || point.y < 0 || point.x > getXSize() || point.y > getYSize())
    {
      return (WALL);
    }
  else
    try
      {
	return (_map.at(point.y).at(point.x));
      }
  catch (const std::out_of_range& orr)
    {
      return (WALL);
    }
}

void		Map::setPlayerList(Player &player)
{
  _playerList.push_back(&player);
}


bool			Map::isEmpty(Point const &point)
{
  std::list<LandType>	landList;
  
  landList.push_back(GRASS);
  landList.push_back(RBONUS);
  landList.push_back(HBONUS);
  landList.push_back(DBONUS);
  if (point.x < 0 || point.y < 0 || point.x > getXSize() || point.y > getYSize())
    return (false);
  for (std::list<LandType>::iterator it = landList.begin(); it != landList.end(); ++it)
    {
      if ((*it) == DefineLandType(point))
	return (true);
    }
  return (false);
}

void		Map::setBomb(Bomb & bomb)
{
  _bombList.push_back(&bomb);
  for (std::vector<Bomb*>::iterator it = _bombList.begin(); it != _bombList.end(); ++it)
    (*it)->setMap(this);
}

int				Map::isBonus(Point const &point) const
{
  std::map<LandType, int>	landMap;
  
  landMap.insert(std::pair<LandType, int>(GRASS, 0));
  landMap.insert(std::pair<LandType, int>(RBONUS, 1));
  landMap.insert(std::pair<LandType, int>(HBONUS, 2));
  landMap.insert(std::pair<LandType, int>(DBONUS, 3));
  for (std::map<LandType, int>::iterator it = landMap.begin(); it!=landMap.end(); ++it)
    {
      if (it->first == DefineLandType(point))
	return (it->second);
    }
  return (0);
}

void		Map::removeBonus(Point const &point)
{
  _map.at(point.y).at(point.x) = GRASS;
}

bool		Map::isPaused() const
{
  return (_pause);
}

void		Map::setPause(bool const &p)
{
  this->_pause = p;
}

std::vector<Player *> const		&Map::getPlayerList() const
{
  return (_playerList);
}
