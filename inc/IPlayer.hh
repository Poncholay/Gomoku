/*
** Player.hh for  in /home/wilmot_g/Epitech/IA/Gomoku/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Wed Oct 26 18:07:17 2016 wilmot_g
** Last update Wed Oct 26 22:14:24 2016 wilmot_g
*/

#ifndef PLAYER_HH_
# define PLAYER_HH_

# include "Referee.hh"

class Referee;

class IPlayer {
public:
  virtual ~IPlayer() {}
  virtual void play(Referee) = 0;
};

#endif /* !PLAYER_HH_ */
