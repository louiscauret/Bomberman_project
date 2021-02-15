//
// Primitive.hpp for Bomberman in /home/chreti_m//projet/C++/bomberman
//
// Made by max chretien
// Login   <chreti_m@epitech.net>
//
// Started on  Tue May  7 18:24:13 2013 max chretien
// Last update Sun Jun  9 18:21:06 2013 louis cauret
//

#ifndef		PRIMITIVE_HPP_
# define	PRIMITIVE_HPP_

# include	<GL/gl.h>
# include	<GL/glu.h>
# include	"AObject.hpp"
# include	"GameClock.hpp"
# include	"Input.hpp"
# include	"Image.hpp"

namespace	Primitive
{
  class Triangle : public AObject
  {
    void	initialize(void);
    void	update(gdl::GameClock const &, gdl::Input &);
    void	draw(void);
  };
  class Rectangle : public AObject
  {
    void	initialize(void);
    void	update(gdl::GameClock const &, gdl::Input &);
    void	draw(void);
  };
}

#endif
