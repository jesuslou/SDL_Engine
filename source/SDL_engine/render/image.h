#ifndef _INC_IMAGE_H_
#define _INC_IMAGE_H_

#include <string>
#include <SDL.h>

class CImage {
public:
  CImage( );
  ~CImage( );

  bool loadFromFile( std::string path );
  void destroy( );

  void draw( );

  bool isValid( ) const;

  void setPosition( TPoint2 & new_pos );
  void setAlpha( unsigned new_alpha );
  void setAngle( double new_angle );
  void setScale( float new_scale );
  void setPivot( TPoint2 & new_pivot );
  void setFlipMode( SDL_RendererFlip new_flip_mode );
  void setTintColor( SDL_Color & new_color, bool overrides_alpha = false );
  void setBlendMode( SDL_BlendMode new_blend_mode );

  unsigned getAlpha( ) const { return m_alpha; }
  double getAngle( ) const { return m_angle; }
  float getScale( ) const { return m_scale; }

  TPoint2 getPivot( ) const { return m_pivot; }
  SDL_RendererFlip getFlipMode( ) const { return m_flip_mode; }
  SDL_Color getTintColor( ) const { return m_tint_color; }
  SDL_BlendMode getBlendMode( ) const { return m_blend_mode; }

  unsigned getWidth( ) const { return m_width; }
  unsigned getHeight( ) const { return m_height; }

  const std::string & getFilePath( ) const { return m_filepath; }

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

  unsigned          m_width;
  unsigned          m_height;

  std::string       m_filepath;

};

#endif
