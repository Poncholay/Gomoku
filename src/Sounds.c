//
// Sdl.cpp for Sdl in /Users/noboud_n/Documents/Share/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Jun  4 16:06:16 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 22:43:51 2016 guillaume wilmot
//

#include "Sdl.hpp"
#include "SdlError.hpp"

void			SDL::init() {
  if (SDL_Init(SDL_INIT_AUDIO) == -1)
    throw SdlError("Error: could not initiate SDL.");
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    throw SdlError("Error: could not initiate MIX.");
  if ((_sounds[PICKPOWERUP] = Mix_LoadWAV(SOUND_PICKPOWERUP)) == NULL
      || (_sounds[EXPLODEBOMB] = Mix_LoadWAV(SOUND_EXPLODEBOMB)) == NULL
      || (_sounds[PUTBOMB] = Mix_LoadWAV(SOUND_PUTBOMB)) == NULL
      || (_sounds[DEATH] = Mix_LoadWAV(SOUND_DEATH)) == NULL
      || (_sounds[FALLINGBLOCK] = Mix_LoadWAV(SOUND_FALLINGBLOCK)) == NULL
      || (_sounds[CREDITS_MUSIC] = Mix_LoadWAV(LOAD_CREDITS_MUSIC)) == NULL
      || (_sounds[HIGHSCORES_MUSIC] = Mix_LoadWAV(LOAD_HIGHSCORES_MUSIC)) == NULL
      || (_sounds[MUSIC_SPLASH] = Mix_LoadWAV(SOUND_SPLASH)) == NULL
      || (_sounds[MUSIC_INTRO] = Mix_LoadWAV(SOUND_INTRO)) == NULL)
    throw SdlError(Mix_GetError());
  if ((_menuMusic = Mix_LoadMUS(LOAD_MENU_THEME)) == NULL
      || (_gameMusic = Mix_LoadMUS(LOAD_GAME_MUSIC)) == NULL)
    throw SdlError(Mix_GetError());
  _volume = 50;
  Mix_VolumeChunk(_sounds[DEATH], _volume == 0 ? 0 : _volume * 2 > 128 ? 128 : _volume * 2);
  Mix_VolumeChunk(_sounds[EXPLODEBOMB], _volume);
}

void			SDL::playSound(e_sound sound) {
  if (_sounds[sound] != NULL
      && sound != MENU_THEME && sound != GAME_MUSIC
      && sound != CREDITS_MUSIC && sound != HIGHSCORES_MUSIC) {
      Mix_VolumeChunk(_sounds[sound], _volume);
      Mix_PlayChannel(-1, _sounds[sound], 0);
    }
  else if (sound == CREDITS_MUSIC || sound == HIGHSCORES_MUSIC) {
      Mix_VolumeChunk(_sounds[sound], _volume);
      Mix_PlayChannel(-1, _sounds[sound], -1);
    }
}

void			SDL::playMusic(e_sound music) {
  if (music == MENU_THEME) {
    Mix_VolumeMusic(_volume == 0 ? 0 : _volume + 10 > 128 ? 128 : _volume + 10);
    if (Mix_PlayMusic(_menuMusic, -1) == -1)
	   throw SdlError(Mix_GetError());
    }
  else if (music == GAME_MUSIC) {
    Mix_VolumeMusic(_volume == 0 ? 0 : _volume - 10 < 0 ? 0 : _volume - 10);
    if (Mix_PlayMusic(_gameMusic, -1) == -1)
	    throw SdlError(Mix_GetError());
    }
}

void			SDL::actualizeVolume(e_sound music) const {
  if (music == MENU_THEME)
    Mix_VolumeMusic(_volume == 0 ? 0 : _volume + 10 > 128 ? 128 : _volume + 10);
  else if (music == GAME_MUSIC)
    Mix_VolumeMusic(_volume == 0 ? 0 : _volume - 10 < 0 ? 0 : _volume - 10);
}
