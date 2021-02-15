//
// AObject.hpp for Bomberman in /home/chreti_m//projet/C++/bomberman
// 
// Made by max chretien
// Login   <chreti_m@epitech.net>
// 
// Started on  Tue May  7 16:49:36 2013 max chretien
// Last update Wed May  8 16:05:44 2013 max chretien
//

#ifndef		AOBJECT_HPP_
# define	AOBJECT_HPP_

# include	"GameClock.hpp"
# include	"Input.hpp"
# include	"Vector3f.hpp"
# include	"Image.hpp"

class		AObject
{
public:
  AObject(void) : position_(0.0f, 0.0f, 0.0f), rotation_(0.0f, 0.0f, 0.0f)
  {}
  virtual void	initialize(void) = 0;
  virtual void	update(gdl::GameClock const &, gdl::Input &) = 0;
  virtual void	draw(void) = 0;

protected:
  Vector3f	position_;
  Vector3f	rotation_;
  gdl::Image	texture_;
};

# include	"Primitive.hpp"
# include	"Object.hpp"
# include	"Bomberman.hpp"

#endif
