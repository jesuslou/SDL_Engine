#include "common.h"
#include "board.h"
#include <cstdio>

//-------------------------
CBoard::CBoard( ) 
: m_render_offset( 0.f, 0.f )
, m_partner_board( nullptr )
, m_time_to_can_shoot( 0.f )
, m_time_between_shoots( 0.5f )
{ }

//-------------------------
bool CBoard::init( int _cells_x, int _cells_y, const char* img_path, const TPoint2 & _render_offset, const TPoint2 & bullets_offset, int max_bullets, TControlKeys ct_keys, CBoard *partner_board ) {
  m_render_offset = _render_offset;
  m_cells_x = _cells_x;
  m_cells_y = _cells_y;
  m_keys = ct_keys;
  m_partner_board = partner_board;

  for( int x = 0; x < m_cells_x; ++x ) {
    for( int y = 0; y < m_cells_y; ++y ) {
      TCell cell( x, y );
      CTexture & img = cell.texture;
      img.loadFromFile( img_path );
      TPoint2 cell_pos;
      cell_pos.x = x * img.getWidth( );
      cell_pos.y = y * img.getHeight( );
      cell_pos += m_render_offset;
      img.setPosition( cell_pos );
      img.setBlendMode( SDL_BlendMode::SDL_BLENDMODE_BLEND );
      m_board.push_back( cell );
    }
  }

  m_target_cursor.init( TPoint2( m_cells_x, m_cells_y ), TPoint2( rand( ) % m_cells_x, rand( ) % m_cells_y ), m_render_offset, "data/textures/target.png" );
  m_target_cursor.setControlKeys( ct_keys );

  m_bullets.init( max_bullets, bullets_offset );
  return true;
}

//-------------------------
void CBoard::destroy( ) {
  for( auto & cell : m_board ) {
    cell.texture.destroy( );
  }

  m_target_cursor.destroy( );
  m_bullets.destroy( );
}


//-------------------------
void CBoard::update( float elapsed ) {
  m_target_cursor.update( elapsed );

  m_time_to_can_shoot -= elapsed;
  if( CInputManager::get( ).isPressed( m_keys.key_shoot ) && m_time_to_can_shoot <= 0.f && m_bullets.canShoot( ) ) {
    onShoot( );
    if( m_partner_board ) {
      m_partner_board->onShoot( );
    }
  }

}

//-------------------------
void CBoard::render( ) {
  for( auto & cell : m_board ) {
    cell.texture.render( );
  }

  m_target_cursor.render( );
  m_bullets.render( );
}

//-------------------------
void CBoard::onShoot( ) {
  m_time_to_can_shoot = m_time_between_shoots;
  m_bullets.addBullets( -1 );
  TPoint2 cursor_pos = m_target_cursor.getBoardPos( );
  TCell & cell = getCell( cursor_pos );
  if( m_partner_board &&  cell.has_enemy ) {
    m_partner_board->m_bullets.addBullets( 1 );
  }
}

//-------------------------
CBoard::TCell & CBoard::getCell( TPoint2 pos ) {
  for( auto & cell : m_board ) {
    if( cell.x == pos.x && cell.y == pos.y ) {
      return cell;
    }
  }
}

