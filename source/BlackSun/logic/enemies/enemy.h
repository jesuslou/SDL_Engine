#ifndef _INC_ENEMY_H_
#define _INC_ENEMY_H_

#include "render/texture.h"

class CBoard;

class CEnemy {
public:
  CEnemy( );

  virtual bool init( const char *img_path, const TPoint2 & render_offset, const TPoint2 & board_pos, CBoard *board );
  virtual void destroy( );
  virtual void update( float ) = 0;
  virtual void render( );

  virtual void setBoardPos( TPoint2 board_pos );
  TPoint2 getBoardPos( ) const { return m_board_pos; }

protected:

  TPoint2 m_render_offset;
  TPoint2 m_board_pos;

  CTexture m_texture;

  CBoard  *m_board;
};

#endif