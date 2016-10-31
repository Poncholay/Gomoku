/*
** Main.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Wed Oct 26 16:30:25 2016 wilmot_g
** Last update Mon Oct 31 20:35:55 2016 wilmot_g
*/

#include "Game.hh"
#include "Menu.hh"

int         main(int ac, char **av) {
  Menu      menu;

  if (!menu.isInit())
    return (-1);
  if (menu.play() == -1) {
    menu.endMenu();
    return (0);
  }
  menu.endMenu();

  Game      game;
  game.play(0);
}
