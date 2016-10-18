//
// Minmax.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 13:59:50 2016 Adrien Milcent
// Last update Tue Oct 18 17:17:12 2016 Adrien Milcent
//

#include "Minmax.hh"

Minmax::Minmax(int nbTurn) {
  _nbTurn = nbTurn;
}

Minmax::~Minmax() {

}

int Minmax::Min(std::vector<std::vector<int> > &goban, int nbTurn, int nbPlayer, int nbOpponent) {

}

int Minmax::Max(std::vector<std::vector<int> > &goban, int nbTurn, int nbPlayer, int nbOpponent) {
  int max = -100000;
  int tmp;

  for (int i = 0; i < goban.size(); ++i) {
    for (int j = 0; j < goban.size(); ++j) {
      if (goban[i][j] == 0) {
        goban[i][j] = _nbOpponent;
        if (referee.checkWin(j, i, _nbPlayer) == true || _minnmax.getNbTurn() == 0)
          tmp = eval(goban);
        else
          tmp = _minnmax.Min(goban, nbTurn - 1, nbPlayer, nbOpponent);

        if (tmp > max) {
          max = tmp;
        }
        goban[i][j] = 0;
      }
    }
  }
  return max;
}

void AI::play() {
  std::vector<std::vector<int> > goban = _goban.getBoard();
  int max = -100000;
  int tmp, maxi, maxj;

  for (int i = 0; i < goban.size(); ++i) {
    for (int j = 0; j < goban.size(); ++j) {
      if (goban[i][j] == 0) {
        goban[i][j] = _nbPlayer;
        if (referee.checkWin(j, i, _nbPlayer) == true || _minnmax.getNbTurn() == 0)
          tmp = eval(goban);
        else
          tmp = _minnmax.Min(goban, nbTurn - 1);

        if (tmp > max) {
          max = tmp;
          maxi = i;
          maxj = j;
        }
        goban[i][j] = 0;
      }
    }
  }
  _goban.addDraught(maxj, maxi, nbPlayer);
}


int Minmax::Eval() {

}
