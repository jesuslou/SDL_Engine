#ifndef _INC_GAMEPLAY_H_
#define _INC_GAMEPLAY_H_

#include "board.h"

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

private:
  CGameplay( );

  CBoard m_board_p1;
  CBoard m_board_p2;

  CTexture m_separator;
};

#endif