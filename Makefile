##
## Makefile for plazza in /home/quesne_p//projet/plazza
## 
## Made by pierre quesnel
## Login   <quesne_p@epitech.net>
## 
## Started on  Tue Apr 16 13:42:33 2013 pierre quesnel
## Last update Sun Jun  9 18:25:03 2013 louis cauret
##

CC      	= g++

RM      	= rm -f

INCLUDE		= ./include/
LIBGDL_INCLUDE	= libgdl/include
LIBGDL_LIB	= libgdl/lib

CXXFLAGS 	= -W -Wextra -Wall
CXXFLAGS	+= -I$(LIBGDL_INCLUDE)
CXXFLAGS	+= -I$(INCLUDE)

LDFLAGS		= -L$(LIBGDL_LIB) -Wl,--rpath=$(LIBGDL_LIB)
LDFLAGS		+= -lpthread -lgdl_gl -lGL -lGLU -g3 -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

NAME    	= bomberman

GAME_DIR	= ./Game/
ITEM_DIR	= ./Item/
PLAYER_DIR	= ./Player/
MAP_DIR		= ./Maps/
SOUND_DIR	= ./Sound/
MENU_DIR	= ./Menu/
SCORE_DIR	= ./Score/

SRCS    	= $(GAME_DIR)main.cpp		\
		  $(GAME_DIR)MyGame.cpp		\
		  $(PLAYER_DIR)Player.cpp	\
		  $(GAME_DIR)Point.cpp		\
		  $(GAME_DIR)Vector3f.cpp	\
		  $(GAME_DIR)Camera.cpp		\
		  $(GAME_DIR)Map.cpp		\
		  $(ITEM_DIR)Bomb.cpp		\
		  $(MAP_DIR)AleaMap.cpp		\
		  $(SOUND_DIR)ThemeSound.cpp	\
		  $(MENU_DIR)Menu.cpp		\
		  $(SCORE_DIR)Score.cpp		\
		  $(MENU_DIR)Intro.cpp		\
		  $(MENU_DIR)EndMenu.cpp	\
		  $(MENU_DIR)Options.cpp

OBJS	    	= $(SRCS:.cpp=.o)

$(NAME):	  $(OBJS)
		  $(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all: 		  $(NAME)

clean:
		  $(RM) $(OBJS) *~ *#

fclean: 	  clean
		  $(RM) $(NAME)

re: 		  fclean all

.PHONY: 	  all clean fclean re