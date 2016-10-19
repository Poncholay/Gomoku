//
// AI.hh for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 14:19:59 2016 Adrien Milcent
// Last update Wed Oct 19 12:48:43 2016 Adrien Milcent
//

#ifndef AI_HH_
# define AI_HH_

class AI {
private:
  Goban _goban;
  auto _algo;
  int _nbPlayer;
  int _nbOpponent;
public:
  AI(Goban &, int, int);
  ~AI();

  play();
};

#endif /* !AI_HH_ */
