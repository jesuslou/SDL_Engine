#include "common.h"
#include "texture_font.h"


//-----------------
CTextureFont::CTextureFont( ) 
: m_new_line( 0 )
, m_space( 0 )
{ }

//-----------------
CTextureFont::CTextureFont( std::string path ) {
  buildFont( path );
}


//-----------------
bool CTextureFont::buildFont( std::string path ) {
  m_texture.loadFromFileEditable( path );

  if( !m_texture.lockTexture( ) ) {
    printf( "Unable to lock bitmap font texture!\n" );
    return false;
  }

    //Set the background color
  Uint32 bgColor = m_texture.getPixel32( 0, 0 );

    //Set the cell dimensions
  int cellW = m_texture.getWidth( ) / 16;
  int cellH = m_texture.getHeight( ) / 16;

    //New line variables
    int top = cellH;
    int baseA = cellH;

    //The current character we're setting
    int currentChar = 0;

    //Go through the cell rows
    for( int rows = 0; rows < 16; ++rows ) {
      //Go through the cell columns
      for( int cols = 0; cols < 16; ++cols ) {
        //Set the character offset
        m_chars[ currentChar ].x = cellW * cols;
        m_chars[ currentChar ].y = cellH * rows;

        //Set the dimensions of the character
        m_chars[ currentChar ].w = cellW;
        m_chars[ currentChar ].h = cellH;

        //Find Left Side
        //Go through pixel columns
        for( int pCol = 0; pCol < cellW; ++pCol ) {
          //Go through pixel rows
          for( int pRow = 0; pRow < cellH; ++pRow ) {
            //Get the pixel offsets
            int pX = ( cellW * cols ) + pCol;
            int pY = ( cellH * rows ) + pRow;

            //If a non colorkey pixel is found
            if( m_texture.getPixel32( pX, pY ) != bgColor ) {
              //Set the x offset
              m_chars[ currentChar ].x = pX;

              //Break the loops
              pCol = cellW;
              pRow = cellH;
            }
          }
        }

        //Find Right Side
        //Go through pixel columns
        for( int pColW = cellW - 1; pColW >= 0; --pColW ) {
          //Go through pixel rows
          for( int pRowW = 0; pRowW < cellH; ++pRowW ) {
            //Get the pixel offsets
            int pX = ( cellW * cols ) + pColW;
            int pY = ( cellH * rows ) + pRowW;

            //If a non colorkey pixel is found
            if( m_texture.getPixel32( pX, pY ) != bgColor ) {
              //Set the width
              m_chars[ currentChar ].w = ( pX - m_chars[ currentChar ].x ) + 1;

              //Break the loops
              pColW = -1;
              pRowW = cellH;
            }
          }
        }

        //Find Top
        //Go through pixel rows
        for( int pRow = 0; pRow < cellH; ++pRow ) {
          //Go through pixel columns
          for( int pCol = 0; pCol < cellW; ++pCol ) {
            //Get the pixel offsets
            int pX = ( cellW * cols ) + pCol;
            int pY = ( cellH * rows ) + pRow;

            //If a non colorkey pixel is found
            if( m_texture.getPixel32( pX, pY ) != bgColor ) {
              //If new top is found
              if( pRow < top ) {
                top = pRow;
              }

              //Break the loops
              pCol = cellW;
              pRow = cellH;
            }
          }
        }

        //Find Bottom of A
        if( currentChar == 'A' ) {
          //Go through pixel rows
          for( int pRow = cellH - 1; pRow >= 0; --pRow ) {
            //Go through pixel columns
            for( int pCol = 0; pCol < cellW; ++pCol ) {
              //Get the pixel offsets
              int pX = ( cellW * cols ) + pCol;
              int pY = ( cellH * rows ) + pRow;

              //If a non colorkey pixel is found
              if( m_texture.getPixel32( pX, pY ) != bgColor ) {
                //Bottom of a is found
                baseA = pRow;

                //Break the loops
                pCol = cellW;
                pRow = -1;
              }
            }
          }
        }

        //Go to the next character
        ++currentChar;
      }
    }

    //Calculate space
    m_space = cellW / 2;

    //Calculate new line
    m_new_line = baseA - top;

    //Lop off excess top pixels
    for( int i = 0; i < 256; ++i ) {
      m_chars[ i ].y += top;
      m_chars[ i ].h -= top;
    }

    m_texture.unlockTexture( );

  return true;
}


//-----------------
void CTextureFont::renderText( int x, int y, std::string text, float scale ) {

  //WARNING! Scale not working properly

  //Temp offsets
  int curX = x, curY = y;

  //Go through the text
  for( int i = 0; i < text.length( ); ++i ) {
    //If the current character is a space
    if( text[ i ] == ' ' ) {
      //Move over
      curX += m_space * scale;
    }
    //If the current character is a newline
    else if( text[ i ] == '\n' ) {
      //Move down
      curY += m_new_line * scale;

      //Move back
      curX = x;
    } else {
      //Get the ASCII value of the character
      int ascii = ( unsigned char ) text[ i ];

      m_texture.setPosition( TPoint2( curX, curY ) );
      SDL_Rect rect = m_chars[ ascii ];
      rect.w *= scale;
      rect.h *= scale;
      m_texture.setClip( m_chars[ ascii ] );
      //Show the character
      m_texture.draw( );

      //Move over the width of the character with one pixel of padding
      curX += m_chars[ ascii ].w * scale + 1;
    }
  }
}

//-----------------
void CTextureFont::destroy( ) {
  m_texture.destroy( );
}
