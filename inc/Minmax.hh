//
// Minmax.hh for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 13:59:45 2016 Adrien Milcent
// Last update Mon Oct 24 11:19:40 2016 Adrien Milcent
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

  std::pair<int, int> loop(std::vector<std::vector<int> > &, int, int, Referee);
  int min(std::vector<std::vector<int> > &, int, int, int, Referee);
  int max(std::vector<std::vector<int> > &, int, int, int, Referee);
  int eval(std::vector<std::vector<int> > &, int, bool, int);
  void checkDiag(std::vector<std::vector<int> > &, int &, int &, int, int, int, int, int);
  void countSeries(std::vector<std::vector<int> > &, int &, int &, int);
};

#endif /* !MINMAX_HH_ */
