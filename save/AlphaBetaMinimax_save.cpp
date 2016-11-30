/*
** AlphaBetaMinimax.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Nov 28 13:51:42 2016 wilmot_g
** Last update Tue Nov 29 17:39:37 2016 Adrien Milcent
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
  std::vector<vector<int> > bannedNodes = r.getGoban().getBoard();

  _player = player;
  _opponent = player == 1 ? 2 : 1;
  _win = Coord(-1, -1);
  checkBannedNodes(ref(bannedNodes), r.getGoban(), _player, _opponent);
  cout << "---------------- BEGIN Player " << _player << "---------------" << endl;
  r.getGoban().printBoard();
  cout << "---------------- MIDDLE ---------------" << endl;
  for (int y = 0; y < r.getGoban().getYBoard(); y++) {
    for (int x = 0; x < r.getGoban().getXBoard(); x++)
      cout << bannedNodes.at(y)[x] << " ";
    cout << endl;
  }
  cout << "---------------- END ---------------" << endl;
  for (int y = 0; y < r.getGoban().getYMaxCheck(); y++)
    for (int x = 0; x < r.getGoban().getXMaxCheck(); x++)
      if (calculate(r.getGoban(), x, y)) {
        int res = r.checkPlay(x, y, player);
        if (res != REPLAY && res != -1) {
          r.getGoban()[y][x] = player;
          v = max(v, evaluate(r, _nbTurn - 1, false, res == WIN, alpha, MAX) + checkPair(r.getGoban().getBoard(), r.getGoban().getBoard().size(), x, y, _player) * 200);
          r.getGoban()[y][x] = 0;
          if (v > alpha)
            _win = Coord(x, y);
          alpha = max(v, alpha);
        }
      }
  return _win;
}

void    AlphaBetaMinimax::checkBannedNodes(vector<vector<int> > &bannedNodes, Goban g, int player, int opponent) {

  checkBannedLines(ref(bannedNodes), g, player, opponent);
/*  checkBannedDiagBTT(ref(bannedNodes), goban, player, opponent);
  checkBannedDiagTTB(ref(bannedNodes), goban, player, opponent);*/
}

void    AlphaBetaMinimax::checkBannedLines(vector<vector<int> > &bannedNodes, Goban g, int player, int opponent) {
  int   save;

  for (int y = 0; y < g.getYMaxCheck(); y++)
    for (int x = 0; x < g.getXMaxCheck(); x++) {
      int tmp = 0;
      if (g[y][x] == player) {
        bannedNodes[y][x] = 1;
        save = x;
        while (x < g.getXBoard() && g[y][x] != opponent) {
          tmp++;
          x++;
        }
        x = save;
        while (x > 0 && g[y][x] != opponent) {
          tmp++;
          x--;
        }
        x = save;
        if (tmp < 4) {
          while (x < g.getXBoard() && g[y][x] != opponent) {
            bannedNodes[y][x] = 1;
            x++;
          }
          x = save;
          while (x > 0 && g[y][x] != opponent) {
            bannedNodes[y][x] = 1;
            x--;
          }
          x = save;
        }
      }
      else if (g[y][x] == opponent)
        bannedNodes[y][x] = 1;
      else {

      }
    }
  for (int x = 0; x < g.getXMaxCheck(); x++)
    for (int y = 0; y < g.getYMaxCheck(); y++) {
      int tmp = 0;
      if (g[y][x] == player) {
        bannedNodes[y][x] = 1;
        save = y;
        while (y < g.getXBoard() && g[y][x] != opponent) {
          tmp++;
          y++;
        }
        y = save;
        while (y > 0 && g[y][x] != opponent) {
          tmp++;
          y--;
        }
        y = save;
        if (tmp < 4) {
          while (y < g.getXBoard() && g[y][x] != opponent) {
            bannedNodes[y][x] = 1;
            y++;
          }
          y = save;
          while (y > 0 && g[y][x] != opponent) {
            bannedNodes[y][x] = 1;
            y--;
          }
          y = save;
        }
      }
      else if (g[y][x] == opponent)
        bannedNodes[y][x] = 1;
    }
}

void    AlphaBetaMinimax::checkBannedDiagBTT(vector<vector<int> > &bannedNodes, Goban goban, int player) {

}

void    AlphaBetaMinimax::checkBannedDiagTTB(vector<vector<int> > &bannedNodes, Goban goban, int player) {

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
            v = max(v, evaluate(r, depth - 1, !maxing, res == WIN, alpha, beta) + checkPair(r.getGoban().getBoard(), r.getGoban().getBoard().size(), x, y, _player) * 200);
            alpha = max(alpha, v);
          } else {
            v = min(v, evaluate(r, depth - 1, !maxing, res == WIN, alpha, beta) - checkPair(r.getGoban().getBoard(), r.getGoban().getBoard().size(), x, y, _opponent) * 200);
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

int AlphaBetaMinimax::checkPair(vector<vector<int> > &goban, int gobanLength, int x, int y, int p) {
  int p2 = p == 1 ? 2 : 1;
  int result = 0;

  x - 3 >= 0 && goban[y][x - 3] == p && goban[y][x - 2] == p2 && goban[y][x - 1] == p2 ? result += 1 : result += 0;
  x + 3 < gobanLength && goban[y][x + 3] == p && goban[y][x + 2] == p2 && goban[y][x + 1] == p2 ? result += 1 : result += 0;
  y - 3 >= 0 && goban[y - 3][x] == p && goban[y - 2][x] == p2 && goban[y - 1][x] == p2 ? result += 1 : result += 0;
  y + 3 < gobanLength && goban[y + 3][x] == p && goban[y + 2][x] == p2 && goban[y + 1][x] == p2 ? result += 1 : result += 0;
  x - 3 >= 0 && y - 3 >= 0 && goban[y - 3][x - 3] == p && goban[y - 2][x - 2] == p2 && goban[y - 1][x - 1] == p2 ? result += 1 : result += 0;
  x + 3 < gobanLength && y - 3 >= 0 && goban[y - 3][x + 3] == p && goban[y - 2][x + 2] == p2 && goban[y - 1][x + 1] == p2 ? result += 1 : result += 0;
  x - 3 >= 0 && y + 3 < gobanLength && goban[y + 3][x - 3] == p && goban[y + 2][x - 2] == p2 && goban[y + 1][x - 1] == p2 ? result += 1 : result += 0;
  x + 3 < gobanLength && y + 3 < gobanLength && goban[y + 3][x + 3] == p && goban[y + 2][x + 2] == p2 && goban[y + 1][x + 1] == p2 ?
  result += 1 : result += 0;

  return result;
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
