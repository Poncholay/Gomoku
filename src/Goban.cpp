//
// Goban.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Wed Oct 12 15:27:04 2016 Adrien Milcent
// Last update Mon Oct 17 16:39:59 2016 Combaud Alban
//

#include "Goban.hh"

Goban::Goban(int xBoard, int yBoard) {
  _xBoard = xBoard;
  _yBoard = yBoard;
  std::vector<int> a = std::vector<int>   (xBoard, 0);
  _board = std::vector<std::vector<int> > (yBoard, a);
}

Goban::~Goban() {}

Goban::Goban(Goban &other) {
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

std::vector<int>  &Goban::operator[](int box) {
  return _board[box];
}

void Goban::addDraught(int x, int y, int player) {
  _board[y].at(x) = player;
}

void Goban::removeDraught(int x, int y) {
  _board[y].at(x) = 0;
}

void Goban::printBoard() const {
  for (std::vector<std::vector<int> >::const_iterator it = _board.begin(); it != _board.end(); it++) {
    for (std::vector<int>::const_iterator it2 = it->begin(); it2 != it->end(); it2++)
      std::cout << *it2 << " ";
    std::cout << std::endl;
  }
}

int Goban::getXBoard() const {return _xBoard;}
int Goban::getYBoard() const {return _yBoard;}
std::vector<std::vector<int> >  Goban::getBoard() const {return _board;}
// void                            setDisplayer(Displayer &d) {_displayer = d;}
