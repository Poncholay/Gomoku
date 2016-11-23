/*
** Main.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Wed Oct 26 16:30:25 2016 wilmot_g
** Last update Wed Nov 23 21:34:15 2016 wilmot_g
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

  Menu      menu;
  Game      game;
  int       value = 0;

  if (!menu.isInit())
    return (-1);
  while (value != -1) {
    menu.resetValues();
    if ((value = menu.play()) == -1) {
      menu.endMenu();
      return (0);
    }
    menu.endMenu();
    if (value > 3) {
      game.setAdvancedRules(true);
      value -= 3;
    }
    else
      game.setAdvancedRules(false);
    game.setPlayers(value);
    game.play(0);
  }
  menu.endMenu();
  return (0);
}
