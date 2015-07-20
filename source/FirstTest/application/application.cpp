#include "application.h"
#include "render/renderer.h"

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

  img_2.setPosition( SDL_Point( 100, 0 ) );
  img_1b.setPosition( SDL_Point( 0, 128 ) );

  img_1.setFlipMode( SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
  img_2.setAlpha( 128 );
  img_2.setBlendMode( SDL_BlendMode::SDL_BLENDMODE_ADD );
  img_1b.setScale( 1.5f );
  img_1b.setPivot(SDL_PointF( 0.5f, 0.5f ) );
  img_1b.setTintColor( SDL_Color( 0, 255, 0, 255 ) );
  img_1b.setAlpha( 128 );
  img_1b.setBlendMode( SDL_BlendMode::SDL_BLENDMODE_BLEND );

  return true;
}

//-----------------
void CApplication::updateProject( float elapsed ) {
  double rot = img_1b.getAngle( );
  rot += elapsed * 10.f;
  img_1b.setAngle( rot );
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
