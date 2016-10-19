//
// AI.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 14:20:06 2016 Adrien Milcent
// Last update Wed Oct 19 13:35:33 2016 Adrien Milcent
//

#include "AI.hh"

AI::AI(Goban &goban, int nbPlayer, int nbTurn) {
  _goban = goban;
  _algo = Minmax(nbTurn);
  _nbPlayer = nbPlayer;
  if (_nbPlayer == 1)
    _nbOpponent = 2;
  else
    _nbOpponent = 1;
}

AI::~AI() {

}

// Main loop of the AI, begining of the Minmax algo
void AI::play() {
  _algo.loop(_goban.getBoard(), _nbPlayer, _nbTurn);
}
