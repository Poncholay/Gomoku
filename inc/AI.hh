//
// AI.hh for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 14:19:59 2016 Adrien Milcent
// Last update Tue Nov  8 15:27:16 2016 Adrien Milcent
//

#ifndef AI_HH_
# define AI_HH_

# include <iostream>
# include <string>
# include <vector>

# include "IPlayer.hh"
# include "Goban.hh"
# include "Minmax.hh"

class AI : public IPlayer {
private:
  Minmax _algo;
  Goban &_goban;
  int _nbPlayer;

public:
  AI(Goban &, int, int);
  ~AI();

  string getType() const;
  int play(Referee);
};

#endif /* !AI_HH_ */
