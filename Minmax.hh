//
// Minmax.hh for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 13:59:45 2016 Adrien Milcent
// Last update Wed Oct 19 17:29:31 2016 Adrien Milcent
//

#ifndef MINMAX_HH_
# define MINMAX_HH_

# include <iostream>
# include <string>
# include <vector>

class Minmax {
private:
  int _nbTurn;
public:
  Minmax(int);
  ~Minmax();

  std::pair<int, int> loop(std::vector<std::vector<int> > &, int, int);
  int min(std::vector<std::vector<int> > &, int, int, int);
  int max(std::vector<std::vector<int> > &, int, int, int);
  int eval(std::vector<std::vector<int> > &, int, bool, int);
  void checkDiag(std::vector<std::vector<int> > &, int &, int &, int, int, int, int, int);
  void countSeries(std::vector<std::vector<int> > &, int &, int &, int);
};

#endif /* !MINMAX_HH_ */
