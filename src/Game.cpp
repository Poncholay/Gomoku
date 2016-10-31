/*
** Main.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Sun Oct 16 15:32:40 2016 wilmot_g
** Last update Mon Oct 31 20:03:49 2016 wilmot_g
*/

#include <iostream>
#include <thread>
#include "Displayer.hpp"
#include "Referee.hh"
#include "AI.hh"
#include "Game.hh"
#include "Human.hh"

Game::Game()  {}
Game::~Game() {}

void          Game::doPlay(IPlayer *player, Referee referee, atomic<bool> &done) {
  player->play(referee);
  done = true;
}

int           Game::play(int param) {
  Displayer   displayer;
  Goban       goban(displayer);
  Referee     referee(goban);
  int         ret = 0;
  int         turn = 0;
  vector<IPlayer *>   players;
  atomic<bool>        done(true);
  thread              *t = NULL;

  //TODO : check param and create accordingly
  players.push_back(new AI(goban, 1, 1));
  players.push_back(new Human(goban, displayer, 2, GOBAN_X, GOBAN_Y));
  //
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
        displayer.animate();
      }
    }
  }
  if (t) {t->join(); delete t;}
  return ret;
}
