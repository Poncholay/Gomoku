//
// Goban.hh for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Wed Oct 12 15:26:56 2016 Adrien Milcent
// Last update Mon Oct 24 15:41:37 2016 Adrien Milcent
//

#ifndef GOBAN_HH_
# define GOBAN_HH_

# include <iostream>
# include <string>
# include <vector>
# include "Referee.hh"
# include "Displayer.hpp"
# include "Dimensions.hh"

class Displayer;
class Referee;

class Goban {
private:
  std::vector<std::vector<int> >      _board;
  Displayer                           &_displayer;
  Referee                             *_r;
  int _xBoard;
  int _yBoard;

public:
  Goban(Displayer &, int xBoard = GOBAN_X, int yBoard = GOBAN_Y);
  Goban(Goban &);
  ~Goban();

  Goban &operator=(Goban &);
  std::vector<int>   &operator[](int);
  void setReferee(Referee *r);
  int getXBoard() const;
  int getYBoard() const;
  bool full() const;
  std::vector<std::vector<int> >  getBoard() const;

  void addDraught(int, int, int, bool = false);
  void removeDraught(int, int, bool = false);

  Displayer &getDisplayer();
  void printBoard() const;
};

#endif /* !GOBAN_HH_*/
