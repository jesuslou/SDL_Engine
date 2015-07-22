#include "common.h"
#include "audio_manager.h"

//-----------------
CAudioManager & CAudioManager::get( ) {
  static CAudioManager am;
  return am;
}

//-----------------
CAudioManager::CAudioManager( ) { }

//-----------------
bool CAudioManager::init( ) {
  if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
    printf( "CAudioManager::SDL Mixer initialization FAILURE! SDL_mixer Error: %s\n", Mix_GetError( ) );
    return false;
  }
  printf( "CAudioManager::SDL Mixer initialization SUCCESS!\n" );
}

//-----------------
void CAudioManager::destroy( ) {
  for( auto & music : m_songs ) {
    Mix_FreeMusic( music.second );
  }
  m_songs.clear( );

  for( auto & audio : m_audios ) {
    Mix_FreeChunk( audio.second );
  }
  m_audios.clear( );

  Mix_Quit( );
}

Mix_Music* CAudioManager::loadSong( const char * path ) {
  Mix_Music *new_music = getSong( path );
  if( !new_music ) {
    new_music = Mix_LoadMUS( path );
    if( !new_music ) {
      printf( "CAudioManager::Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError( ) );
    } else {
      m_songs[ path ] = new_music;
    }
  }
  return new_music;
}

Mix_Chunk* CAudioManager::loadAudio( const char * path ) {
  Mix_Chunk *new_audio = getAudio( path );
  if( !new_audio ) {
    new_audio = Mix_LoadWAV( path );
    if( !new_audio ) {
      printf( "CAudioManager::Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError( ) );
    } else {
      m_audios[ path ] = new_audio;
    }
  }
  return new_audio;
}

Mix_Music* CAudioManager::getSong( const char * path ) {
  auto it = m_songs.find( path );
  if( it != m_songs.end( ) ) {
    return it->second;
  }
  return nullptr;
}

Mix_Chunk* CAudioManager::getAudio( const char * path ) {
  auto it = m_audios.find( path );
  if( it != m_audios.end( ) ) {
    return it->second;
  }
  return nullptr;
}

void CAudioManager::playSong( const char * path, bool loop ) {
  Mix_Music *music = getSong( path );
  if( music ) {
    Mix_PlayMusic( music, loop ? -1 : 0 );
  } else {
    printf( "CAudioManager:: song '%s' not loaded!\n", path );
  }
}

void CAudioManager::playAudio( const char * path ) {
  Mix_Chunk *audio = getAudio( path );
  if( audio ) {
    Mix_PlayChannel( -1, audio, 0 );
  } else {
    printf( "CAudioManager:: audio '%s' not loaded!\n", path );
  }
}
