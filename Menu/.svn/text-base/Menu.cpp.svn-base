//
// menu.cpp for bomberman in /home/cauret_l//Projets_epi/tek2/C++/Bomberman/MYFOLDERTEST
//
// Made by louis cauret
// Login   <cauret_l@epitech.net>
//
// Started on  Wed Jun  5 12:25:06 2013 louis cauret
// Last update Sun Jun  9 16:43:15 2013 louis cauret
//

#include		"Menu.hpp"
#include		"MyGame.hpp"
#include		"Options.hpp"

MainMenu::MainMenu()
{
  _App = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Bomberman", sf::Style::Titlebar);
  _image = new sf::Image;
  _pos = true;
  _font = new sf::Font;
  _text = new sf::String("Nem Gawe", *_font, 14);
  _text2 = new sf::String("Nem Gawe", *_font, 14);
  _text3 = new sf::String("Load Gawe", *_font, 14);
  _text4 = new sf::String("Load Gawe", *_font, 14);
  _text5 = new sf::String("'O' for options", *_font, 10);
  _text6 = new sf::String("Player vs BOT", *_font, 10);
  _text7 = new sf::String("Player vs BOT", *_font, 10);
  _text8 = new sf::String("Player vs Player vs BOT", *_font, 10);
  _text9 = new sf::String("Player vs Player vs BOT", *_font, 10);
  _fond = new sf::Image;
  _sprite = new sf::Sprite;
  _multi = false;
  _nbBot = 1;
  _Preload = true;
}

MainMenu::~MainMenu(){}



void			MainMenu::initialize(void)
{
  if (!_font->LoadFromFile("./Menu/Abo_Mando.ttf", 50))
    {
      exit(EXIT_FAILURE);
    }
  if (!_fond->LoadFromFile("./Menu/menu_fond.png"))
    {
      exit(EXIT_FAILURE);
    }
  _text->SetColor(sf::Color(128, 128, 0));
  _text->SetScale(2.f, 2.f);
  _text->Move(260.f, 400.f);
  _text2->SetColor(sf::Color(255, 204, 0));
  _text2->SetScale(2.f, 2.f);
  _text2->Move(260.f, 400.f);
  _text3->SetColor(sf::Color(128, 128, 0));
  _text3->SetScale(2.f, 2.f);
  _text3->Move(250.f, 475.f);
  _text4->SetColor(sf::Color(255, 204, 0));
  _text4->SetScale(2.f, 2.f);
  _text4->Move(250.f, 475.f);
  _text5->SetColor(sf::Color(128, 204, 0));
  _text5->SetScale(2.f, 2.f);
  _text5->Move(250.f, 550.f);
  _text6->SetColor(sf::Color(128, 128, 0));
  _text6->SetScale(2.f, 2.f);
  _text6->Move(220.f, 400.f);
  _text7->SetColor(sf::Color(255, 204, 0));
  _text7->SetScale(2.f, 2.f);
  _text7->Move(220.f, 400.f);
  _text8->SetColor(sf::Color(128, 128, 0));
  _text8->SetScale(2.f, 2.f);
  _text8->Move(100.f, 475.f);
  _text9->SetColor(sf::Color(255, 204, 0));
  _text9->SetScale(2.f, 2.f);
  _text9->Move(100.f, 475.f);

  _sprite->SetImage(*_fond);
  _App->Clear();
  _App->Draw(*_sprite);
  _App->Draw(*_text2);
  _App->Draw(*_text3);
  _App->Draw(*_text5);
}

void			MainMenu::chooseMode()
{
  _App->Clear();
  _App->Draw(*_sprite);
  _App->Draw(*_text7);
  _App->Draw(*_text8);
  while (_App->IsOpened())
    {
      sf::Event		Event;

      while (_App->GetEvent(Event))
        {
	  if (Event.Type == sf::Event::Closed)
	    _App->Close();
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
	    {
	      _App->Close();
	      exit(EXIT_FAILURE);
	    }
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return))
	    {
	      return ;
	    }
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up))
	    {
	      _App->Clear();
	      _App->Draw(*_sprite);
	      _App->Draw(*_text7);
	      _App->Draw(*_text8);
	      _multi = false;
	    }
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down))
	    {
	      _App->Clear();
	      _App->Draw(*_sprite);
	      _App->Draw(*_text6);
	      _App->Draw(*_text9);
	      _multi = true;
	    }
	  _App->Display();
	}
    }
}

bool			MainMenu::menu()
{
  while (_App->IsOpened())
    {
      sf::Event		Event;

      while (_App->GetEvent(Event))
        {
	  if (Event.Type == sf::Event::Closed)
	    _App->Close();
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
	    {
	      _App->Close();
	      exit(EXIT_FAILURE);
	    }
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return))
	    {
	      if (_pos == true)
		{
		  _App->Clear();
		  chooseMode();
		  _App->Close();
		  return (false);
		}
	    }
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return))
	    {
	      if (_pos == false)
		{
		  //////////////////////////////////
		  //Loaded
		  //////////////////////////////////
		  _App->Clear();
		  _App->Close();
		  return (true);
		}
	    }
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up))
	    {
	      _App->Clear();
	      _App->Draw(*_sprite);
	      _App->Draw(*_text2);
	      _App->Draw(*_text3);
	      _App->Draw(*_text5);
	      _pos = true;
	    }
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down))
	    {
	      _App->Clear();
	      _App->Draw(*_sprite);
	      _App->Draw(*_text);
	      _App->Draw(*_text4);
	      _App->Draw(*_text5);
	      _pos = false;
	    }
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::O))
	    {
	      Options	opt;

	      opt.initialize();
	      opt.gameOptions();
	      ////////////////////////////////////
	      //lancer la fenetre d'option
	      ////////////////////////////////////
	      if ((_Preload = opt.getPreload()) == false)
		_MapName = opt.getMapName();
	      _nbBot = opt.getNbBot();
	      _App->Clear();
	      chooseMode();
	      _App->Close();
	      return (false);
	    }
        }
      _App->Display();
    }
  return (false);
}

bool			MainMenu::getPreload() const
{
  return (_Preload);
}

std::string const	&MainMenu::getMapName() const
{
  return (_MapName);
}

int			MainMenu::getNbBot() const
{
  return (_nbBot);
}

bool			MainMenu::getMultiPlayer() const
{
  return (_multi);
}
