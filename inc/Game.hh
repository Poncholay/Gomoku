/*
** Game.hh for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Wed Oct 26 16:07:43 2016 wilmot_g
** Last update Sun Dec 11 23:01:09 2016 wilmot_g
*/

#ifndef GAME_HH_
# define GAME_HH_

# include <atomic>
# include "IPlayer.hh"

class     Game {
public:
  Game();
  ~Game();

  static void doPlay(IPlayer *, Referee &, atomic<bool> &, atomic<int> &);

  int         play();
  void        setPlayers(int);
  void        setAiDepth(int);
  void        setBenchmark(bool);
  void        setOptimisation(bool);
  void        setOptiFive(bool);
  void        setAlphaBeta(bool);
  void        setAdvancedRules(bool);
  void        setCalculateDiagonals(bool);
  void        setCalculateRows(bool);
  string      score(const Referee &r, const vector<IPlayer *> &p, int);

private:

  int         _aiDepth;
  int         _players;
  bool        _rules;
  bool        _bench;
  bool        _optimise;
  bool        _optiFive;
  bool        _alphaBeta;
  bool        _rows;
  bool        _diago;
};

#endif /* !GAME_HH_ */
