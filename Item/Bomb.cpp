//
// Bomb.cpp for  in /home/quesne_p//Bomber/Game
//
// Made by pierre quesnel
// Login   <quesne_p@epitech.net>
//
// Started on  Fri May 31 05:15:12 2013 pierre quesnel
// Last update Sun Jun  9 18:23:23 2013 louis cauret
//

#include		<stdio.h>
#include		"Map.hpp"
#include		"Bomb.hpp"
#include		"ThemeSound.hpp"

Bomb::Bomb(Point const &loc, int const &dmg, int const &rad)
{
  this->_loc = loc;
  this->_dmg = dmg;
  this->_rad = rad;
  this->_model = gdl::Model::load("models/bomb.fbx");
  this->_timer.play();
  this->_over = false;
  this->_expTxtr = gdl::Image::load("Txtr/Explosion.png");
  this->_visualTimer = 0;
  this->_explosed = false;
  this->_over = false;
  this->_sound = new ThemeSound("./Sound/Bomb.ogg");
  this->_sound->initialize();
  glMatrixMode(GL_MODELVIEW);

}

Bomb::Bomb(Bomb const &cpy)
{
  this->_loc = cpy._loc;
  this->_dmg = cpy._dmg;
  this->_rad = cpy._rad;
  this->_model = cpy._model;
  this->_timer.play();
  this->_over = cpy._over;
  this->_expTxtr = gdl::Image::load("Txtr/Explosion.png");
  this->_visualTimer = cpy._visualTimer;
  this->_explosed = false;
  this->_over = false;
 glMatrixMode(GL_MODELVIEW);
}

Bomb const		&Bomb::operator=(Bomb const &cpy)
{
  if (this != &cpy)
    {
      this->_loc = cpy._loc;
      this->_dmg = cpy._dmg;
      this->_rad = cpy._rad;
      this->_model = cpy._model;
      this->_timer.play();
      this->_over = cpy._over;
      this->_expTxtr = gdl::Image::load("Txtr/Explosion.png");
      this->_visualTimer = cpy._visualTimer;
      this->_explosed = false;
      this->_over = false;
      glMatrixMode(GL_MODELVIEW);
    }
  return (*this);
}

void			Bomb::blowUp(void)
{
  _over = true;
  return ;
}

void			Bomb::initialize(void){}

void			Bomb::update(gdl::GameClock const & timer, gdl::Input & input)
{
  if (!getExp())
    {
      _timer.update();
      if (_timer.getTotalElapsedTime() > 1.0f && _over == false)
	{
	  blowUp();
	}
      if (!_model.animation_hasStarted("Take 001"))
	this->_model.play("Take 001");
    }
  _model.update(timer);
  (void)input;
}

unsigned int const	&Bomb::getVisualTimer() const
{
  return (_visualTimer);
}

void			Bomb::setVisualTimer(unsigned int const & time)
{
  this->_visualTimer = time;
}

void			Bomb::draw()
{
  if (_over == false)
    {
      glPushMatrix();
      glTranslatef(_loc.x * BOMB_SCALE, 10.0f, _loc.y * BOMB_SCALE);
      gdl::Model::Begin();
      _model.draw();
      glPopMatrix();
    }
  else if (_over == true && _explosed == false)
    {
      setVisualTimer(3);
    }
  if (getVisualTimer())
    {
      Point		loc = _loc;

      for (int v = (loc.x); v <= (loc.x + (_rad - 1)); ++v)
      	{
      	  int h = loc.y;
      	  if (v >= 0 && h >= 0 && _map->isEmpty(Point(v, h)))
      	    drawExp(_expTxtr, Point(v, h));
      	  else
      	    break;
      	}
      for (int v = (loc.x); v >= (loc.x - (_rad - 1)); --v)
      	{
      	  int h = loc.y;
      	  if (v >= 0 && h >= 0 && _map->isEmpty(Point(v, h)))
      	    drawExp(_expTxtr, Point(v, h));
      	  else
      	    break;
      	}
      for (int h = (loc.y); h <= (loc.y + (_rad - 1)); ++h)
      	{
      	  int v = loc.x;
      	  if (v >= 0 && h >= 0 && _map->isEmpty(Point(v, h)))
      	    drawExp(_expTxtr, Point(v, h));
      	  else
      	    break;
      	}
      for (int h = (loc.y); h >= (loc.y - (_rad - 1)); --h)
      	{
      	  int v = loc.x;
      	  if (v >= 0 && h >= 0 && _map->isEmpty(Point(v, h)))
      	    drawExp(_expTxtr, Point(v, h));
      	  else
      	    break;
      	}
      setVisualTimer(getVisualTimer() - 1);
    }
}

Point const		&Bomb::getLoc(void) const
{
  return (_loc);
}

int const		&Bomb::getDmg(void) const
{
  return (_dmg);
}

int const		&Bomb::getRad(void) const
{
  return (_rad);
}

bool const		&Bomb::getOver(void) const
{
  return (_over);
}

bool const		&Bomb::getExp(void) const
{
  return (_explosed);
}

void			Bomb::setExp(bool const &etat)
{
  this->_explosed = etat;
}

void			Bomb::drawExp(gdl::Image &txtr, Point const &point)
{
  Point			coor(point.x * 2 * 150.0f, point.y * 2 * 150.0f);

  txtr.bind();
  glBegin(GL_QUADS);
  //////////////////
  // 4 coté + 1 top
  //////////////////
  glTexCoord2d(0, 0);
  glVertex3f(-150.0f + coor.x, 2 * 150.0f, 150.0f + coor.y);
  glTexCoord2d(0, 1);
  glVertex3f(-150.0f + coor.x, 0.0f, 150.0f + coor.y);
  glTexCoord2d(1, 1);
  glVertex3f(150.0f + coor.x, 0.0f, 150.0f + coor.y);
  glTexCoord2d(1, 0);
  glVertex3f(150.0f + coor.x, 2 * 150.0f, 150.0f + coor.y);
  glTexCoord2d(0, 0);
  glVertex3f(-150.0f + coor.x, 2 * 150.0f, -150.0f + coor.y);
  glTexCoord2d(0, 1);
  glVertex3f(-150.0f + coor.x, 0.0f, -150.0f + coor.y);
  glTexCoord2d(1, 1);
  glVertex3f(-150.0f + coor.x, 0.0f, 150.0f + coor.y);
  glTexCoord2d(1, 0);
  glVertex3f(-150.0f + coor.x, 2 * 150.0f, 150.0f + coor.y);
  glTexCoord2d(0, 0);
  glVertex3f(150.0f + coor.x, 2 * 150.0f, -150.0f + coor.y);
  glTexCoord2d(0, 1);
  glVertex3f(150.0f + coor.x, 0.0f, -150.0f + coor.y);
  glTexCoord2d(1, 1);
  glVertex3f(-150.0f + coor.x, 0.0f, -150.0f + coor.y);
  glTexCoord2d(1, 0);
  glVertex3f(-150.0f + coor.x, 2 * 150.0f, -150.0f + coor.y);
  glTexCoord2d(0, 0);
  glVertex3f(150.0f + coor.x, 2 * 150.0f, 150.0f + coor.y);
  glTexCoord2d(0, 1);
  glVertex3f(150.0f + coor.x, 0.0f, 150.0f + coor.y);
  glTexCoord2d(1, 1);
  glVertex3f(150.0f + coor.x, 0.0f, -150.0f + coor.y);
  glTexCoord2d(1, 0);
  glVertex3f(150.0f + coor.x, 2 * 150.0f, -150.0f + coor.y);
  glTexCoord2d(0, 0);
  glVertex3f(-150.0f + coor.x, 2 * 150.0f, 150.0f + coor.y);
  glTexCoord2d(0, 1);
  glVertex3f(150.0f + coor.x, 2 * 150.0f, 150.0f + coor.y);
  glTexCoord2d(1, 1);
  glVertex3f(150.0f + coor.x, 2 * 150.0f, -150.0f + coor.y);
  glTexCoord2d(1, 0);
  glVertex3f(-150.0f + coor.x, 2 * 150.0f, -150.0f + coor.y);
  /////////////////
  glEnd();
}

void			Bomb::setMap(Map *map)
{
  this->_map = map;
}

void			Bomb::stopSound()
{
  _sound->StopTheme();
}
