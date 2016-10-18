//
// AI.hh for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 14:19:59 2016 Adrien Milcent
// Last update Tue Oct 18 17:10:24 2016 Adrien Milcent
//

#ifndef AI_HH_
# define AI_HH_

class AI {
private:
  Goban _goban;
  Minmax _minmax;
  int _nbPlayer;
  int _nbOpponent;
public:
  AI(Goban &, int, int);
  ~AI();

  play();
};

#endif /* !AI_HH_ */
