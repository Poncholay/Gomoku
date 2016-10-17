//
// Referee.cpp for Gomoku in /home/albanbin/rendu/Gomoku/
//
// Made by Combaud Alban
// Login   <alban.combaud@epitech.eu@epitech.eu>
//
// Started on  Wed Oct 12 13:12:15 2016 Combaud Alban
// Last update Mon Oct 17 18:15:22 2016 Combaud Alban
//

#include "Referee.hh"

Referee::Referee()
{
}

Referee::~Referee()
{
}

Goban &Referee::getGoban(){
  return goban;
}

bool Referee::checkWinBy5(int x, int y, int player){
  int x_temp = x - 5 <= 0 ? 0 : x - 5;
  int y_temp = y - 5 <= 0 ? 0 : y - 5;
  int count = 0;

  goban.addDraught(x, y, player);

  for (int i = x_temp; i < goban.getXBoard(); i++) {
    goban[y][i] == player ? count++ : count = 0;
    if (count == 5)
      return true;
    }

  for (int i = y_temp; i < goban.getYBoard(); i++) {
    goban[i][x] == player ? count++ : count = 0;
    if (count == 5)
      return true;
    }

  int a = x < y ? (x - 5 <= 0 ? 0 : x - 5) : x - y;
  for (int i = y < x ? (y - 5 <= 0 ? 0 : y - 5) : y - x; i < goban.getYBoard(); i++) {
    goban[i][a++] == player ? count++ : count = 0;
    if (count == 5)
      return true;
    }

  a = x < 5 ? y + x : y + 5;
  for (int i = x <= 5 ? 0 : x - 5; i < goban.getYBoard(); i++) {
    std::cout << "a = " << a << " i = " << i << std::endl;
    goban[a--][i] == player ? count++ : count = 0;
    if (count == 5)
      return true;
    }

  goban.removeDraught(x, y);
  return false;
}

bool  Referee::checkPlay(int x, int y){
  return (goban.getBoard()[y][x] ? false : true);
}

bool  Referee::checkWin(int x, int y, int player){
  if (checkWinBy5(x, y, player))
    return true;
  return false;
}
