//
// Minmax.hh for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 13:59:45 2016 Adrien Milcent
// Last update Mon Nov 28 19:00:14 2016 Adrien Milcent
//

#ifndef MINMAX_HH_
# define MINMAX_HH_

# include <iostream>
# include <string>
# include <vector>

# include "Referee.hh"

class Minmax {
private:
  int _nbTurn;
public:
  Minmax(int);
  ~Minmax();

  std::pair<int, int> loop(std::vector<std::vector<int> > &, int, Referee);
  int min(std::vector<std::vector<int> > &, int, int, int, int, Referee, int, int);
  int max(std::vector<std::vector<int> > &, int, int, int, int, Referee, int, int);
  int checkPair(vector<vector<int> > &, int, int, int, int);
  int eval(std::vector<std::vector<int> > &, int, int, bool, int, int, int);
  void checkDiag(std::vector<std::vector<int> > &, int &, int &, int, int, int, int, int &, int);
  void countSeries(std::vector<std::vector<int> > &, int, int &, int &, int, int, int);
  void setDivider(std::vector<std::vector<int> >, int, int, int, int, int &, int &, int);
  void setDividerDiag1(std::vector<std::vector<int> >, int, int, int, int, int &, int &, int);
  void setDividerDiag2(std::vector<std::vector<int> >, int, int, int, int, int &, int &, int);
  void addScore(int, int &, int);
};

#endif /* !MINMAX_HH_ */
