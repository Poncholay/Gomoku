//
// Referee.hh for Gomoku in /home/albanbin/rendu/Gomoku/
//
// Made by Combaud Alban
// Login   <alban.combaud@epitech.eu@epitech.eu>
//
// Started on  Wed Oct 12 13:15:51 2016 Combaud Alban
// Last update Wed Oct 12 16:28:20 2016 Combaud Alban
//

#ifndef REFEREE_HH_
# define REFEREE_HH_

# include <vector>
# include <iostream>

class Referee
{
private:
public:
  Referee();
  ~Referee();

  bool  checkPlay();
  bool checkEmptyCase();
};

#endif
