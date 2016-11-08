//
// Referee.cpp for Gomoku in /home/albanbin/rendu/Gomoku/
//
// Made by Combaud Alban
// Login   <alban.combaud@epitech.eu@epitech.eu>
//
// Started on  Wed Oct 12 13:12:15 2016 Combaud Alban
// Last update Tue Nov  8 11:58:55 2016 Adrien Milcent
//

#include "Referee.hh"

Referee::Referee(Goban &poncholay) : nbPairplayer1(0), nbPairplayer2(0), goban(poncholay)
{
}

Referee::~Referee()
{
}

Goban &Referee::getGoban(){
  return goban;
}

void Referee::setPair(int nb, int player){
  (player == 1 ? nbPairplayer1 = nb : nbPairplayer2 = nb);
}

int Referee::checkWinByPair(int x, int y, int p){
  int count = 0;
  int p2 = p == 1 ? 2 : 1;

  /////////////////////// check draught ///////////////////
  if (goban.getBoard()[y][x])
    return (p == 1 ? nbPairplayer1 : nbPairplayer2);
  ////////////////////////////////////////////////////////

  goban.addDraught(x, y, p);

  x - 3 >= 0 && goban[y][x - 3] == p && goban[y][x - 2] == p2 && goban[y][x - 1] == p2 ? count++ : 0;
  x + 3 < goban.getXBoard() && goban[y][x + 3] == p && goban[y][x + 2] == p2 && goban[y][x + 1] == p2 ? count++ : 0;
  y - 3 >= 0 && goban[y - 3][x] == p && goban[y - 2][x] == p2 && goban[y - 1][x] == p2 ? count++ : 0;
  y + 3 < goban.getYBoard() && goban[y + 3][x] == p && goban[y + 2][x] == p2 && goban[y + 1][x] == p2 ? count++ : 0;
  x - 3 >= 0 && y - 3 >= 0 && goban[y - 3][x - 3] == p && goban[y - 2][x - 2] == p2 && goban[y - 1][x - 1] == p2 ? count++ : 0;
  x + 3 < goban.getXBoard() && y - 3 >= 0 && goban[y - 3][x + 3] == p && goban[y - 2][x + 2] == p2 && goban[y - 1][x + 1] == p2 ? count++ : 0;
  x - 3 >= 0 && y + 3 < goban.getYBoard() && goban[y + 3][x - 3] == p && goban[y + 2][x - 2] == p2 && goban[y + 1][x - 1] == p2 ? count++ : 0;
  x + 3 < goban.getXBoard() && y + 3 < goban.getYBoard() && goban[y + 3][x + 3] == p && goban[y + 2][x + 2] == p2 && goban[y + 1][x + 1] == p2 ? count++ : 0;
  goban.removeDraught(x, y);
  return (p == 1 ? count + nbPairplayer1 : count + nbPairplayer2);
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

bool Referee::checkHorizon(int x, int y, int player, int max){
  int p2 = player == 1 ? 2 : 1;
  for (int i = x + 4; i < goban.getXBoard() && goban[y][i] == player; i++) {
    goban[y][i] == player && i != x + 4 ? max++ : 0;}
  int begin = 5 - (10 - max);
  for (int i = x + begin; i < x + 5; ++i ){
      if ((y - 2  >= 0 && y + 1 < goban.getYBoard()) &&
          ((i - 2 >= 0 && i + 1 < goban.getXBoard() && goban[y - 2][i - 2] == p2 && goban[y - 1][i - 1] == player && checkWinByPair(i + 1, y + 1, p2) >= 5) ||
          (i - 2 >= 0 && i + 1 < goban.getXBoard() && goban[y + 1][i + 1] == p2 && goban[y - 1][i - 1] == player && checkWinByPair(i - 2, y - 2, p2) >= 5) ||
          (goban[y - 2][i] == p2 && goban[y - 1][i] == player && checkWinByPair(i, y + 1, p2) >= 5) ||
          (goban[y + 1][i] == p2 && goban[y - 1][i] == player && checkWinByPair(i, y - 2, p2) >= 5) ||
          (i - 1 >= 0 && i + 2 < goban.getXBoard() && goban[y - 2][i + 2] == p2 && goban[y - 1][i + 1] == player && checkWinByPair(i - 1, y + 1, p2) >= 5) ||
          (i - 1 >= 0 && i + 2 < goban.getXBoard() && goban[y + 1][i - 1] == p2 && goban[y - 1][i + 1] == player && checkWinByPair(i + 2, y - 2, p2) >= 5)))
            return false;
      if ((y - 1  >= 0 && y + 2 < goban.getYBoard()) &&
          ((i - 2 >= 0 && i + 1 < goban.getXBoard() && goban[y + 2][i - 2] == p2 && goban[y + 1][i - 1] == player && checkWinByPair(i + 1, y - 1, p2) >= 5) ||
          (i - 2 >= 0 && i + 1 < goban.getXBoard() && goban[y - 1][i + 1] == p2 && goban[y + 1][i - 1] == player && checkWinByPair(i - 2, y + 2, p2) >= 5) ||
          (goban[y + 2][i] == p2 && goban[y + 1][i] == player && checkWinByPair(i, y - 1, p2) >= 5) ||
          (goban[y - 1][i] == p2 && goban[y + 1][i] == player && checkWinByPair(i, y + 2, p2) >= 5) ||
          (i - 1 >= 0 && i + 2 < goban.getXBoard() && goban[y + 2][i + 2] == p2 && goban[y + 1][i + 1] == player && checkWinByPair(i - 1, y - 1, p2) >= 5) ||
          (i - 1 >= 0 && i + 2 < goban.getXBoard() && goban[y - 1][i - 1] == p2 && goban[y + 1][i + 1] == player && checkWinByPair(i + 2, y + 2, p2) >= 5)))
            return false;
          }
  return true;
}

bool Referee::checkVertical(int x, int y, int player, int max){
  int p2 = player == 1 ? 2 : 1;
  for (int i = y + 4; i < goban.getYBoard() && goban[i][x] == player; i++) {
    goban[i][x] == player && i != y + 4 ? max++ : 0;}
  int begin = 5 - (10 - max);
  for (int i = y + begin; i < y + 5; ++i ){
      if ((x - 2  >= 0 && x + 1 < goban.getXBoard()) &&
          ((i - 2 >= 0 && i + 1 < goban.getYBoard() && goban[i - 2][x - 2] == p2 && goban[i - 1][x - 1] == player && checkWinByPair(x + 1, i + 1, p2) >= 5) ||
          (i - 2 >= 0 && i + 1 < goban.getYBoard() && goban[i + 1][x + 1] == p2 && goban[i - 1][x - 1] == player && checkWinByPair(x - 2, i - 2, p2) >= 5) ||
          (goban[i][x - 2] == p2 && goban[i][x - 1] == player && checkWinByPair(x + 1, i, p2) >= 5) ||
          (goban[i][x + 1] == p2 && goban[i][x - 1] == player && checkWinByPair(x - 2, i, p2) >= 5) ||
          (i - 1 >= 0 && i + 2 < goban.getYBoard() && goban[i + 2][x - 2] == p2 && goban[i + 1][x - 1] == player && checkWinByPair(x + 1, i - 1, p2) >= 5) ||
          (i - 1 >= 0 && i + 2 < goban.getYBoard() && goban[i - 1][x + 1] == p2 && goban[i + 1][x - 1] == player && checkWinByPair(x - 2, i + 2, p2) >= 5)))
            return false;
      if ((x - 1  >= 0 && x + 2 < goban.getXBoard()) &&
          ((i - 2 >= 0 && i + 1 < goban.getYBoard() && goban[i - 2][x + 2] == p2 && goban[i - 1][x + 1] == player && checkWinByPair(x - 1, i + 1, p2) >= 5) ||
          (i - 2 >= 0 && i + 1 < goban.getYBoard() && goban[i + 1][x - 1] == p2 && goban[i - 1][x + 1] == player && checkWinByPair(x + 2, i - 2, p2) >= 5) ||
          (goban[i][x + 2] == p2 && goban[i][x + 1] == player && checkWinByPair(x - 1, i, p2) >= 5) ||
          (goban[i][x - 1] == p2 && goban[i][x + 1] == player && checkWinByPair(x + 2, i, p2) >= 5) ||
          (i - 1 >= 0 && i + 2 < goban.getYBoard() && goban[i + 2][x + 2] == p2 && goban[i + 1][x + 1] == player && checkWinByPair(x - 1, i - 1, p2) >= 5) ||
          (i - 1 >= 0 && i + 2 < goban.getYBoard() && goban[i - 1][x - 1] == p2 && goban[i + 1][x + 1] == player && checkWinByPair(x + 2, i + 2, p2) >= 5)))
            return false;
          }
  return true;
}

bool Referee::checkDiagoDown(int x, int y, int player, int max){
  int p2 = player == 1 ? 2 : 1;
  for (int i = y + 4; i < goban.getYBoard() && goban[i][x] == player && x < goban.getXBoard(); i++) {
    goban[i][x++] == player && i != y + 4 ? max++ : 0;}
  int begin = 5 - (10 - max);
  x += begin;
  for (int i = y + begin; i < y + 5; ++i ){
      if ((x - 2  >= 0 && x + 1 < goban.getXBoard() && i + 2 < goban.getYBoard() && i - 1 >= 0) &&
          ((goban[i + 2][x - 2] == p2 && goban[i + 1][x - 1] == player && checkWinByPair(x + 1, i - 1, p2) >= 5) ||
          (goban[i - 1][x + 1] == p2 && goban[i + 1][x - 1] == player && checkWinByPair(x - 2, i + 2, p2) >= 5) ||
          (goban[i][x - 2] == p2 && goban[i][x - 1] == player && checkWinByPair(x + 1, i, p2) >= 5) ||
          (goban[i][x + 1] == p2 && goban[i][x - 1] == player && checkWinByPair(x - 2, i, p2) >= 5) ||
          (goban[i + 2][x] == p2 && goban[i + 1][x] == player && checkWinByPair(x, i - 1, p2) >= 5) ||
          (goban[i - 1][x] == p2 && goban[i + 1][x] == player && checkWinByPair(x, i + 2, p2) >= 5)))
            return false;
            if ((i - 2  >= 0 && i + 1 < goban.getYBoard() && x + 2 < goban.getXBoard() && x - 1 >= 0) &&
                ((goban[i - 2][x + 2] == p2 && goban[i - 1][x + 1] == player && checkWinByPair(x - 1, i + 1, p2) >= 5) ||
                (goban[i + 1][x - 1] == p2 && goban[i - 1][x + 1] == player && checkWinByPair(x + 2, i - 2, p2) >= 5) ||
                (goban[i - 2][x] == p2 && goban[i - 1][x] == player && checkWinByPair(x, i + 1, p2) >= 5) ||
                (goban[i + 1][x] == p2 && goban[i - 1][x] == player && checkWinByPair(x, i - 2, p2) >= 5) ||
                (goban[i][x + 2] == p2 && goban[i][x + 1] == player && checkWinByPair(x - 1, i, p2) >= 5) ||
                (goban[i][x - 1] == p2 && goban[i][x + 1] == player && checkWinByPair(x + 2, i, p2) >= 5)))
            return false;
      ++x;
    }
  return true;
}

bool Referee::checkDiagoUp(int x, int y, int player, int max){
  int p2 = player == 1 ? 2 : 1;
  for (int i = y - 4; i >= 0 && goban[i][x] == player && x < goban.getXBoard(); i--) {
    goban[i][x++] == player && i != y - 4 ? max++ : 0;}
  int begin = 5 - (10 - max);
  x += begin;
  for (int i = y - begin; i > y - 5; --i ){
      if ((x - 2  >= 0 && x + 1 < goban.getXBoard() && i + 1 < goban.getYBoard() && i - 2 >= 0) &&
          ((goban[i - 2][x - 2] == p2 && goban[i - 1][x - 1] == player && checkWinByPair(x + 1, i + 1, p2) >= 5) ||
          (goban[i + 1][x + 1] == p2 && goban[i - 1][x - 1] == player && checkWinByPair(x - 2, i - 2, p2) >= 5) ||
          (goban[i][x - 2] == p2 && goban[i][x - 1] == player && checkWinByPair(x + 1, i, p2) >= 5) ||
          (goban[i][x + 1] == p2 && goban[i][x - 1] == player && checkWinByPair(x - 2, i, p2) >= 5) ||
          (goban[i - 2][x] == p2 && goban[i - 1][x] == player && checkWinByPair(x, i + 1, p2) >= 5) ||
          (goban[i + 1][x] == p2 && goban[i - 1][x] == player && checkWinByPair(x, i - 2, p2) >= 5)))
            return false;
      if ((i - 1  >= 0 && i + 2 < goban.getYBoard() && x + 2 < goban.getXBoard() && x - 1 >= 0) &&
                ((goban[i + 2][x + 2] == p2 && goban[i + 1][x + 1] == player && checkWinByPair(x - 1, i - 1, p2) >= 5) ||
                (goban[i - 1][x - 1] == p2 && goban[i + 1][x + 1] == player && checkWinByPair(x + 2, i + 2, p2) >= 5) ||
                (goban[i + 2][x] == p2 && goban[i + 1][x] == player && checkWinByPair(x, i - 1, p2) >= 5) ||
                (goban[i - 1][x] == p2 && goban[i + 1][x] == player && checkWinByPair(x, i + 2, p2) >= 5) ||
                (goban[i][x + 2] == p2 && goban[i][x + 1] == player && checkWinByPair(x - 1, i, p2) >= 5) ||
                (goban[i][x - 1] == p2 && goban[i][x + 1] == player && checkWinByPair(x + 2, i, p2) >= 5)))
            return false;
      ++x;
    }
  return true;
}

bool Referee::checkWinBy5(int x, int y, int player){
  goban.addDraught(x, y, player);

  std::cout << "x = " << x << " y = " << y << std::endl;
  int xsave = x - 5 <= 0 ? 0 : x - 5;
  int count = 0;
  for (int i = xsave; i < goban.getXBoard(); i++) {
    count == 0 ? xsave = i : 0;
    goban[y][i] == player ? count++ : count = 0;
    if (count >= 5 && checkHorizon(xsave, y, player, 5))
      return true;
    else if (count >= 5)
      i = goban.getXBoard();
  }

  int ysave = y - 5 <= 0 ? 0 : y - 5;
  count = 0;
  for (int i = ysave; i < goban.getYBoard(); i++) {
    count == 0 ? ysave = i : 0;
    goban[i][x] == player ? count++ : count = 0;
    if (count >= 5 && checkVertical(x, ysave, player, 5))
      return true;
    else if (count >= 5)
      i = goban.getYBoard();
    }

  count = 0;

  int tmp = x < y ? (x - 5 <= 0 ? x : 5) : (y - 5 <= 0 ? y : 5);
  int xtmp = x - tmp;
  for (int ytmp = y - tmp; ytmp < goban.getYBoard() && xtmp < goban.getXBoard(); ytmp++) {
    count == 0 ? xsave = xtmp, ysave = ytmp : 0;
    goban[ytmp][xtmp++] == player ? count++ : count = 0;
    if (count >= 5 && checkDiagoDown(xsave, ysave, player, 5))
      return true;
    else if (count >= 5)
      ytmp = goban.getYBoard();
  }

  count = 0;

  tmp = x - 4 >= 0 ? (y + 4 < goban.getYBoard() ? 4 : goban.getYBoard() - y - 1) :
  (y + x < goban.getYBoard() ? x : goban.getYBoard() - y - 1);

  xtmp = x - tmp;

  for (int ytmp = y + tmp; ytmp >= 0 && xtmp < goban.getXBoard(); ytmp--) {
    count == 0 ? xsave = xtmp, ysave = ytmp : 0;
    goban[ytmp][xtmp++] == player ? count++ : count = 0;
    if (count == 5 && checkDiagoUp(xsave, ysave, player, 5))
      return true;
    else if (count >= 5)
      ytmp = -1;
    }
  return false;
}

bool  Referee::checkRules(int x, int y, int player, int check) {
  int beginx = x - 3 < 0 ? 0 : x - 3;
  int beginy = y - 3 < 0 ? 0 : y - 3;

  std::vector<std::vector<int> > board = goban.getBoard();

  goban.addDraught(x, y, player);

  for (int i = beginx; i <= x; i++) {
    if (i + 4 < goban.getXBoard() && !board[y][i] && board[y][i + 1] == player && board[y][i + 2] == player &&
      board[y][i + 3] == player && !board[y][i + 4]) {
          if (!check && (checkRules(i + 1, y, player, 1) || checkRules(i + 2, y, player, 1) || checkRules(i + 3, y, player, 1))) {
            return true;}
          if (check && check != 1){return true;}
      }
    if (i - 1 >= 0 && i + 4 < goban.getXBoard() && !board[y][i - 1] && board[y][i] == player && board[y][i + 1] == player &&
      !board[y][i + 2] && board[y][i + 3] == player && !board[y][i + 4]) {
        if (!check && (checkRules(i, y, player, 1) || checkRules(i + 1, y, player, 1) || checkRules(i + 3, y, player, 1))) {
          return true;}
        if (check && check != 1){return true;}
      }
    if (i - 1 >= 0 && i + 4 < goban.getXBoard() && !board[y][i - 1] && board[y][i] == player && board[y][i + 1] == 0 &&
      board[y][i + 2] == player && board[y][i + 3] == player && !board[y][i + 4])
      {
        if (!check && (checkRules(i, y, player, 1) || checkRules(i + 2, y, player, 1) || checkRules(i + 3, y, player, 1))) {
          return true;}
        if (check && check != 1){return true;}
      }
  }

  for (int i = beginy; i <= y; i++) {
    if (i + 4 < goban.getYBoard() && !board[i][x] && board[i + 1][x] == player && board[i + 2][x] == player &&
      board[i + 3][x] == player && !board[i + 4][x]){
        if (!check && (checkRules(x, i + 1, player, 2) || checkRules(x, i + 2, player, 2) || checkRules(x, i + 3, player, 2))) {
          return true;}
        if (check && check != 2){return true;}
      }
    if (i - 1 >= 0 && i + 4 < goban.getYBoard() && !board[i - 1][x] && board[i][x] == player && board[i + 1][x] == player &&
      board[i + 2][x] == 0 && board[i + 3][x] == player && !board[i + 4][x]) {
        if (!check && (checkRules(x, i, player, 2) || checkRules(x, i + 1, player, 2) || checkRules(x, i + 3, player, 2))) {
          return true;}
        if (check && check != 2){return true;}
      }
    if (i - 1 >= 0 && i + 4 < goban.getYBoard() && !board[i - 1][x] && board[i][x] == player && board[i + 1][x] == 0 &&
      board[i + 2][x] == player && board[i + 3][x] == player && !board[i + 4][x]) {
        if (!check && (checkRules(x, i, player, 2) || checkRules(x, i + 2, player, 2) || checkRules(x, i + 3, player, 2))) {
          return true;}
        if (check && check != 2){return true;}
      }
  }

  int tmp = x < y ? (x - 3 <= 0 ? x : 3) : (y - 3 <= 0 ? y : 3);

  for (int i = y - tmp, a = x - tmp; i <= y && a <= x; i++, a++) {
    if (i + 4 < goban.getYBoard() && a + 4 < goban.getXBoard() && !board[i][a] && board[i + 1][a + 1] == player && board[i + 2][a + 2] == player &&
      board[i + 3][a + 3] == player && !board[i + 4][a + 4]) {
        if (!check && (checkRules(a + 1, i + 1, player, 3) || checkRules(a + 2, i + 2, player, 3) || checkRules(a + 3, i + 3, player, 3))) {
          return true;}
        if (check && check != 3){return true;}
      }
    if (i - 1 >= 0 && a - 1 >= 0 && i + 4 < goban.getYBoard() && a + 4 < goban.getXBoard() &&
     !board[i - 1][a - 1] && board[i][a] == player && board[i + 1][a + 1] == player &&
      board[i + 2][a + 2] == 0 && board[i + 3][a + 3] == player && !board[i + 4][a + 4]) {
        if (!check && (checkRules(a, i, player, 3) || checkRules(a + 1, i + 1, player, 3) || checkRules(a + 3, i + 3, player, 3))) {
          return true;}
        if (check && check != 3){return true;}
      }
    if (i - 1 >= 0 && i + 4 < goban.getYBoard() && a - 1 >= 0 && a + 4 < goban.getXBoard() && !board[i - 1][a - 1] && board[i][a] == player && board[i + 1][a + 1] == 0 &&
      board[i + 2][a + 2] == player && board[i + 3][a + 3] == player && !board[i + 4][a + 4]) {
        if (!check && (checkRules(a, i, player, 3) || checkRules(a + 2, i + 2, player, 3) || checkRules(a + 3, i + 3, player, 3))) {
          return true;}
        if (check && check != 3){return true;}
      }
    }

    tmp = x - 4 >= 0 ? (y + 4 < goban.getYBoard() ? 4 : goban.getYBoard() - y - 1) :
    (y + x < goban.getYBoard() ? x : goban.getYBoard() - y - 1);

    for (int i = y + tmp, a = x - tmp; i >= 0 && a < goban.getXBoard(); i--, a++) {
      if (i - 4 >= 0 && a + 4 < goban.getXBoard() && !board[i][a] && board[i - 1][a + 1] == player && board[i - 2][a + 2] == player &&
        board[i - 3][a + 3] == player && !board[i - 4][a + 4]) {
          if (!check && (checkRules(a + 1, i - 1, player, 4) || checkRules(a + 2, i - 2, player, 4) || checkRules(a + 3, i - 3, player, 4))) {
            return true;}
          if (check && check != 4){return true;}
        }
      if (i + 1 < goban.getYBoard() && a - 1 >= 0 && i - 4 >= 0 && a + 4 < goban.getXBoard() &&
        !board[i + 1][a - 1] && board[i][a] == player && board[i - 1][a + 1] == player &&
        board[i - 2][a + 2] == 0 && board[i - 3][a + 3] == player && !board[i - 4][a + 4]) {
          if (!check && (checkRules(a, i, player, 4) || checkRules(a + 1, i - 1, player, 4) || checkRules(a + 3, i - 3, player, 4))) {
            return true;}
          if (check && check != 4){return true;}
        }
      if (i + 1 < goban.getYBoard() && i - 4 >= 0 && a - 1 >= 0 && a + 4 < goban.getXBoard() && !board[i + 1][a - 1] && board[i][a] == player && board[i - 1][a + 1] == 0 &&
        board[i - 2][a + 2] == player && board[i - 3][a + 3] == player && !board[i - 4][a + 4]) {
          if (!check && (checkRules(a, i, player, 4) || checkRules(a + 2, i - 2, player, 4) || checkRules(a + 3, i - 3, player, 4))) {
            return true;}
          if (check && check != 4){return true;}
        }
      }

  return false;
}

Result  Referee::checkPlay(int x, int y, int player) {
  return (goban.getBoard()[y][x] ? REPLAY : checkWin(x, y, player));
}

Result  Referee::checkWin(int x, int y, int player) {
  if (checkWinByPair(x, y, player) >= 5) {
      goban.removeDraught(x, y);
      return WIN;
    }
  if (checkWinBy5(x, y, player)) {
      goban.removeDraught(x, y);
      return WIN;
    }
  if (checkRules(x, y, player, 0)) {
    goban.removeDraught(x, y);
    return REPLAY;
  }
  goban.removeDraught(x, y);
  return CONTINUE;
}
