//
// main.cpp for bomberman in /home/chreti_m//projet/C++/bomberman
// 
// Made by max chretien
// Login   <chreti_m@epitech.net>
// 
// Started on  Mon May  6 17:10:49 2013 max chretien
// Last update Sun Jun  9 03:30:33 2013 pierre quesnel
//

#include	<cstdlib>
#include	<SFML/Graphics.hpp>
#include	<iostream>
#include	"MyGame.hpp"
#include	"Intro.hpp"

int		main(int ac, char **av, char **env)
{  
  (void)ac;
  (void)av;
  if (!env[0])
    {
      std::cerr << "Environement unloded, quit" << std::endl;
      return (EXIT_FAILURE);
    }
  Intro		intro;
  MyGame	game;
  gdl::Clock	timer;

  intro.gameIntro();
  game.run();		    
  return (EXIT_SUCCESS);
}
