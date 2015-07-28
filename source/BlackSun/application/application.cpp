#include "common.h"
#include "application.h"
#include "render/renderer.h"
#include "render/texture_manager.h"
#include "audio/audio_manager.h"
#include "input/input_manager.h"
#include "fonts/font_manager.h"
#include "logic/gameplay.h"

//-----------------
CApplication & CApplication::get( ) {
  static CApplication ca;
  return ca;
}

//-----------------
CApplication::CApplication( ) {
}

//-----------------
bool CApplication::initProject( ) {

  CRenderer::get( ).setClearColor( SDL_Color( 0, 0, 0, 0 ) );
  //CRenderer::get( ).setClearColor( SDL_Color( 255, 0, 0, 255 ) );

  CGameplay::get( ).init( );

  return true;
}

//-----------------
void CApplication::updateProject( float elapsed ) {
  CGameplay::get( ).update( elapsed );
}

//-----------------
void CApplication::renderProject( ) { 
  CGameplay::get( ).render( );
}

//-----------------
void CApplication::destroyProject( ) { 
  CGameplay::get( ).destroy( );
}
