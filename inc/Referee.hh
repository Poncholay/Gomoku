//
// Referee.hh for Gomoku in /home/albanbin/rendu/Gomoku/
//
// Made by Combaud Alban
// Login   <alban.combaud@epitech.eu@epitech.eu>
//
// Started on  Wed Oct 12 13:15:51 2016 Combaud Alban
// Last update Sun Dec  4 12:04:37 2016 Adrien Milcent
//

#ifndef REFEREE_HH_
# define REFEREE_HH_

# include <vector>
# include <iostream>
# include "Goban.hpp"
# include "Displayer.hpp"

class Goban;

enum Result {
WIN,
CONTINUE,
REPLAY,
WIN_INVERSE  };

class Referee {
private:
  bool _advanced;
  int   nbPairplayer1;
  int   nbPairplayer2;
  int   nbPairBroken1;
  int   nbPairBroken2;
  bool  isBroke1;
  bool  isBroke2;
  bool  isMockBroke1;
  bool  isMockBroke2;
  pair<int, int> play;
  pair<int, int> breakingPlay;
  Goban &goban;

  Result  checkWin(int, int, int);
  bool checkRules(int, int, int, int);
  bool checkWinBy5(int, int, int, bool = false);
  bool checkBrokenFive(int, int, int, int);
  int  checkWinByPair(int, int, int);
  void setPair(int, int);
  bool checkHorizon(int, int, int, int);
  bool checkVertical(int, int, int, int);
  bool checkDiagoDown(int, int, int, int);
  bool checkDiagoUp(int, int, int, int);

public:
  Referee(Goban &, bool);
  ~Referee();

  Result checkPlay(int, int, int, bool = true);
  void removePair(int, int, int, int, int, bool);
  void undoNbPair(int);
  void updatePair(int, int, int, bool = true);

  bool   getIsBroke(int) const;
  string getPairs(int) const;
  Goban &getGoban();

};

#endif
