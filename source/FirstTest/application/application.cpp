#include "common.h"
#include "application.h"
#include "render/renderer.h"
#include "audio/audio_manager.h"
#include "input/input_manager.h"
#include "fonts/font_manager.h"

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
  img_1.loadFromFile( "data/textures/enemy_00.png" );
  img_2.loadFromFile( "data/textures/enemy_01.png" );
  img_1b.loadFromFile( "data/textures/target.png" );

  CRenderer::get( ).setClearColor( SDL_Color( 0, 128, 255, 255 ) );

  img_2.setPosition( TPoint2( 100.f, 0.f ) );
  img_1b.setPosition( TPoint2( 100.f, 0.f ) );

  img_1.setBlendMode( SDL_BlendMode::SDL_BLENDMODE_BLEND );
  img_2.setBlendMode( SDL_BlendMode::SDL_BLENDMODE_BLEND );
  img_1b.setBlendMode( SDL_BlendMode::SDL_BLENDMODE_BLEND );

  CAudioManager::get( ).loadSong( "data/music/beat.wav" );
  //CAudioManager::get( ).playSong( "data/music/beat.wav" );

  CAudioManager::get( ).loadAudio( "data/audio/scratch.wav" );

  return true;
}

//-----------------
void CApplication::updateProject( float elapsed ) {

  if( CInputManager::get( ).isPressed( VK_ENTER ) ) {
    double rot = img_1b.getAngle( );
    rot += elapsed * 10.f;
    img_1b.setAngle( rot );

   /* if( ( int ) rot % 40 == 0 ) {
      CAudioManager::get( ).playAudio( "data/audio/scratch.wav" );
    }*/
  }

  fonts.printText( CFontManager::FT_GENERAL, "Eh tu, cipote", 20, 200 );
}

//-----------------
void CApplication::renderProject( ) { 
  img_1.draw( );
  img_2.draw( );
  img_1b.draw( );
}

//-----------------
void CApplication::destroyProject( ) { 
  img_1.destroy( );
  img_2.destroy( );
  img_1b.destroy( );
}
