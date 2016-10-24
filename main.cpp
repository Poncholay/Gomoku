//
// main.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Wed Oct 12 17:25:59 2016 Adrien Milcent
// Last update Mon Oct 24 14:37:21 2016 Combaud Alban
//

#include "Referee.hh"

int main()
{
  Referee referee;

/*  referee.getGoban().addDraught(0, 7, 1);
  referee.getGoban().addDraught(1, 6, 1);
  referee.getGoban().addDraught(2, 5, 1);
  referee.getGoban().addDraught(3, 4, 1);*/

  //referee.getGoban().addDraught(13, 16, 1);
//  referee.getGoban().addDraught(0, 11, 1);
//  referee.getGoban().addDraught(1, 10, 1);
  referee.getGoban().addDraught(2, 9, 1);
  referee.getGoban().addDraught(3, 8, 1);
//  referee.getGoban().addDraught(5, 4, 1);

/*  referee.getGoban().addDraught(5, 5, 1);
  referee.getGoban().addDraught(6, 5, 1);
  referee.getGoban().addDraught(7, 5, 1);
  referee.getGoban().addDraught(8, 5, 1);

  referee.getGoban().addDraught(6, 0, 2);
  referee.getGoban().addDraught(6, 1, 1);
  referee.getGoban().addDraught(6, 2, 1);*/
  //referee.getGoban().addDraught(4, 6, 2);
  //referee.getGoban().addDraught(5, 6, 2);
  //referee.getGoban().addDraught(6, 6, 2);
  //referee.getGoban().addDraught(7, 6, 2);
//  referee.getGoban().addDraught(8, 6, 2);
  //referee.getGoban().addDraught(9, 6, 2);

  referee.setPair(4, 2);
  std::cout << referee.checkPlay(0, 11, 1) << std::endl;

  referee.getGoban().printBoard();
  std::cout << std::endl;

//  referee.updatePair(14, 16, 2);
//  referee.getGoban().printBoard();
/*  if (referee.checkWin(2, 4, 1) == false){std::cout << "false" << std::endl;}
  else{std::cout << "true" << std::endl;}
    referee.getGoban().printBoard();*/
  return 0;
}
