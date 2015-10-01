#include "common.h"
#include "font_manager.h"

//-----------------
CFontManager & CFontManager::get( ) {
  static CFontManager fm;
  return fm;
}

//-----------------
CFontManager::CFontManager( ) {
}

//-----------------
bool CFontManager::init( ) {
  m_fonts[ FT_GENERAL ].buildFont( "data/textures/fonts/lazyfont.png" );
  return true;
}

//-----------------
void CFontManager::destroy( ) {
  for( auto & t_font : m_fonts ) {
    t_font.destroy( );
  }
}

//-----------------
void CFontManager::printText( EFontType f_type, int x, int y, const char *msg, ... ) {
  va_list ap;
  va_start( ap, msg );
  printTextInternal( f_type, x, y, msg, ap );
}

//-----------------
void CFontManager::render( ) {
  for( auto & b_text : m_buffered_texts ) {
    m_fonts[ b_text.font_type ].renderText( b_text.x, b_text.y, b_text.text, b_text.scale );
  }
  m_buffered_texts.clear( );
}

//-----------------
void CFontManager::printTextInternal( EFontType f_type, int x, int y, const char *fmt, va_list argp ) {
  static const int max_chars = 1024;
  char text[ max_chars ];
  int n = vsnprintf_s( text, max_chars, fmt, argp );   // Copies N characters
  if( n == -1 || n == max_chars ) {
    text[ max_chars - 1 ] = 0x00;                      // Manually set termination char
  }

  m_buffered_texts.push_back( TBufferedText( f_type, text, x, y, 1.f ) ); // No scales atm
}
