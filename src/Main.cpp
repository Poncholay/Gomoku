/*
** Main.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Wed Oct 26 16:30:25 2016 wilmot_g
** Last update Sun Dec 11 23:00:23 2016 wilmot_g
*/

#include "Sounds.hpp"
#include "Game.hh"
#include "Menu.hh"
#include "SdlError.hpp"

int         main(int ac, char **av) {
  try {
    Sounds::get().init();
  } catch(const SdlError &e) {
    cerr << e.what() << endl;
    return -1;
  }

  srand(time(0));

  Game      game;
  int       value = 1;
  float     volume = 0.5f;
  int       depth = 3;
  bool      *choices = new bool[7];

  for (int i = 0; i < 7; ++i) choices[i] = true;
  choices[3] = false;

  while (value != -1) {
    Menu *menu = new Menu;

    menu->setValues(value, volume, choices);
    if (!menu->isInit())
      return (-1);
    if ((value = menu->play()) == -1)
      return (0);
    choices = menu->getRules();
    volume = menu->getVolume();
    Sounds::get().setVolume(volume * 100);
    game.setPlayers(value);
    game.setAiDepth(menu->getDepth());
    game.setAdvancedRules(choices[0]);
    game.setBenchmark(choices[1]);
    game.setOptimisation(choices[2]);
    game.setOptiFive(choices[3]);
    game.setAlphaBeta(choices[4]);
    game.setCalculateRows(choices[5]);
    game.setCalculateDiagonals(choices[6]);
    delete menu;
    game.play();
  }
  return (0);
}
