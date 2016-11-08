/*
** Main.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Last update Tue Nov 08 19:27:58 2016 wilmot_g
** Last update Tue Nov 08 19:42:22 2016 wilmot_g
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

void          Game::doPlay(IPlayer *player, Referee referee, atomic<bool> &done, atomic<int> &play_value) {
  play_value = player->play(referee);
  done = true;
}

void          Game::setPlayers(int p) {_players = p;}
void          Game::setAdvancedRules(bool r) {_rules = r;}

string        Game::score(const Referee &r, const vector<IPlayer *> &p) {
  string      score;

  score += "Player 1 (" + p[0]->getType() + ") : " + r.getPairs(1) + "\n";
  score += "Player 2 (" + p[0]->getType() + ") : " + r.getPairs(2) + "\n";
  return score;
}

int           Game::play(int param) {
  Displayer   displayer;
  Goban       goban(displayer);
  Referee     referee(goban, _rules);
  int         ret = 0;
  int         turn = 0;
  vector<IPlayer *>   players;
  atomic<bool>        done(true);
  atomic<int>         play_value(0);
  thread              *t = NULL;

  Sounds::get().stopMusic();
  Sounds::get().playMusic("game");
  goban.setReferee(&referee);

  players.push_back(_players != 3 ? (IPlayer *)(new Human(goban, displayer, 1, GOBAN_X, GOBAN_Y)) : (IPlayer *)(new AI(goban, 1, 1)));
  players.push_back(_players != 1 ? (IPlayer *)(new AI(goban, 2, 1)) : (IPlayer *)(new Human(goban, displayer, 2, GOBAN_X, GOBAN_Y)));

  if (displayer.error() || !displayer.instanciate()) return -1;

  while (displayer.isRunning() && play_value != -1 && play_value != 1) {
    displayer.setScore(score(referee, players));
    if ((ret = displayer.display()) != 0)
      break;
    if (!displayer.isAnimating() && done) {
      if (!t) {
        done = false;
        t = new thread(doPlay, players[(turn = turn ? 0 : 1)], referee, ref(done), ref(play_value));
      } else {
        t->join();
        delete t;
        t = NULL;
        if (displayer.getReceiver().checkEnd()) break;
        displayer.animate();
      }
    }
  }
  if (play_value == 1) {
    std::cout << "Win" << std::endl;
  }
  if (t) {t->join(); delete t;}
  Sounds::get().stopMusic();
  Sounds::get().stopSounds();
  return ret;
}
