#ifndef _INC_BOARD_H_
#define _INC_BOARD_H_
 
#include <vector>
#include "render/texture.h"
#include "target_cursor.h"
#include "bullet_storage.h"

class CBoard {
public:

  struct TCell {
    int      x;
    int      y;
    bool     has_enemy;
    CTexture texture;
    TCell( ) : x( 0 ), y( 0 ), has_enemy( false ) { }
    TCell( int _x, int _y ) : x( _x ), y( _y ), has_enemy( false ) { }
  };

  CBoard( );

  bool init( int cells_x, int cells_y, const char* img_path, const TPoint2 & render_offset, const TPoint2 & bullets_offset, int max_bullets, TControlKeys ct_keys, CBoard *partner_board );
  void destroy( );
  void update( float elapsed );

  void render( );

  void onShoot( );

private:
  TPoint2         m_render_offset;
  int             m_cells_x;
  int             m_cells_y;

  typedef std::vector<TCell> VCells;
  VCells          m_board;
  TControlKeys    m_keys;

  CTargetCursor   m_target_cursor;
  CBulletStorage  m_bullets;

  CBoard         *m_partner_board;

  float           m_time_to_can_shoot;
  float           m_time_between_shoots;

  TCell & getCell( TPoint2 pos );

};

#endif