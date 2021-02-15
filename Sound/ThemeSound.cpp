//
// ThemeSound.cpp for  in /home/quesne_p//Bomber/Bomber/Sound
// 
// Made by pierre quesnel
// Login   <quesne_p@epitech.net>
// 
// Started on  Fri Jun  7 18:00:07 2013 pierre quesnel
// Last update Sun Jun  9 02:13:27 2013 pierre quesnel
//

#include		<SFML/Audio.hpp>
#include		"ThemeSound.hpp"


ThemeSound::ThemeSound(const std::string &filename)
{
  if (!_music.OpenFromFile(filename))
    {
      std::cerr << "Error: Audio file "
		<< filename
		<< " can not be opened."
		<< std::endl;
    }
  this->_stop = false;
}

void		ThemeSound::initialize()
{
  this->_music.Play();
}

bool		ThemeSound::isStop() const
{
  return (this->_stop);
}

void		ThemeSound::StopTheme()
{
  this->_stop = true;
}

void		ThemeSound::PauseTheme()
{
  this->_music.Pause();
}

void		ThemeSound::update(void)
{
  if (!_music.GetStatus() == sf::Music::Playing)
    this->initialize();
  if (this->_stop)
    this->_music.Stop();
}
