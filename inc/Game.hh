/*
** Game.hh for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Wed Oct 26 16:07:43 2016 wilmot_g
** Last update Tue Nov  8 14:11:31 2016 Adrien Milcent
*/

#ifndef GAME_HH_
# define GAME_HH_

# include <atomic>
# include "IPlayer.hh"

class     Game {
public:
  Game();
  ~Game();

  static void doPlay(IPlayer *, Referee, atomic<bool> &, atomic<bool> &);
  int         play(int);

  void        setPlayers(int);
  void        setAdvancedRules(bool);

  int         _players;
  bool        _rules;
};

#endif /* !GAME_HH_ */
