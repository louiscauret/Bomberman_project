//
// Player.cpp for  in /home/quesne_p//Bomber
//
// Made by pierre quesnel
// Login   <quesne_p@epitech.net>
//
// Started on  Sun May 26 15:52:31 2013 pierre quesnel
// Last update Sun Jun  9 18:31:03 2013 louis cauret
//

#include		<iostream>
#include		<stdlib.h>
#include		<stdio.h>
#include		<string>
#include		"Map.hpp"
#include		"Player.hpp"
#include		"Bomberman.hpp"

gdl::Color const	Player::randomColor() const
{
  return (gdl::Color(rand() % 255, rand() % 255, rand() % 255));
}

Player::Player(Sort const &sort, Point point, std::string id)
{
  this->_loc = point;
  this->_sort = sort;
  this->_lookAt = (Dir)(rand() % 4);
  this->_ms = Point(50, 50);
  this->_timer.play();
  this->_timer.update();
  this->_bombTimer.play();
  this->_bombTimer.update();
  this->_model = gdl::Model::load("models/marvin.fbx");
  if (this->_sort == P1)
    {
      this->_model.set_default_model_color(gdl::Color(0, 255, 0));
    }
  else if (this->_sort == P2)
    {
      this->_model.set_default_model_color(gdl::Color(0, 0, 255));
    }
  else
    this->_model.set_default_model_color(gdl::Color(255, 0, 0));
  gdl::Model::cut_animation(_model, "Take 001", 36, 53, "TakeRun");
  gdl::Model::cut_animation(_model, "Take 001", 100, 120, "TakeStop");
  this->_model.set_anim_speed("TakeRun", 50);
  this->_model.set_anim_speed("TakeStop", 50);
  this->_isTired = false;
  this->_hp = 100;
  this->_alive = true;
  if (this->_sort == P1)
    this->_name = "Joueur 1";
  else if (this->_sort == P2)
    this->_name = "Joueur 2";
  else
    this->_name = "bot" + id;
  this->_rad = 3;
  this->_dmg = 50;
  this->_moving = false;
  this->_stoping = true;
  this->_running = false;
  this->_nbBonus = 0;
  this->_nbBomb = 0;
  this->_score = 0;
  this->_botMove = false;
}

Player::Player(Player const &cpy)
{
  this->_loc = cpy._loc;
  this->_sort = cpy._sort;
  this->_lookAt = cpy._lookAt;
  this->_ms = cpy._ms;
  this->_model = cpy._model;
  this->_isTired = cpy._isTired;
  this->_hp = cpy._hp;
  this->_alive = cpy._alive;
  this->_x = cpy._x;
  this->_y = cpy._y;
  this->_rad = cpy._rad;
  this->_dmg = cpy._dmg;
  this->_moving = false;
  this->_stoping = true;
  this->_running = false;
  gdl::Model::cut_animation(_model, "Take 001", 36, 53, "TakeRun");
  gdl::Model::cut_animation(_model, "Take 001", 100, 120, "TakeStop");
  this->_model.set_anim_speed("TakeRun", 50);
  this->_model.set_anim_speed("TakeStop", 50);
  this->_nbBonus = 0;
  this->_nbBomb = 0;
  this->_score = 0;
}

Player const		&Player::operator=(Player const &cpy)
{
  if (this != &cpy)
    {
      this->_loc = cpy._loc;
      this->_sort = cpy._sort;
      this->_lookAt = cpy._lookAt;
      this->_ms = cpy._ms;
      this->_model = cpy._model;
      this->_isTired = cpy._isTired;
      this->_hp = cpy._hp;
      this->_alive = cpy._alive;
      this->_x = cpy._x;
      this->_y = cpy._y;
      this->_rad = cpy._rad;
      this->_dmg = cpy._dmg;
      this->_moving = false;
      this->_stoping = true;
      this->_running = false;
      gdl::Model::cut_animation(_model, "Take 001", 36, 53, "TakeRun");
      gdl::Model::cut_animation(_model, "Take 001", 100, 120, "TakeStop");
      this->_model.set_anim_speed("TakeRun", 50);
      this->_model.set_anim_speed("TakeStop", 50);
      this->_nbBonus = 0;
      this->_nbBomb = 0;
      this->_score = 0;
    }
  return (*this);
}

Player::~Player(){}

void			Player::headUp(void) const
{
  glRotatef(180.0f, 0.0f, 20.0f, 0.0f);
}

void			Player::headDown(void) const
{
  glRotatef(0.0f, 0.0f, 20.0f, 0.0f);
}

void			Player::headLeft(void) const
{
  glRotatef(-90.0f, 0.0f, 20.0f, 0.0f);
}

void			Player::headRight(void) const
{
  glRotatef(90.0f, 0.0f, 20.0f, 0.0f);
}

void			Player::headTracking() const
{
  void			(Player::*ptr_head[C_HEAD])(void) const;

  ptr_head[UP] = &Player::headUp;
  ptr_head[DOWN] = &Player::headDown;
  ptr_head[LEFT] = &Player::headLeft;
  ptr_head[RIGHT] = &Player::headRight;
  if (_lookAt >= 0 && _lookAt < C_HEAD)
    (this->*ptr_head[_lookAt])();
}

void			Player::draw()
{
  if (_alive == true)
    {
      glPushMatrix();
      float		x = (SCALE * 2) * (_ms.x / 100.0f) - SCALE;
      float		y = (SCALE * 2) * (_ms.y / 100.0f) - SCALE;
      glTranslatef((_loc.x * (SCALE * 2)) + x, 0.0f, (_loc.y * (SCALE * 2)) + y);
      headTracking();
      gdl::Model::Begin();
      this->_model.draw();
      gdl::Model::End();
      glPopMatrix();
    }
}

void			Player::updateP1(gdl::Input & input, Map & map)
{
  std::map<int, Dir>	keysMap;

  keysMap.insert(std::pair<int, Dir>(input.isKeyDown(gdl::Keys::Z), Player::UP));
  keysMap.insert(std::pair<int, Dir>(input.isKeyDown(gdl::Keys::S), Player::DOWN));
  keysMap.insert(std::pair<int, Dir>(input.isKeyDown(gdl::Keys::Q), Player::LEFT));
  keysMap.insert(std::pair<int, Dir>(input.isKeyDown(gdl::Keys::D), Player::RIGHT));
  for (std::map<int, Dir>::iterator it = keysMap.begin(); it!=keysMap.end(); ++it)
    {
      if (it->first == true && _isTired == false)
	moving(it->second, map);
    }
  if (input.isKeyDown(gdl::Keys::Space))
    {
      if (_bombTimer.getTotalElapsedTime() > 0.5f)
	{
	  _bombTimer.reset();
	  Bomb *b = new Bomb(_loc, _dmg, _rad);
	  map.setBomb(*b);
	  _nbBomb++;
	}
    }
}

void			Player::updateP2(gdl::Input & input, Map & map)
{
  std::map<int, Dir>	keysMap;

  keysMap.insert(std::pair<int, Dir>(input.isKeyDown(gdl::Keys::Up), Player::UP));
  keysMap.insert(std::pair<int, Dir>(input.isKeyDown(gdl::Keys::Down), Player::DOWN));
  keysMap.insert(std::pair<int, Dir>(input.isKeyDown(gdl::Keys::Left), Player::LEFT));
  keysMap.insert(std::pair<int, Dir>(input.isKeyDown(gdl::Keys::Right), Player::RIGHT));
  for (std::map<int, Dir>::iterator it = keysMap.begin(); it!=keysMap.end(); ++it)
    {
      if (it->first == true && _isTired == false)
	moving(it->second, map);
    }
  if (input.isKeyDown(gdl::Keys::Numpad0))
    {
      if (_bombTimer.getTotalElapsedTime() > 0.5f)
	{
	  _bombTimer.reset();
	  Bomb		*b = new Bomb(_loc, _dmg, _rad);
	  map.setBomb(*b);
	  _nbBomb++;
	}
    }
}

void			Player::botMoveToPlayer(Point &pLoc, Map &map)
{
  int			dir;

  dir = rand() % 2;
  if (dir == 0)
    {
      if (_loc.y > pLoc.y)
	{
	  _botMove = moving(Player::UP, map);
	}
      else if (_loc.y < pLoc.y)
	{
	  _botMove = moving(Player::DOWN, map);
	}
    }
  else if (dir == 1)
    {
      if (_loc.x > pLoc.x)
	{
	  _botMove = moving(Player::LEFT, map);
	}
      else if (_loc.x < pLoc.x)
	{
	  _botMove = moving(Player::RIGHT, map);
	}
    }
  if (_botMove == false)
    botAleaMove(map);
}

void			Player::botAleaMove(Map &map)
{
  int			dir;

  dir = rand () % 40;
  if (dir == 10 && _bombUse == false)
    {
      _bombTimer.reset();
      Bomb		*b = new Bomb(_loc, _dmg, _rad);
      map.setBomb(*b);
      _bombLoc.x = _loc.x;
      _bombLoc = _loc.y;
      _nbBomb++;
      _bombUse = true;
    }
  dir = rand () % 4;
  if (dir == 0)
    moving(Player::LEFT, map);
  else if (dir == 1)
    moving(Player::RIGHT, map);
  else if (dir == 2)
    moving(Player::UP, map);
  else
    moving(Player::DOWN, map);
}

void			Player::botRunAwayFromBomb(Map &map)
{
  int			dir;

  dir = rand() % 2;
  if (dir == 0)
    {
      if (_loc.y < _bombLoc.y)
	{
	  _botMove = moving(Player::UP, map);
	}
      else if (_loc.y > _bombLoc.y)
	{
	  _botMove = moving(Player::DOWN, map);
	}
    }
  else if (dir == 1)
    {
      if (_loc.x < _bombLoc.x)
	{
	  _botMove = moving(Player::LEFT, map);
	}
      else if (_loc.x > _bombLoc.x)
	{
	  _botMove = moving(Player::RIGHT, map);
	}
    }
  if (_botMove == false)
    botAleaMove(map);
}

void			Player::botGetEnemyLoc(Point &pLoc, Map &map)
{
  bool			p1Alive = false;

  _playerList = map.getPlayerList();
  for (unsigned i = 0; i < _playerList.size(); i++)
    {
      if ((_playerList[i]->getName() == "Joueur 1"
	   || _playerList[i]->getName() == "Joueur 2")
	  && _playerList[i]->isAlive() == true)
	{
	  pLoc = _playerList[i]->getLoc();
	  p1Alive = true;
	  break;
	}
    }
  if (p1Alive == false)
    for (unsigned i = 0; i < _playerList.size(); i++)
      {
	if (_playerList[i]->isAlive() == true && _playerList[i]->getName() != _name)
	  {
	    pLoc = _playerList[i]->getLoc();
	    break;
	  }
      }
}

void			Player::botPutBomb(Point &pLoc, Map &map)
{
  if ((((pLoc.x == _loc.x || pLoc.x == _loc.x) &&
	(pLoc.y + 1 == _loc.y || pLoc.y - 1 == _loc.y)) ||
       ((pLoc.x + 1 == _loc.x || pLoc.x - 1== _loc.x) &&
	(pLoc.y == _loc.y || pLoc.y  == _loc.y)))
      &&
      _bombUse == false)
    {
      _bombTimer.reset();
      Bomb		*b = new Bomb(_loc, _dmg, _rad);
      map.setBomb(*b);
      _nbBomb++;
      _bombUse = true;
    }
}

bool			Player::botGetItem(Map &map)
{
  if (map.isBonus(Point(_loc.x + 1, _loc.y)))
    {
      moving(Player::RIGHT, map);
      return (true);
    }
  if (map.isBonus(Point(_loc.x - 1, _loc.y)))
    {
      moving(Player::LEFT, map);
      return (true);
    }
  if (map.isBonus(Point(_loc.x, _loc.y - 1)))
    {
      moving(Player::UP, map);
      return (true);
    }
  if (map.isBonus(Point(_loc.x, _loc.y + 1)))
    {
      moving(Player::DOWN, map);
      return (true);
    }
  return (false);
}

void			Player::updateBot(gdl::Input & input, Map & map)
{
  Point			pLoc;

  if (botGetItem(map))
    return ;
  if (!_botMove)
    {
      botAleaMove(map);
      _botMove = true;
      return;
    }
  botGetEnemyLoc(pLoc, map);
  if (_bombTimer.getTotalElapsedTime() > 1.5f)
    _bombUse = false;
  else
    {
      botRunAwayFromBomb(map);
      return ;
    }
  botMoveToPlayer(pLoc, map);
  botPutBomb(pLoc, map);
  (void)input;
}

void			Player::handleScore()
{
  this->_score = (int)((_hp) + (_nbBonus * 20) + (_nbBomb));
}

int			Player::getScore() const
{
  return (_score);
}

void			Player::update(gdl::GameClock const &timer, gdl::Input & input, Map & map)
{
  if (_alive == true)
    {
      void			(Player::*ptr_sort[C_SORT])(gdl::Input & input, Map & map);

      ptr_sort[P1] = &Player::updateP1;
      ptr_sort[P2] = &Player::updateP2;
      ptr_sort[BOT] = &Player::updateBot;
      _model.update(timer);
      _timer.update();
      _bombTimer.update();
      handleScore();
      if (_timer.getTotalElapsedTime() > 0.05f)
	{
	  _moving = false;
	  _timer.reset();
	  _isTired = false;
	}
      if (_sort >= 0 && _sort <= C_SORT)
	{
	  (this->*ptr_sort[_sort])(input, map);
	}
      handlerTake();
     }
  usleep(5000);
}


void			Player::handlerTake()
{
  ///////////////////////////////////////////////////////////////////
  //Animation
  ///////////////////////////////////////////////////////////////////
  if (_moving == true)
    {
      _model.play("TakeRun");
      _running = true;
      _stoping = false;
    }
  else if (_running == true  && _stoping == false && _moving == false)
    if (!_model.animation_hasStarted("TakeStop") && !_model.animation_hasStarted("TakeRun"))
      {
	_model.play("TakeStop");
	_running = false;
	_stoping = true;
      }
}

void			Player::setLookAt(Dir const& dir)
{
  _lookAt = dir;
}

void			Player::moveUp(void)
{
  _y = -1;
}

void			Player::moveDown(void)
{
  _y = 1;
}

void			Player::moveLeft(void)
{
  _x = -1;
}

void			Player::moveRight(void)
{
  _x = 1;
}

bool			Player::checkOtherLoc(Map &map)
{
  Point			otherLoc;

  _playerList = map.getPlayerList();
  for (unsigned i = 0; i < _playerList.size(); i++)
    {
      if (_playerList[i]->getName() != _name && _playerList[i]->isAlive() == true)
	{
	  otherLoc = _playerList[i]->getLoc();
	  if (otherLoc.x == (_loc.x + _x) && otherLoc.y == (_loc.y + _y))
	    return (true);
	}
    }
  return (false);
}

bool			Player::oldMove()
{
  if (_sort == BOT && _loc.x + _x == _oldPos.x && _loc.y + _y == _oldPos.y)
    return (true);
  return (false);
}

bool			Player::moving(Dir const &dir, Map & map)
{
  void			(Player::*ptr_move[C_HEAD])(void);

  _x = 0;
  _y = 0;
  ptr_move[UP] = &Player::moveUp;
  ptr_move[DOWN] = &Player::moveDown;
  ptr_move[LEFT] = &Player::moveLeft;
  ptr_move[RIGHT] = &Player::moveRight;
  setLookAt(dir);
  if (dir >= 0 && dir < C_HEAD)
    {
      (this->*ptr_move[dir])();
      if (map.isEmpty(Point(_loc.x + _x, _loc.y + _y)) && _isTired == false
	  && !checkOtherLoc(map))
	{
	  if  (!oldMove())
	    {
	      _moving = true;
	      _isTired = true;
	    }
	  _loc = (Point(_loc.x + _x, _loc.y + _y));
	  _oldPos = (Point(_loc.x, _loc.y));
	  if (map.isBonus(this->_loc))
	    {
	      setBonus(map.isBonus(this->_loc));
	      map.removeBonus(this->_loc);
	    }
	  return (true);
	}
    }
  return (false);
}

void			Player::setBonus(int const &b)
{
  bool			isBonus = false;

  if (b == 1)
    {
      this->_rad += 1;
      isBonus = true;
    }
  if (b == 2)
    {
      if ((this->_hp + 50) > 150)
	this->_hp = 150;
      else
	this->_hp += 50;
      isBonus = true;
    }
  if (b == 3)
    {
      this->_dmg += 20;
      isBonus = true;
    }
  if (isBonus)
    {
      this->_BonusSound = new ThemeSound("./Sound/Bonus.ogg");
      this->_BonusSound->initialize();
      this->_nbBonus++;
    }
}

Point			Player::getLoc() const
{
  return (_loc);
}

void			Player::setDmg(int const &dmg)
{
  if (_hp - dmg < 0)
    _hp = 0;
  else
    _hp -= dmg;
  if (_hp <= 0)
    _alive = false;
}

bool			Player::isAlive() const
{
  return (_alive);
}

int			Player::getHp() const
{
  return (_hp);
}

std::string		Player::getName() const
{
  return (_name);
}
