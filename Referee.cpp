//
// Referee.cpp for Gomoku in /home/albanbin/rendu/Gomoku/
//
// Made by Combaud Alban
// Login   <alban.combaud@epitech.eu@epitech.eu>
//
// Started on  Wed Oct 12 13:12:15 2016 Combaud Alban
// Last update Wed Oct 12 16:28:19 2016 Combaud Alban
//

#include "Referee.hh"

Referee::Referee()
{

}

Referee::~Referee()
{
}

bool  Referee::checkEmptyCase()
{
  return true;
}

bool  Referee::checkPlay()
{
  if (checkEmptyCase())
    return false;
  return true;
}

int main() {

  Referee toto;

  toto.checkPlay();
  return 0;
}
