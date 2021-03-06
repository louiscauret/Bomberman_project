//
// Options.cpp for bomberman in /home/cauret_l//Projets_epi/tek2/C++/Bomberman/BomberV03/Bomber
//
// Made by louis cauret
// Login   <cauret_l@epitech.net>
//
// Started on  Sat Jun  8 16:49:56 2013 louis cauret
// Last update Sun Jun  9 18:28:22 2013 louis cauret
//

#include		"Options.hpp"

Options::Options()
{
  _App = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Bomberman",  sf::Style::Titlebar);
  _font = new sf::Font;
  _botNbr = 1;
  _botNbrStream << _botNbr;
  _botNbrString = new std::string(_botNbrStream.str());
  _text = new sf::String("Select Your Wap Type", *_font, 14);
  _text2 = new sf::String("Randow Wap", *_font, 10);
  _text3 = new sf::String("Randow Wap", *_font, 10);
  _text4 = new sf::String("Pre-Build Wap", *_font, 10);
  _text5 = new sf::String("Pre-Build Wap", *_font, 10);
  _text6 = new sf::String("Bots NuWber", *_font, 12);
  _text8 = new sf::String(*_botNbrString, *_font, 14);
  _text9 = new sf::String("+ / -", *_font, 14);
  _text10 = new sf::String("'S' to Save your choice", *_font, 14);

  std::ifstream		file("./Maps/listMap.conf", std::ios::in);

  if (file)
    {
      std::string	content;

      while (getline(file, content))
	{
	  std::string	subStr;

	  subStr = content.substr(0, content.find(";"));
	  content = content.substr(content.find(";") + 1);
	  if (subStr.size() > 4)
	    _listMap.push_back(subStr);
	}
      _exist = true;
    }
  else
    {
      _exist = false;
    }
  _indexMap = 0;
}

Options::~Options()
{}

void			Options::initialize()
{
  /////////////////////////////////////////////
  //Police
  /////////////////////////////////////////////
  if (!_font->LoadFromFile("./Menu/Abo_Mando.ttf", 50))
    exit(EXIT_FAILURE);
  /////////////////////////////////////////////
  //texte
  /////////////////////////////////////////////
  _text->SetColor(sf::Color(153, 153, 255));
  _text->SetScale(2.f, 2.f);
  _text->Move(15.f, 50.f);
  _text2->SetColor(sf::Color(128, 128, 0));
  _text2->SetScale(2.f, 2.f);
  _text2->Move(25.f, 100.f);
  _text3->SetColor(sf::Color(255, 204, 0));
  _text3->SetScale(2.f, 2.f);
  _text3->Move(25.f, 100.f);
  _text4->SetColor(sf::Color(128, 128, 0));
  _text4->SetScale(2.f, 2.f);
  _text4->Move(200.f, 100.f);
  _text5->SetColor(sf::Color(255, 204, 0));
  _text5->SetScale(2.f, 2.f);
  _text5->Move(200.f, 100.f);
  _text6->SetColor(sf::Color(153, 153, 255));
  _text6->SetScale(2.f, 2.f);
  _text6->Move(120.f, 180.f);
  _text9->SetColor(sf::Color(255, 204, 0));
  _text9->SetScale(2.f, 2.f);
  _text9->Move(250.f, 210.f);
  _text10->SetColor(sf::Color(255, 0, 0));
  _text10->SetScale(2.f, 2.f);
  _text10->Move(15.f, 270.f);

  /////////////////////////////////////////////
  //Affichage
  /////////////////////////////////////////////
  _App->Clear();
  _App->Draw(*_text);
  _App->Draw(*_text3);
  _App->Draw(*_text4);
  _App->Draw(*_text6);
  _App->Draw(*_text8);
  _App->Draw(*_text9);
  _App->Draw(*_text10);
  _pos = true;
}

void			Options::gameOptions()
{
  this->initialize();
  while (_App->IsOpened())
    {
      sf::Event         Event;

      if (_App->GetEvent(Event))
        {
	  if (Event.Type == sf::Event::Closed)
            _App->Close();
          if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
            _App->Close();
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Left))
	    {
	      _App->Clear();
	      _App->Draw(*_text);
	      _App->Draw(*_text3);
	      _App->Draw(*_text4);
	      _App->Draw(*_text6);
	      _App->Draw(*_text8);
	      _App->Draw(*_text9);
	      _App->Draw(*_text10);
	      _pos = true;
	    }
	  if (((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Right) && _exist) || _pos == false)
	    {
	      if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return))
		{
		  if (_indexMap < (int)_listMap.size() - 1)
		    _indexMap++;
		  else
		    _indexMap = 0;
		  _App->Clear();
		  _text7 = new sf::String(_listMap[_indexMap], *_font, 14);
		  _text7->SetColor(sf::Color(153, 153, 255));
		  _text7->SetScale(2.f, 2.f);
		  _text7->Move(100.f, 100.f);
		  _App->Draw(*_text7);
		  _App->Draw(*_text);
		  _App->Draw(*_text2);
		  _App->Draw(*_text5);
		  _App->Draw(*_text6);
		  _App->Draw(*_text8);
		  _App->Draw(*_text9);
		  _App->Draw(*_text10);
		  _pos = false;
		}
	      _App->Clear();
	      _text7 = new sf::String(_listMap[_indexMap], *_font, 14);
	      _text7->SetColor(sf::Color(153, 153, 255));
	      _text7->SetScale(2.f, 2.f);
	      _text7->Move(150.f, 270.f);
	      _App->Draw(*_text7);
	      _App->Draw(*_text);
	      _App->Draw(*_text2);
	      _App->Draw(*_text5);
	      _App->Draw(*_text6);
	      _App->Draw(*_text8);
	      _App->Draw(*_text9);
	      _App->Draw(*_text10);
	      _pos = false;
	    }
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Add))
	    {
	      if (_botNbr >= 0 && _botNbr < 500)
		_botNbr++;
	      if (_pos == true)
		{
		  _App->Clear();
		  _botNbrStream.str("");
		  _botNbrStream << _botNbr;
		  _botNbrString = new std::string(_botNbrStream.str());
		  _text8 = new sf::String(*_botNbrString, *_font, 14);
		  _text8->SetColor(sf::Color(153, 153, 255));
		  _text8->SetScale(2.f, 2.f);
		  _text8->Move(220.f, 420.f);
		  _App->Draw(*_text);
		  _App->Draw(*_text3);
		  _App->Draw(*_text4);
		  _App->Draw(*_text6);
		  _App->Draw(*_text8);
		  _App->Draw(*_text9);
		  _App->Draw(*_text10);
		}
	      else
		{
		  _App->Clear();
		  _botNbrStream.str("");
		  _botNbrStream << _botNbr;
		  _botNbrString = new std::string(_botNbrStream.str());
		  _text8 = new sf::String(*_botNbrString, *_font, 14);
		  _text8->SetColor(sf::Color(153, 153, 255));
		  _text8->SetScale(2.f, 2.f);
		  _text8->Move(220.f, 420.f);
		  _App->Draw(*_text);
		  _App->Draw(*_text2);
		  _App->Draw(*_text5);
		  _App->Draw(*_text6);
		  _App->Draw(*_text8);
		  _App->Draw(*_text9);
		  _App->Draw(*_text10);
		}
	    }
	  else if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Subtract))
	    {
	      if (_botNbr > 0 && _botNbr <= 500)
		_botNbr--;
	      if (_pos == true)
		{
		  _App->Clear();
		  _botNbrStream.str("");
		  _botNbrStream << _botNbr;
		  _botNbrString = new std::string(_botNbrStream.str());
		  _text8 = new sf::String(*_botNbrString, *_font, 14);
		  _text8->SetColor(sf::Color(153, 153, 255));
		  _text8->SetScale(2.f, 2.f);
		  _text8->Move(220.f, 420.f);
		  _App->Draw(*_text);
		  _App->Draw(*_text3);
		  _App->Draw(*_text4);
		  _App->Draw(*_text6);
		  _App->Draw(*_text8);
		  _App->Draw(*_text9);
		  _App->Draw(*_text10);
		}
	      else
		{
		  _App->Clear();
		  _botNbrStream.str("");
		  _botNbrStream << _botNbr;
		  _botNbrString = new std::string(_botNbrStream.str());
		  _text8 = new sf::String(*_botNbrString, *_font, 14);
		  _text8->SetColor(sf::Color(153, 153, 255));
		  _text8->SetScale(2.f, 2.f);
		  _text8->Move(220.f, 420.f);
		  _App->Draw(*_text);
		  _App->Draw(*_text2);
		  _App->Draw(*_text5);
		  _App->Draw(*_text6);
		  _App->Draw(*_text8);
		  _App->Draw(*_text9);
		  _App->Draw(*_text10);
		}
	    }
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::S))
	    {
	      _App->Close();
	    }
	}
      _App->Display();
    }
}

int			Options::getNbBot() const
{
  return (_botNbr);
}

std::string const	&Options::getMapName() const
{
  return (_listMap[_indexMap]);
}

bool			Options::getPreload() const
{
  return (_pos);
}
