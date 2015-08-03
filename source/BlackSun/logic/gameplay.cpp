#include "common.h"
#include "gameplay.h"
#include "fonts/font_manager.h"

const int CGameplay::CELLS_X = 4;
const int CGameplay::CELLS_Y = 6;
const int CGameplay::MAX_BULLETS = 6;

//-----------------
CGameplay & CGameplay::get( ) {
  static CGameplay gp;
  return gp;
}

//-----------------
CGameplay::CGameplay( ) 
: m_time_to_can_shoot( 0.f )
, m_time_between_shoots( 0.5f )
, m_game_state( GS_GAME )
, m_points( 0 )
{
}

static const int maring_up = 78;
//-----------------
bool CGameplay::init( ) {
  m_board_p1.init( CELLS_X, CELLS_Y, "data/textures/cell.png", TPoint2( 75, maring_up ), TPoint2( 0, maring_up ), MAX_BULLETS, TControlKeys( VK_W, VK_S, VK_A, VK_D, VK_SPACE, VK_ENTER ), &m_board_p2 );
  m_board_p2.init( CELLS_X, CELLS_Y, "data/textures/cell.png", TPoint2( 549, maring_up ), TPoint2( 549 + 400, maring_up ), MAX_BULLETS, TControlKeys( VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_SPACE, VK_ENTER ), &m_board_p1 );
  
  m_separator.loadFromFile( "data/textures/bullet_storage.png" );
  m_separator.setPosition( TPoint2( 75 + 400, maring_up ) );

  m_popup.loadFromFile( "data/textures/popup_bg.png" );
  m_popup.setPosition( TPoint2( 275, 178 ) );

  m_barrier.init( TPoint2( 0, 78 + 600 ), TPoint2( 1024, 78 ) );

  m_enemy_generator.init( &m_board_p1, &m_board_p2, 2.0f );
  return true;
}

//-----------------
void CGameplay::destroy( ) {
  m_board_p1.destroy( );
  m_board_p2.destroy( );
  m_separator.destroy( );
  m_barrier.destroy( );
  m_popup.destroy( );
  m_enemy_generator.destroy( );
}

//-----------------
void CGameplay::update( float elapsed ) {

  if( m_game_state == GS_GAME ) {
    m_enemy_generator.update( elapsed );

    m_board_p1.update( elapsed );
    m_board_p2.update( elapsed );

    m_time_to_can_shoot -= elapsed;
    if( CInputManager::get( ).isPressed( VK_SPACE ) && m_time_to_can_shoot <= 0.f ) {
      m_time_to_can_shoot = m_time_between_shoots;

      int points = 0;
      if( m_board_p1.canShoot( ) ) {
        points += m_board_p1.onShoot( );
      }
      if( m_board_p2.canShoot( ) ) {
        points += m_board_p2.onShoot( );
      }
      m_points += points;
      //addPoints( points );
    }

    m_barrier.update( elapsed );
  } else if( m_game_state == GS_LOSE ) {
    fonts.printText( CFontManager::FT_GENERAL, "YOU LOSE", 275, 178 );
    fonts.printText( CFontManager::FT_GENERAL, std::to_string( m_points ), 275, 228 );
    if( CInputManager::get( ).isPressed( VK_ENTER ) ) {
      reset( );
    }
  }
  fonts.printText( CFontManager::FT_GENERAL, std::to_string( m_points ), 475, 0 );
}

//-----------------
void CGameplay::render( ) {
  m_enemy_generator.render( );
  m_board_p1.render( );
  m_board_p2.render( );
  m_separator.render( );
  m_barrier.render( );

  if( m_game_state == GS_LOSE ) {
    m_popup.render( );
  }
}

//-----------------
void CGameplay::reset( ) {
  m_board_p1.reset( );
  m_board_p2.reset( );
  m_barrier.reset( );
  m_enemy_generator.reset( );
  m_points = 0;
  setGameState( GS_GAME );
}

//-----------------
void CGameplay::onBarrierReached( ) {
  bool finish = false;// m_barrier.addLife( -1 );
  if( finish ) {
    setGameState( GS_LOSE );
  }
}

//-----------------
void CGameplay::setGameState( EGameState new_state ) {
  m_game_state = new_state;
}
