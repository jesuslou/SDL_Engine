#include "common.h"
#include "gameplay.h"

const int CGameplay::CELLS_X = 4;
const int CGameplay::CELLS_Y = 6;
const int CGameplay::MAX_BULLETS = 6;

//-----------------
CGameplay & CGameplay::get( ) {
  static CGameplay gp;
  return gp;
}

//-----------------
CGameplay::CGameplay( ) {
}

static const int maring_up = 78;
//-----------------
bool CGameplay::init( ) {
  m_board_p1.init( CELLS_X, CELLS_Y, "data/textures/cell.png", TPoint2( 75, maring_up ), TPoint2( 0, maring_up ), MAX_BULLETS, TControlKeys( VK_W, VK_S, VK_A, VK_D, VK_SPACE, VK_ENTER ), &m_board_p2 );
  m_board_p2.init( CELLS_X, CELLS_Y, "data/textures/cell.png", TPoint2( 549, maring_up ), TPoint2( 549 + 400, maring_up ), MAX_BULLETS, TControlKeys( VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_SPACE, VK_ENTER ), &m_board_p1 );
  
  m_separator.loadFromFile( "data/textures/bullet_storage.png" );
  m_separator.setPosition( TPoint2( 75 + 400, maring_up ) );

  return true;
}

//-----------------
void CGameplay::destroy( ) {
  m_board_p1.destroy( );
  m_board_p2.destroy( );
  m_separator.destroy( );
}

//-----------------
void CGameplay::update( float elapsed ) {
  m_board_p1.update( elapsed );
  m_board_p2.update( elapsed );
}

//-----------------
void CGameplay::render( ) {
  m_board_p1.render( );
  m_board_p2.render( );
  m_separator.render( );
}
