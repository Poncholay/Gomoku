//
// Minmax.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 13:59:50 2016 Adrien Milcent
// Last update Tue Nov 15 17:48:58 2016 Adrien Milcent
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
          tmp = eval(goban, nbPlayer, true, nbPlayer, maxY, maxX);
        else if (res != REPLAY) {
          if (nbTurn == 0)
            tmp = eval(goban, nbPlayer, false, nbPlayer, maxY, maxX);
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
  //std::cout << maxX << " " << maxY << " checked: " << cnt << std::endl;
  std::pair<int, int> result = std::pair<int, int> (maxj, maxi);
  return result;
}

int Minmax::min(std::vector<std::vector<int> > &goban, int nbTurn, int nbPlayer, int nbOpponent, Referee referee, int maxY, int maxX) {
  int min_nb = 100000;
  int tmp = 100000;

  for (int i = 0; i < maxY; ++i) {
    for (int j = 0; j < maxX; ++j) {
      if (goban[i][j] == 0) {
        goban[i][j] = nbPlayer;
        if (referee.checkPlay(j, i, nbOpponent) == WIN)
          tmp = eval(goban, nbPlayer, true, nbOpponent, maxY, maxX);
        else if (nbTurn == 0)
          tmp = eval(goban, nbPlayer, false, nbOpponent, maxY, maxX);
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
          tmp = eval(goban, nbPlayer, true, nbPlayer, maxY, maxX);
        else if (nbTurn == 0)
          tmp = eval(goban, nbPlayer, false, nbPlayer, maxY, maxX);
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

void Minmax::addScore(int nb, int &total) {
  if (nb == 2)
    total += 2;
  else if (nb == 3)
    total += 20;
  else if (nb == 4)
    total += 100;
}

void Minmax::checkDiag(std::vector<std::vector<int> > &goban, int &totalj1, int &totalj2, int gobanLength, int i, int j, int nb) {
  int tmp = 1, k = i, l = j;

  while (k < gobanLength && l < gobanLength && goban[k][l] == nb) {
    if (nb == 1)
      addScore(tmp, totalj1);
    else
      addScore(tmp, totalj2);

    k += 1;
    l += 1;
    ++tmp;
  }

  k = i;
  l = j;
  tmp = 1;
  while (k >= 0 && l < gobanLength && goban[k][l] == nb) {
    if (nb == 1)
      addScore(tmp, ref(totalj1));
    else
      addScore(tmp, ref(totalj2));

    k -= 1;
    l += 1;
    ++tmp;
  }
}

void Minmax::countSeries(std::vector<std::vector<int> > &goban, int &totalj1, int &totalj2, int gobanLength, int maxY, int maxX) {
  int tmp1, tmp2, tmp3, tmp4;

  for (int i = 0; i < maxY; ++i) {
    tmp1 = 0;
    tmp2 = 0;
    tmp3 = 0;
    tmp4 = 0;

    for (int j = 0; j < maxX; ++j) {

      if (goban[i][j] == 1) {
        ++tmp1;
        tmp2 = 0;
        addScore(tmp1, ref(totalj1));
      }
      else if (goban[i][j] == 2) {
        ++tmp2;
        tmp1 = 0;
        addScore(tmp2, ref(totalj2));
      }

      if (goban[j][i] == 1) {
        ++tmp3;
        tmp4 = 0;
        addScore(tmp3, ref(totalj1));
      }
      else if (goban[j][i] == 2) {
        ++tmp4;
        tmp3 = 0;
        addScore(tmp4, ref(totalj2));
      }

      if (goban[i][j] == 1)
        checkDiag(goban, ref(totalj1), ref(totalj2), gobanLength, i, j, 1);
      else if (goban[i][j] == 2)
        checkDiag(goban, ref(totalj1), ref(totalj2), gobanLength, i, j, 2);
    }
  }
}

int Minmax::eval(std::vector<std::vector<int> > &goban, int nbPlayer, bool win, int nbWinner, int maxY, int maxX) {
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
    countSeries(goban, ref(totalj1), ref(totalj2), size, maxY, maxX);
    if (nbPlayer == 1)
      return totalj1 - totalj2;
    else
      return totalj2 - totalj1;
  }
}
