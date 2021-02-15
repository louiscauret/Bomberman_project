//
// EndMenu.cpp for bomberman in /home/cauret_l//Projets_epi/tek2/C++/Bomberman/MYFOLDERTEST/menu_fin
//
// Made by louis cauret
// Login   <cauret_l@epitech.net>
//
// Started on  Wed Jun  5 21:02:49 2013 louis cauret
// Last update Sun Jun  9 18:25:51 2013 louis cauret
//

#include		"EndMenu.hpp"
#include		"MyGame.hpp"


EndMenu::EndMenu(std::string player, int pScore, int bScore)
{
  _App = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Bomberman", sf::Style::Titlebar);
  _image = new sf::Image;
  _font = new sf::Font;
  _intScore << pScore;
  _intBestScore << bScore;
  _playerScore = new std::string(_intScore.str());
  _bestScore = new std::string(_intBestScore.str());
  _text = new sf::String(player, *_font, 40);
  _text2 = new sf::String("WIN", *_font, 40);
  _text3 = new sf::String("Your Score is", *_font, 30);
  _text4 = new sf::String(*_playerScore, *_font, 30);
  _text5 = new sf::String("Try again", *_font, 40);
  _text6 = new sf::String("YES", *_font, 40);
  _text7 = new sf::String("NO", *_font, 40);
  _text8 = new sf::String("YES", *_font, 40);
  _text9 = new sf::String("NO", *_font, 40);
  _text10 = new sf::String("Best score is", *_font, 30);
  _text11 = new sf::String(*_bestScore, *_font, 30);
  _pos = true;
  _fond = new sf::Image;
  _sprite = new sf::Sprite;

}

EndMenu::~EndMenu(){}

void			EndMenu::initialize()
{
  if (!_font->LoadFromFile("./Menu/arcade.ttf", 50))
    exit(EXIT_FAILURE);
  _text->SetColor(sf::Color(0, 0, 0));
  _text->SetScale(2.f, 2.f);
  _text->Move(230.f, 40.f);
  _text2->SetColor(sf::Color(0, 0, 0));
  _text2->SetScale(2.f, 2.f);
  _text2->Move(310.f, 100.f);
  _text3->SetColor(sf::Color(0, 0, 0));
  _text3->SetScale(2.f, 2.f);
  _text3->Move(200.f, 200.f);
  _text4->SetColor(sf::Color(51, 204, 0));
  _text4->SetScale(2.f, 2.f);
  _text4->Move(330.f, 250.f);
  _text5->SetColor(sf::Color(0, 0, 0));
  _text5->SetScale(2.f, 2.f);
  _text5->Move(200.f, 400.f);
  _text6->SetColor(sf::Color(0, 0, 0));
  _text6->SetScale(2.f, 2.f);
  _text6->Move(220.f, 475.f);
  _text7->SetColor(sf::Color(0, 0, 0));
  _text7->SetScale(2.f, 2.f);
  _text7->Move(450.f, 475.f);
  _text8->SetColor(sf::Color(255, 204, 0));
  _text8->SetScale(2.f, 2.f);
  _text8->Move(220.f, 475.f);
  _text9->SetColor(sf::Color(255, 204, 0));
  _text9->SetScale(2.f, 2.f);
  _text9->Move(450.f, 475.f);
  _text10->SetColor(sf::Color(0, 0, 0));
  _text10->SetScale(2.f, 2.f);
  _text10->Move(200.f, 300.f);
  _text11->SetColor(sf::Color(255, 0, 0));
  _text11->SetScale(2.f, 2.f);
  _text11->Move(330.f, 350.f);
  if (!_fond->LoadFromFile("./Menu/menu_end.png"))
    exit(EXIT_FAILURE);
  _sprite->SetImage(*_fond);
  _App->Clear();
  _App->Draw(*_sprite);
  _App->Draw(*_text);
  _App->Draw(*_text2);
  _App->Draw(*_text3);
  _App->Draw(*_text4);
  _App->Draw(*_text5);
  _App->Draw(*_text6);
  _App->Draw(*_text7);
  _App->Draw(*_text10);
  _App->Draw(*_text11);
}

void			EndMenu::endGame(void)
{
  while (_App->IsOpened())
    {
      sf::Event		Event;
      while (_App->GetEvent(Event))
        {
	  if (Event.Type == sf::Event::Closed)
	    _App->Close();
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
	    _App->Close();
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return))
	    if (_pos == true)
	      {
		MyGame	game;
		_App->Close();
		game.run();

	      }
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return))
	    if (_pos == false)
	      _App->Close();
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Left))
	    {
	      _App->Clear();
	      _App->Draw(*_sprite);
	      _App->Draw(*_text);
	      _App->Draw(*_text2);
	      _App->Draw(*_text3);
	      _App->Draw(*_text4);
	      _App->Draw(*_text5);
	      _App->Draw(*_text8);
	      _App->Draw(*_text7);
	      _App->Draw(*_text10);
	      _App->Draw(*_text11);
	      _pos = true;
	    }
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Right))
	    {
	      _App->Clear();
	      _App->Draw(*_sprite);
	      _App->Draw(*_text);
	      _App->Draw(*_text2);
	      _App->Draw(*_text3);
	      _App->Draw(*_text4);
	      _App->Draw(*_text5);
	      _App->Draw(*_text6);
	      _App->Draw(*_text9);
	      _App->Draw(*_text10);
	      _App->Draw(*_text11);
	      _pos = false;
	    }
	}
      _App->Display();
    }
  exit(EXIT_SUCCESS);
}
