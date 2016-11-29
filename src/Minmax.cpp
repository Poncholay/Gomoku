//
// Minmax.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 13:59:50 2016 Adrien Milcent
// Last update Mon Nov 28 18:59:40 2016 Adrien Milcent
//

#include <functional>

#include "Minmax.hh"
#include "Referee.hh"
#include "unistd.h"

Minmax::Minmax(int nbTurn) {
  _nbTurn = nbTurn;
}

Minmax::~Minmax() {

}

pair<int, int> Minmax::loop(vector<vector<int> > &goban, int nbPlayer, Referee referee) {
  int max_nb = -100000;
  int nbTurn = _nbTurn;
  int maxX = referee.getGoban().getXMaxCheck();
  int maxY = referee.getGoban().getYMaxCheck();
  int size = goban.size();
  Result res;
  int cnt = 0;
  int tmp = 0, maxi = -1, maxj = -1, nbOpponent = 0;

  nbOpponent = nbPlayer == 1 ? 2 : 1;
  for (int i = 0; i < maxY; ++i) {
    for (int j = 0; j < maxX; ++j) {
      if (goban[i][j] == 0) {
        goban[i][j] = nbPlayer;
        res = referee.checkPlay(j, i, nbPlayer);
        if (res == WIN)
          tmp = eval(goban, nbPlayer, nbOpponent, true, nbPlayer, maxY, maxX);
        else if (res != REPLAY) {
          if (nbTurn == 0)
            tmp = eval(goban, nbPlayer, nbOpponent, false, nbPlayer, maxY, maxX);
          else
            tmp = min(goban, size, nbTurn - 1, nbPlayer, nbOpponent, referee, maxY, maxX);
          tmp += (checkPair(goban, size, i, j, nbOpponent) * 100);
          if (tmp > max_nb) {
            max_nb = tmp;
            maxi = i;
            maxj = j;
          }
        }
        goban[i][j] = 0;
        ++cnt;
      }
    }
  }
  pair<int, int> result = pair<int, int> (maxj, maxi);
  return result;
}

int Minmax::min(vector<vector<int> > &goban, int size, int nbTurn, int nbPlayer, int nbOpponent, Referee referee, int maxY, int maxX) {
  int min_nb = 100000;
  int tmp = 100000;

  for (int i = 0; i < maxY; ++i) {
    for (int j = 0; j < maxX; ++j) {
      if (goban[i][j] == 0) {
        goban[i][j] = nbOpponent;
        if (referee.checkPlay(j, i, nbOpponent) == WIN)
          tmp = eval(goban, nbPlayer, nbOpponent, true, nbOpponent, maxY, maxX);
        else if (nbTurn == 0)
          tmp = eval(goban, nbPlayer, nbOpponent, false, nbOpponent, maxY, maxX);
        else
          tmp = max(goban, size, nbTurn - 1, nbPlayer, nbOpponent, referee, maxY, maxX);
        tmp -= (checkPair(goban, size, i, j, nbOpponent) * 100);
        if (tmp < min_nb) {
          min_nb = tmp;
        }
        goban[i][j] = 0;
      }
    }
  }
  return min_nb;
}

int Minmax::max(vector<vector<int> > &goban, int size, int nbTurn, int nbPlayer, int nbOpponent, Referee referee, int maxY, int maxX) {
  int max_nb = -100000;
  int tmp = -100000;

  for (int i = 0; i < maxY; ++i) {
    for (int j = 0; j < maxX; ++j) {
      if (goban[i][j] == 0) {
        goban[i][j] = nbPlayer;
        if (referee.checkPlay(j, i, nbPlayer) == WIN)
          tmp = eval(goban, nbPlayer, nbOpponent, true, nbPlayer, maxY, maxX);
        else if (nbTurn == 0)
          tmp = eval(goban, nbPlayer, nbOpponent, false, nbPlayer, maxY, maxX);
        else
          tmp = min(goban, size, nbTurn - 1, nbPlayer, nbOpponent, referee, maxY, maxX);
        tmp += (checkPair(goban, size, i, j, nbOpponent) * 100);
        if (tmp > max_nb) {
          max_nb = tmp;
        }
        goban[i][j] = 0;
      }
    }
  }
  return max_nb;
}

int Minmax::checkPair(vector<vector<int> > &goban, int gobanLength, int x, int y, int p) {
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

void Minmax::addScore(int nb, int &total, int divider) {
  if (nb == 2 && divider != 0)
    total += (2 / divider);
  else if (nb == 3 && divider != 0)
    total += (20 / divider);
  else if (nb == 4 && divider != 0)
    total += (100 / divider);
}

void Minmax::setDivider(vector<vector<int> > goban, int tmp, int i, int j, int gobanLength, int &save, int &divider, int nbOpponent) {
  if (tmp == 0) {
    if (j == 0)
      save = 2;
    else if (goban[i][j - 1] == nbOpponent)
      save = 2;
    else
      save = 1;
  }
  if (j < gobanLength) {
    if (save == 2 && goban[i][j + 1] == 0)
      divider = 2;
    else if (save == 2)
      divider = 0;
    else if (save == 1 && goban[i][j + 1] == 0)
      divider = 1;
    else
      divider = 2;
  }
  else {
    if (save == 2)
      divider = 0;
    else
      divider = 2;
  }
}

void Minmax::setDividerDiag1(vector<vector<int> > goban, int tmp, int i, int j, int gobanLength, int &save, int &divider, int nbOpponent) {
  if (tmp == 1) {
    if (i == 0 || j == 0)
      save = 2;
    else if (goban[i - 1][j - 1] == nbOpponent)
      save = 2;
    else
      save = 1;
  }
  if (i < gobanLength && j < gobanLength) {
    if (save == 2 && goban[i + 1][j + 1] == 0)
      divider = 2;
    else if (save == 2)
      divider = 0;
    else if (save == 1 && goban[i + 1][j + 1] == 0)
      divider = 1;
    else
      divider = 2;
  }
  else {
    if (save == 2)
      divider = 0;
    else
      divider = 2;
  }
}

void Minmax::setDividerDiag2(vector<vector<int> > goban, int tmp, int i, int j, int gobanLength, int &save, int &divider, int nbOpponent) {
  if (tmp == 1) {
    if (i == 0 || j == 0)
      save = 2;
    else if (goban[i - 1][j + 1] == nbOpponent)
      save = 2;
    else
      save = 1;
  }
  if (i > 0 && j < gobanLength) {
    if (save == 2 && goban[i - 1][j + 1] == 0)
      divider = 2;
    else if (save == 2)
      divider = 0;
    else if (save == 1 && goban[i - 1][j + 1] == 0)
      divider = 1;
    else
      divider = 2;
  }
  else {
    if (save == 2)
      divider = 0;
    else
      divider = 2;
  }
}

void Minmax::checkDiag(vector<vector<int> > &goban, int &totalj1, int &totalj2, int gobanLength, int i, int j, int nb, int &divider, int nbOpponent) {
  int tmp = 1, save = 0, k = i, l = j;

  while (k < gobanLength && l < gobanLength && goban[k][l] == nb) {
    setDividerDiag1(goban, tmp, i, j, gobanLength, save, divider, nbOpponent);
    if (nb == 1)
      addScore(tmp, totalj1, divider);
    else
      addScore(tmp, totalj2, divider);

    k += 1;
    l += 1;
    ++tmp;
  }

  k = i;
  l = j;
  tmp = 1;
  save = 0;
  while (k >= 0 && l < gobanLength && goban[k][l] == nb) {
    setDividerDiag2(goban, tmp , i, j, gobanLength, save, divider, nbOpponent);
    if (nb == 1)
      addScore(tmp, totalj1, divider);
    else
      addScore(tmp, totalj2, divider);

    k -= 1;
    l += 1;
    ++tmp;
  }
}

void Minmax::countSeries(vector<vector<int> > &goban, int nbOpponent, int &totalj1, int &totalj2, int gobanLength, int maxY, int maxX) {
  int tmp1, tmp2, tmp3, tmp4, divider, save1, save2, save3, save4;

  for (int i = 0; i < maxY; ++i) {
    tmp1 = 0;
    tmp3 = 0;
    tmp2 = 0;
    tmp4 = 0;

    save1 = 0;
    save2 = 0;
    save3 = 0;
    save4 = 0;

    for (int j = 0; j < maxX; ++j) {

      divider = 0;
      if (goban[i][j] == 1) {
        setDivider(goban, tmp1, i, j, gobanLength, save1, divider, nbOpponent);
        ++tmp1;
        tmp2 = 0;
        save2 = 0;
        addScore(tmp1, totalj1, divider);
      }
      else if (goban[i][j] == 2) {
        setDivider(goban, tmp2, i, j, gobanLength, save2, divider, nbOpponent);
        ++tmp2;
        tmp1 = 0;
        save1 = 0;
        addScore(tmp2, totalj2, divider);
      }

      divider = 0;
      if (goban[j][i] == 1) {
        setDivider(goban, tmp3, j, i, gobanLength, save3, divider, nbOpponent);
        ++tmp3;
        tmp4 = 0;
        save4 = 0;
        addScore(tmp3, totalj1, divider);
      }
      else if (goban[j][i] == 2) {
        setDivider(goban, tmp4, j, i, gobanLength, save4, divider, nbOpponent);
        ++tmp4;
        tmp3 = 0;
        save3 = 0;
        addScore(tmp4, totalj2, divider);
      }

      divider = 0;
      if (goban[i][j] == 1)
        checkDiag(goban, totalj1, totalj2, gobanLength, i, j, 1, divider, nbOpponent);
      else if (goban[i][j] == 2)
        checkDiag(goban, totalj1, totalj2, gobanLength, i, j, 2, divider, nbOpponent);
    }
  }
}

int Minmax::eval(vector<vector<int> > &goban, int nbPlayer, int nbOpponent, bool win, int nbWinner, int maxY, int maxX) {
  int seriej1 = 0, seriej2 = 0, totalj1 = 0, totalj2 = 0, nbDraughts = 0, size = goban.size();

  if (win == true) {
    for (int i = 0; i < maxY; ++i)
      for (int j = 0; j < maxX; ++j)
        if (goban[i][j] != 0)
          ++nbDraughts;
    return nbPlayer == nbWinner ? 10000 - nbDraughts : -10000 + nbDraughts;
  } else {
    countSeries(goban, nbOpponent, totalj1, totalj2, size, maxY, maxX);
    return nbPlayer == 1 ? totalj1 - totalj2 : totalj2 - totalj1;
  }
}
