#include "common.h"
#include "enemy.h"
#include "../board.h"
#include "../gameplay.h"

//-----------------
CEnemy::CEnemy( ) 
: m_render_offset( 0.f, 0.f )
, m_board_pos( 0.f, 0.f )
, m_board( nullptr )
{ }

//-----------------
bool CEnemy::init( const char *img_path, const TPoint2 & render_offset, const TPoint2 & board_pos, CBoard *board ) {
  m_board = board;
  m_render_offset = render_offset;
  m_texture.loadFromFile( img_path );
  m_texture.setBlendMode( SDL_BlendMode::SDL_BLENDMODE_BLEND );
  setBoardPos( board_pos );
  return true;
}

//-----------------
void CEnemy::destroy( ) {
  m_texture.destroy( );
}

//-----------------
void CEnemy::render( ) {
  m_texture.render( );
}

//-----------------
void CEnemy::setBoardPos( TPoint2 board_pos ) {
  m_board_pos = board_pos;

  if( m_board_pos.y > 5 ) {
    CGameplay::get( ).onBarrierReached( );
  }

  TPoint2 texture_pos;
  texture_pos.x = m_board_pos.x * m_texture.getWidth( );
  texture_pos.y = m_board_pos.y * m_texture.getHeight( );
  texture_pos += m_render_offset;
  m_texture.setPosition( texture_pos );
}
