//
// AI.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 14:20:06 2016 Adrien Milcent
// Last update Tue Nov  8 14:17:41 2016 Adrien Milcent
//

#include "AI.hh"

AI::AI(Goban &goban, int nbPlayer, int nbTurn): _algo(Minmax(nbTurn)), _goban(goban) {
  _nbPlayer = nbPlayer;
}

AI::~AI() {}

bool     AI::play(Referee referee) {
  std::vector<std::vector<int> > goban = _goban.getBoard();
  std::pair<int, int> result = _algo.loop(goban, _nbPlayer, referee);
  if (result.first != -1 && result.second != -1) {
    _goban.addDraught(result.first, result.second, _nbPlayer, true);
    return true;
  }
  return false;
}
