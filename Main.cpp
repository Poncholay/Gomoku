//
// main.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Wed Oct 12 17:25:59 2016 Adrien Milcent
// Last update Mon Oct 17 18:13:14 2016 Combaud Alban
//

#include "Referee.hh"

int main()
{
  Referee referee;

  referee.getGoban().addDraught(0, 7, 1);
  referee.getGoban().addDraught(1, 6, 1);
  referee.getGoban().addDraught(2, 5, 1);
  referee.getGoban().addDraught(3, 4, 1);



  std::cout << referee.getGoban()[2][1] << std::endl;

  if (referee.checkWin(4, 3, 1) == false){std::cout << "false" << std::endl;}
  else{std::cout << "true" << std::endl;}
  referee.getGoban().printBoard();
  return 0;
}
