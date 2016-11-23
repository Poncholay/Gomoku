//
// Minmax.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 13:59:50 2016 Adrien Milcent
// Last update Tue Nov 22 18:51:44 2016 Adrien Milcent
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

std::pair<int, int> Minmax::loop(std::vector<std::vector<int> > &goban, int nbPlayer, Referee referee) {
  int max_nb = -100000;
  int nbTurn = _nbTurn;
  int maxX = referee.getGoban().getXMaxCheck();
  int maxY = referee.getGoban().getYMaxCheck();
  int size = goban.size();
  Result res;
  int cnt = 0;
  int tmp = 0, maxi = -1, maxj = -1, nbOpponent = 0;

  if (nbPlayer == 1)
    nbOpponent = 2;
  else
    nbOpponent = 1;

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
            tmp = min(goban, nbTurn - 1, nbPlayer, nbOpponent, referee, maxY, maxX);
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
  std::pair<int, int> result = std::pair<int, int> (maxj, maxi);
  return result;
}

int Minmax::min(std::vector<std::vector<int> > &goban, int nbTurn, int nbPlayer, int nbOpponent, Referee referee, int maxY, int maxX) {
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
          tmp = max(goban, nbTurn - 1, nbPlayer, nbOpponent, referee, maxY, maxX);
        if (tmp < min_nb) {
          min_nb = tmp;
        }
        goban[i][j] = 0;
      }
    }
  }
  return min_nb;
}

int Minmax::max(std::vector<std::vector<int> > &goban, int nbTurn, int nbPlayer, int nbOpponent, Referee referee, int maxY, int maxX) {
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
          tmp = min(goban, nbTurn - 1, nbPlayer, nbOpponent, referee, maxY, maxX);

        if (tmp > max_nb) {
          max_nb = tmp;
        }
        goban[i][j] = 0;
      }
    }
  }
  return max_nb;
}

void Minmax::addScore(int nb, int &total, int divider) {
  if (nb == 2 && divider != 0)
    total += (2 / divider);
  else if (nb == 3 && divider != 0)
    total += (20 / divider);
  else if (nb == 4 && divider != 0)
    total += (100 / divider);
}

void Minmax::setDivider(std::vector<std::vector<int> > goban, int tmp, int i, int j, int gobanLength, int &save, int &divider, int nbOpponent) {
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

void Minmax::setDividerDiag1(std::vector<std::vector<int> > goban, int tmp, int i, int j, int gobanLength, int &save, int &divider, int nbOpponent) {
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

void Minmax::setDividerDiag2(std::vector<std::vector<int> > goban, int tmp, int i, int j, int gobanLength, int &save, int &divider, int nbOpponent) {
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

void Minmax::checkDiag(std::vector<std::vector<int> > &goban, int &totalj1, int &totalj2, int gobanLength, int i, int j, int nb, int &divider, int nbOpponent) {
  int tmp = 1, save = 0, k = i, l = j;

  while (k < gobanLength && l < gobanLength && goban[k][l] == nb) {
    setDividerDiag1(goban, tmp, i, j, gobanLength, ref(save), ref(divider), nbOpponent);
    if (nb == 1)
      addScore(tmp, ref(totalj1), divider);
    else
      addScore(tmp, ref(totalj2), divider);

    k += 1;
    l += 1;
    ++tmp;
  }

  k = i;
  l = j;
  tmp = 1;
  save = 0;
  while (k >= 0 && l < gobanLength && goban[k][l] == nb) {
    setDividerDiag2(goban, tmp , i, j, gobanLength, ref(save), ref(divider), nbOpponent);
    if (nb == 1)
      addScore(tmp, ref(totalj1), divider);
    else
      addScore(tmp, ref(totalj2), divider);

    k -= 1;
    l += 1;
    ++tmp;
  }
}

void Minmax::countSeries(std::vector<std::vector<int> > &goban, int nbOpponent, int &totalj1, int &totalj2, int gobanLength, int maxY, int maxX) {
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
        setDivider(goban, tmp1, i, j, gobanLength, ref(save1), ref(divider), nbOpponent);
        ++tmp1;
        tmp2 = 0;
        save2 = 0;
        addScore(tmp1, ref(totalj1), divider);
      }
      else if (goban[i][j] == 2) {
        setDivider(goban, tmp2, i, j, gobanLength, ref(save2), ref(divider), nbOpponent);
        ++tmp2;
        tmp1 = 0;
        save1 = 0;
        addScore(tmp2, ref(totalj2), divider);
      }

      divider = 0;
      if (goban[j][i] == 1) {
        setDivider(goban, tmp3, j, i, gobanLength, ref(save3), ref(divider), nbOpponent);
        ++tmp3;
        tmp4 = 0;
        save4 = 0;
        addScore(tmp3, ref(totalj1), divider);
      }
      else if (goban[j][i] == 2) {
        setDivider(goban, tmp4, j, i, gobanLength, ref(save4), ref(divider), nbOpponent);
        ++tmp4;
        tmp3 = 0;
        save3 = 0;
        addScore(tmp4, ref(totalj2), divider);
      }



      divider = 0;
      if (goban[i][j] == 1)
        checkDiag(goban, ref(totalj1), ref(totalj2), gobanLength, i, j, 1, ref(divider), nbOpponent);
      else if (goban[i][j] == 2)
        checkDiag(goban, ref(totalj1), ref(totalj2), gobanLength, i, j, 2, ref(divider), nbOpponent);
    }
  }
}

int Minmax::eval(std::vector<std::vector<int> > &goban, int nbPlayer, int nbOpponent, bool win, int nbWinner, int maxY, int maxX) {
  int seriej1 = 0, seriej2 = 0, totalj1 = 0, totalj2 = 0, nbDraughts = 0, size = goban.size();

  if (win == true) {
    for (int i = 0; i < maxY; ++i) {
      for (int j = 0; j < maxX; ++j) {
        if (goban[i][j] != 0)
          ++nbDraughts;
      }
    }
    if (nbPlayer == nbWinner)
      return (10000 - nbDraughts);
    else
      return (-10000 + nbDraughts);
  }
  else {
    countSeries(goban, nbOpponent, ref(totalj1), ref(totalj2), size, maxY, maxX);
    if (nbPlayer == 1)
      return totalj1 - totalj2;
    else
      return totalj2 - totalj1;
  }
}
