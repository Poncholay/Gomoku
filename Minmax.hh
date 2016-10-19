//
// Minmax.hh for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 13:59:45 2016 Adrien Milcent
// Last update Wed Oct 19 14:32:39 2016 Adrien Milcent
//

#ifndef MINMAX_HH_
# define MINMAX_HH_

class Minmax {
private:
  int _nbTurn;
public:
  Minmax(int);
  ~Minmax();

  Min();
  Max();
  Eval();
};

#endif /* !MINMAX_HH_ */
