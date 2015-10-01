#include "common.h"
#include "application_base.h"
#include "render/renderer.h"
#include <SDL.h>
#include <stdio.h>
#include <time.h>
#include <SDL_image.h>
#include "audio/audio_manager.h"
#include "input/input_manager.h"
#include "fonts/font_manager.h"
#include "utils/timer.h"

//-------------------------
CApplicationBase::CApplicationBase( ) 
: elapsed( 1.f / 60.f )
{ }

//-------------------------
bool CApplicationBase::init( const char *app_title, unsigned x_res, unsigned y_res ) {

  srand( static_cast<unsigned int>( time( nullptr ) ) );

  bool is_ok = CRenderer::get( ).init( app_title, x_res, y_res );
  if( !is_ok ) {
    printf( "CApplicationBase::CRenderer initialization FAILURE!\n" );
    return false;
  }

  is_ok = CAudioManager::get( ).init( );
  if( !is_ok ) {
    printf( "CApplicationBase::CAudioManager initialization FAILURE!\n" );
    return false;
  } 

  is_ok = CFontManager::get( ).init( );
  if( !is_ok ) {
    printf( "CApplicationBase::CFontManager initialization FAILURE!\n" );
    return false;
  }

  printf( "CApplicationBase::Loading specific project content\n" );
  return initProject( );

}

//-------------------------
void CApplicationBase::update( ) {

  //Main loop flag
  bool quit = false;

  //Event handler
  SDL_Event e;

  //Set text color as black
  SDL_Color textColor = { 0, 0, 0, 255 };

  //While application is running
  while( !quit ) {

    CTimer timer;
    timer.start( );

    CInputManager::get( ).setupMouseState( );

    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ) {
      //User requests quit
      if( e.type == SDL_QUIT ) {
        quit = true;
      }

      CInputManager::get( ).updateMouse( e );
    }

    CInputManager::get( ).updateKeyboard( );

    updateProject( elapsed );

    CRenderer::get( ).beginRender( );
    renderProject( );
    CFontManager::get( ).render( );
    CRenderer::get( ).endRender( );

    elapsed = timer.elapsed( );
  }
}

//-------------------------
void CApplicationBase::destroy( ) {

  // Project specific destruction
  destroyProject( );

  CInputManager::get( ).destroy( );
  CFontManager::get( ).destroy( );
  CRenderer::get( ).destroy( );

}
