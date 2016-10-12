//
// Referee.cpp for Gomoku in /home/albanbin/rendu/Gomoku/
//
// Made by Combaud Alban
// Login   <alban.combaud@epitech.eu@epitech.eu>
//
// Started on  Wed Oct 12 13:12:15 2016 Combaud Alban
// Last update Wed Oct 12 14:47:30 2016 Combaud Alban
//

#include "Referee.hh"

Referee::Referee()
{

}

Referee::~Referee()
{
}

bool  Referee::checkPlay()
{
  std::vector<std::vector<int> > map;
  std::vector<int>    content;

  for (size_t i = 0; i < 19; i++) {
    for (size_t i = 0; i < 19; i++) {
      content.push_back(0);
    }
    map.push_back(content);
  }

  return BITE;
}

int main() {

  Referee toto;

  toto.checkPlay();
  return 0;
}
