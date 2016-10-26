/*
** Game.hh for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Wed Oct 26 16:07:43 2016 wilmot_g
** Last update Wed Oct 26 22:29:30 2016 wilmot_g
*/

#ifndef GAME_HH_
# define GAME_HH_

# include <atomic>
# include "IPlayer.hh"

class     Game {
public:
  Game();
  ~Game();

  static void doPlay(IPlayer *, Referee, atomic<bool> &);
  int         play(int);
};

#endif /* !GAME_HH_ */
