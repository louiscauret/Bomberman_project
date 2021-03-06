//
// Score.cpp for  in /home/quesne_p//Bomber/Bomber
//
// Made by pierre quesnel
// Login   <quesne_p@epitech.net>
//
// Started on  Thu Jun  6 15:25:06 2013 pierre quesnel
// Last update Sun Jun  9 18:32:05 2013 louis cauret
//

#include				"Score.hpp"

void					Score::ScoreStat()
{
  std::ifstream				file("./Score/score.txt", std::ios::in);

  if (file)
    {
      std::string                       content;

      while (getline(file, content))
        {
	  std::string			subStr;
	  std::stringstream		ss;
	  int				pop = 0;

	  subStr = content.substr(0, content.find(";"));
	  content = content.substr(content.find(";") + 1);
	  ss << subStr;
	  ss >> pop;
	  ss.clear();
	  scoreList.push_back(pop);
	}
      file.close();
    }
  else
    std::cerr << "no previous score" << std::endl;
}

int		Score::getMaxScore()
{
  int		max = 0;

  for (int i = 0; i < (int)scoreList.size(); ++i)
    {
      if (max < scoreList[i])
	max = scoreList[i];
    }
  return (max);
}

void		Score::insertScore(int const & score)
{
  std::ofstream fichier("./Score/score.txt", std::ios::out| std::ios::app);

  if(fichier)
    {
      fichier << score;
      fichier << ";\n";
    }
  else
    throw std::string("Scoring log fail.");
}
