//
// Goban.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Wed Oct 12 15:27:04 2016 Adrien Milcent
// Last update Sun Dec 11 18:30:30 2016 Adrien Milcent
//

#include <bitset>
#include "Goban.hpp"

Goban::Goban(Displayer &d, int xBoard, int yBoard) : _displayer(d) {
  _xBoard = xBoard;
  _yBoard = yBoard;
  _board = vector<char> (yBoard * xBoard, 0);
  _heuristics = vector<char> (yBoard * xBoard, 1);
  int a = 10;
  int b = 10;
  _heuristics[a * _xBoard + b] = 0;
}

Goban::~Goban() {}

Goban::Goban(Goban &other) : _displayer(other.getDisplayer()) {
  if (this != &other) {
    _xBoard = other.getXBoard();
    _yBoard = other.getYBoard();
    _board = other.getBoard();
  }
}

Goban &Goban::operator=(Goban &other) {
  if (this != &other) {
    _xBoard = other.getXBoard();
    _yBoard = other.getYBoard();
    _board = other.getBoard();
  }
  return *this;
}

void Goban::addDraught(int x, int y, int player, bool move) {
  _board[y * _xBoard + x] = player;
  if (move) {
    _displayer.setAnimate(x, y, player);
    if (_r) _r->updatePair(x, y, player);
    updateWeights(x, y, _heuristics);
  }
}

void Goban::removeDraught(int x, int y, bool move) {
  _board[y * _xBoard + x] = 0;
  if (move) {
    _displayer.setAnimate(x, y, 0);
    setHeuristicXY(x, y, 0, false, _heuristics);
  }
}

void Goban::printBoard(int x1, int y1) const {
  cout << "Goban :" << endl;
  for (int y = 0; y < _yBoard; y++) {
    for (int x = 0; x < _xBoard; x++)
      if (x == x1 && y == y1)
        cout << "\033[0;31m" << static_cast<int>(_board[y * _xBoard + x]) << " " << "\033[0m";
      else
        cout << static_cast<int>(_board[y * _xBoard + x]) << " ";
    cout << endl;
  }
  cout << endl;
}

void Goban::printHeuristic(vector<char> &heuristics) const {
  cout << "Heuristics :" << endl;
  for (int y = 0; y < _yBoard; y++) {
    for (int x = 0; x < _xBoard; x++)
      cout << static_cast<int>(heuristics[y * _xBoard + x]) << " ";
    cout << endl;
  }
  cout << endl;
}

bool Goban::setHeuristicXY(int x, int y, int bit, bool set, vector<char> &heuristics) const {
  if (x >= 0 && y >= 0 && x < _xBoard && y < _yBoard) {
    bool back = (heuristics[y * _xBoard + x] >> bit) & 1;
    if (_board[y * _xBoard + x] != 0 && bit == 0)
      set = true;
    if (set)
      heuristics[y * _xBoard + x] |= 1 << bit;
    else
      heuristics[y * _xBoard + x] &= ~(1 << bit);
    return back;
  }
  return false;
}

int Goban::updateWeights(int x, int y, vector<char> &heuristics) const {
  int ret = 0;
  ret = setHeuristicXY(x - 1, y - 1, 0, false, heuristics) ? ret | 1 << 0 : ret & ~(1 << 0);
  ret = setHeuristicXY(x    , y - 1, 0, false, heuristics) ? ret | 1 << 1 : ret & ~(1 << 1);
  ret = setHeuristicXY(x + 1, y - 1, 0, false, heuristics) ? ret | 1 << 2 : ret & ~(1 << 2);
  ret = setHeuristicXY(x - 1, y    , 0, false, heuristics) ? ret | 1 << 3 : ret & ~(1 << 3);
  ret = setHeuristicXY(x    , y    , 0, true , heuristics) ? ret | 1 << 4 : ret & ~(1 << 4);
  ret = setHeuristicXY(x + 1, y    , 0, false, heuristics) ? ret | 1 << 5 : ret & ~(1 << 5);
  ret = setHeuristicXY(x - 1, y + 1, 0, false, heuristics) ? ret | 1 << 6 : ret & ~(1 << 6);
  ret = setHeuristicXY(x    , y + 1, 0, false, heuristics) ? ret | 1 << 7 : ret & ~(1 << 7);
  ret = setHeuristicXY(x + 1, y + 1, 0, false, heuristics) ? ret | 1 << 8 : ret & ~(1 << 8);
  return ret;
}

void Goban::revertWeights(int x, int y, int changes, vector<char> &heuristics) const {
  setHeuristicXY(x - 1, y - 1, 0, (changes >> 0) & 1, heuristics);
  setHeuristicXY(x    , y - 1, 0, (changes >> 1) & 1, heuristics);
  setHeuristicXY(x + 1, y - 1, 0, (changes >> 2) & 1, heuristics);
  setHeuristicXY(x - 1, y    , 0, (changes >> 3) & 1, heuristics);
  setHeuristicXY(x    , y    , 0, (changes >> 4) & 1, heuristics);
  setHeuristicXY(x + 1, y    , 0, (changes >> 5) & 1, heuristics);
  setHeuristicXY(x - 1, y + 1, 0, (changes >> 6) & 1, heuristics);
  setHeuristicXY(x    , y + 1, 0, (changes >> 7) & 1, heuristics);
  setHeuristicXY(x + 1, y + 1, 0, (changes >> 8) & 1, heuristics);
}

bool Goban::full() const            {for (auto i : _board) if (i == 0) return false; return true;}
void Goban::setReferee(Referee *r)  {_r = r;}
int Goban::getXBoard() const        {return _xBoard;}
int Goban::getYBoard() const        {return _yBoard;}

vector<char>  &Goban::getBoard()              {return _board;}
vector<char>  &Goban::getHeuristics()         {return _heuristics;}
Displayer     &Goban::getDisplayer()          {return _displayer;}
