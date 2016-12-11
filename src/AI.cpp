//
// AI.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 14:20:06 2016 Adrien Milcent
// Last update Sun Dec 11 18:01:01 2016 Adrien Milcent
//

#include "AI.hh"

AI::AI(Goban &goban, int nbPlayer, int nbTurn, bool opti, bool rows, bool diago, bool bench, bool alpha) : _algo(AlphaBetaMinimax(nbTurn, opti, rows, diago, alpha)), _goban(goban) {
  _nbPlayer = nbPlayer;
  _benchmark = bench;
  _thinking = false;
  _start = chrono::high_resolution_clock::now();
}

AI::~AI() {}

int     AI::play(Referee &referee) {
  if (_benchmark) {
    _start = chrono::high_resolution_clock::now();
    _thinking = true;
  }
  pair<int, int> result = _algo.loop(_nbPlayer, referee);
  if (_benchmark) {
    _end = chrono::high_resolution_clock::now();
    _thinking = false;
  }

  if (result.first == -1 || result.second == -1)
    return -1;
  int res = referee.checkPlay(result.first, result.second, _nbPlayer, false);
  _goban.addDraught(result.first, result.second, _nbPlayer, true);
  return res;
}

void    AI::setBenchmark(bool b) {_benchmark = b;}

string  AI::getReflexionTime() const {
  if (!_benchmark)
    return "";
  if (_thinking) {
    auto res = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count() - chrono::duration_cast<chrono::microseconds>(_start.time_since_epoch()).count();
    return "Player " + to_string(_nbPlayer) + " Decision time : " + to_string(res / 1000000.0) + '\n';
  }
  auto res = chrono::duration_cast<chrono::microseconds>(_end.time_since_epoch()).count() - chrono::duration_cast<chrono::microseconds>(_start.time_since_epoch()).count();
  return "Player " + to_string(_nbPlayer) + " Decision time : " + to_string(res / 1000000.0) + '\n';
}

string  AI::getType() const {
  return "AI";
}
