/*
** Main.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Wed Oct 26 16:30:25 2016 wilmot_g
** Last update Wed Dec 07 10:19:11 2016 wilmot_g
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
  bool      *choices = new bool[6];

  for (int i = 0; i < 6; ++i)
    choices[i] = true;

  while (value != -1) {
    Menu menu;

    menu.setValues(value, volume, choices);
    if (!menu.isInit())
      return (-1);
    if ((value = menu.play()) == -1) {
      return (0);
    }
    volume = menu.getVolume();
    choices = menu.getRules();
    game.setAdvancedRules(choices[0]);
    game.setPlayers(value);
    game.play(0);
  }
  return (0);
}
