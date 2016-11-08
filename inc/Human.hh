/*
** Human.hh for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Oct 31 19:20:43 2016 wilmot_g
** Last update Tue Nov 08 19:39:34 2016 wilmot_g
*/

#ifndef HUMAN_HH_
# define HUMAN_HH_

# include "IPlayer.hh"
# include "Displayer.hpp"
# include "Goban.hh"

class Human : public IPlayer {
public:
  Human(Goban &, Displayer &, int, int, int);
  ~Human();

  string getType() const;
  int play(Referee);

private:
  Displayer   &_displayer;
  Goban       &_goban;
  int         _x;
  int         _y;
  int         _i;
  int         _j;
  int         _nb;
};

#endif /* !HUMAN_HH_ */
