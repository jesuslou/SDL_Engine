#ifndef _INC_ENEMY_GENERATOR_H_
#define _INC_ENEMY_GENERATOR_H_

#include "render/texture.h"

class CBoard;

class CEnemyGenerator {
public:
  CEnemyGenerator( );

  bool init( CBoard *board_p1, CBoard *board_p2, float time_between_enemies );
  void destroy( );
  
  void update( float elapsedd );
  void render( );

  void reset( );

  void spawnEnemies( CBoard *board, int x );

private:

  CBoard *m_board_p1;
  CBoard *m_board_p2;

  float m_time_p1;
  float m_time_p2;
  float m_time_between_enemies;
  
  float m_global_acc_time;

  float m_time_to_next_enemy_p1;
  float m_time_to_next_enemy_p2;

  int   m_next_enemy_x_p1;
  int   m_next_enemy_x_p2;

  CTexture m_next_enemy_img_p1;
  CTexture m_next_enemy_img_p2;
};

#endif