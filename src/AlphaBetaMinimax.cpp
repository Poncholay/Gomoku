/*
** AlphaBetaMinimax.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Nov 28 13:51:42 2016 wilmot_g
** Last update Tue Nov 29 11:08:53 2016 wilmot_g
*/

#include <functional>

#include "AlphaBetaMinimax.hh"
#include "Referee.hh"
#include "unistd.h"

AlphaBetaMinimax::AlphaBetaMinimax(int nbTurn) {
  _nbTurn = nbTurn;
}

AlphaBetaMinimax::~AlphaBetaMinimax() {}

// Coord   Expectiminmax::loop(Referee &referee, int player) {
Coord   AlphaBetaMinimax::loop(vector<vector<int> > &goban, int player, Referee &r) {
  int v = -MAX;
  int alpha = -MAX;

  _player = player;
  _opponent = player == 1 ? 2 : 1;
  _win = Coord(-1, -1);
  for (int y = 0; y < r.getGoban().getYMaxCheck(); y++)
    for (int x = 0; x < r.getGoban().getXMaxCheck(); x++)
      if (calculate(r.getGoban(), x, y)) {
        int res = r.checkPlay(x, y, player);
        if (res != REPLAY && res != -1) {
          r.getGoban()[y][x] = player;
          v = max(v, evaluate(r, _nbTurn - 1, false, res == WIN, alpha, MAX));
          r.getGoban()[y][x] = 0;
          if (v > alpha)
            _win = Coord(x, y);
          alpha = max(v, alpha);
        }
      }
  return _win;
}

bool    AlphaBetaMinimax::calculate(Goban &g, int x, int y) {
  return true;
}

int     AlphaBetaMinimax::evaluate(Referee &r, int depth, bool maxing, bool win, int alpha, int beta) {
  int   v;
  int   turn;

  if (!depth || win)
    return score(r, !maxing ? _player : _opponent, win, depth);
  turn = maxing ? _player : _opponent;
  v = maxing ? -MAX : MAX;
  for (int y = 0; y < r.getGoban().getYMaxCheck(); y++)
    for (int x = 0; x < r.getGoban().getXMaxCheck(); x++)
      if (calculate(r.getGoban(), x, y)) {
        int res = r.checkPlay(x, y, turn);
        if (res != REPLAY && res != -1) {
          r.getGoban()[y][x] = turn;
          if (maxing) {
            v = max(v, evaluate(r, depth - 1, !maxing, res == WIN, alpha, beta));
            alpha = max(alpha, v);
          } else {
            v = min(v, evaluate(r, depth - 1, !maxing, res == WIN, alpha, beta));
            beta = min(beta, v);
          }
          r.getGoban()[y][x] = 0;
          if (beta <= alpha)
            return v;
        }
      }
  // if (depth == _nbTurn) cout << "alpha : " << alpha << " beta : " << beta << endl;
  return v;
}

int     AlphaBetaMinimax::diagsTopToBottom(Goban &g, int player) {
  int   score = 0;
  int   opponent = player == 1 ? 2 : 1;
  int   x = 0, y = 0, tmp = 0;

  for (int x1 = 0; x1 < g.getXMaxCheck(); x1++) {
    x = x1;
    y = 0;
    while (x < g.getXMaxCheck() && y < g.getYMaxCheck()) {
      if (g[y][x] == player) {
        tmp++;
        score += pow(tmp, 3);
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
        score += pow(tmp, 3);
      } else {
        tmp = 0;
      }
      x++;
      y++;
    }
  }
  return score;
}

int   AlphaBetaMinimax::diagsBottomToTop(Goban &g, int player) {
  int   score = 0;
  int   opponent = player == 1 ? 2 : 1;
  int   x = 0, y = 0, tmp = 0;

  for (int x1 = 0; x1 < g.getXMaxCheck(); x1++) {
    x = x1;
    y = g.getYMaxCheck() - 1;
    while (x < g.getXMaxCheck() && y >= 0) {
      if (g[y][x] == player) {
        tmp++;
        score += pow(tmp, 3);
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
        score += pow(tmp, 3);
      } else {
        tmp = 0;
      }
      x++;
      y--;
    }
  }
}

int     AlphaBetaMinimax::countDiags(Goban &g, int player) {
  int   score = 0;

  score += diagsBottomToTop(g, player);
  score += diagsTopToBottom(g, player);
  return score;
}

int     AlphaBetaMinimax::countSeries(Goban &g, int player) {
  int   score = 0;;
  int   opponent = player == 1 ? 2 : 1;

  for (int y = 0; y < g.getYMaxCheck(); y++)
    for (int x = 0; x < g.getXMaxCheck(); x++) {
      int tmp = 0;
      if (g[y][x] == player)
        while (x < g.getXMaxCheck() && g[y][x] == player) {
          tmp++;
          score += pow(tmp, 3);
          x++;
        }
    }
  for (int x = 0; x < g.getXMaxCheck(); x++)
    for (int y = 0; y < g.getYMaxCheck(); y++) {
      int tmp = 0;
      if (g[y][x] == player)
        while (y < g.getYMaxCheck() && g[y][x] == player) {
          tmp++;
          score += pow(tmp, 3);
          y++;
        }
    }
  return score;
}

int     AlphaBetaMinimax::score(Referee &r, int player, bool win, int depth) {
  if (win == true) {
    int   nbDraughts = 0;
    for (int i = 0; i < r.getGoban().getYMaxCheck(); ++i)
      for (int j = 0; j < r.getGoban().getXMaxCheck(); ++j)
        if (r.getGoban()[i][j] != 0)
          ++nbDraughts;
    return player == _player ? MAX - nbDraughts : -MAX + nbDraughts;
  }

  int opponent = player == 1 ? 2 : 1;
  int scorePlayer = countSeries(r.getGoban(), player) + countDiags(r.getGoban(), player);
  int scoreOpponent = countSeries(r.getGoban(), opponent) +  + countDiags(r.getGoban(), opponent);

  // r.getGoban().printBoard();
  // cout << "Player " << player << " Score : " << scorePlayer << " | " << scoreOpponent << endl << endl;

  return scorePlayer - scoreOpponent;
}
