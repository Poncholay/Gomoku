##
## Makefile for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
##
## Made by Adrien Milcent
## Login   <adrien.milcent@epitech.eu>
##
## Started on  Wed Oct 12 17:48:57 2016 Adrien Milcent
## Last update Wed Oct 19 14:59:12 2016 Adrien Milcent
##

SRC =	main.cpp	\
			Goban.cpp \
			AI.cpp \
			Minmax.cpp \
			Referee.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	gomoku

CXXFLAGS	= -Wextra -W -Wall

CXX	= g++ -std=c++11

$(NAME): $(OBJ)
				$(CXX) $(CXXGLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
			rm -f *.o

fclean: clean
			rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
