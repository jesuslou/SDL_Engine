#include "common.h"
#include "enemy_generator.h"
#include "logic/board.h"
#include "enemy_basic.h"

//-----------------
CEnemyGenerator::CEnemyGenerator( )
: m_board_p1( nullptr )
, m_board_p2( nullptr )
, m_time( 0.f )
, m_time_between_enemies( 0.f )
, m_global_acc_time( 0.f )
{ }

//-----------------
bool CEnemyGenerator::init( CBoard *board_p1, CBoard *board_p2, float time_between_enemies ) {
  m_board_p1 = board_p1;
  m_board_p2 = board_p2;
  m_time_between_enemies = time_between_enemies;

  reset( );

  return true;
}

//-----------------
void CEnemyGenerator::destroy( ) {
}

//-----------------
void CEnemyGenerator::update( float elapsed ) {
  m_global_acc_time += elapsed;
  m_time -= elapsed;
  if( m_time < 0.f ) {
    m_time = m_time_between_enemies;
    spawnEnemies( );
  }
}

//-----------------
void CEnemyGenerator::reset( ) {
  m_global_acc_time = 0.f;
  m_time = 0.f;
}

//-----------------
void CEnemyGenerator::spawnEnemies( ) {
  float base_speed = 0.7;
  base_speed *= ( 1.f - ( m_global_acc_time / 60.f ) );
  m_board_p1->addEnemy( new CEnemyBasic( "data/textures/enemy_01.png", TPoint2( rand( ) % 4, 0 ), m_board_p1, base_speed ) );
  m_board_p2->addEnemy( new CEnemyBasic( "data/textures/enemy_01.png", TPoint2( rand( ) % 4, 0 ), m_board_p2, base_speed ) );
}
