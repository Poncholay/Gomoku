//
// main.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Wed Oct 12 17:25:59 2016 Adrien Milcent
// Last update Tue Oct 18 12:45:50 2016 Adrien Milcent
//

#include "Goban.hh"

int main()
{
  Goban goban;

  goban.addDraught(0, 7, 1);
  goban.addDraught(1, 6, 1);

  goban.printBoard();
  return 0;
}
