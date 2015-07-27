#include "common.h"
#include "application.h"
#include "render/renderer.h"
#include "audio/audio_manager.h"
#include "input/input_manager.h"

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
  img_1.loadFromFile( "data/textures/test1.png" );
  img_2.loadFromFile( "data/textures/test2.png" );
  img_1b.loadFromFile( "data/textures/test1.png" );

  CRenderer::get( ).setClearColor( SDL_Color( 0, 128, 255, 255 ) );

  img_2.setPosition( TPoint2( 100.f, 0.f ) );
  img_1b.setPosition( TPoint2( 0.f, 128.f ) );

  img_1.setFlipMode( SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
  img_2.setAlpha( 128 );
  img_2.setBlendMode( SDL_BlendMode::SDL_BLENDMODE_ADD );
  img_1b.setScale( 1.5f );
  img_1b.setPivot(TPoint2( 0.5f, 0.5f ) );
  img_1b.setTintColor( SDL_Color( 0, 255, 0, 255 ) );
  img_1b.setAlpha( 128 );
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
