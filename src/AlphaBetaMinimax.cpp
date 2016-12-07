/*
** AlphaBetaMinimax.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Nov 28 13:51:42 2016 wilmot_g
** Last update Wed Dec 07 10:34:17 2016 wilmot_g
*/

#include <functional>

#include "AlphaBetaMinimax.hh"
#include "Referee.hh"
#include "unistd.h"

AlphaBetaMinimax::AlphaBetaMinimax(int nbTurn) {
  _nbTurn = nbTurn;
  _multiplier = vector<float>(5, 0);
  for (float &m : _multiplier)
    m = (1000 + rand() % 4000) / 1000.0;
}

AlphaBetaMinimax::~AlphaBetaMinimax() {}

Coord   AlphaBetaMinimax::loop(int player, Referee &r) {
  int v = -MAX;
  int alpha = -MAX;
  Goban &g = r.getGoban();
  vector<vector<char> > heuristics = g.getHeuristics();

  _player = player;
  _opponent = player == 1 ? 2 : 1;
  _win = Coord(-1, -1);
  for (int y = 0; y < g.getYMaxCheck(); y++)
    for (int x = 0; x < g.getXMaxCheck(); x++)
      if (!heuristics[y][x]) {
        int res = r.checkPlay(x, y, player);
        if (res == WIN) {
          //
          // cout << "Winning : [" << y << "][" << x << "]" << endl << endl << endl << endl;
          //
          return Coord(x, y);
        }
        if (res == WIN_INVERSE)
          res == REPLAY;
        if (res != REPLAY && res != -1) {
          vector<pair<char, char> > pairs;
          //
          // cout << "____________________________" << endl;
          // cout << "[" << y << "][" << x << "]" << endl;
          // g.printHeuristic(heuristics);
          //
          g.addDraught(x, y, player);
          //
          // g.printBoard(x, y);
          // cout << "____________________________" << endl;
          //
          updatePair(r, pairs, x, y, _player);
          int changes = r.getGoban().updateWeights(x, y, heuristics);
          //
          // int e = evaluate(r, _nbTurn - 1, false, alpha, MAX, heuristics);
          // cout << "Valeur : " << e << endl;
          // v = max(v, e);
          //
          v = max(v, evaluate(r, _nbTurn - 1, false, alpha, MAX, heuristics));
          restorePair(r, pairs, _opponent);
          g.removeDraught(x, y);
          g.revertWeights(x, y, changes, heuristics);
          if (v > alpha)
            _win = Coord(x, y);
          alpha = max(v, alpha);
        }
      }
  cout << "Alpha  : " << alpha << endl;
  cout << "Result : [" << get<1>(_win) << "][" << get<0>(_win) << "]" << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
  //
  return _win;
}

void    AlphaBetaMinimax::saveChanges(Referee &r, vector<pair<char, char> > &changes, int x1, int y1, int x2, int y2, int p) const {
  r.removePair(x1, y1, x2, y2, p, false);
  changes.push_back(make_pair(x1, y1));
  changes.push_back(make_pair(x2, y2));
}

void    AlphaBetaMinimax::restorePair(Referee &r, vector<pair<char, char> > changes, int player) const {
  for (auto it = changes.begin(); it != changes.end(); it++) {
    r.getGoban().addDraught((*it).first, (*it).second, player);
  }
  for (unsigned int i = 0; i < (changes.size() / 2); i++)
    r.undoNbPair(player == 1 ? 2 : 1);
}

void    AlphaBetaMinimax::updatePair(Referee &r, vector<pair<char, char> > &changes, int x, int y, int p) const {
  int p2 = p == 1 ? 2 : 1;
  Goban goban = r.getGoban();

  x - 3 >= 0 && goban[y][x - 3] == p && goban[y][x - 2] == p2 && goban[y][x - 1] == p2 ? saveChanges(r, changes, x - 2, y, x - 1, y, p) : (void)0;
  x + 3 < goban.getXBoard() && goban[y][x + 3] == p && goban[y][x + 2] == p2 && goban[y][x + 1] == p2 ? saveChanges(r, changes, x + 2, y, x + 1, y, p) : (void)0;
  y - 3 >= 0 && goban[y - 3][x] == p && goban[y - 2][x] == p2 && goban[y - 1][x] == p2 ? saveChanges(r, changes, x, y - 2, x, y - 1, p) : (void)0;
  y + 3 < goban.getYBoard() && goban[y + 3][x] == p && goban[y + 2][x] == p2 && goban[y + 1][x] == p2 ? saveChanges(r, changes, x, y + 2, x, y + 1, p) : (void)0;
  x - 3 >= 0 && y - 3 >= 0 && goban[y - 3][x - 3] == p && goban[y - 2][x - 2] == p2 && goban[y - 1][x - 1] == p2 ? saveChanges(r, changes, x - 2, y - 2, x - 1, y - 1, p) : (void)0;
  x + 3 < goban.getXBoard() && y - 3 >= 0 && goban[y - 3][x + 3] == p && goban[y - 2][x + 2] == p2 && goban[y - 1][x + 1] == p2 ? saveChanges(r, changes, x + 2, y - 2, x + 1, y - 1, p) : (void)0;
  x - 3 >= 0 && y + 3 < goban.getYBoard() && goban[y + 3][x - 3] == p && goban[y + 2][x - 2] == p2 && goban[y + 1][x - 1] == p2 ? saveChanges(r, changes, x - 2, y + 2, x - 1, y + 1, p) : (void)0;
  x + 3 < goban.getXBoard() && y + 3 < goban.getYBoard() && goban[y + 3][x + 3] == p && goban[y + 2][x + 2] == p2 && goban[y + 1][x + 1] == p2 ? saveChanges(r, changes, x + 2, y + 2, x + 1, y + 1, p) : (void)0;
}

int     AlphaBetaMinimax::evaluate(Referee &r, int depth, bool maxing, int alpha, int beta, vector<vector<char> > heuristics) const {
  int   v;
  int   turn;
  Goban &g = r.getGoban();

  //
  // static int cacaX = -1;
  // static int pipiY = -1;
  //

  if (!depth) {
    //
    // cout << "[" << pipiY << "][" << cacaX << "]" << endl;
    // g.printBoard(cacaX, pipiY);
    //
    return score(r, !maxing ? _player : _opponent);
  }
  turn = maxing ? _player : _opponent;
  v = maxing ? -MAX : MAX;
  for (int y = 0; y < g.getYMaxCheck(); y++)
    for (int x = 0; x < g.getXMaxCheck(); x++)
      if (!heuristics[y][x]) {
        int res = r.checkPlay(x, y, turn);
        if (res == WIN)
          return scoreWin(r, turn, depth);
        if (res == WIN_INVERSE)
          return scoreWin(r, turn == 1 ? 2 : 1, depth);
        if (res != REPLAY && res != -1) {
          vector<pair<char, char> > pairs;
          g.addDraught(x, y, turn);
          //
          // cacaX = x;
          // pipiY = y;
          //
          updatePair(r, pairs, x, y, maxing ? _player : _opponent);
          int changes = g.updateWeights(x, y, heuristics);
          if (maxing) {
            v = max(v, evaluate(r, depth - 1, !maxing, alpha, beta, heuristics));
            alpha = max(alpha, v);
          } else {
            v = min(v, evaluate(r, depth - 1, !maxing, alpha, beta, heuristics));
            beta = min(beta, v);
          }
          restorePair(r, pairs, maxing ? _opponent : _player);
          g.removeDraught(x, y);
          g.revertWeights(x, y, changes, heuristics);
          if (beta <= alpha)
            return v;
        }
      }
  return v;
}

int     AlphaBetaMinimax::diagsTopToBottom(Goban &g, int player) const {
  int   score = 0;
  int   opponent = player == 1 ? 2 : 1;
  int   x = 0, y = 0, tmp = 0;
  bool  openBefore = false;
  int   res;
  int   maxY = g.getYBoard();
  int   maxX = g.getXBoard();
  int   broken;

  for (int x1 = 0; x1 < maxX; x1++) {
    x = x1;
    y = 0;
    broken = 1;
    openBefore = false;
    tmp = 0;
    while (x < maxX && y < maxY) {
      if (g[y][x] == player) {
        tmp++;
        res = addScore(score, tmp, openBefore, x + 1 >= maxX ? false : y + 1 >= maxY ? false : g[y + 1][x + 1] == 0, broken);
        if (res)
          return MAX;
      } else if (g[y][x] == opponent || x + 1 >= maxX || y + 1 >= maxY || g[y + 1][x + 1] != player) {
        tmp = 0;
        openBefore = g[y][x] != opponent;
        broken = 1;
      } else if (tmp)
        broken = 2;
      x++;
      y++;
    }
  }
  tmp = 0;
  for (int y1 = 1; y1 < maxY; y1++) {
    y = y1;
    x = 0;
    openBefore = false;
    broken = 1;
    tmp = 0;
    while (x < maxX && y < maxY) {
      if (g[y][x] == player) {
        tmp++;
        res = addScore(score, tmp, openBefore, x + 1 >= maxX ? false : y + 1 >= maxY ? false : g[y + 1][x + 1] == 0, broken);
        if (res)
          return MAX;
      } else if (g[y][x] == opponent || x + 1 >= maxX || y + 1 >= maxY || g[y + 1][x + 1] != player) {
        tmp = 0;
        openBefore = g[y][x] != opponent;
        broken = 1;
      } else if (tmp)
        broken = 2;
      x++;
      y++;
    }
  }
  return score;
}

int   AlphaBetaMinimax::diagsBottomToTop(Goban &g, int player) const {
  int   score = 0;
  int   opponent = player == 1 ? 2 : 1;
  int   x = 0, y = 0, tmp = 0;
  bool  openBefore = false;
  int   res;
  int   maxY = g.getYBoard();
  int   maxX = g.getXBoard();
  int   broken;

  for (int x1 = 0; x1 < maxX; x1++) {
    x = x1;
    y = maxY - 1;
    openBefore = false;
    broken = 1;
    tmp = 0;
    while (x < maxX && y >= 0) {
      if (g[y][x] == player) {
        tmp++;
        res = addScore(score, tmp, openBefore, x + 1 >= maxX ? false : y - 1 < 0 ? false : g[y - 1][x + 1] == 0, broken);
        if (res)
          return MAX;
      } else if (g[y][x] == opponent || y - 1 < 0 || x + 1 >= maxX || g[y - 1][x + 1] != player) {
        broken = 1;
        tmp = 0;
        openBefore = g[y][x] != opponent;
      } else if (tmp)
        broken = 2;
      x++;
      y--;
    }
  }
  for (int y1 = maxY - 2; y1 >= 0; y1--) {
    y = y1;
    x = 0;
    openBefore = false;
    broken = 1;
    tmp = 0;
    while (x < maxX && y >= 0) {
      if (g[y][x] == player) {
        tmp++;
        res = addScore(score, tmp, openBefore, x + 1 >= maxX ? false : y - 1 < 0 ? false : g[y - 1][x + 1] == 0, broken);
        if (res)
          return MAX;
      } else if (g[y][x] == opponent || y - 1 < 0 || x + 1 >= maxX || g[y - 1][x + 1] != player) {
        broken = 1;
        tmp = 0;
        openBefore = g[y][x] != opponent;
      } else if (tmp)
        broken = 2;
      x++;
      y--;
    }
  }
  return score;
}

int     AlphaBetaMinimax::countDiags(Goban &g, int player) const {
  int   score = 0;

  score += diagsBottomToTop(g, player);
  score += diagsTopToBottom(g, player);
  return score;
}

int     AlphaBetaMinimax::countSeries(Goban &g, int player) const {
  int   score = 0;
  int   res = 0;
  int   opponent = player == 1 ? 2 : 1;
  bool  openBefore;
  int  broken;
  int   maxY = g.getYBoard();
  int   maxX = g.getXBoard();
  int   tmp = 0;

  for (int y = 0; y < maxY; y++) {
    openBefore = false;
    broken = 1;
    tmp = 0;
    for (int x = 0; x < maxX; x++) {
      if (g[y][x] == player) {
        tmp++;
        res = addScore(score, tmp, openBefore, x + 1 >= maxX ? false : g[y][x + 1] == 0, broken);
        if (res)
          return MAX;
      } else if (g[y][x] == opponent || x + 1 >= maxX || g[y][x + 1] != player) {
        broken = 1;
        tmp = 0;
        openBefore = g[y][x] != opponent;
      } else if (tmp)
        broken = 2;
    }
  }
  for (int x = 0; x < maxX; x++) {
    openBefore = false;
    broken = 1;
    tmp = 0;
    for (int y = 0; y < maxY; y++) {
      if (g[y][x] == player) {
          tmp++;
          res = addScore(score, tmp, openBefore, y + 1 >= maxY ? false : g[y + 1][x] == 0, broken);
          if (res)
            return MAX;
      } else if (g[y][x] == opponent || y + 1 >= maxY || g[y + 1][x] != player) {
        broken = 1;
        tmp = 0;
        openBefore = g[y][x] != opponent;
      } else if (tmp)
        broken = 2;
    }
  }
  return score;
}

int     AlphaBetaMinimax::addScore(int &score, int val, bool openBefore, bool openAfter, int broken) const {
  if (!broken && (val >= 5 || (val == 4 && openAfter && openBefore)))
    return true;
  else if ((val == 3 && openAfter && openBefore))
    score += 10000 / broken * _multiplier[0];
  else if (val == 4 && (openAfter || openBefore))
    score += 5000  / broken * _multiplier[1];
  else if (val == 3 && (openAfter || openBefore))
    score += 1000 / broken * _multiplier[2];
  else if (val == 3)
    score += 100 / broken * _multiplier[3];
  else
    score += pow(val, val) / broken * _multiplier[4];
  return false;
}

int     AlphaBetaMinimax::score(Referee &r, int player) const {
  int opponent = player == 1 ? 2 : 1;
  int tmp;
  int scorePlayer = 0;
  int scoreOpponent = 0;

  tmp = countSeries(r.getGoban(), player);
  if (tmp == MAX)
    return scoreWin(r, player, 0);
  scorePlayer += tmp;
  tmp = countDiags(r.getGoban(), player);
  if (tmp == MAX)
    return scoreWin(r, player, 0);
  scorePlayer += tmp;

  tmp = countSeries(r.getGoban(), opponent);
  if (tmp == MAX)
    return scoreWin(r, opponent, 0);
  scoreOpponent += tmp;
  tmp = countDiags(r.getGoban(), opponent);
  if (tmp == MAX)
    return scoreWin(r, opponent, 0);
  scoreOpponent += tmp;

  //
  // cout << "Player " << player << " Score : " << scorePlayer << " | " << scoreOpponent << endl << endl;
  //

  return scorePlayer - scoreOpponent * 3.0;
}

int     AlphaBetaMinimax::scoreWin(Referee &r, int player, int depth) const {
  //
  // cout << "Player " << player << " ScoreWin : " << (player == _player ? MAX - (_nbTurn - depth) : -MAX + (_nbTurn - depth)) << endl << endl;
  //
  return player == _player ? MAX - (_nbTurn - depth) : -MAX + (_nbTurn - depth);
}
