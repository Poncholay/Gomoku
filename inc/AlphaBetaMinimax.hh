/*
** AlphaBetaMinimax.hh for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Nov 28 14:14:53 2016 wilmot_g
** Last update Wed Nov 30 10:25:53 2016 Adrien Milcent
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

  int   score(Referee &, int) const;
  int   addScore(int &, int, bool, bool) const;
  int   scoreWin(Referee &, int, int) const;
  int   evaluate(Referee &, int, bool, int, int, vector<vector<char> >) const;
  // int   checkPair(vector<vector<int> > &, int, int, int, int);
  int   countSeries(Goban &, int) const;
  int   countDiags(Goban &, int) const;
  int   diagsBottomToTop(Goban &, int) const;
  int   diagsTopToBottom(Goban &, int) const;

  // void  checkBannedNodes(vector<vector<int> > &, Goban, int, int);
  // void  checkBannedLines(vector<vector<int> > &, Goban, int, int);
  // void  checkBannedDiagBTT(vector<vector<int> > &, Goban, int);
  // void  checkBannedDiagTTB(vector<vector<int> > &, Goban, int);

public:
  AlphaBetaMinimax(int);
  ~AlphaBetaMinimax();

  Coord loop(int, Referee &);
};

#endif /* !ALPHABETAMINIMAX_HH_ */
