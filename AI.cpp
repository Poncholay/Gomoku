//
// AI.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 14:20:06 2016 Adrien Milcent
// Last update Wed Oct 19 17:32:28 2016 Adrien Milcent
//

#include "AI.hh"

AI::AI(Goban &goban, int nbPlayer, int nbTurn): _algo(Minmax(nbTurn)) {
  _goban = goban;
  _nbPlayer = nbPlayer;
}

AI::~AI() {

}

void AI::play() {
  std::vector<std::vector<int> > goban = _goban.getBoard();
  std::pair<int, int> result = _algo.loop(goban, _nbPlayer, 5);
  _goban.addDraught(result.first, result.second, _nbPlayer);
}
