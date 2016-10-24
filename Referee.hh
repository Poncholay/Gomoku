//
// Referee.hh for Gomoku in /home/albanbin/rendu/Gomoku/
//
// Made by Combaud Alban
// Login   <alban.combaud@epitech.eu@epitech.eu>
//
// Started on  Wed Oct 12 13:15:51 2016 Combaud Alban
// Last update Sat Oct 22 18:31:54 2016 Combaud Alban
//

#ifndef REFEREE_HH_
# define REFEREE_HH_

#include "Goban.hh"
# include <vector>
# include <iostream>

enum Result {
WIN,
CONTINUE,
REPLAY  };

class Referee
{
private:
  Goban goban;
  int   nbPairplayer1;
  int   nbPairplayer2;
public:
  Referee();
  ~Referee();

  Result checkPlay(int, int, int);
  Result  checkWin(int, int, int);
  bool  checkRules(int, int, int);
  bool  checkWinBy5(int, int, int);
  int  checkWinByPair(int, int, int);
  void  setPair(int, int);
  void updatePair(int, int, int);
  void removePair(int, int, int, int, int);
  bool checkHorizon(int x, int y, int player, int max);
  bool checkVertical(int x, int y, int player, int max);
  bool checkDiagoDown(int x, int y, int player, int max);
  bool checkDiagoUp(int x, int y, int player, int max);
  Goban &getGoban();
};

#endif
