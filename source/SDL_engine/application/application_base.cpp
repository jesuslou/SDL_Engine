#include "common.h"
#include "application_base.h"
#include "render/renderer.h"
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "audio/audio_manager.h"
#include "utils/timer.h"

//-------------------------
CApplicationBase::CApplicationBase( ) 
: elapsed( 1.f / 60.f )
{ }

//-------------------------
bool CApplicationBase::init( const char *app_title, unsigned x_res, unsigned y_res ) {
  bool is_ok = CRenderer::get( ).init( app_title, x_res, y_res );
  if( !is_ok ) {
    printf( "CApplicationBase::CRenderer initialization FAILURE!\n" );
    return false;
  } else {
    is_ok = CAudioManager::get( ).init( );
    if( !is_ok ) {
      printf( "CApplicationBase::CAudioManager initialization FAILURE!\n" );
    } else {
      printf( "CApplicationBase::Loading specific project content\n" );
      return initProject( );
    }
  }
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

    printf( "elapsed %f\n", elapsed );

    CTimer timer;
    timer.start( );

    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ) {
      //User requests quit
      if( e.type == SDL_QUIT ) {
        quit = true;
      }
      
    }

    updateProject( elapsed );

    CRenderer::get( ).beginRender( );
    renderProject( );
    CRenderer::get( ).endRender( );

    elapsed = timer.elapsed( );
  }
}

//-------------------------
void CApplicationBase::destroy( ) {

  // Project specific destruction
  destroyProject( );

  CRenderer::get( ).destroy( );

}
