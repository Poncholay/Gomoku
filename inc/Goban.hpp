//
// Goban.hh for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Wed Oct 12 15:26:56 2016 Adrien Milcent
// Last update Tue Nov 15 15:20:27 2016 Adrien Milcent
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

using namespace std;

class Goban {
private:
  // vector<vector<char> >      _board;
  vector<char>               _board;
  vector<char>               _heuristics;
  Displayer                  &_displayer;
  Referee                    *_r;
  int _xBoard;
  int _yBoard;

public:
  Goban(Displayer &, int xBoard = GOBAN_X, int yBoard = GOBAN_Y);
  Goban(Goban &);
  ~Goban();

  inline int operator()(int y, int x) {return _board[y * _xBoard + x];}

  Goban &operator=(Goban &);
  void setReferee(Referee *r);
  int getXBoard() const;
  int getYBoard() const;
  bool full() const;

  void setBoard(vector<char> &);
  void setHeuristic(vector<char> &);

  vector<char>  &getBoard();
  vector<char>  &getHeuristics();

  void addDraught(int, int, int, bool = false);
  void removeDraught(int, int, bool = false);
  int  updateWeights(int, int, vector<char> &) const;
  void revertWeights(int, int, int, vector<char> &) const;
  bool setHeuristicXY(int, int, int, bool, vector<char> &) const;

  Displayer &getDisplayer();
  void printBoard(int = -1, int = -1) const;
  void printHeuristic(vector<char> &) const;
};

#endif /* !GOBAN_HH_*/
