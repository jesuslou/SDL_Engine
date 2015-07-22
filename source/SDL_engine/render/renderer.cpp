#include "common.h"
#include "renderer.h"
#include "texture_manager.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

//-----------------
CRenderer & CRenderer::get( ) {
  static CRenderer cr;
  return cr;
}

//-------------------------
CRenderer::CRenderer( )
: m_x_res( 640 )
, m_y_res( 480 )
, m_window( nullptr )
, m_renderer( nullptr ) 
, m_clear_color( 0, 0, 0, 0 ) { }

//-------------------------
bool CRenderer::init( const char *app_title, unsigned x_res, unsigned y_res ) {
  m_x_res = x_res;
  m_y_res = y_res;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) {
    printf( "CRenderer::SDL initialization FAILURE! SDL_Error: %s\n", SDL_GetError( ) );
    return false;
  } else {
    printf( "CRenderer::SDL initialization SUCCESS!\n" );
    //Create window
    m_window = SDL_CreateWindow( app_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_x_res, m_y_res, SDL_WINDOW_SHOWN );
    if( m_window == nullptr ) {
      printf( "CRenderer::Window creation FAILURE! SDL_Error: %s\n", SDL_GetError( ) );
      return false;
    } else {
      printf( "CRenderer::SDL Window creation SUCCESS!\n" );
      m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
      // Project specific initialization
      if( m_renderer == nullptr ) {
        printf( "CRenderer::Renderer creation FAILURE! SDL Error: %s\n", SDL_GetError( ) );
        return false;
      } else {
        printf( "CRenderer::SDL Renderer creation SUCCESS!\n" );
        //Initialize renderer color
        SDL_SetRenderDrawColor( m_renderer, m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a );

        return CTextureManager::get( ).init( );
        
      }
    }
  }
  return false;
}

//-------------------------
void CRenderer::destroy( ) {
  if( m_renderer ) {
    SDL_DestroyRenderer( m_renderer );
    m_renderer = nullptr;
  }
  if( m_window ) {
    SDL_DestroyWindow( m_window );
    m_window = nullptr;
  }

  SDL_Quit( );
}

//-------------------------
void CRenderer::beginRender( ) {
  //Clear screen
  SDL_SetRenderDrawColor( m_renderer, m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a );
  SDL_RenderClear( m_renderer );
}

//-------------------------
void CRenderer::endRender( ) {
  //Update screen
  SDL_RenderPresent( m_renderer );
}
