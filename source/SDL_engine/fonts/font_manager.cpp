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
void CFontManager::printText( EFontType f_type, std::string text, int x, int y, float scale ) {
  m_buffered_texts.push_back( TBufferedText( f_type, text, x, y, scale ) );
}

//-----------------
void CFontManager::render( ) {
  for( auto & b_text : m_buffered_texts ) {
    m_fonts[ b_text.font_type ].renderText( b_text.x, b_text.y, b_text.text, b_text.scale );
  }
  m_buffered_texts.clear( );
}
