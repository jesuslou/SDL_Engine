#include "common.h"
#include "enemy_basic.h"
#include "../board.h"
#include "fonts/font_manager.h"

//-----------------
CEnemyBasic::CEnemyBasic( )
{ }

//-----------------
CEnemyBasic::CEnemyBasic( const char *img_path, const TPoint2 & board_pos, CBoard *board, float time_percentage )
{
  init( img_path, board->getRenderOffset( ), board_pos, board );
  m_min_vel = 0.7f;
  m_max_vel = 0.45f;

  m_time_between_moves = m_min_vel - ( ( m_min_vel - m_max_vel ) * time_percentage );
  m_acc_elaspsed = m_time_between_moves;

}

//-----------------
void CEnemyBasic::update( float elapsed ) {
  m_acc_elaspsed -= elapsed;

  if( m_acc_elaspsed < 0.f ) {
    m_acc_elaspsed = m_time_between_moves;
    move( 1 );
  }

  fonts.printText( CFontManager::FT_GENERAL, std::to_string( m_time_between_moves ), m_texture.getPosition( ).x, m_texture.getPosition( ).y );
}

//-----------------
void CEnemyBasic::move( int amount ) {
  TPoint2 new_pos = m_board_pos;
  new_pos.y += 1;
  setBoardPos( new_pos );
}
