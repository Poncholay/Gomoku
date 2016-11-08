//
// Sdl.cpp for Sdl in /Users/noboud_n/Documents/Share/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Jun  4 16:06:16 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 22:43:51 2016 guillaume wilmot
//

#include "Sounds.hpp"
#include "SdlError.hpp"

void			Sounds::init() {
  if (SDL_Init(SDL_INIT_AUDIO) == -1)
    throw SdlError("Error: could not initiate SDL.");
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    throw SdlError("Error: could not initiate MIX.");
  _volume = MIX_MAX_VOLUME;
  if (!loadSound("play", SOUND_PLAY) ||
      !loadSound("replay", SOUND_REPLAY) ||
      !loadSound("pop", SOUND_POP))
    throw SdlError(Mix_GetError());
  if (!loadMusic("menu", MENU_MUSIC) ||
      !loadMusic("game", GAME_MUSIC))
    throw SdlError(Mix_GetError());
}

bool       Sounds::loadMusic(const string &so, const string &s) {
  if (!(_musics[so] = Mix_LoadMUS(s.c_str())))
    return cerr << "Error: " << s << " not found" << endl, false;
  return true;
}

bool       Sounds::loadSound(const string &so, const string &s) {
  if (!(_sounds[so] = Mix_LoadWAV(s.c_str())))
    return cerr << "Error: " << s << " not found" << endl, false;
  return true;
}

void			Sounds::playSound(const string &s) {
  Mix_Chunk *sound = _sounds[s];

  if (sound) {
      Mix_VolumeChunk(sound, _volume);
      Mix_PlayChannel(-1, sound, 0);
  } else
      cerr << "WARN : No such sound : " << s << endl;
}

void			Sounds::playMusic(const string &m) {
  Mix_Music *music = _musics[m];

  if (music) {
    Mix_VolumeMusic(_volume);
    if (Mix_PlayMusic(music, -1) == -1)
	    cerr << Mix_GetError() << endl;
    } else
      cerr << "WARN : No such music : " << m << endl;
}

void      Sounds::stopSounds() {Mix_HaltChannel(-1);}
void      Sounds::stopMusic()  {Mix_HaltMusic();}
