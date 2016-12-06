/*
** AlphaBetaMinimax.hh for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Nov 28 14:14:53 2016 wilmot_g
** Last update Tue Dec 06 10:41:14 2016 wilmot_g
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
  int   scoreWin(Referee &, int, int) const;
  int   addScore(int &, int, bool, bool) const;
  int   evaluate(Referee &, int, bool, int, int, vector<vector<char> >) const;
  int   countSeries(Goban &, int) const;
  int   countDiags(Goban &, int) const;
  int   diagsBottomToTop(Goban &, int) const;
  int   diagsTopToBottom(Goban &, int) const;

  void  updatePair(Referee &, vector<pair<char, char> > &, int, int, int) const;
  void  restorePair(Referee &, vector<pair<char, char> >, int) const;
  void  saveChanges(Referee &, vector<pair<char, char> > &, int, int, int, int, int) const;

public:
  AlphaBetaMinimax(int);
  ~AlphaBetaMinimax();

  Coord loop(int, Referee &);
};

#endif /* !ALPHABETAMINIMAX_HH_ */
