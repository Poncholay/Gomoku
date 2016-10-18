//
// Referee.cpp for Gomoku in /home/albanbin/rendu/Gomoku/
//
// Made by Combaud Alban
// Login   <alban.combaud@epitech.eu@epitech.eu>
//
// Started on  Wed Oct 12 13:12:15 2016 Combaud Alban
// Last update Tue Oct 18 15:59:28 2016 Combaud Alban
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
  int count = 0;
  goban.addDraught(x, y, player);

  for (int i = x - 5 <= 0 ? 0 : x - 5; i < goban.getXBoard(); i++) {
    goban[y][i] == player ? count++ : count = 0;
    if (count == 5)
      return true;}

  for (int i = y - 5 <= 0 ? 0 : y - 5; i < goban.getYBoard(); i++) {
    goban[i][x] == player ? count++ : count = 0;
    if (count == 5)
      return true;}

  int tmp = x < y ? (x - 5 <= 0 ? x : 5) : (y - 5 <= 0 ? y : 5);
  int xtmp = x - tmp;
  for (int ytmp = y - tmp; ytmp < goban.getYBoard() && xtmp < goban.getXBoard(); ytmp++) {
    goban[ytmp][xtmp++] == player ? count++ : count = 0;
    if (count == 5)
      return true;}

  tmp = x < y  && goban.getXBoard() - y  >= 5 ? (x - 5 <= 0 ? x : 5) :
   (y + 5 >= goban.getXBoard() ? goban.getXBoard() - 1 - y : 5);
  xtmp = x - tmp;
  for (int ytmp = y + tmp; ytmp >= 0 && xtmp < goban.getXBoard(); ytmp--) {
    goban[ytmp][xtmp++] == player ? count++ : count = 0;
    if (count == 5)
      return true;}

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
