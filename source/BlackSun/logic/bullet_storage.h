#ifndef _INC_BULLET_STORAGE_H_
#define _INC_BULLET_STORAGE_H_

#include <vector>
#include "render/texture.h"

class CBulletStorage {
public:
  CBulletStorage( );

  bool init( int max_bullets, TPoint2 render_offset );
  void destroy( );

  void update( float elapsed );
  void render( );

  bool canShoot( ) const { return m_n_bullets > 0; }

  void addBullets( int amount );

private:
  typedef std::vector<CTexture> VBulletTextures;

  TPoint2         m_render_offset;
  int             m_max_bullets;
  int             m_n_bullets;

  // Render
  CTexture        m_background;
  VBulletTextures m_bullet_textures;

  void setupBulletTextures( );
};

#endif