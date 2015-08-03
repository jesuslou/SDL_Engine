#ifndef _INC_BARRIER_H_
#define _INC_BARRIER_H_

#include "render/texture.h"

class CBarrier {
public:
  CBarrier( );

  bool init( const TPoint2 & pos, const TPoint2 & size );
  void destroy( );

  void update( float elapsed );
  void render( );

  void reset( );

  bool addLife( unsigned amount );

private:
  CTexture          m_texture;

  static const int  MAX_LIVES = 3;
  unsigned          m_cur_lives;

  SDL_Color         colors[ MAX_LIVES ];
};

#endif