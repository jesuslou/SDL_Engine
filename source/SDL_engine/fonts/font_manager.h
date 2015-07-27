#ifndef _INC_FONT_MANAGER_H_
#define _INC_FONT_MANAGER_H_

#include <vector>
#include <SDL.h>
#include "texture_font.h"

class CFontManager {
public:

  enum EFontType {
      FT_GENERAL = 0
    , FT_N_FONTS
  };

  static CFontManager & get( );

  bool init( );
  void destroy( );

  void printText( EFontType f_type, std::string text, int x, int y, float scale = 1.f );

  void render( );

private:
  CFontManager( );

  CTextureFont m_fonts[ FT_N_FONTS ];

  struct TBufferedText {
    EFontType font_type;
    std::string text;
    int x;
    int y;
    float scale;
    TBufferedText( ) : font_type( FT_GENERAL ), text( ), x( 0 ), y( 0 ), scale( 1.f ) { }
    TBufferedText( EFontType _ft, std::string _t, int _x, int _y, float _s ) : font_type( _ft ), text( _t ), x( _x ), y( _y ), scale( _s ) { }
  };

  static const int MAX_BUFFERED_TEXTS = 64;
  typedef std::vector<TBufferedText> VBufferedTexts;
  VBufferedTexts m_buffered_texts;
};

#define fonts CFontManager::get( ) 

#endif