/*
** Main.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Sun Oct 16 15:32:40 2016 wilmot_g
** Last update Tue Nov 08 11:19:21 2016 wilmot_g
*/

#include <iostream>
#include <thread>
#include "Displayer.hpp"
#include "Referee.hh"
#include "AI.hh"
#include "Game.hh"
#include "Human.hh"
#include "Sounds.hpp"

Game::Game()  {_players = 2;}
Game::~Game() {}

void          Game::doPlay(IPlayer *player, Referee referee, atomic<bool> &done) {
  player->play(referee);
  done = true;
}

void          Game::setPlayers(int p) {_players = p;}
void          Game::setAdvancedRules(bool r) {_rules = r;}

int           Game::play(int param) {
  Displayer   displayer;
  Goban       goban(displayer);
  Referee     referee(goban, _rules);
  int         ret = 0;
  int         turn = 0;
  vector<IPlayer *>   players;
  atomic<bool>        done(true);
  thread              *t = NULL;

  Sounds::get().stopMusic();
  Sounds::get().playMusic("game");
  goban.setReferee(&referee);

  players.push_back(_players != 3 ? (IPlayer *)(new Human(goban, displayer, 1, GOBAN_X, GOBAN_Y)) : (IPlayer *)(new AI(goban, 1, 1)));
  players.push_back(_players != 1 ? (IPlayer *)(new AI(goban, 2, 1)) : (IPlayer *)(new Human(goban, displayer, 2, GOBAN_X, GOBAN_Y)));

  if (displayer.error() || !displayer.instanciate()) return -1;
  while (displayer.isRunning()) {
    if ((ret = displayer.display()) != 0)
      break;
    if (!displayer.isAnimating() && done) {
      if (!t) {
        done = false;
        t = new thread(doPlay, players[(turn = turn ? 0 : 1)], referee, ref(done));
      } else {
        t->join();
        delete t;
        t = NULL;
        if (displayer.getReceiver().checkEnd()) break;
        displayer.animate();
      }
    }
  }
  if (t) {t->join(); delete t;}
  Sounds::get().stopMusic();
  Sounds::get().stopSounds();
  return ret;
}
