#ifndef _INC_ENEMY_BASIC_H_
#define _INC_ENEMY_BASIC_H_

#include "enemy.h"

class CEnemyBasic : public CEnemy {
public:
  CEnemyBasic( );
  CEnemyBasic( const char *img_path, const TPoint2 & board_pos, CBoard *board, float time_percentage );

  //virtual bool init( const char *img_path, const TPoint2 & render_offset, const TPoint2 & board_pos ) override;
  //virtual void destroy( ) override;
  virtual void update( float ) override;
  //virtual void render( ) override;

  //virtual void setBoardPos( TPoint2 board_pos ) override;

protected:



  void move( int amount );
};

#endif