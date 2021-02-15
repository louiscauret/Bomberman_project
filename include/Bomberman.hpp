//
// Bomberman.hpp for Bomberman in /home/chreti_m//projet/C++/bomberman
//
// Made by max chretien
// Login   <chreti_m@epitech.net>
//
// Started on  Tue May  7 22:51:29 2013 max chretien
// Last update Sun Jun  9 18:11:07 2013 louis cauret
//

#ifndef		BOMBERMAN_HPP_
# define	BOMBERMAN_HPP_

# include	"AObject.hpp"
# include	"GameClock.hpp"
# include	"Input.hpp"
# include	"Model.hpp"

namespace	Model
{
  class Bomberman : public AObject
  {
  public:
    Bomberman(void);
    ~Bomberman(void);
    void	initialize(void);
    void	update(gdl::GameClock const &, gdl::Input &);
    void	draw(void);
  private:
    gdl::Model		model_;
  public:
    static const float	BLOCK_SIZE = 150.0f;
  };
}
#endif
