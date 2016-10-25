/*
** Main.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Sun Oct 16 15:32:40 2016 wilmot_g
** Last update Tue Oct 25 13:21:05 2016 wilmot_g
*/

#include "Displayer.hpp"
#include "Referee.hh"

using namespace std;

int           main(int ac, char **av) {
  Displayer   d;
  Referee     r;
  int         ret = 0;

  r.getGoban().setDisplayer(Displayer);
  if (!d.instanciate()) return -1;
  while (d.isRunning()) {
    if (d.animate() == -1) return -1;
    if ((ret = d.display()) != 0) break;
  }
  return ret;
}
