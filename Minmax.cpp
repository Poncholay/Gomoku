//
// Minmax.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 13:59:50 2016 Adrien Milcent
// Last update Wed Oct 19 14:32:20 2016 Adrien Milcent
//

#include "Minmax.hh"

Minmax::Minmax(int nbTurn) {
  _nbTurn = nbTurn;
}

Minmax::~Minmax() {

}

int Minmax::loop(std::vector<std::vector<int> > &goban, int nbPlayer, int nbTurn) {
  int max = -100000;
  int tmp, maxi, maxj;

  for (int i = 0; i < goban.size(); ++i) {
    for (int j = 0; j < goban.size(); ++j) {
      if (goban[i][j] == 0) {
        goban[i][j] = _nbPlayer;
        if (referee.checkWin(j, i, nbPlayer) == true || nbTurn == 0)
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

int Minmax::min(std::vector<std::vector<int> > &goban, int nbTurn, int nbPlayer, int nbOpponent) {
  int min = 100000;
  int tmp;

  for (int i = 0; i < goban.size(); ++i) {
    for (int j = 0; j < goban.size(); ++j) {
      if (goban[i][j] == 0) {
        goban[i][j] = _nbPlayer;
        if (referee.checkWin(j, i, nbPlayer) == true)
          tmp = eval(goban, nbPlayer, true, nbPlayer);
        else if (nbTurn == 0)
          tmp = eval(goban, nbPlayer, false, nbPlayer);
        else
          tmp = _minnmax.max(goban, nbTurn - 1, nbPlayer, nbOpponent);

        if (tmp < min) {
          min = tmp;
        }
        goban[i][j] = 0;
      }
    }
  }
  return min;
}

int Minmax::max(std::vector<std::vector<int> > &goban, int nbTurn, int nbPlayer, int nbOpponent) {
  int max = -100000;
  int tmp;

  for (int i = 0; i < goban.size(); ++i) {
    for (int j = 0; j < goban.size(); ++j) {
      if (goban[i][j] == 0) {
        goban[i][j] = _nbOpponent;
        if (referee.checkWin(j, i, _nbOpponent) == true)
          tmp = eval(goban, nbPlayer, true, nbOpponent);
        else if (nbTurn == 0)
          tmp = eval(goban, nbPlayer, false, nbOpponent);
        else
          tmp = _minnmax.min(goban, nbTurn - 1, nbPlayer, nbOpponent);

        if (tmp > max) {
          max = tmp;
        }
        goban[i][j] = 0;
      }
    }
  }
  return max;
}

void Minmax::checkDiag(std::vector<std::vector<int> > &goban, int &seriej1, int &seriej2, int gobanLength, int length, int i, int j, int nb) {
  int tmp = 1, k = i, l = j;

  while (k < gobanLength && l < gobanLength && goban[k][l] == nb) {
    if (tmp == length)
      if (nb == 1)
        ++seriej1;
      else
        ++seriej2;
    k += 1;
    l += 1;
    ++tmp;
  }

  k = i;
  l = j;
  tmp = 1;
  while (k >= 0 && l < gobanLength && goban[k][l] == nb) {
    if (tmp == length)
    if (nb == 1)
      ++seriej1;
    else
      ++seriej2;
    k -= 1;
    l += 1;
    ++tmp;
  }
}

void Minmax::countSeries(std::vector<std::vector<int> > &goban, int &seriej1, int &seriej2, int length) {
  int gobanLength = goban.size();
  seriej1 = 0;
  seriej2 = 0;

  for (int i = 0; i < goban.size(); ++i) {
    for (int j = 0; j < goban.size(); ++j) {
      if (goban[i][j] == 1)
        checkDiag(goban, seriej1, seriej2, gobanLength, length, i, j, 1);
      else if (goban[i][j] == 2)
        checkDiag(goban, seriej1, seriej2, gobanLength, length, i, j, 2);
    }
  }

  for (int i = 0; i < gobanLength; ++i) {

    tmp1 = 0;
    tmp2 = 0;

    for (int j = 0; j < gobanLength; ++j) {
      if (goban[i][j] == 1) {
        ++tmp1;
        tmp2 = 0;
        if (tmp1 == length)
          ++seriej1;
      }
      else if (goban[i][j] == 2) {
        ++tmp2;
        tmp1 = 0;
        if (tmp2 == length)
          ++seriej2;
      }
    }

    tmp1 = 0;
    tmp2 = 0;

    for (int j = 0; j < gobanLength; ++j) {
      if (goban[j][i] == 1) {
        ++tmp1;
        tmp2 = 0;
        if (tmp1 == length)
          ++seriej1;
      }
      else if (goban[j][i] == 2) {
        ++tmp2;
        tmp1 = 0;
        if (tmp2 == length)
          ++seriej2;
      }
    }
  }
}

int Minmax::eval(std::vector<std::vector<int> > &goban, int nbPlayer, bool win, int nbWinner) {
  int seriej1 = 0, seriej2 = 0, totalj1 = 0, totalj2 = 0, nbDraughts = 0;

  if (win == true) {
    for (int i = 0; i < goban.size(); ++i) {
      for (int j = 0; j < goban.size(); ++j) {
        if (goban[i][j] != 0)
          ++nbDraughts;

    if (nbPlayer == nbWinner)
      return 1000 - nbDraughts;
    else
      return -1000 + nbDraughts;
  }
  else {
    countSeries(goban, seriej1, seriej2, 4);
    totalj1 += seriej1 * 10;
    totalj2 += seriej2 * 10;
    countSeries(goban, seriej1, seriej2, 3);
    totalj1 += seriej1 * 5;
    totalj2 += seriej2 * 5;
    countSeries(goban, seriej1, seriej2, 2);
    totalj1 += seriej1 * 2;
    totalj2 += seriej2 * 2;

    if (nbPlayer == 1)
      return totalj1 - totalj2;
    else
      return totalj2 - totalj1;
  }
}
