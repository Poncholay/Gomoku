/*
** Main.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Last update Tue Nov 08 19:27:58 2016 wilmot_g
** Last update Tue Dec 06 13:29:06 2016 wilmot_g
*/

#include <iostream>
#include <thread>
#include "Displayer.hpp"
#include "Referee.hh"
#include "AI.hh"
#include "Game.hh"
#include "Human.hh"
#include "Sounds.hpp"

Game::Game()  {_players = 1;}
Game::~Game() {}

void          Game::setPlayers(int p)         {_players = p;}
void          Game::setAdvancedRules(bool r)  {_rules = r;}

void          Game::doPlay(IPlayer *player, Referee &referee, atomic<bool> &done, atomic<int> &playValue) {
  playValue = player->play(referee);
  done = true;
}

string        Game::score(const Referee &r, const vector<IPlayer *> &p, int turn) {
  string      score;

  score += "Player 1 pairs (" + p[0]->getType() + ")\t: " + r.getPairs(1) + "\n";
  score += "Player 2 pairs (" + p[1]->getType() + ")\t: " + r.getPairs(2) + "\n";
  score += p[turn]->getReflexionTime();
  return score;
}

int           Game::play(int param) {
  Displayer   displayer;
  Goban       goban(displayer);
  Referee     referee(goban, _rules);
  int         ret = 0;
  int         turn = 1;
  vector<IPlayer *>   players;
  atomic<bool>        done(true);
  atomic<int>         playValue(CONTINUE);
  thread              *t = NULL;

  if (displayer.error() || !displayer.instanciate()) return -1;

  Sounds::get().stopMusic();
  Sounds::get().playMusic("game");
  goban.setReferee(&referee);

  players.push_back(_players != 3 ? (IPlayer *)(new Human(goban, displayer, 1, GOBAN_X, GOBAN_Y)) : (IPlayer *)(new AI(goban, 1, 3)));
  players.push_back(_players != 1 ? (IPlayer *)(new AI(goban, 2, 3)) : (IPlayer *)(new Human(goban, displayer, 2, GOBAN_X, GOBAN_Y)));

  while (displayer.isRunning() && !displayer.getReceiver().checkEnd() && playValue == CONTINUE) {
    displayer.setScore(score(referee, players, turn));
    if ((ret = displayer.display()) != 0)
      break;
    if (!displayer.isAnimating() && done) {
      if (!t && playValue == CONTINUE) {
        done = false;
        t = new thread(doPlay, players[(turn = turn ? 0 : 1)], ref(referee), ref(done), ref(playValue));
      } else {
        if (t) {
          t->join();
          delete t;
        }
        t = NULL;
        if (displayer.getReceiver().checkEnd()) break;
        displayer.animate();
      }
    }
  }
  if (playValue == WIN || playValue == WIN_INVERSE) {
    while (displayer.isRunning() && displayer.isAnimating())
      if ((ret = displayer.display()) != 0 || displayer.getReceiver().checkEnd())
        break;
    displayer.setAnimate(0, 0, -1);
    displayer.setTime(5);
    while (displayer.isRunning() && displayer.isAnimating())
      if ((ret = displayer.display(playValue == WIN ? turn + 1 : turn ? 1 : 2)) != 0 || displayer.getReceiver().checkEnd())
        break;
  }
  if (t) {t->join(); delete t;}
  Sounds::get().stopMusic();
  Sounds::get().stopSounds();
  return ret;
}
