#include "common.h"
#include "application_base.h"
#include "render/renderer.h"
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>

//-------------------------
CApplicationBase::CApplicationBase( ) 
{ }

//-------------------------
bool CApplicationBase::init( const char *app_title, unsigned x_res, unsigned y_res ) {
  bool is_ok = CRenderer::get( ).init( app_title, x_res, y_res );
  if( !is_ok ) {
    printf( "CApplicationBase::CRenderer initialization FAILURE!\n" );
    return false;
  } else {
    printf( "CApplicationBase::CRenderer initialization SUCCESS!\n" );
    printf( "CApplicationBase::Loading specific project content\n" );
    return initProject( );
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
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ) {
      //User requests quit
      if( e.type == SDL_QUIT ) {
        quit = true;
      }
      
    }

    updateProject( 0.033f );

    CRenderer::get( ).beginRender( );
    renderProject( );
    CRenderer::get( ).endRender( );
  }
}

//-------------------------
void CApplicationBase::destroy( ) {

  // Project specific destruction
  destroyProject( );

  CRenderer::get( ).destroy( );

}
