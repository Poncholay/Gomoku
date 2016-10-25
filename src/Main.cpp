/*
** Main.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Sun Oct 16 15:32:40 2016 wilmot_g
** Last update Tue Oct 25 19:11:04 2016 wilmot_g
*/

#include <iostream>
#include "Displayer.hpp"
#include "Referee.hh"
#include "AI.hh"

using namespace std;

int           main(int ac, char **av) {
  Displayer   displayer;
  Goban       goban(displayer);
  Referee     referee(goban);
  AI          ai1(goban, 1, 1);
  AI          ai2(goban, 2, 1);
  int         ret = 0;

  int i = 0;
  bool turn = false;
  if (displayer.error() || !displayer.instanciate()) return -1;
  while (displayer.isRunning()) {
    if (!displayer.isAnimating())
      if (++i < 100)
        (turn = !turn) ? ai1.play(referee) : ai2.play(referee);
    if ((ret = displayer.display()) != 0) break;
  }
  return ret;
}
