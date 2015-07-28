#ifndef _INC_TEXTURE_H_
#define _INC_TEXTURE_H_

#include <SDL.h>

class CTexture {
public:
  CTexture( );
  CTexture( const CTexture &rhs );
  ~CTexture( );

  bool loadFromFile( const char* path );
  bool loadFromFileEditable( const char* path );
  void destroy( );

  void render( );

  bool isValid( ) const;

  void setPosition( const TPoint2 & new_pos );
  void setAlpha( unsigned new_alpha );
  void setAngle( double new_angle );
  void setScale( float new_scale );
  void setPivot( const TPoint2 & new_pivot );
  void setFlipMode( SDL_RendererFlip new_flip_mode );
  void setTintColor( SDL_Color & new_color, bool overrides_alpha = false );
  void setBlendMode( SDL_BlendMode new_blend_mode );
  void setClip( SDL_Rect & new_clip );

  unsigned getAlpha( ) const { return m_alpha; }
  double getAngle( ) const { return m_angle; }
  float getScale( ) const { return m_scale; }

  TPoint2 getPivot( ) const { return m_pivot; }
  SDL_RendererFlip getFlipMode( ) const { return m_flip_mode; }
  SDL_Color getTintColor( ) const { return m_tint_color; }
  SDL_BlendMode getBlendMode( ) const { return m_blend_mode; }
  SDL_Rect getClip( ) const { return m_clip; }
  void* getPixels( ) { return m_pixels; }
  unsigned getPixel32( unsigned int x, unsigned int y );

  bool lockTexture( );
  bool unlockTexture( );

  unsigned getWidth( ) const { return m_width; }
  unsigned getHeight( ) const { return m_height; }
  int getPitch( ) const { return m_pitch; }

  const char* getFilePath( ) const { return m_filepath.c_str( ); }

protected:
  SDL_Texture      *m_texture;

  TPoint2           m_position;
  unsigned          m_alpha;
  double            m_angle;
  float             m_scale;

  TPoint2           m_pivot;
  SDL_RendererFlip  m_flip_mode;
  SDL_Color         m_tint_color;
  SDL_BlendMode     m_blend_mode;
  SDL_Rect          m_clip;

  void             *m_pixels
    ;
  int               m_pitch;
  unsigned          m_width;
  unsigned          m_height;

  std::string       m_filepath;

};

#endif
