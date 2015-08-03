#include "common.h"
#include "enemy_generator.h"
#include "logic/board.h"
#include "enemy_basic.h"

//-----------------
CEnemyGenerator::CEnemyGenerator( )
: m_board_p1( nullptr )
, m_board_p2( nullptr )
, m_time_p1( 0.f )
, m_time_p2( 0.f )
, m_time_between_enemies( 0.f )
, m_global_acc_time( 0.f )
, m_time_to_next_enemy_p1( 0.f )
, m_time_to_next_enemy_p2( 0.f )
, m_next_enemy_x_p1( 0 )
, m_next_enemy_x_p2( 0 )
{ }

//-----------------
bool CEnemyGenerator::init( CBoard *board_p1, CBoard *board_p2, float time_between_enemies ) {
  m_board_p1 = board_p1;
  m_board_p2 = board_p2;
  m_time_between_enemies = time_between_enemies;

  m_next_enemy_img_p1.loadFromFile( "data/textures/arrow.png" );
  m_next_enemy_img_p2.loadFromFile( "data/textures/arrow.png" );

  reset( );

  return true;
}

//-----------------
void CEnemyGenerator::destroy( ) {
  m_next_enemy_img_p1.destroy( );
  m_next_enemy_img_p2.destroy( );
}

//-----------------
void CEnemyGenerator::update( float elapsed ) {
  m_global_acc_time += elapsed;
  m_time_p1 -= elapsed;
  m_time_p2 -= elapsed;

  if( m_time_p1 < 0.f ) {
    spawnEnemies( m_board_p1, m_next_enemy_x_p1 );
    int rnd = ( rand( ) % ( 100 - 75 ) ) + 75;
    rnd = ( rnd > 100 ? 100 : rnd );
    float rnd_percentage = static_cast< float >( rnd ) / 100.f;
    m_time_to_next_enemy_p1 = 2.5f * rnd_percentage;
    m_time_p1 = m_time_to_next_enemy_p1;
    m_next_enemy_x_p1 = rand( ) % 4;
    TPoint2 r_offset = m_board_p1->getRenderOffset( );
    m_next_enemy_img_p1.setPosition( TPoint2( r_offset.x + ( m_next_enemy_x_p1 * 100 ), r_offset.y ) );
  }
  if( m_time_p2 < 0.f ) {
    spawnEnemies( m_board_p2, m_next_enemy_x_p2 );
    int rnd = ( rand( ) % 25 ) + 75;
    float rnd_percentage = static_cast< float >( rnd ) / 100.f;
    m_time_to_next_enemy_p2 = 1.5f * rnd_percentage;
    m_time_p2 = m_time_to_next_enemy_p2;
    m_next_enemy_x_p2 = rand( ) % 4;
    TPoint2 r_offset = m_board_p2->getRenderOffset( );
    m_next_enemy_img_p2.setPosition( TPoint2( r_offset.x + ( m_next_enemy_x_p2 * 100 ), r_offset.y ) );
  }

}

//-----------------
void CEnemyGenerator::render( ) {
  m_next_enemy_img_p1.render( );
  m_next_enemy_img_p2.render( );
}

//-----------------
void CEnemyGenerator::reset( ) {
  m_global_acc_time = 0.f;
  m_time_p1 = 0.f;
  m_time_p2 = 0.f;

  m_next_enemy_x_p1 = rand( ) % 4;
  m_next_enemy_x_p2 = rand( ) % 4;

}

//-----------------
void CEnemyGenerator::spawnEnemies( CBoard *board, int x ) {
  float time_percentage = m_global_acc_time / 60.f;
  time_percentage = ( time_percentage > 1.f ? 1.f : time_percentage );
  board->addEnemy( new CEnemyBasic( "data/textures/enemy_01.png", TPoint2( x, 0 ), board, time_percentage ) );
}
