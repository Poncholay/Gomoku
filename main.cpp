//
// main.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Wed Oct 12 17:25:59 2016 Adrien Milcent
// Last update Tue Oct 25 13:36:43 2016 Adrien Milcent
//

#include "Referee.hh"
#include "AI.hh"

int main()
{
  Goban goban(6, 6);
  Referee referee(goban);
  AI      ai1(goban, 1, 1);
  AI      ai2(goban, 2, 1);


  ai1.play(referee);
  //ai2.play(referee);
  //goban.addDraught(1, 0, 2);

  ai1.play(referee);
  //ai2.play(referee);
  //
  //goban.addDraught(0, 2, 2);
  ai1.play(referee);
  //ai2.play(referee);
  //goban.addDraught(2, 1, 2);
  ai1.play(referee);
  //ai2.play(referee);
  //
  ai1.play(referee);
  //ai2.play(referee);

  goban.printBoard();

  return 0;
}
