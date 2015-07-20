#ifndef _INC_TEXTURE_MANAGER_H_
#define _INC_TEXTURE_MANAGER_H_

#include <string>
#include <map>

struct SDL_Texture;

class CTextureManager {
private:
  struct TTextureRef;
public:

  static CTextureManager & get( );

  bool init( );
  void destroy( );

  SDL_Texture* loadTexture( std::string & path, unsigned *width, unsigned *height );
  SDL_Texture* getTexture( std::string & path );
  TTextureRef* getTextureRef( std::string & path );

  bool releaseTexture( std::string & path );

private:
  CTextureManager( );

  struct TTextureRef {
    SDL_Texture  *m_texture;
    unsigned      m_nrefs;
    int           w;
    int           h;

    TTextureRef( ) : m_texture( nullptr ), m_nrefs( 0 ), w( 0 ), h( 0 ) { }
    TTextureRef( SDL_Texture *tex, int _w, int _h ) : m_texture( tex ), m_nrefs( 1 ), w( _w ), h( _h ) { }
  };

  typedef std::map<std::string, TTextureRef> MTextures;
  MTextures m_textures;

};

#endif