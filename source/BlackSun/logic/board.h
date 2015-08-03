#ifndef _INC_BOARD_H_
#define _INC_BOARD_H_
 
#include <vector>
#include "render/texture.h"
#include "target_cursor.h"
#include "bullet_storage.h"
#include "enemies/enemy_basic.h"

class CBoard {
public:

  struct TCell {
    int      x;
    int      y;
    bool     has_enemy;
    CTexture texture;
    CTexture debug_texture;
    TCell( ) : x( 0 ), y( 0 ), has_enemy( false ) { }
    TCell( int _x, int _y ) : x( _x ), y( _y ), has_enemy( false ) { }
  };

  CBoard( );

  bool init( int cells_x, int cells_y, const char* img_path, const TPoint2 & render_offset, const TPoint2 & bullets_offset, int max_bullets, TControlKeys ct_keys, CBoard *partner_board );
  void destroy( );
  void update( float elapsed );

  void render( );

  void reset( );

  bool canShoot( ) const;
  int onShoot( );

  void addEnemy( CEnemy *enemy );

  const TPoint2 & getRenderOffset( ) const { return m_render_offset; }
  CTargetCursor & getTargetCursor( ) { return m_target_cursor; }
private:
  typedef std::vector<TCell> VCells;
  typedef std::vector<CEnemy*> VEnemies;

  TPoint2         m_render_offset;
  int             m_cells_x;
  int             m_cells_y;

  VCells          m_board;
  TControlKeys    m_keys;

  CTargetCursor   m_target_cursor;
  CBulletStorage  m_bullets;
  VEnemies        m_enemies;

  CBoard         *m_partner_board;

  CTexture        m_warning_frame;

  TCell * getCell( TPoint2 pos );
  CEnemy * getEnemy( TPoint2 pos );
  VEnemies::iterator getEnemyIterator( TPoint2 pos );
  void updateEnemiesInCells( );
  void updateDestroyableEnemies( );
  void destroyEnemy( TPoint2 pos );
  void checksIfCursorOverEnemy( );

};

#endif