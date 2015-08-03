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

  enum EGameState {
    GS_GAME = 0
    , GS_LOSE
  };

  static CGameplay & get( );
  
  bool init( );
  void destroy( );

  void update( float elapsed );
  void render( );

  void reset( );

  void onBarrierReached( );

  void setGameState( EGameState new_state );
private:
  CGameplay( );

  CBoard m_board_p1;
  CBoard m_board_p2;

  CBarrier m_barrier;
  CEnemyGenerator m_enemy_generator;

  CTexture m_separator;
  CTexture m_popup;

  float    m_time_to_can_shoot;
  float    m_time_between_shoots;

  int      m_points;

  EGameState m_game_state;
};

#endif