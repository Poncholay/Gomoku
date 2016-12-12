/*
** AlphaBetaMinimax.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Nov 28 13:51:42 2016 wilmot_g
** Last update Mon Dec 12 11:27:02 2016 Adrien Milcent
*/

#include <functional>

#include "AlphaBetaMinimax.hh"
#include "Referee.hh"
#include "unistd.h"

AlphaBetaMinimax::AlphaBetaMinimax(int nbTurn, bool opti, bool rows, bool diago, bool alpha, bool optiFive) {
  _opti = opti;
  _optiFive = optiFive;
  _rows = rows;
  _diago = diago;
  _alphaBeta = alpha;
  _nbTurn = nbTurn;
  _multiplier = vector<float>(5, 0);
  for (float &m : _multiplier)
    m = 1 + (1000 + rand() % 4000) / 100000.0;
}

AlphaBetaMinimax::~AlphaBetaMinimax() {}

Coord   AlphaBetaMinimax::loop(int player, Referee &r) {
  int v = -MAX;
  int alpha = -MAX;
  Goban &g = r.getGoban();
  vector<char> heuristics = g.getHeuristics();

  _player = player;
  _opponent = player == 1 ? 2 : 1;
  _win = Coord(-1, -1);

  for (int y = 0; y < g.getYBoard(); y++)
    for (int x = 0; x < g.getXBoard(); x++)
      if (!_opti || (_opti && !heuristics[y * g.getXBoard() + x])) {
        int res = r.checkPlay(x, y, player);
        if (res == WIN)
          return Coord(x, y);
        if (res == CONTINUE) {
          vector<pair<char, char> > pairs;
          vector<pair<char, char> > save_to5;
          vector<bool> saveRetTo5;
          g.addDraught(x, y, player);
          updatePair(r, pairs, x, y, _player);
          int changes = r.getGoban().updateWeights(x, y, heuristics);
          if (_optiFive) setHeuriscticTo5(g, _player, heuristics, save_to5, saveRetTo5);
          v = max(v, evaluate(r, _nbTurn - 1, false, alpha, MAX, heuristics));
          if (_optiFive) unsetHeuriscticTo5(g, heuristics, save_to5, saveRetTo5);
          restorePair(r, pairs, _opponent);
          g.removeDraught(x, y);
          g.revertWeights(x, y, changes, heuristics);
          if (v > alpha)
            _win = Coord(x, y);
          alpha = max(v, alpha);
        }
      }
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

  x - 3 >= 0 && goban(y, x - 3) == p && goban(y, x - 2) == p2 && goban(y, x - 1) == p2 ? saveChanges(r, changes, x - 2, y, x - 1, y, p) : (void)0;
  x + 3 < goban.getXBoard() && goban(y, x + 3) == p && goban(y, x + 2) == p2 && goban(y, x + 1) == p2 ? saveChanges(r, changes, x + 2, y, x + 1, y, p) : (void)0;
  y - 3 >= 0 && goban(y - 3, x) == p && goban(y - 2, x) == p2 && goban(y - 1, x) == p2 ? saveChanges(r, changes, x, y - 2, x, y - 1, p) : (void)0;
  y + 3 < goban.getYBoard() && goban(y + 3, x) == p && goban(y + 2, x) == p2 && goban(y + 1, x) == p2 ? saveChanges(r, changes, x, y + 2, x, y + 1, p) : (void)0;
  x - 3 >= 0 && y - 3 >= 0 && goban(y - 3, x - 3) == p && goban(y - 2, x - 2) == p2 && goban(y - 1, x - 1) == p2 ? saveChanges(r, changes, x - 2, y - 2, x - 1, y - 1, p) : (void)0;
  x + 3 < goban.getXBoard() && y - 3 >= 0 && goban(y - 3, x + 3) == p && goban(y - 2, x + 2) == p2 && goban(y - 1, x + 1) == p2 ? saveChanges(r, changes, x + 2, y - 2, x + 1, y - 1, p) : (void)0;
  x - 3 >= 0 && y + 3 < goban.getYBoard() && goban(y + 3, x - 3) == p && goban(y + 2, x - 2) == p2 && goban(y + 1, x - 1) == p2 ? saveChanges(r, changes, x - 2, y + 2, x - 1, y + 1, p) : (void)0;
  x + 3 < goban.getXBoard() && y + 3 < goban.getYBoard() && goban(y + 3, x + 3) == p && goban(y + 2, x + 2) == p2 && goban(y + 1, x + 1) == p2 ? saveChanges(r, changes, x + 2, y + 2, x + 1, y + 1, p) : (void)0;
}

bool  AlphaBetaMinimax::checkLineTo5(Goban &goban, int x, int y, int player) const {
  int count = 0, j = x;

  while (j <= goban.getXBoard() && (goban(y, j) == 0 || goban(y, j) == player) && count < 5) {
    ++j;
    if (++count == 5)
      return true;
  }
  count = 0;
  j = x;
  while (j >= 0 && (goban(y, j) == 0 || goban(y, j) == player) && count < 5) {
    --j;
    if (++count == 5)
      return true;
  }
  count = 0;
  j = y;
  while (j <= goban.getYBoard() && (goban(j, x) == 0 || goban(j, x) == player) && count < 5) {
    ++j;
    if (++count == 5)
      return true;
  }
  count = 0;
  j = y;
  while (j > 0 && (goban(j, x) == 0 || goban(j, x) == player) && count < 5) {
    --j;
    if (++count == 5)
      return true;
  }
  return false;
}

bool  AlphaBetaMinimax::checkDiagTo5(Goban &goban, int x, int y, int player) const {
  int count = 0, j = x, i = y;

  while (j <= goban.getXBoard() && i <= goban.getYBoard() && (goban(i, j) == 0 || goban(i, j) == player) && count < 5) {
    ++j;
    ++i;
    if (++count == 5)
      return true;
  }
  count = 0;
  j = x;
  i = y;
  while (j <= goban.getXBoard() && i >= 0 && (goban(i, j) == 0 || goban(i, j) == player) && count < 5) {
    ++j;
    --i;
    if (++count == 5)
      return true;
  }
  count = 0;
  j = x;
  i = y;
  while (j >= 0 && i <= goban.getYBoard() && (goban(i, j) == 0 || goban(i, j) == player) && count < 5) {
    --j;
    ++i;
    if (++count == 5)
      return true;
  }
  count = 0;
  j = x;
  i = y;
  while (j >= 0 && i >= 0 && (goban(i, j) == 0 || goban(i, j) == player) && count < 5) {
    --j;
    --i;
    if (++count == 5)
      return true;
  }
  return false;
}

void  AlphaBetaMinimax::setHeuriscticTo5(Goban &goban, int player, vector<char> &heuristics, vector<pair<char, char> > &saveTo5, vector<bool> &saveRetTo5) const {
  for (int y1 = 0; y1 < goban.getYBoard(); y1++)
    for (int x1 = 0; x1 < goban.getXBoard(); x1++)
      if (!checkLineTo5(goban, x1, y1, player) && !checkDiagTo5(goban, x1, y1, player)) {
        saveRetTo5.push_back(goban.setHeuristicXY(x1, y1, 1, true, heuristics));
        saveTo5.push_back(make_pair(x1, y1));
      }
}

void  AlphaBetaMinimax::unsetHeuriscticTo5(Goban &goban, vector<char> &heuristics, vector<pair<char, char> > &save_to5, vector<bool> &saveRetTo5) const {
  unsigned int i = 0;
  while (i < save_to5.size()) {
    goban.setHeuristicXY(save_to5.at(i).first, save_to5.at(i).second, 1, saveRetTo5.at(i), heuristics);
    ++i;
  }
}

int     AlphaBetaMinimax::evaluate(Referee &r, int depth, bool maxing, int alpha, int beta, vector<char> heuristics) const {
  int   v;
  int   turn;
  Goban &g = r.getGoban();

  if (!depth)
    return score(r, !maxing ? _player : _opponent);
  turn = maxing ? _player : _opponent;
  v = maxing ? -MAX : MAX;
  for (int y = 0; y < g.getYBoard(); y++)
    for (int x = 0; x < g.getXBoard(); x++)
      if (!_opti || (_opti && !heuristics[y * g.getXBoard() + x])) {
        int res = r.checkPlay(x, y, turn);
        if (res == WIN)
          return scoreWin(r, turn, depth);
        if (res == WIN_INVERSE)
          return scoreWin(r, turn == 1 ? 2 : 1, depth);
        if (res != REPLAY && res != -1) {
          vector<pair<char, char> > pairs;
          vector<pair<char, char> > save_to5;
          vector<bool> saveRetTo5;
          g.addDraught(x, y, turn);
          updatePair(r, pairs, x, y, maxing ? _player : _opponent);
          int changes = g.updateWeights(x, y, heuristics);
          if (_optiFive) setHeuriscticTo5(g, _player, heuristics, save_to5, saveRetTo5);
          if (maxing) {
            v = max(v, evaluate(r, depth - 1, !maxing, alpha, beta, heuristics));
            alpha = max(alpha, v);
          } else {
            v = min(v, evaluate(r, depth - 1, !maxing, alpha, beta, heuristics));
            beta = min(beta, v);
          }
          if (_optiFive) unsetHeuriscticTo5(g, heuristics, save_to5, saveRetTo5);
          restorePair(r, pairs, maxing ? _opponent : _player);
          g.removeDraught(x, y);
          g.revertWeights(x, y, changes, heuristics);
          if (beta <= alpha && _alphaBeta)
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
      if (g(y, x) == player) {
        tmp++;
        res = addScore(score, tmp, openBefore, x + 1 >= maxX ? false : y + 1 >= maxY ? false : g(y + 1, x + 1) == 0, broken);
        if (res)
          return MAX;
      } else if (g(y, x) == opponent || x + 1 >= maxX || y + 1 >= maxY || g(y + 1, x + 1) != player) {
        openBefore = false;
        tmp = 0;
        broken = 1;
      } else if (tmp)
        broken++;
        if (!tmp && g(y, x) == 0)
          openBefore = true;
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
      if (g(y, x) == player) {
        tmp++;
        res = addScore(score, tmp, openBefore, x + 1 >= maxX ? false : y + 1 >= maxY ? false : g(y + 1, x + 1) == 0, broken);
        if (res)
          return MAX;
      } else if (g(y, x) == opponent || x + 1 >= maxX || y + 1 >= maxY || g(y + 1, x + 1) != player) {
        openBefore = false;
        tmp = 0;
        broken = 1;
      } else if (tmp)
        broken++;
        if (!tmp && g(y, x) == 0)
          openBefore = true;
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
      if (g(y, x) == player) {
        tmp++;
        res = addScore(score, tmp, openBefore, x + 1 >= maxX ? false : y - 1 < 0 ? false : g(y - 1, x + 1) == 0, broken);
        if (res)
          return MAX;
      } else if (g(y, x) == opponent || y - 1 < 0 || x + 1 >= maxX || g(y - 1, x + 1) != player) {
        openBefore = false;
        broken = 1;
        tmp = 0;
      } else if (tmp)
        broken++;
        if (!tmp && g(y, x) == 0)
          openBefore = true;
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
      if (g(y, x) == player) {
        tmp++;
        res = addScore(score, tmp, openBefore, x + 1 >= maxX ? false : y - 1 < 0 ? false : g(y - 1, x + 1) == 0, broken);
        if (res)
          return MAX;
      } else if (g(y, x) == opponent || y - 1 < 0 || x + 1 >= maxX || g(y - 1, x + 1) != player) {
        openBefore = false;
        broken = 1;
        tmp = 0;
      } else if (tmp)
        broken++;
        if (!tmp && g(y, x) == 0)
          openBefore = true;
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
      if (g(y, x) == player) {
        tmp++;
        res = addScore(score, tmp, openBefore, x + 1 >= maxX ? false : g(y, x + 1) == 0, broken);
        if (res)
          return MAX;
      } else if (g(y, x) == opponent || x + 1 >= maxX || g(y, x + 1) != player) {
        openBefore = false;
        broken = 1;
        tmp = 0;
      } else if (tmp)
        broken++;
        if (!tmp && g(y, x) == 0)
          openBefore = true;
    }
  }
  for (int x = 0; x < maxX; x++) {
    openBefore = false;
    broken = 1;
    tmp = 0;
    for (int y = 0; y < maxY; y++) {
      if (g(y, x) == player) {
          tmp++;
          res = addScore(score, tmp, openBefore, y + 1 >= maxY ? false : g(y + 1, x) == 0, broken);
          if (res)
            return MAX;
      } else if (g(y, x) == opponent || y + 1 >= maxY || g(y + 1, x) != player) {
        openBefore = false;
        broken = 1;
        tmp = 0;
      } else if (tmp)
        broken++;
        if (!tmp && g(y, x) == 0)
          openBefore = true;
    }
  }
  return score;
}

int     AlphaBetaMinimax::addScore(int &score, int val, bool openBefore, bool openAfter, int broken) const {
  if (broken == 1 && (val >= 5 || (val == 4 && openAfter && openBefore)))
    return true;
  else if (val >= 5 || (val == 4 && openAfter && openBefore))
    score += 50000;
  else if ((val == 3 && openAfter && openBefore))
    score += 10000 * _multiplier[0];
  else if (val == 4 && (openAfter || openBefore))
    score += 5000  / broken * _multiplier[1];
  else if (val == 4 && broken)
    score += 3000 * _multiplier[2];
  else if (val == 3 && (openAfter || openBefore))
    score += 1000 / broken * _multiplier[3];
  else
    score += pow(val, val) / broken * _multiplier[4];
  return false;
}

int     AlphaBetaMinimax::score(Referee &r, int player) const {
  int opponent = player == 1 ? 2 : 1;
  int tmp;
  int scorePlayer = 0;
  int scoreOpponent = 0;

  if (_rows) {
    tmp = countSeries(r.getGoban(), player);
    if (tmp == MAX)
      return scoreWin(r, player, 0);
    scorePlayer += tmp;

    tmp = countSeries(r.getGoban(), opponent);
    if (tmp == MAX)
      return scoreWin(r, opponent, 0);
    scoreOpponent += tmp;
  }
  if (_diago) {
    tmp = countDiags(r.getGoban(), player);
    if (tmp == MAX)
      return scoreWin(r, player, 0);
    scorePlayer += tmp;

    tmp = countDiags(r.getGoban(), opponent);
    if (tmp == MAX)
      return scoreWin(r, opponent, 0);
    scoreOpponent += tmp;
  }
  return scorePlayer - scoreOpponent;
}

int     AlphaBetaMinimax::scoreWin(Referee &r, int player, int depth) const {
  return player == _player ? MAX - (_nbTurn - depth) * 5 : -MAX + (_nbTurn - depth) * 5;
}
