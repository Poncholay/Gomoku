/*
** AlphaBetaMinimax.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Nov 28 13:51:42 2016 wilmot_g
** Last update Tue Nov 29 20:58:05 2016 wilmot_g
*/

#include <functional>

#include "AlphaBetaMinimax.hh"
#include "Referee.hh"
#include "unistd.h"

AlphaBetaMinimax::AlphaBetaMinimax(int nbTurn) {
  _nbTurn = nbTurn;
}

AlphaBetaMinimax::~AlphaBetaMinimax() {}

Coord   AlphaBetaMinimax::loop(int player, Referee &r) {
  int v = -MAX;
  int alpha = -MAX;
  Goban &g = r.getGoban();
  vector<vector<char> > heuristics = r.getGoban().getHeuristics();

  _player = player;
  _opponent = player == 1 ? 2 : 1;
  _win = Coord(-1, -1);

  g.printBoard();

  for (int y = 0; y < g.getYMaxCheck(); y++)
    for (int x = 0; x < g.getXMaxCheck(); x++)
      if (!r.getGoban()(y)[x]) {
        int res = r.checkPlay(x, y, player);
        if (res == WIN) {
          cout << "Winning : [" << y << "][" << x << "]" << endl;
          return Coord(x, y);
        }
        if (res != REPLAY && res != -1) {
          r.getGoban().addDraught(x, y, player);
          int changes = r.getGoban().updateWeights(x, y, heuristics);
          int e = evaluate(r, _nbTurn - 1, false, alpha, MAX, heuristics);
          cout << _player << " [" << y << "][" << x << "] " << e << endl;
          v = max(v, e);
          // v = max(v, evaluate(r, _nbTurn - 1, false, alpha, MAX, heuristics));
          r.getGoban().removeDraught(x, y, 0);
          r.getGoban().revertWeights(x, y, changes, heuristics);
          if (v > alpha)
            _win = Coord(x, y);
          alpha = max(v, alpha);
        }
      }
  cout << "Alpha  : " << alpha << endl;
  cout << "Result : [" << get<1>(_win) << "][" << get<0>(_win) << "]" << endl;
  return _win;
}

int     AlphaBetaMinimax::evaluate(Referee &r, int depth, bool maxing, int alpha, int beta, vector<vector<char> > heuristics) const {
  int   v;
  int   turn;
  Goban &g = r.getGoban();

  if (!depth)
    return score(r, !maxing ? _player : _opponent);
  turn = maxing ? _player : _opponent;
  v = maxing ? -MAX : MAX;
  for (int y = 0; y < g.getYMaxCheck(); y++)
    for (int x = 0; x < g.getXMaxCheck(); x++)
      if (!heuristics[y][x]) {
        int res = r.checkPlay(x, y, turn);
        if (res == WIN)
          return scoreWin(r, turn, depth);
        if (res != REPLAY && res != -1) {
          g.addDraught(x, y, turn);
          int changes = g.updateWeights(x, y, heuristics);
          if (maxing) {
            v = max(v, evaluate(r, depth - 1, !maxing, alpha, beta, heuristics));
            alpha = max(alpha, v);
          } else {
            v = min(v, evaluate(r, depth - 1, !maxing, alpha, beta, heuristics));
            beta = min(beta, v);
          }
          g.removeDraught(x, y, 0);
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

  for (int x1 = 0; x1 < g.getXMaxCheck(); x1++) {
    x = x1;
    y = 0;
    while (x < g.getXMaxCheck() && y < g.getYMaxCheck()) {
      if (g[y][x] == player) {
        tmp++;
        addScore(score, tmp, false, false);
      } else {
        tmp = 0;
      }
      x++;
      y++;
    }
  }
  for (int y1 = 1; y1 < g.getYMaxCheck(); y1++) {
    y = y1;
    x = 0;
    while (x < g.getXMaxCheck() && y < g.getYMaxCheck()) {
      if (g[y][x] == player) {
        tmp++;
        addScore(score, tmp, false, false);
      } else {
        tmp = 0;
      }
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

  for (int x1 = 0; x1 < g.getXMaxCheck(); x1++) {
    x = x1;
    y = g.getYMaxCheck() - 1;
    while (x < g.getXMaxCheck() && y >= 0) {
      if (g[y][x] == player) {
        tmp++;
        addScore(score, tmp, false, false);
      } else {
        tmp = 0;
      }
      x++;
      y--;
    }
  }
  for (int y1 = g.getYMaxCheck() - 2; y1 >= 0; y1--) {
    y = y1;
    x = 0;
    while (x < g.getXMaxCheck() && y >= 0) {
      if (g[y][x] == player) {
        tmp++;
        addScore(score, tmp, false, false);
      } else {
        tmp = 0;
      }
      x++;
      y--;
    }
  }
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
  bool  openBefore = false;

  for (int y = 0; y < g.getYMaxCheck(); y++)
    for (int x = 0; x < g.getXMaxCheck(); x++) {
      int tmp = 0;
      if (g[y][x] == player) {
        while (x < g.getXMaxCheck() && g[y][x] == player) {
          tmp++;
          res = addScore(score, tmp, openBefore, x + 1 == g.getXMaxCheck() ? false : g[y][x + 1] == 0);
          if (res)
            return MAX;
          x++;
        }
      } else
        openBefore = g[y][x] == opponent;
    }
  for (int x = 0; x < g.getXMaxCheck(); x++)
    for (int y = 0; y < g.getYMaxCheck(); y++) {
      int tmp = 0;
      if (g[y][x] == player) {
        while (y < g.getYMaxCheck() && g[y][x] == player) {
          tmp++;
          res = addScore(score, tmp, openBefore, y + 1 == g.getYMaxCheck() ? false : g[y + 1][x] == 0);
          if (res)
            return MAX;
          y++;
        }
      } else
        openBefore = g[y][x] == opponent;
    }
  return score;
}

int     AlphaBetaMinimax::addScore(int &score, int val, bool openBefore, bool openAfter) const {
  if ((val == 3 && openAfter && openBefore) || (val == 4 && (openAfter || openBefore)))
    return true;
  if ((val == 4 && !openAfter && !openBefore) || (val == 3 && (openAfter || openBefore)))
    score += 10000;
  else if (val == 3)
    score += 500;
  else
    score += pow(val, val);
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

  // r.getGoban().printBoard();
  // cout << "Player " << player << " Score : " << scorePlayer << " | " << scoreOpponent << endl << endl;

  return scorePlayer - scoreOpponent * 2;
}

int     AlphaBetaMinimax::scoreWin(Referee &r, int player, int depth) const {
  return player == _player ? MAX - (_nbTurn - depth) : -MAX + (_nbTurn - depth);
}
