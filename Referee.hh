//
// Referee.hh for Gomoku in /home/albanbin/rendu/Gomoku/
//
// Made by Combaud Alban
// Login   <alban.combaud@epitech.eu@epitech.eu>
//
// Started on  Wed Oct 12 13:15:51 2016 Combaud Alban
// Last update Tue Oct 18 17:45:33 2016 Combaud Alban
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
  bool  checkWinBy5(int, int, int);
  bool  checkWinByPair(int, int, int);
  void updatePair(int, int, int);
  void removePair(int, int, int, int, int);
  Goban &getGoban();
};

#endif
