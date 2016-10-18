//
// Referee.hh for Gomoku in /home/albanbin/rendu/Gomoku/
//
// Made by Combaud Alban
// Login   <alban.combaud@epitech.eu@epitech.eu>
//
// Started on  Wed Oct 12 13:15:51 2016 Combaud Alban
// Last update Mon Oct 17 15:52:02 2016 Combaud Alban
//

#ifndef REFEREE_HH_
# define REFEREE_HH_

#include "Goban.hh"
# include <vector>
# include <iostream>

class Referee
{
private:
  Goban goban;
public:
  Referee();
  ~Referee();

  bool  checkPlay(int, int);
  bool  checkWin(int, int, int);
  bool  checkWinBy5(int, int, int);
  Goban &getGoban();
};

#endif
