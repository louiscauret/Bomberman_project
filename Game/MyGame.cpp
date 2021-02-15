//
// MyGame.cpp for Bomberman in /home/chreti_m//projet/C++/bomberman
//
// Made by max chretien
// Login   <chreti_m@epitech.net>
//
// Started on  Tue May  7 16:54:57 2013 max chretien
// Last update Sun Jun  9 18:09:19 2013 louis cauret
//

# include		<iostream>
# include		<stdio.h>
# include		<fstream>
# include		<sstream>
# include		<iomanip>
# include		<string>
# include		<vector>
# include		<utility>
# include		"Player.hpp"
# include		"MyGame.hpp"
# include		"Point.hpp"
# include		"AleaMap.hpp"
# include		"ThemeSound.hpp"
# include		"Menu.hpp"

void			MyGame::initialize(void)
{
  srand(time(NULL));
  bool			preload;
  int			nbBot;
  bool			multi;
  ////////////////////////////////////////////////////////////////////////////////
  /// Creation du contexte OpenGL et de la fenetre
  ////////////////////////////////////////////////////////////////////////////////
  MainMenu		*mainMenu = new MainMenu();
  mainMenu->initialize();
  bool			isLoad = mainMenu->menu();
  nbBot = mainMenu->getNbBot();
  preload = mainMenu->getPreload();
  multi = mainMenu->getMultiPlayer();
  ////////////////////
  //New game or load
  ///////////////////
  window_.create();
  camera_.initialize();
  map_ = new Map(this);
  try
    {
      if (isLoad == false)
	{
	  if (preload)
	    {
	      genMap();
	      map_->mapLoad("Maps/AleaMap.bbr");
	    }
	  else
	    map_->mapLoad(mainMenu->getMapName());
	  map_->setPause(true);
	  ////////////////////////////////////////////////////////////////////////////////
	  /// Ajout des objets heritant de AObject dans la liste
	  ////////////////////////////////////////////////////////////////////////////////

	  Player		*p1 = new Player(Player::P1, randPlacement(), "");
	  map_->setPlayerList(*p1);
	  if (multi)
	    {
	      Player		*p2 = new Player(Player::P2, randPlacement(), "");
	      map_->setPlayerList(*p2);
	    }
	  for (int i = 0; i != nbBot; i++)
	    {
	      std::ostringstream oss;
	      oss << i;
	      Player		*bot = new Player(Player::BOT, randPlacement(), oss.str());
	      map_->setPlayerList(*bot);
	      oss.clear();
	    }
	}
      else
	{
	  ///////////////////////////////////////////////////////////////////////
	  //Load from save
	  ///////////////////////////////////////////////////////////////////////
	  std::ifstream		iss("./Save/save.conf");
	  std::string		content;
	  int			loaded = 0;
	  int			idBot = 0;
	  int			nbPlayer1 = 0;
	  int			nbPlayer2 = 0;

	  map_->mapLoad("Save/save.bbr");
	  map_->setPause(true);
	  if (iss)
	    {
	      while (getline(iss, content))
		{
		  loaded++;
		  Player			*p;
		  std::string                   subStr;
		  std::stringstream             ss;
		  Player::Sort   		_sort;
		  Point				_loc;
		  int                           pop = 0;
		  int				x;
		  int				y;

		  subStr = content.substr(0, content.find(";"));
		  content = content.substr(content.find(";") + 1);
		  ss << subStr;
		  ss >> pop;
		  ss.clear();
		  if (pop >= 0 && pop <= 2)
		    {
		      if (pop == 0)
			{
			  _sort = Player::P1;
			  nbPlayer1++;
			}
		      else if (pop == 1)
			{
			  _sort = Player::P2;
			  nbPlayer2++;
			}
		      else
			_sort = Player::BOT;
		    }
		  else
		    {
		      std::cerr << "Corrupted back-up.\n";
		      exit(EXIT_FAILURE);
		    }
		  subStr = content.substr(0, content.find(";"));
		  content = content.substr(content.find(";") + 1);
		  ss << subStr;
		  ss >> pop;
		  ss.clear();
		  x = pop;
		  subStr = content.substr(0, content.find(";"));
		  content = content.substr(content.find(";") + 1);
		  ss << subStr;
		  ss >> pop;
		  ss.clear();
		  y = pop;
		  if (!map_->isEmpty(Point(x, y)))
		    {
		      std::cerr << "Corrupted location in back-up.\n";
		      exit (EXIT_FAILURE);
		    }
		  if (_sort == Player::P1)
		    p = new Player(Player::P1, Point(x, y), "");
		  else if (_sort == Player::P2)
		    p = new Player(Player::P2, Point(x, y), "");
		  else
		    {
		      std::ostringstream oss;
		      oss << idBot;
		      idBot++;
		      p = new Player(Player::BOT, Point(x, y), oss.str());
		    }
		  map_->setPlayerList(*p);
		}
	      iss.close();
	    }
	  if (loaded <= 0 || nbPlayer1 > 1 || nbPlayer2 > 1)
	    {
	      std::cerr << "Empty or corrupted back-up.\n";
	      exit(EXIT_FAILURE);
	    }
	  else
	    {
	      ThemeSound		*loaded = new ThemeSound("./Sound/Load.ogg");
	      loaded->initialize();
	    }
	}
      ////////////////////////////////////////////////////////////////////////////////
      /// Appel de la methode initialize des objets
      ////////////////////////////////////////////////////////////////////////////////
      this->objects_.push_back(map_);
      std::list<AObject*>::iterator	itb = this->objects_.begin();
      for (; itb != this->objects_.end(); ++itb)
	(*itb)->initialize();
    }
  catch (std::string const &err)
    {
      std::cerr << "ERROR: " << err << std::endl;
    }

}

Point			MyGame::randPlacement()
{

  int			x1 = (rand() % map_->getXSize());
  int			y1 = (rand() % map_->getYSize());
  Point			point1(x1, y1);

  while (!map_->isEmpty(point1))
    {
      x1 = (rand() % map_->getXSize());
      y1 = (rand() % map_->getYSize());
      point1 = Point(x1, y1);
    }
  return (point1);
}

void			MyGame::update(void)
{
  std::list<AObject*>::iterator itb = this->objects_.begin();
  ////////////////////////////////////////////////////////////////////////////////
  /// Appel de la methode update des objets
  ////////////////////////////////////////////////////////////////////////////////
  for (; itb != this->objects_.end(); ++itb)
    (*itb)->update(gameClock_, input_);
  camera_.update(gameClock_, input_, map_, window_);
}

void			MyGame::draw(void)
{
  ////////////////////////////////////////////////////////////////////////////////
  /// Vidage des buffers
  ////////////////////////////////////////////////////////////////////////////////
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.74f, 0.84f, 95.0f, 1.0f);
  glClearDepth(1.0f);
  std::list<AObject*>::iterator itb = this->objects_.begin();
  ////////////////////////////////////////////////////////////////////////////////
  /// Appel de la methode draw des objets
  ////////////////////////////////////////////////////////////////////////////////
  for (; itb != this->objects_.end(); ++itb)
    (*itb)->draw();
  ////////////////////////////////////////////////////////////////////////////////
  /// Affichage du rendu dans la fenetre
  ////////////////////////////////////////////////////////////////////////////////
  this->window_.display();
}

void			 MyGame::unload(void)
{
  ////////////////////////////////////////////////////////////////////////////////
  /// Liberation memoire des ressources allouees.
  ////////////////////////////////////////////////////////////////////////////////
  std::list<AObject*>::iterator itb = this->objects_.begin();
  for (; itb != this->objects_.end(); ++itb)
    delete *itb;
}

void			MyGame::close(void)
{
  this->window_.close();
}
