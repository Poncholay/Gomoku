//
// AI.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 14:20:06 2016 Adrien Milcent
// Last update Tue Oct 18 17:10:13 2016 Adrien Milcent
//

#include "AI.hh"

AI::AI(Goban &goban, int nbPlayer, int nbTurn) {
  _goban = goban;
  _minmax = Minmax(nbTurn);
  _nbPlayer = nbPlayer;
  if (_nbPlayer == 1)
    _nbOpponent = 2;
  else
    _nbOpponent = 1;
}

AI::~AI() {

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
