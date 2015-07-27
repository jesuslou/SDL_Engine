#ifndef _INC_TEXTURE_FONT_H_
#define _INC_TEXTURE_FONT_H_

#include <SDL.h>
#include "render/texture.h"

class CTexture;

class CTextureFont {
public:
  CTextureFont( );
  CTextureFont( std::string path );

  //Generates the font
  bool buildFont( std::string path );

  //Shows the text
  void renderText( int x, int y, std::string text, float scale = 1.f );

  void destroy( );
protected:
  //The font texture
  CTexture m_texture;

  //The individual characters in the surface
  SDL_Rect  m_chars[ 256 ];

  //Spacing Variables
  int       m_new_line;
  int       m_space;

};

#endif
