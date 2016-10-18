//
// AI.cpp for Gomoku in /home/drartemi/depos/Gomoku/Gomoku/
//
// Made by Adrien Milcent
// Login   <adrien.milcent@epitech.eu>
//
// Started on  Tue Oct 18 14:20:06 2016 Adrien Milcent
// Last update Tue Oct 18 14:25:39 2016 Adrien Milcent
//

#include "AI.hh"

AI::AI(Goban &goban)
{
  _goban = goban;
  _minmax = Minmax();
}

AI::~AI()
{}
