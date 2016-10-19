//
// Referee.cpp for Gomoku in /home/albanbin/rendu/Gomoku/
//
// Made by Combaud Alban
// Login   <alban.combaud@epitech.eu@epitech.eu>
//
// Started on  Wed Oct 12 13:12:15 2016 Combaud Alban
// Last update Wed Oct 19 16:57:08 2016 Adrien Milcent
//

#include "Referee.hh"

Referee::Referee() : nbPairplayer1(0), nbPairplayer2(4)
{
}

Referee::~Referee()
{
}

Goban &Referee::getGoban(){
  return goban;
}

bool Referee::checkWinByPair(int x, int y, int p){
  int count = 0;
  int p2 = p == 1 ? 2 : 1;

  goban.addDraught(x, y, p);
  if ((p == 1 && nbPairplayer1 != 4) || (p == 2 && nbPairplayer2 != 4))
    return false;
  x - 3 >= 0 && goban[y][x - 3] == p && goban[y][x - 2] == p2 && goban[y][x - 1] == p2 ? count++ : 0;
  x + 3 < goban.getXBoard() && goban[y][x + 3] == p && goban[y][x + 2] == p2 && goban[y][x + 1] == p2 ? count++ : 0;
  y - 3 >= 0 && goban[y - 3][x] == p && goban[y - 2][x] == p2 && goban[y - 1][x] == p2 ? count++ : 0;
  y + 3 < goban.getYBoard() && goban[y + 3][x] == p && goban[y + 2][x] == p2 && goban[y + 1][x] == p2 ? count++ : 0;
  x - 3 >= 0 && y - 3 >= 0 && goban[y - 3][x - 3] == p && goban[y - 2][x - 2] == p2 && goban[y - 1][x - 1] == p2 ? count++ : 0;
  x + 3 < goban.getXBoard() && y - 3 >= 0 && goban[y - 3][x + 3] == p && goban[y - 2][x + 2] == p2 && goban[y - 1][x + 1] == p2 ? count++ : 0;
  x - 3 >= 0 && y + 3 < goban.getYBoard() && goban[y + 3][x - 3] == p && goban[y + 2][x - 2] == p2 && goban[y + 1][x - 1] == p2 ? count++ : 0;
  x + 3 < goban.getXBoard() && y + 3 < goban.getYBoard() && goban[y + 3][x + 3] == p && goban[y + 2][x + 2] == p2 && goban[y + 1][x + 1] == p2 ? count++ : 0;
  return (p == 1 && count + nbPairplayer1 >= 5 ? true : p == 2 && count + nbPairplayer2 >= 5 ? true : false);
}

void Referee::removePair(int x, int y, int x2, int y2, int player){
  goban.removeDraught(x, y);
  goban.removeDraught(x2, y2);
  player == 1 ? nbPairplayer1++ : nbPairplayer2++;
}

void Referee::updatePair(int x, int y, int p){
  int p2 = p == 1 ? 2 : 1;

  x - 3 >= 0 && goban[y][x - 3] == p && goban[y][x - 2] == p2 && goban[y][x - 1] == p2 ? removePair(x - 2, y, x - 1, y, p) : (void)0;
  x + 3 < goban.getXBoard() && goban[y][x + 3] == p && goban[y][x + 2] == p2 && goban[y][x + 1] == p2 ? removePair(x + 2, y, x + 1, y, p) : (void)0;
  y - 3 >= 0 && goban[y - 3][x] == p && goban[y - 2][x] == p2 && goban[y - 1][x] == p2 ? removePair(x, y - 2, x, y - 1, p) : (void)0;
  y + 3 < goban.getYBoard() && goban[y + 3][x] == p && goban[y + 2][x] == p2 && goban[y + 1][x] == p2 ? removePair(x, y + 2, x, y + 1, p) : (void)0;
  x - 3 >= 0 && y - 3 >= 0 && goban[y - 3][x - 3] == p && goban[y - 2][x - 2] == p2 && goban[y - 1][x - 1] == p2 ? removePair(x - 2, y - 2, x - 1, y - 1, p) : (void)0;
  x + 3 < goban.getXBoard() && y - 3 >= 0 && goban[y - 3][x + 3] == p && goban[y - 2][x + 2] == p2 && goban[y - 1][x + 1] == p2 ? removePair(x + 2, y - 2, x + 1, y - 1, p) : (void)0;
  x - 3 >= 0 && y + 3 < goban.getYBoard() && goban[y + 3][x - 3] == p && goban[y + 2][x - 2] == p2 && goban[y + 1][x - 1] == p2 ? removePair(x - 2, y + 2, x - 1, y + 1, p) : (void)0;
  x + 3 < goban.getXBoard() && y + 3 < goban.getYBoard() && goban[y + 3][x + 3] == p && goban[y + 2][x + 2] == p2 && goban[y + 1][x + 1] == p2 ?
  removePair(x + 2, y + 2, x + 1, y + 1, p) : (void)0;
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
  return false;
}

Result  Referee::checkPlay(int x, int y, int player){
  return (goban.getBoard()[y][x] ? REPLAY : checkWin(x, y, player));
}

Result  Referee::checkWin(int x, int y, int player){
  if (checkWinBy5(x, y, player))
    {
      goban.removeDraught(x, y);
      return WIN;
    }
  if (checkWinByPair(x, y, player))
    {
      goban.removeDraught(x, y);
      return WIN;
    }
  goban.removeDraught(x, y);
  return CONTINUE;
}
