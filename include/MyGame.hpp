//
// MyGame.hpp for Bomberman in /home/chreti_m//projet/C++/bomberman
// 
// Made by max chretien
// Login   <chreti_m@epitech.net>
// 
// Started on  Tue May  7 16:45:53 2013 max chretien
// Last update Fri Jun  7 19:56:37 2013 pierre quesnel
//

#ifndef			MYGAME_HPP_
# define		MYGAME_HPP_

# include		<cstdlib>
# include		<list>
# include		"AObject.hpp"
# include		"Game.hpp"
# include		"Camera.hpp"
# include		"Map.hpp"

class MyGame : public gdl::Game
{
public:
  void			initialize(void);
  void			update(void);
  void			draw(void);
  void			unload(void);
  void			close(void);

private:
  Camera		camera_;
  std::list<AObject*>	objects_;
  Map*			map_;
  Point			randPlacement();
};

#endif
