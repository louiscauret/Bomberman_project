//
// Camera.hpp for Bomberman in /home/chreti_m//projet/C++/bomberman
// 
// Made by max chretien
// Login   <chreti_m@epitech.net>
// 
// Started on  Tue May  7 17:25:39 2013 max chretien
// Last update Sat Jun  8 16:52:00 2013 pierre quesnel
//

#ifndef		CAMERA_HPP_
# define	CAMERA_HPP_

# include	<GL/gl.h>
# include	<GL/glu.h>
# include	"GameClock.hpp"
# include	"Input.hpp"
# include	"Vector3f.hpp"
# include	"Player.hpp"
# include	"Map.hpp"
# include	"Point.hpp"

# define	C_CAM	5

class		Camera
{
public:
  enum		Cam
    {
      F1,
      F2,
      F3,
      F4,
      F5
    };

public:
  Camera(void);
  void		initialize(void);
  void		update(gdl::GameClock const &, gdl::Input &, Map *, gdl::Window &);

private:
  void		zoom(void);
  void		dezoom(void);
  void		vuePlayer1(void);
  void		vuePlayer2(void);
  void		vueFixe(void);

private:
  Vector3f		position_;
  Vector3f		rotation_;
  Vector3f		location_;
  std::vector<Player *>	_playerList;
  bool			_fixe;
  std::string		_name;
};

#endif
