#include "texture_manager.h"
#include "renderer.h"
#include <SDL.h>
#include <SDL_image.h>

//-----------------
CTextureManager & CTextureManager::get( ) {
  static CTextureManager tm;
  return tm;
}

//-----------------
CTextureManager::CTextureManager( ) {
}

//-----------------
bool CTextureManager::init( ) {
  int img_flags = IMG_INIT_PNG;
  if( !( IMG_Init( img_flags ) & img_flags ) ) {
    printf( "CTextureManager::SDL_image initialization FAILURE! SDL_image Error: %s\n", IMG_GetError( ) );
    return false;
  }
  printf( "CTextureManager::SDL_Image initialization SUCCESS! ( png files )\n" );
  return true;
}

//-----------------
void CTextureManager::destroy( ) {
  IMG_Quit( );
}

//-----------------
SDL_Texture* CTextureManager::loadTexture( std::string & path, unsigned *width, unsigned *height ) {
  //The final texture
  TTextureRef *tex_ref = getTextureRef( path );
  if( tex_ref ) {
    if( width ) {
      *width = static_cast<unsigned>( tex_ref->w );
    }
    if( height ) {
      *height = static_cast<unsigned>( tex_ref->h );
    }
    return tex_ref->m_texture;
  }
  SDL_Texture *new_texture = nullptr;

  //Load image at specified path
  SDL_Surface* loaded_surface = IMG_Load( path.c_str( ) );
  if( loaded_surface == nullptr ) {
    printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str( ), IMG_GetError( ) );
  } else {
    //Color key image
    SDL_SetColorKey( loaded_surface, SDL_TRUE, SDL_MapRGB( loaded_surface->format, 0, 0xFF, 0xFF ) );

    //Create texture from surface pixels
    new_texture = SDL_CreateTextureFromSurface( CRenderer::get( ).getRenderer( ), loaded_surface );
    if( new_texture == nullptr ) {
      printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str( ), SDL_GetError( ) );
    } else {
      //Get image dimensions
      if( width ) {
        *width = static_cast<unsigned>( loaded_surface->w );
      }
      if( height ) {
        *height = static_cast<unsigned>( loaded_surface->h );
      }

      m_textures[ path ] = TTextureRef( new_texture, loaded_surface->w, loaded_surface->h );

    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loaded_surface );
  }
  return new_texture;
}

//-----------------
SDL_Texture* CTextureManager::getTexture( std::string & path ) {
  auto it = m_textures.find( path );
  if( it != m_textures.end( ) ) {
    ++it->second.m_nrefs;
    return it->second.m_texture;
  }
  return nullptr;
}

//-----------------
CTextureManager::TTextureRef * CTextureManager::getTextureRef( std::string & path ) {
  auto it = m_textures.find( path );
  if( it != m_textures.end( ) ) {
    ++it->second.m_nrefs;
    return &it->second;
  }
  return nullptr;
}

//-----------------
bool CTextureManager::releaseTexture( std::string & path ) {
  auto it = m_textures.find( path );
  if( it != m_textures.end( ) ) {
    --it->second.m_nrefs;
    if( it->second.m_nrefs <= 0 ) {
      if( it->second.m_texture ) {
        SDL_DestroyTexture( it->second.m_texture );
      }
      m_textures.erase( it );
    }
    return true;
  }
  return false;
}
