##
## Makefile for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
##
## Made by Adrien Milcent
## Login   <adrien.milcent@epitech.eu>
##
## Started on  Wed Oct 12 17:48:57 2016 Adrien Milcent
## Last update Tue Oct 18 14:07:25 2016 Adrien Milcent
##

SRC =	Main.cpp	\
			Goban.cpp \
			Referee.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	gomoku

CXXFLAGS	= -Wextra -W -Wall

CXX	= g++

$(NAME): $(OBJ)
				$(CXX) $(CXXGLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
			rm -f *.o

fclean: clean
			rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
