//
// main.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Wed Oct 12 17:25:59 2016 Adrien Milcent
// Last update Tue Nov  8 11:54:21 2016 Adrien Milcent
//

#include "Referee.hh"
#include "AI.hh"

int main()
{
  Goban goban(6, 6);
  Referee referee(goban);
  AI      ai1(goban, 1, 2);
  AI      ai2(goban, 2, 2);


  while (1) {
    //std::cout << "coucou" << std::endl;
    ai1.play(referee);
    //std::cout << "coucou1" << std::endl;
    ai2.play(referee);
    //std::cout << "coucou2" << std::endl;
    goban.printBoard();
  }

  goban.printBoard();

  return 0;
}
