//
// Goban.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Wed Oct 12 15:27:04 2016 Adrien Milcent
// Last update Tue Nov 29 23:11:06 2016 Adrien Milcent
//

#include <bitset>
#include "Goban.hh"

Goban::Goban(Displayer &d, int xBoard, int yBoard) : _displayer(d) {
  _xBoard = xBoard;
  _yBoard = yBoard;
  _board = vector<vector<char> > (yBoard, vector<char>(xBoard, 0));
  _heuristics = vector<vector<char> > (yBoard, vector<char>(xBoard, 1));
  _heuristics[1][1] = 0;
  _xMaxCheck = 3;
  _yMaxCheck = 3;
}

Goban::~Goban() {}

Goban::Goban(Goban &other) : _displayer(other.getDisplayer()) {
  if (this != &other) {
    _xBoard = other.getXBoard();
    _yBoard = other.getYBoard();
    _board = other.getBoard();
    _xMaxCheck = other.getXMaxCheck();
    _yMaxCheck = other.getYMaxCheck();
  }
}

Goban &Goban::operator=(Goban &other) {
  if (this != &other) {
    _xBoard = other.getXBoard();
    _yBoard = other.getYBoard();
    _board = other.getBoard();
    _xMaxCheck = other.getXMaxCheck();
    _yMaxCheck = other.getYMaxCheck();
  }
  return *this;
}

void Goban::addDraught(int x, int y, int player, bool move) {
  _board[y].at(x) = player;
  if (_r) _r->updatePair(x, y, player);
  if (move) {
    _displayer.setAnimate(x, y, player);
    if (x > _xMaxCheck - 2) _xMaxCheck = x + 2;
    if (y > _yMaxCheck - 2) _yMaxCheck = y + 2;
    _xMaxCheck = _xMaxCheck > _xBoard ? _xBoard : _xMaxCheck;
    _yMaxCheck = _yMaxCheck > _yBoard ? _yBoard : _yMaxCheck;
    updateWeights(x, y, _heuristics);
  }
}

void Goban::removeDraught(int x, int y, bool move) {
  _board[y].at(x) = 0;
  if (move)
    _displayer.setAnimate(x, y, 0);
}

void Goban::printBoard(int x1, int y1) const {
  cout << "Goban :" << endl;
  for (int y = 0; y < _yMaxCheck; y++) {
    for (int x = 0; x < _xMaxCheck; x++)
      if (x == x1 && y == y1)
        cout << "\033[0;31m" << static_cast<int>(_board[y][x]) << " " << "\033[0m";
      else
        cout << static_cast<int>(_board[y][x]) << " ";
    cout << endl;
  }
  cout << endl;
}

void Goban::printHeuristic(vector<vector<char> > &heuristics) const {
  cout << "Heuristics :" << endl;
  for (int y = 0; y < _yMaxCheck; y++) {
    for (int x = 0; x < _xMaxCheck; x++)
      cout << static_cast<int>(heuristics[y][x]) << " ";
      // cout << bitset<8>(_heuristics[y][x]) << " ";
      // cout << ((_heuristics[y][x] >> 0) & 1) << " ";
    cout << endl;
  }
  cout << endl;
}

bool Goban::setHeuristicXY(int x, int y, int bit, bool set, vector<vector<char> > &heuristics) const {
  if (x >= 0 && y >= 0 && x < _xBoard - 1 && y < _yBoard - 1) {
      bool back = (heuristics[y][x] >> bit) & 1;
      if (set && _board[y][x] == 0)
        heuristics[y][x] |= 1 << bit;
      else if (!set)
        heuristics[y][x] &= ~(1 << bit);
      return back;
  }
  return false;
}

int Goban::updateWeights(int x, int y, vector<vector<char> > &heuristics) const {
  // cout << "Before" << endl;
  // printBoard();
  // printHeuristic(heuristics);
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
  // cout << "After" << endl;
  // printBoard();
  // printHeuristic(heuristics);
  return ret;
}

void Goban::revertWeights(int x, int y, int changes, vector<vector<char> > &heuristics) const {
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

bool Goban::full() const {for (auto i : _board) for(auto j : i) if (j == 0) return false; return true;}
void Goban::setReferee(Referee *r)   {_r = r;}
int Goban::getXBoard()    const {return _xBoard;}
int Goban::getYBoard()    const {return _yBoard;}
int Goban::getXMaxCheck() const {return _xMaxCheck;}
int Goban::getYMaxCheck() const {return _yMaxCheck;}

vector<char>  &Goban::operator[](int box)     {return _board[box];}
vector<char>  &Goban::operator()(int box)     {return _heuristics[box];}
vector<vector<char> > &Goban::getBoard()      {return _board;}
vector<vector<char> > &Goban::getHeuristics() {return _heuristics;}
Displayer             &Goban::getDisplayer()  {return _displayer;}
