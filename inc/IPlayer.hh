/*
** Player.hh for  in /home/wilmot_g/Epitech/IA/Gomoku/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Wed Oct 26 18:07:17 2016 wilmot_g
** Last update Tue Nov 08 19:39:13 2016 wilmot_g
*/

#ifndef PLAYER_HH_
# define PLAYER_HH_

# include "Referee.hh"

class Referee;

class IPlayer {
public:
  virtual ~IPlayer() {}
  virtual string getType() const = 0;
  virtual int play(Referee) = 0;
};

#endif /* !PLAYER_HH_ */
