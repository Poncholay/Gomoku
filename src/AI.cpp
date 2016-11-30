//
// AI.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 14:20:06 2016 Adrien Milcent
// Last update Tue Nov 15 17:31:08 2016 Adrien Milcent
//

#include "AI.hh"

// AI::AI(Goban &goban, int nbPlayer, int nbTurn): _algo(Minmax(nbTurn)), _goban(goban) {
//   _nbPlayer = nbPlayer;
// }

AI::AI(Goban &goban, int nbPlayer, int nbTurn) : _algo(AlphaBetaMinimax(nbTurn)), _goban(goban) {
  _nbPlayer = nbPlayer;
}

AI::~AI() {}

int     AI::play(Referee &referee) {
  pair<int, int> result = _algo.loop(_nbPlayer, referee);

  if (result.first == -1 || result.second == -1)
    return -1;
  int res = referee.checkPlay(result.first, result.second, _nbPlayer);
  _goban.addDraught(result.first, result.second, _nbPlayer, true);
  return res;
}

string  AI::getType() const {
  return "AI   ";
}
