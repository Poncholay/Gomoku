//
// Minmax.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 13:59:50 2016 Adrien Milcent
// Last update Tue Nov  8 13:41:41 2016 Adrien Milcent
//

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

  int tmp = 0, maxi = -1, maxj = -1, nbOpponent = 0;
  if (nbPlayer == 1)
    nbOpponent = 2;
  else
    nbOpponent = 1;

  for (unsigned int i = 0; i < goban.size(); ++i) {
    for (unsigned int j = 0; j < goban.size(); ++j) {
      if (goban[i][j] == 0) {
        goban[i][j] = nbPlayer;
        if (referee.checkPlay(j, i, nbPlayer) == WIN)
          tmp = eval(goban, nbPlayer, true, nbPlayer);
        else if (nbTurn == 0)
          tmp = eval(goban, nbPlayer, false, nbPlayer);
        else
          tmp  = max(goban, nbTurn - 1, nbPlayer, nbOpponent, referee);
        if (tmp > max_nb) {
          max_nb = tmp;
          maxi = i;
          maxj = j;
        }
        goban[i][j] = 0;
      }
    }
  }
  std::pair<int, int> result = std::pair<int, int> (maxj, maxi);
  return result;
}

int Minmax::min(std::vector<std::vector<int> > &goban, int nbTurn, int nbPlayer, int nbOpponent, Referee referee) {
  int min_nb = 100000;
  int tmp = 0;

  for (unsigned int i = 0; i < goban.size(); ++i) {
    for (unsigned int j = 0; j < goban.size(); ++j) {
      if (goban[i][j] == 0) {
        goban[i][j] = nbPlayer;
        if (referee.checkPlay(j, i, nbPlayer) == WIN)
          tmp = eval(goban, nbPlayer, true, nbPlayer);
        else if (nbTurn == 0)
          tmp = eval(goban, nbPlayer, false, nbPlayer);
        else
          tmp = max(goban, nbTurn - 1, nbPlayer, nbOpponent, referee);

        if (tmp < min_nb) {
          min_nb = tmp;
        }
        goban[i][j] = 0;
      }
    }
  }
  return min_nb;
}

int Minmax::max(std::vector<std::vector<int> > &goban, int nbTurn, int nbPlayer, int nbOpponent, Referee referee) {
  int max_nb = -100000;
  int tmp = 0;

  for (unsigned int i = 0; i < goban.size(); ++i) {
    for (unsigned int j = 0; j < goban.size(); ++j) {
      if (goban[i][j] == 0) {
        goban[i][j] = nbOpponent;
        if (referee.checkPlay(j, i, nbOpponent) == WIN)
          tmp = eval(goban, nbPlayer, true, nbOpponent);
        else if (nbTurn == 0)
          tmp = eval(goban, nbPlayer, false, nbOpponent);
        else
          tmp = min(goban, nbTurn - 1, nbPlayer, nbOpponent, referee);

        if (tmp > max_nb) {
          max_nb = tmp;
        }
        goban[i][j] = 0;
      }
    }
  }
  return max_nb;
}

void Minmax::checkDiag(std::vector<std::vector<int> > &goban, int &seriej1, int &seriej2, int gobanLength, int length, int i, int j, int nb) {
  int tmp = 1, k = i, l = j;

  while (k < gobanLength && l < gobanLength && goban[k][l] == nb) {
    if (tmp == length) {
      if (nb == 1)
        ++seriej1;
      else
        ++seriej2;
    }
    k += 1;
    l += 1;
    ++tmp;
  }

  k = i;
  l = j;
  tmp = 1;
  while (k >= 0 && l < gobanLength && goban[k][l] == nb) {
    if (tmp == length) {
      if (nb == 1)
        ++seriej1;
      else
        ++seriej2;
    }
    k -= 1;
    l += 1;
    ++tmp;
  }
}

void Minmax::countSeries(std::vector<std::vector<int> > &goban, int &seriej1, int &seriej2, int length) {
  int gobanLength = goban.size(), tmp1, tmp2;
  seriej1 = 0;
  seriej2 = 0;

  for (unsigned int i = 0; i < goban.size(); ++i) {
    for (unsigned int j = 0; j < goban.size(); ++j) {
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
    for (unsigned int i = 0; i < goban.size(); ++i) {
      for (unsigned int j = 0; j < goban.size(); ++j) {
        if (goban[i][j] != 0)
          ++nbDraughts;
      }
    }
    if (nbPlayer == nbWinner)
      return 10000 - nbDraughts;
    else {
      std::cout << "c'est la merde: " << -10000 + nbDraughts << std::endl;
      return -10000 + nbDraughts;
    }
  }
  else {
    // countSeries(goban, seriej1, seriej2, 5);
    // totalj1 += seriej1 * 1000;
    // totalj2 += seriej2 * 1000;
    countSeries(goban, seriej1, seriej2, 4);
    totalj1 += seriej1 * 100;
    totalj2 += seriej2 * 100;
    countSeries(goban, seriej1, seriej2, 3);
    totalj1 += seriej1 * 20;
    totalj2 += seriej2 * 20;
    countSeries(goban, seriej1, seriej2, 2);
    totalj1 += seriej1 * 2;
    totalj2 += seriej2 * 2;

    if (nbPlayer == 1)
      return totalj1 - totalj2;
    else
      return totalj2 - totalj1;
  }
}
