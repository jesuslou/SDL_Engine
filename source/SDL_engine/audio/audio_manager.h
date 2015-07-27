#ifndef _INC_AUDIO_MANAGER_H_
#define _INC_AUDIO_MANAGER_H_

#include <map>
#include <SDL_mixer.h>

class CAudioManager {
public:
  
  static CAudioManager & get( );

  bool init( );
  void destroy( );

  Mix_Music* loadSong( const char *path );
  Mix_Chunk* loadAudio( const char *path );

  Mix_Music* getSong( const char *path );
  Mix_Chunk* getAudio( const char *path );

  void playSong( const char *path, bool loop = true );
  void playAudio( const char *path );

private:
  CAudioManager( );

  typedef std::map<std::string, Mix_Music*> MSongs;
  MSongs m_songs;

  typedef std::map<std::string, Mix_Chunk*> MAudios;
  MAudios m_audios;

};

#endif