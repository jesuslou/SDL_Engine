#include "common.h"
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
SDL_Texture* CTextureManager::loadTexture( const char* path, unsigned *width, unsigned *height ) {
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
  SDL_Surface* loaded_surface = IMG_Load( path );
  if( loaded_surface == nullptr ) {
    printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError( ) );
  } else {
    //Color key image
    SDL_SetColorKey( loaded_surface, SDL_TRUE, SDL_MapRGB( loaded_surface->format, 0, 0xFF, 0xFF ) );

    //Create texture from surface pixels
    new_texture = SDL_CreateTextureFromSurface( CRenderer::get( ).getRenderer( ), loaded_surface );
    if( new_texture == nullptr ) {
      printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError( ) );
    } else {
      //Get image dimensions
      if( width ) {
        *width = static_cast<unsigned>( loaded_surface->w );
      }
      if( height ) {
        *height = static_cast<unsigned>( loaded_surface->h );
      }

      m_textures[ path ] = TTextureRef( new_texture, loaded_surface->w, loaded_surface->h, 0 );

    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loaded_surface );
  }
  return new_texture;
}

//-----------------
SDL_Texture* CTextureManager::loadEditableTexture( const char* path, unsigned *width, unsigned *height, int *pitch ) {
  //The final texture
  TTextureRef *tex_ref = getTextureRef( path );
  if( tex_ref ) {
    if( width ) {
      *width = static_cast<unsigned>( tex_ref->w );
    }
    if( height ) {
      *height = static_cast<unsigned>( tex_ref->h );
    }
    if( pitch ) {
      *pitch = static_cast<unsigned>( tex_ref->pitch );
    }
    return tex_ref->m_texture;
  }
  SDL_Texture *new_texture = nullptr;

  //Load image at specified path
  SDL_Surface* loaded_surface = IMG_Load( path );
  if( loaded_surface == nullptr ) {
    printf( "CTextureManager::Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError( ) );
  } else {

    SDL_Surface* formatted_surface = SDL_ConvertSurfaceFormat( loaded_surface, SDL_PIXELFORMAT_RGBA8888, NULL );
    if( !formatted_surface ) {
      printf( "CTextureManager::Unable to convert loaded surface to display format! %s\n", SDL_GetError( ) );
    } else {
      // Empty texture
      new_texture = SDL_CreateTexture( CRenderer::get( ).getRenderer( ), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formatted_surface->w, formatted_surface->h );
      if( !new_texture ) {
        printf( "CTextureManager::Unable to create blank texture! SDL Error: %s\n", SDL_GetError( ) );
      } else {
        void *pixels = nullptr;
        int l_pitch = 0;
        //Lock texture for manipulation
        SDL_LockTexture( new_texture, &formatted_surface->clip_rect, &pixels, &l_pitch );

        //Copy loaded/formatted surface pixels
        memcpy( pixels, formatted_surface->pixels, formatted_surface->pitch * formatted_surface->h );

        //Get image dimensions
        if( width ) {
          *width = static_cast<unsigned>( loaded_surface->w );
        }
        if( height ) {
          *height = static_cast<unsigned>( loaded_surface->h );
        }
        if( pitch ) {
          *pitch = static_cast<unsigned>( l_pitch );
        }

        //Get pixel data in editable format
        Uint32* u32_pixels = ( Uint32* ) pixels;
        int pixelCount = ( l_pitch / 4 ) * loaded_surface->h;

        //Map colors                
        Uint32 colorKey = SDL_MapRGB( formatted_surface->format, 0xFF, 0x00, 0xFF );
        Uint32 transparent = SDL_MapRGBA( formatted_surface->format, 0xFF, 0x00, 0xFF, 0x00 );

        //Color key pixels
        for( int i = 0; i < pixelCount; ++i ) {
          if( u32_pixels[ i ] == colorKey ) {
            u32_pixels[ i ] = transparent;
          }
        }

        //Unlock texture to update
        SDL_UnlockTexture( new_texture );

        m_textures[ path ] = TTextureRef( new_texture, loaded_surface->w, loaded_surface->h, formatted_surface->pitch );
      }

      SDL_FreeSurface( formatted_surface );

    }
    //Get rid of old loaded surface
    SDL_FreeSurface( loaded_surface );
  }
  return new_texture;
}

//-----------------
SDL_Texture* CTextureManager::getTexture( const char* path ) {
  auto it = m_textures.find( path );
  if( it != m_textures.end( ) ) {
    ++it->second.m_nrefs;
    return it->second.m_texture;
  }
  return nullptr;
}

//-----------------
CTextureManager::TTextureRef * CTextureManager::getTextureRef( const char* path ) {
  auto it = m_textures.find( path );
  if( it != m_textures.end( ) ) {
    ++it->second.m_nrefs;
    return &it->second;
  }
  return nullptr;
}

//-----------------
bool CTextureManager::releaseTexture( const char* path ) {
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
