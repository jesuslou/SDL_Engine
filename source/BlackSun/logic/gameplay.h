#ifndef _INC_GAMEPLAY_H_
#define _INC_GAMEPLAY_H_

#include "board.h"
#include "barrier.h"
#include "enemies/enemy_generator.h"

class CGameplay {
public:

  static const int CELLS_X;
  static const int CELLS_Y;
  static const int MAX_BULLETS;

  static CGameplay & get( );
  
  bool init( );
  void destroy( );

  void update( float elapsed );
  void render( );

  void onBarrierReached( );

private:
  CGameplay( );

  CBoard m_board_p1;
  CBoard m_board_p2;

  CBarrier m_barrier;
  CEnemyGenerator m_enemy_generator;

  CTexture m_separator;

  float    m_time_to_can_shoot;
  float    m_time_between_shoots;
};

#endif