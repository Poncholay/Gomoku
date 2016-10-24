//
// main.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Wed Oct 12 17:25:59 2016 Adrien Milcent
// Last update Mon Oct 24 11:35:40 2016 Adrien Milcent
//

#include "Referee.hh"
#include "AI.hh"

int main()
{
  Referee referee;
  AI      ai1(referee.getGoban(), 1, 5);
  AI      ai2(referee.getGoban(), 2, 5);


  ai1.play(referee);

  ai2.play(referee);

  referee.getGoban().printBoard();
/*  referee.getGoban().addDraught(0, 7, 1);
  referee.getGoban().addDraught(1, 6, 1);
  referee.getGoban().addDraught(2, 5, 1);
  referee.getGoban().addDraught(3, 4, 1);*/
  //
  // referee.getGoban().addDraught(16, 16, 1);
  // referee.getGoban().addDraught(17, 16, 1);
  // referee.getGoban().addDraught(18, 16, 2);
  //
  // std::cout << referee.checkPlay(15, 16, 2) << std::endl;
  //
  // if (referee.checkPlay(15, 16, 2) == WIN)
  // {
  //   referee.getGoban().addDraught(15, 16, 2);
  //   referee.updatePair(15, 16, 2);
  // }
  // referee.getGoban().printBoard();
/*  if (referee.checkWin(2, 4, 1) == false){std::cout << "false" << std::endl;}
  else{std::cout << "true" << std::endl;}
    referee.getGoban().printBoard();*/
  return 0;
}
