//
// Goban.hh for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Wed Oct 12 15:26:56 2016 Adrien Milcent
// Last update Mon Oct 24 15:41:37 2016 Adrien Milcent
//

#ifndef GOBAN_HH_
# define GOBAN_HH_

# include <iostream>
# include <string>
# include <vector>

class Goban {
private:
  std::vector<std::vector<int> >  _board;
  int _xBoard;
  int _yBoard;
public:
  Goban(int xBoard = 20, int yBoard = 20);
  Goban(Goban &);
  ~Goban();

  Goban &operator=(Goban &);
  std::vector<int>   &operator[](int);

  int getXBoard() const;
  int getYBoard() const;
  std::vector<std::vector<int> >  getBoard() const;

  void addDraught(int, int, int);
  void removeDraught(int, int);

  void printBoard() const;
};

#endif /* !GOBAN_HH_*/
