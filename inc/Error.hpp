//
// Error.hpp for Error in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Apr 26 12:41:14 2016 Nyrandone Noboud-Inpeng
// Last update Wed Jun  1 15:35:52 2016 Nyrandone Noboud-Inpeng
//

#ifndef ERROR_HPP_
# define ERROR_HPP_

# include <iostream>
# include <stdexcept>

class			Error : public std::exception
{
public:
  Error() {};
  ~Error() {};

  virtual char const	*what() const throw() { return (_message.c_str()); };
protected:
  std::string		_message;
};

#endif /* !ERROR_HPP_ */
