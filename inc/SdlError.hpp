//
// SdlError.hpp for SDLError in /Users/noboud_n/Documents/Share/cpp_indie_studio/includes/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Jun  4 17:02:12 2016 Nyrandone Noboud-Inpeng
// Last update Sat Jun  4 17:04:47 2016 Nyrandone Noboud-Inpeng
//

#ifndef SDLERROR_HPP_
# define SDLERROR_HPP_

# include "Error.hpp"

class		SdlError : public Error
{
public:
  SdlError(std::string const &message = "An error occured.") { _message = message; };
  virtual		~SdlError() throw() {};
};

#endif /* !SDLERROR_HPP_ */
