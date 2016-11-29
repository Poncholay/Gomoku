/*
** AlphaBetaMinimax.hh for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Nov 28 14:14:53 2016 wilmot_g
** Last update Tue Nov 29 16:34:27 2016 Adrien Milcent
*/

#ifndef ALPHABETAMINIMAX_HH_
# define ALPHABETAMINIMAX_HH_

# include <iostream>
# include <string>
# include <vector>

# include "Referee.hh"

using namespace std;

typedef pair<int, int> Coord;

# define MAX 100000000

class AlphaBetaMinimax {
private:
  int _nbTurn;
  int _player;
  int _opponent;
  Coord _win;

  int   score(Referee &, int, bool, int);
  int   evaluate(Referee &, int, bool, bool, int, int);
  int   checkPair(vector<vector<int> > &, int, int, int, int);
  bool  calculate(Goban &, int, int);
  int   countSeries(Goban &, int);
  int   countDiags(Goban &, int);
  int   diagsBottomToTop(Goban &, int);
  int   diagsTopToBottom(Goban &, int);

  void  checkBannedNodes(vector<vector<int> > &, Goban, int, int);
  void  checkBannedLines(vector<vector<int> > &, Goban, int, int);
  void  checkBannedDiagBTT(vector<vector<int> > &, Goban, int);
  void  checkBannedDiagTTB(vector<vector<int> > &, Goban, int);

public:
  AlphaBetaMinimax(int);
  ~AlphaBetaMinimax();

  Coord loop(vector<vector<int> > &, int, Referee &);
};

#endif /* !ALPHABETAMINIMAX_HH_ */
