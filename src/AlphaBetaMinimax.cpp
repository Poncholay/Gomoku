/*
** AlphaBetaMinimax.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Nov 28 13:51:42 2016 wilmot_g
** Last update Sun Dec  4 18:26:13 2016 Adrien Milcent
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
  vector<vector<char> > heuristics = g.getHeuristics();

  _player = player;
  _opponent = player == 1 ? 2 : 1;
  _win = Coord(-1, -1);
  for (int y = 0; y < g.getYMaxCheck(); y++)
    for (int x = 0; x < g.getXMaxCheck(); x++)
      if (!heuristics[y][x]) {
        int res = r.checkPlay(x, y, player);
        if (res == WIN) {
          // cout << "Winning : [" << y << "][" << x << "]" << endl;
          // r.getGoban().printBoard();
          return Coord(x, y);
        }
        if (res != REPLAY && res != -1) {
          vector<pair<int, int> > pairs;
          g.addDraught(x, y, player);
          updatePair(r, pairs, x, y, _player);
          int changes = r.getGoban().updateWeights(x, y, heuristics);
          // int e = evaluate(r, _nbTurn - 1, false, alpha, MAX, heuristics);
          // cout << _player << " [" << y << "][" << x << "] " << e << endl;
          // v = max(v, e);
          v = max(v, evaluate(r, _nbTurn - 1, false, alpha, MAX, heuristics));
          restorePair(r, pairs, _opponent);
          g.removeDraught(x, y);
          g.revertWeights(x, y, changes, heuristics);
          if (v > alpha)
            _win = Coord(x, y);
          alpha = max(v, alpha);
        }
      }
  // cout << "Alpha  : " << alpha << endl;
  // cout << "Result : [" << get<1>(_win) << "][" << get<0>(_win) << "]" << endl;
  // g.printHeuristic(heuristics);
  // g.printBoard(get<0>(_win), get<1>(_win));
  return _win;
}

void    AlphaBetaMinimax::saveChanges(Referee &r, vector<pair<int, int> > &changes, int x1, int y1, int x2, int y2, int p) const {
  r.removePair(x1, y1, x2, y2, p, false);
  changes.push_back(make_pair(x1, y1));
  changes.push_back(make_pair(x2, y2));
}

void    AlphaBetaMinimax::restorePair(Referee &r, vector<pair<int, int> > changes, int player) const {
  int check = 0;
  for (vector<pair<int, int> >::iterator it = changes.begin(); it != changes.end(); it++) {
    check = 1;
    r.getGoban().addDraught((*it).first, (*it).second, player);
  }
  check == 1 ? r.undoNbPair(player == 1 ? 2 : 1) : (void)0;
}

void    AlphaBetaMinimax::updatePair(Referee &r, vector<pair<int, int> > &changes, int x, int y, int p) const {
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

  if (!depth) {
    int myscore = score(r, _player);
    // std::cout << "Score for player " << (maxing ? _player : _opponent) << ": " << myscore << std::endl;
    // g.printBoard();
    return myscore;
  }
  turn = maxing ? _player : _opponent;
  v = maxing ? -MAX : MAX;
  for (int y = 0; y < g.getYMaxCheck(); y++)
    for (int x = 0; x < g.getXMaxCheck(); x++)
      if (!heuristics[y][x]) {
        int res = r.checkPlay(x, y, turn);
        if (res == WIN)
          return scoreWin(r, turn, depth);
        if (res != REPLAY && res != -1) {
          vector<pair<int, int> > pairs;
          g.addDraught(x, y, turn);
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
          if (beta <= alpha) {
            if (maxing)
              return MAX;
            else
              return -MAX;
          }
        }
      }
  if (!maxing)
    cout << "Min return: " << v << endl;
  return v;
}

int     AlphaBetaMinimax::diagsTopToBottom(Goban &g, int player) const {
  int   score = 0;
  int   opponent = player == 1 ? 2 : 1;
  int   x = 0, y = 0, tmp = 0;
  bool  openBefore;

  for (int x1 = 0; x1 < g.getXMaxCheck(); x1++) {
    x = x1;
    y = 0;
    openBefore = false;
    while (x < g.getXMaxCheck() && y < g.getYMaxCheck()) {
      if (g[y][x] == player) {
        tmp++;
        addScore(score, tmp, openBefore, x + 1 == g.getXMaxCheck() || y + 1 == g.getYMaxCheck() ? false : g[y + 1][x + 1] == 0);
      } else {
        openBefore = g[y][x] != opponent;
        tmp = 0;
      }
      x++;
      y++;
    }
  }
  for (int y1 = 1; y1 < g.getYMaxCheck(); y1++) {
    y = y1;
    x = 0;
    openBefore = false;
    while (x < g.getXMaxCheck() && y < g.getYMaxCheck()) {
      if (g[y][x] == player) {
        tmp++;
        addScore(score, tmp, openBefore, x + 1 == g.getXMaxCheck() || y + 1 == g.getYMaxCheck() ? false : g[y + 1][x + 1] == 0);
      } else {
        openBefore = g[y][x] != opponent;
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
  bool openBefore;

  for (int x1 = 0; x1 < g.getXMaxCheck(); x1++) {
    x = x1;
    y = g.getYMaxCheck() - 1;
    openBefore = false;
    while (x < g.getXMaxCheck() && y >= 0) {
      if (g[y][x] == player) {
        tmp++;
        addScore(score, tmp, openBefore, x + 1 == g.getXMaxCheck() || y - 1 == -1 ? false : g[y - 1][x + 1] == 0);
      } else {
        openBefore = g[y][x] != opponent;
        tmp = 0;
      }
      x++;
      y--;
    }
  }
  for (int y1 = g.getYMaxCheck() - 2; y1 >= 0; y1--) {
    y = y1;
    x = 0;
    openBefore = false;
    while (x < g.getXMaxCheck() && y >= 0) {
      if (g[y][x] == player) {
        tmp++;
        addScore(score, tmp, openBefore, x + 1 == g.getXMaxCheck() || y - 1 == -1 ? false : g[y - 1][x + 1] == 0);
      } else {
        openBefore = g[y][x] != opponent;
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
  bool  openBefore;

  for (int y = 0; y < g.getYMaxCheck(); y++) {
    openBefore = false;
    for (int x = 0; x < g.getXMaxCheck(); x++) {
      int tmp = 0;
      if (g[y][x] == player) {
        while (x < g.getXMaxCheck() && g[y][x] == player) {
          tmp++;
          res = addScore(score, tmp, openBefore, x + 1 == g.getXMaxCheck() ? false : g[y][x + 1] == 0);
          if (res) {
            // std::cout << "Toto 1" << std::endl;
            return MAX;
          }
          x++;
        }
      } else
        openBefore = g[y][x] != opponent;
    }
  }
  for (int x = 0; x < g.getXMaxCheck(); x++) {
    openBefore = false;
    for (int y = 0; y < g.getYMaxCheck(); y++) {
      int tmp = 0;
      if (g[y][x] == player) {
        while (y < g.getYMaxCheck() && g[y][x] == player) {
          tmp++;
          res = addScore(score, tmp, openBefore, y + 1 == g.getYMaxCheck() ? false : g[y + 1][x] == 0);
          if (res) {
            // std::cout << "Toto 2" << std::endl;
            return MAX;
          }
          y++;
        }
      } else
        openBefore = g[y][x] != opponent;
    }
  }
  return score;
}

int     AlphaBetaMinimax::addScore(int &score, int val, bool openBefore, bool openAfter) const {

  // cout << val << " " << (openBefore ? "true" : "false") << " " << (openAfter ? "true" : "false") << endl;

  // if (val == 4 && (openAfter || openBefore))
  //   sleep(1);

  if (val == 4 && openAfter && openBefore) {
    cout << "coucou" << endl;
    return true;
  }
  if ((val == 3 && openAfter && openBefore) || (val == 4 && (openAfter || openBefore)))
    score += 20000;
  else if ((val == 4 && !openAfter && !openBefore) || (val == 3 && (openAfter || openBefore)))
    score += 8000;
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
