//
// Sdl.hpp for sdl in /Users/noboud_n/Documents/Share/cpp_indie_studio/includes/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Jun  4 15:05:08 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 22:43:43 2016 guillaume wilmot
//

#ifndef SDL_HPP_
# define SDL_HPP_

# include "SDL.h"
# include "SDL_mixer.h"
# include <iostream>
# include <map>

using namespace std;

# define GAME_MUSIC	  "./assets/Sounds/GameMusic.wav"
# define MENU_MUSIC   "./assets/Sounds/BackMusic.wav"
# define SOUND_PLAY	  "./assets/Sounds/Play.wav"
# define SOUND_REPLAY	"./assets/Sounds/Replay.wav"
# define SOUND_POP	  "./assets/Sounds/Pop.wav"
# define SOUND_WIN		"./assets/Sounds/Win.wav"
# define SOUND_LOSE		"./assets/Sounds/Lose.wav"

class			Sounds {
public:
  static Sounds		&get() {static Sounds _mgr; return (_mgr);}

  bool      loadSound(const string &, const string &);
  bool      loadMusic(const string &, const string &);
  void			init();
  void			playSound(const string &);
  void			playMusic(const string &);
  void			setVolume(float volume) {_volume = volume;}
  void      stopSounds();
  void      stopMusic();

private:

  Sounds() {};
  Sounds(const Sounds &);

  void			operator=(const Sounds &);

  float			                _volume;
  map<string, Mix_Chunk *>	_sounds;
  map<string, Mix_Music *>	_musics;
};

#endif /* !SDL_HPP_ */
