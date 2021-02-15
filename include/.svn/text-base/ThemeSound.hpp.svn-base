//
// GameSound.hpp for  in /home/quesne_p//Bomber/include
// 
// Made by pierre quesnel
// Login   <quesne_p@epitech.net>
// 
// Started on  Tue Jun  4 15:50:54 2013 pierre quesnel
// Last update Sat Jun  8 21:34:22 2013 pierre quesnel
//

#ifndef			THEMESOUND_HPP
# define		THEMESOUND_HPP

# include		<pthread.h>
# include		<stdio.h>
# include		<stdlib.h>
# include		<unistd.h>
# include		<iostream>
# include		<string>
# include		<vector>
# include		<GL/gl.h>
# include		<GL/glu.h>
# include		<pthread.h>
# include		<stdio.h>
# include		<stdlib.h>
# include		<unistd.h>
# include		"AObject.hpp"
# include		<SFML/Audio.hpp>


class			ThemeSound
{
private:
  sf::Music		_music;
  bool			_stop;

public:
  ThemeSound(const std::string &filename);
  ~ThemeSound(){};

public:
  void			initialize(void);
  void			update();
  bool			isStop(void) const;
  void			StopTheme(void);
  void			PauseTheme(void);
};

#endif
