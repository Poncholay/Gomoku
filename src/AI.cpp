//
// AI.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 14:20:06 2016 Adrien Milcent
// Last update Wed Nov  9 13:34:07 2016 Combaud Alban
//

#include "AI.hh"

AI::AI(Goban &goban, int nbPlayer, int nbTurn): _algo(Minmax(nbTurn)), _goban(goban) {
  _nbPlayer = nbPlayer;
}

AI::~AI() {}

int     AI::play(Referee &referee) {
  int res = 0;
  std::vector<std::vector<int> > goban = _goban.getBoard();
  std::pair<int, int> result = _algo.loop(goban, _nbPlayer, referee);

  if (result.first != -1 && result.second != -1) {
    res = referee.checkPlay(result.first, result.second, _nbPlayer);
    _goban.addDraught(result.first, result.second, _nbPlayer, true);
    return res;
  }
  return -1;
}

string  AI::getType() const {
  return "AI   ";
}
