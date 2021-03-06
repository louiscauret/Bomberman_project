//
// IntroMenu.cpp for bomberman in /home/cauret_l//Projets_epi/tek2/C++/Bomberman/MYFOLDERTEST/intro
//
// Made by louis cauret
// Login   <cauret_l@epitech.net>
//
// Started on  Fri Jun  7 16:36:10 2013 louis cauret
// Last update Sun Jun  9 18:26:16 2013 louis cauret
//

#include		"Intro.hpp"

Intro::Intro()
{
  _App = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Bomberman",  sf::Style::Titlebar);
  _image = new sf::Image();
  _font = new sf::Font();
  _text = new sf::String("Press Space Button", *_font, 14);
  _text2 = new sf::String("Press Space Button", *_font, 14);
  _fond = new sf::Image();
  _sprite = new sf::Sprite();
  _voice = new ThemeSound("./Sound/Voice.ogg");
  _time = true;
}


void			Intro::initialize()
{
  /////////////////////////////////////////////
  //Police
  /////////////////////////////////////////////
  if (!_font->LoadFromFile("./Menu/Abo_Mando.ttf", 50))
    exit(EXIT_FAILURE);
  /////////////////////////////////////////////
  //text clignotant
  /////////////////////////////////////////////
  _text->SetColor(sf::Color(128, 128, 0));
  _text->SetScale(2.f, 2.f);
  _text->Move(75.f, 450.f);
  _text2->SetColor(sf::Color(0, 0, 0));
  _text2->SetScale(2.f, 2.f);
  _text2->Move(175.f, 400.f);
  /////////////////////////////////////////////
  //Logo
  /////////////////////////////////////////////
  if (!_fond->LoadFromFile("./Menu/menu_fond.png"))
    exit(EXIT_FAILURE);
  _sprite->SetImage(*_fond);
  _App->Clear();
  _App->Draw(*_sprite);
  _App->Draw(*_text);
}

void			Intro::gameIntro(void)
{
  /////////////////////////////////////////////
  //initialise
  /////////////////////////////////////////////
  this->initialize();
  /////////////////////////////////////////////
  //check le press space
  /////////////////////////////////////////////
  while (_App->IsOpened())
    {
      sf::Event		Event;

      if (_App->GetEvent(Event))
        {
	  if (Event.Type == sf::Event::Closed)
	    _App->Close();
	  else if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
	    _App->Close();
	  else if (!(Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Space))
	    {
	      _voice->initialize();
	      _App->Close();
	    }
        }
      else
	{
	  //////////////////////////////////////
	  //or alterne color
	  //////////////////////////////////////
	  usleep(400000);
	  if (_time == true)
	    {
	      _App->Clear();
	      _App->Draw(*_sprite);
	      _App->Draw(*_text);
	      _time = false;
	    }
	  else
	    {
	      _App->Clear();
	      _App->Draw(*_sprite);
	      _App->Draw(*_text2);
	      _time = true;
	    }
	}
      _App->Display();
    }
}
