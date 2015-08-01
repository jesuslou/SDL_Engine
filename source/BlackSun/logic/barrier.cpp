#include "common.h"
#include "barrier.h"

//-----------------
CBarrier::CBarrier( )
: m_cur_lives( 0 )
{ }

//-----------------
bool CBarrier::init( const TPoint2 & pos, const TPoint2 & size ) {
  m_texture.loadFromFile( "data/textures/blank.png" );
  m_texture.setPosition( pos );
  m_texture.setClip( SDL_Rect( 0, 0, size.x, size.y ) );

  m_cur_lives = MAX_LIVES;

  colors[ 2 ] = SDL_Color( 0, 255, 0, 255 );
  colors[ 1 ] = SDL_Color( 255, 255, 0, 255 );
  colors[ 0 ] = SDL_Color( 255, 0, 0, 255 );
  return true;
}

//-----------------
void CBarrier::destroy( ) {
  m_texture.destroy( );
}

//-----------------
void CBarrier::update( float ) {
  if( m_cur_lives - 1 >= 0 ) {
    m_texture.setTintColor( colors[ m_cur_lives - 1 ] );
  } else {
    m_texture.setTintColor( SDL_Color( 0, 0, 0, 255 ) );
  }
}

//-----------------
void CBarrier::render( ) {
  m_texture.render( );
}

//-----------------
void CBarrier::addLife( unsigned amount ) {
  m_cur_lives += amount;
  m_cur_lives = ( m_cur_lives > MAX_LIVES ? MAX_LIVES : m_cur_lives );
}
