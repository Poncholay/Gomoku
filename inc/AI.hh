//
// AI.hh for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 14:19:59 2016 Adrien Milcent
// Last update Wed Nov  9 13:33:52 2016 Combaud Alban
//

#ifndef AI_HH_
# define AI_HH_

# include <iostream>
# include <string>
# include <vector>

# include "IPlayer.hh"
# include "Goban.hpp"
# include "AlphaBetaMinimax.hh"

class AI : public IPlayer {
private:
  AlphaBetaMinimax _algo;
  Goban &_goban;
  int _nbPlayer;
  bool  _benchmark;
  bool  _opti;
  bool  _rows;
  bool  _diago;
  bool _thinking;
  chrono::high_resolution_clock::time_point _end;
  chrono::high_resolution_clock::time_point _start;

public:
  AI(Goban &, int, int, bool = true, bool = true, bool = true, bool = true, bool = true, bool = false);
  ~AI();

  void setBenchmark(bool);
  string getType() const;
  string getReflexionTime() const;
  int play(Referee &);
};

#endif /* !AI_HH_ */
