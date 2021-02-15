//
// Camera.cpp for Bomberman in /home/chreti_m//projet/C++/bomberman/Game
// 
// Made by max chretien
// Login   <chreti_m@epitech.net>
// 
// Started on  Tue May  7 18:07:13 2013 max chretien
// Last update Sat Jun  8 17:48:42 2013 pierre quesnel
//

#include		"Camera.hpp"
#include		<iostream>

Camera::Camera(void) : position_(0.50f, 5500.0f, 2300.0f), rotation_(0.0f, 0.0f, 0.0f),
		       location_(-0.45, 0.32f, -1.0f)
{
}

void			Camera::initialize(void)
{
  ////////////////////////////////////////////////////////////////////////////////
  /// Configuration du frustum de la camera
  ////////////////////////////////////////////////////////////////////////////////
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glTranslatef(-0.45f, 0.32f, -1.0f);
  gluPerspective(55.0f, 1600.0f/1024.0f, 1.0f, 50000.0f);
  ////////////////////////////////////////////////////////////////////////////////
  /// Positionnement de la camera
  ////////////////////////////////////////////////////////////////////////////////
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
  gluLookAt(position_.x, position_.y, position_.z,
	    0.0f, 0.0f, -1.0f,
	    0.0f, 1.0f, 0.0f);
  ////////////////////////////////////////////////////////////////////////////////
  /// Activation des tests de profondeur
  ////////////////////////////////////////////////////////////////////////////////
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  ////////////////////////////////////////////////////////////////////////////////
  /// Positionnement de la caméra
  ////////////////////////////////////////////////////////////////////////////////
  _name = "Joueur 1";
  _fixe = false;
}

void			Camera::zoom(void)
{
  if (position_.y < 10000.0f)
    position_.y += 50.0f;
}

void			Camera::dezoom(void)
{
  if (position_.y > 3000.0f)
    position_.y -= 50.0f;
}

void			Camera::vuePlayer1(void)
{
  _name = "Joueur 1";
  _fixe = false;
}

void			Camera::vuePlayer2(void)
{
  _name = "Joueur 2";
  _fixe = false;
}

void			Camera::vueFixe(void)
{
  _fixe = true;
}

void			Camera::update(gdl::GameClock const & gameClock, gdl::Input & input,
				       Map *map, gdl::Window &window_)
{
  Point			_p;
  std::map<int, Cam>	keysMap;
  void			(Camera::*ptr_cam[C_CAM])(void);

  keysMap.insert(std::pair<int, Cam>(input.isKeyDown(gdl::Keys::F1), Camera::F1));
  keysMap.insert(std::pair<int, Cam>(input.isKeyDown(gdl::Keys::F2), Camera::F2));
  keysMap.insert(std::pair<int, Cam>(input.isKeyDown(gdl::Keys::F3), Camera::F3));
  keysMap.insert(std::pair<int, Cam>(input.isKeyDown(gdl::Keys::F4), Camera::F4));
  keysMap.insert(std::pair<int, Cam>(input.isKeyDown(gdl::Keys::F5), Camera::F5));
  ptr_cam[0] = &Camera::zoom;
  ptr_cam[1] = &Camera::dezoom;
  ptr_cam[2] = &Camera::vuePlayer1;
  ptr_cam[3] = &Camera::vuePlayer2;
  ptr_cam[4] = &Camera::vueFixe;
  for (std::map<int, Cam>::iterator it = keysMap.begin(); it != keysMap.end(); ++it)
    {
      if (it->first == true)
	(this->*ptr_cam[it->second])();
    }
  if (!_fixe)
    {
      location_.x = -0.45;
      location_.y = 0.32f;
      position_.x = 0.50f; 
      position_.z = 2300.0f;
    }
  _playerList = map->getPlayerList();
  for (unsigned i = 0; i < _playerList.size(); i++)
    {
      if (_playerList[i]->getName() == _name)
	{
	  _p = _playerList[i]->getLoc();
	  break;
	}
    }
  if (!_fixe)
    {
      location_.x -= 0.04f * (_p.x - 1);
      location_.y += 0.07f * (_p.y - 1);
      position_.x += 5.0f * (_p.x - 1);
      position_.z += 350.0f * (_p.y - 1);
    }
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glTranslatef(location_.x, location_.y, location_.z);
  gluPerspective(55.0f, 1600.0f/1024.0f, 1.0f, 50000.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(position_.x, position_.y, position_.z,
	    0.0f, 0.0f, -1.0f,
	    0.0f, 1.0f, 0.0f);
  glViewport(0, 0, window_.getWidth(), window_.getHeight());
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  (void)gameClock;
}
