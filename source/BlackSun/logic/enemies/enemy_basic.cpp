#include "common.h"
#include "enemy_basic.h"
#include "../board.h"

//-----------------
CEnemyBasic::CEnemyBasic( )
: m_acc_elaspsed( 0.f )
, m_time_between_moves( 0.7 )
{ }

//-----------------
CEnemyBasic::CEnemyBasic( const char *img_path, const TPoint2 & board_pos, CBoard *board )
: m_acc_elaspsed( 0.f )
, m_time_between_moves( 0.7 )
{
  init( img_path, board->getRenderOffset( ), board_pos, board );
}

//-----------------
void CEnemyBasic::update( float elapsed ) {
  m_acc_elaspsed -= elapsed;

  if( m_acc_elaspsed < 0.f ) {
    m_acc_elaspsed = m_time_between_moves;
    move( 1 );
  }
}

//-----------------
void CEnemyBasic::move( int amount ) {
  TPoint2 new_pos = m_board_pos;
  new_pos.y += 1;
  setBoardPos( new_pos );
}
