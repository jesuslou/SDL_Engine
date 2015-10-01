#include "common.h"
#include "application.h"
#include "render/renderer.h"
#include "audio/audio_manager.h"
#include "input/input_manager.h"
#include "fonts/font_manager.h"
#include "utils/interpolators.h"

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
  img_1b.loadFromFile( "data/textures/target.png" );

  CRenderer::get( ).setClearColor( SDL_Color( 0, 128, 255, 255 ) );

  img_1.setPosition( TPoint2( 128.f, 128.f ) );
  img_1.setPivot( TPoint2( 0.5f, 0.5f ) );
  img_2.setPosition( TPoint2( 128.f, 128.f ) );
  img_1b.setPosition( TPoint2( 0.f, 100.f ) );

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

  static float t = 0.f;
  if( CInputManager::get( ).isPressed( VK_ENTER ) ) {
    double rot = img_1b.getAngle( );
    rot += elapsed;
    //img_1b.setAngle( rot );

    t = 0.f;

   /* if( ( int ) rot % 40 == 0 ) {
      CAudioManager::get( ).playAudio( "data/audio/scratch.wav" );
    }*/
  }

  static float min_scale = 0.f;
  static float max_scale = 1.f;
  static float time = 1.f;

  double rot = img_1.getAngle( );
  rot += elapsed * 40.f;
  img_1.setAngle( rot );

  t += elapsed;
  EaseInBackInterpolation interpolator;
  float scale = interpolator( min_scale, max_scale, t / time );
  img_1.setScale( scale );

  fonts.printText( CFontManager::FT_GENERAL, 20, 200, "Eh tu, cipote %.2f", scale );
}

//-----------------
void CApplication::renderProject( ) { 
  img_1.render( );
  img_2.render( );
  //img_1b.render( );
}

//-----------------
void CApplication::destroyProject( ) { 
  img_1.destroy( );
  img_2.destroy( );
  img_1b.destroy( );
}
