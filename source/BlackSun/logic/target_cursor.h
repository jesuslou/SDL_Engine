#ifndef _INC_TARGET_CURSOR_H_
#define _INC_TARGET_CURSOR_H_

#include "render/texture.h"
#include "control_keys_data.h"

class CEnemy;

class CTargetCursor {
public:

  CTargetCursor( );

  bool init( TPoint2 board_size, TPoint2 board_pos, TPoint2 render_offset, const char *img_path );
  void destroy( );
  void update( float elapsed );
  void render( );

  void setControlKeys( TControlKeys keys ) { m_keys = keys; }
  void setBoardPos( TPoint2 board_pos );
  TPoint2 getBoardPos( ) const { return m_board_pos; }

  void setTargetEnemy( CEnemy *e );
  const CEnemy* getTargetEnemy( ) const { return m_target_enemy; }

private:
  CTexture m_texture;

  TPoint2 m_render_offset;
  TPoint2 m_board_size;
  TPoint2 m_board_pos;

  TControlKeys m_keys;

  CEnemy      *m_target_enemy;

  int acc_frames;
  int n_freezed_frames;

  void moveVertical( int n );
  void moveHorizontal( int n );

};

#endif