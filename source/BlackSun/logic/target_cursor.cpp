#include "common.h"
#include "target_cursor.h"
#include "enemies/enemy.h"

//-----------------
CTargetCursor::CTargetCursor( ) 
: m_render_offset( 0.f, 0.f )
, m_board_size( 0.f, 0.f )
, m_board_pos( 0.f, 0.f )
, m_target_enemy( nullptr )
, acc_frames( 0 )
, n_freezed_frames( 8 )
{ }

//-----------------
bool CTargetCursor::init( TPoint2 board_size, TPoint2 board_pos, TPoint2 render_offset, const char *img_path ) {
  m_texture.loadFromFile( img_path );
  m_texture.setBlendMode( SDL_BlendMode::SDL_BLENDMODE_BLEND );
  m_board_size = board_size;
  m_render_offset   = render_offset;
  setBoardPos( board_pos );
  return true;
}

//-----------------
void CTargetCursor::destroy( ) {
  m_texture.destroy( );
}

//-----------------
void CTargetCursor::update( float elapsed ) {
  --acc_frames;
  if( acc_frames > 0 ) {
    return;
  }
  if( CInputManager::get( ).isPressed( m_keys.key_up ) ) {
    acc_frames = n_freezed_frames;
    moveVertical( -1 );
  } 
  if( CInputManager::get( ).isPressed( m_keys.key_down ) ) {
    acc_frames = n_freezed_frames;
    moveVertical( 1 );
  } 
  if( CInputManager::get( ).isPressed( m_keys.key_left ) ) {
    acc_frames = n_freezed_frames;
    moveHorizontal( -1 );
  } 
  if( CInputManager::get( ).isPressed( m_keys.key_right ) ) {
    acc_frames = n_freezed_frames;
    moveHorizontal( 1 );
  }

  if( m_target_enemy ) {
    setBoardPos( m_target_enemy->getBoardPos( ) );
    m_texture.setTintColor( SDL_Color( 0, 255, 0, 255 ) );
  } else {
    m_texture.setTintColor( SDL_Color( 255, 0, 0, 255 ) );
  }

}

//-----------------
void CTargetCursor::render( ) {
  m_texture.render( );
}

//-----------------
void CTargetCursor::setBoardPos( TPoint2 board_pos ) {
  m_board_pos = board_pos;

  if( m_board_pos.y > 5 ) {
    m_board_pos.y = 5;
  }

  TPoint2 texture_pos;
  texture_pos.x = m_board_pos.x * m_texture.getWidth( );
  texture_pos.y = m_board_pos.y * m_texture.getHeight( );
  texture_pos += m_render_offset;
  m_texture.setPosition( texture_pos );
}

//-----------------
void CTargetCursor::setTargetEnemy( CEnemy *e ) {
  m_target_enemy = e;
  if( !m_target_enemy ) {
    setBoardPos( getBoardPos( ) );
  }
}

//-----------------
void CTargetCursor::moveVertical( int n ) {
  m_board_pos.y += n;
  m_board_pos.y = ( m_board_pos.y < 0 ? 0 : ( m_board_pos.y >= m_board_size.y ? m_board_size.y -1 : m_board_pos.y ) );
  setBoardPos( m_board_pos );
  m_target_enemy = nullptr;
}

//-----------------
void CTargetCursor::moveHorizontal( int n ) {
  m_board_pos.x += n;
  m_board_pos.x = ( m_board_pos.x < 0 ? 0 : ( m_board_pos.x >= m_board_size.x ? m_board_size.x - 1 : m_board_pos.x ) );
  setBoardPos( m_board_pos );
  m_target_enemy = nullptr;
}
