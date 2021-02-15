//
// AleaMap.cpp for  in /home/quesne_p//Bomber/Maps
// 
// Made by pierre quesnel
// Login   <quesne_p@epitech.net>
// 
// Started on  Mon Jun  3 11:58:19 2013 pierre quesnel
// Last update Sun Jun  9 02:10:22 2013 pierre quesnel
//

#include	<iostream>
#include	<string>
#include	<fstream>
#include	<stdio.h>
#include	<stdexcept>
#include	<vector>
#include	<stdlib.h>

void		genMap()
{
  int		max_x = (rand() % 20) + 10;
  int		max_y = (rand() % 20) + 10;
  std::ofstream fichier("./Maps/AleaMap.bbr", std::ios::out | std::ios::trunc);
  int		alea;

  if(fichier)
    {
      for (int i = 0; i < max_x; ++i)
	fichier << "1";
      fichier << std::endl;
      for (int idx = 0; idx < (max_y - 2); ++idx)
	{
	  fichier << "1";
	  for (int i = 0; i < (max_x - 2); ++i)
	    {
	      alea = rand() % 10;
	      if (alea == 0 || alea == 1)
		fichier << "2";
	      else if (alea == 2)
		fichier << "1";
	      else
		fichier << " ";
	    }
	  fichier << "1";
	  fichier << std::endl;
	}
      for (int i = 0; i < max_x; ++i)
	fichier << "1";
    }
  else
    throw std::string("Generation of map failed.");
}
