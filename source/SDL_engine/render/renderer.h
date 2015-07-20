#ifndef _INC_RENDERER_H_
#define _INC_RENDERER_H_

#include <SDL.h>

class CRenderer {
public:
  static CRenderer & get( );

  bool init( const char *app_title, unsigned x_res, unsigned y_res );
  void destroy( );

  void beginRender( );
  void endRender( );

  void setClearColor( SDL_Color & new_color ) { m_clear_color = new_color; }
  SDL_Color getClearColor( ) const { return m_clear_color; }

  SDL_Window* getWindow( ) const { return m_window; }
  SDL_Renderer* getRenderer( ) const { return m_renderer; }

private:
  CRenderer( );

  unsigned      m_x_res;
  unsigned      m_y_res;

  SDL_Window   *m_window;
  SDL_Renderer *m_renderer;

  SDL_Color     m_clear_color;
};

#endif