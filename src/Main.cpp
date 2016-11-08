/*
** Main.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Wed Oct 26 16:30:25 2016 wilmot_g
** Last update Tue Nov  8 13:33:20 2016 Adrien Milcent
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
  int value;

  if (!menu.isInit())
    return (-1);
  if ((value = menu.play()) == -1) {
    menu.endMenu();
    return (0);
  }
  menu.endMenu();

  Game      game;
  game.setPlayers(value);
  game.play(0);

  return 0;
}
