#include "common.h"
#include "image.h"
#include "renderer.h"
#include "texture_manager.h"

//-----------------
CImage::CImage( ) 
: m_texture( nullptr )
, m_position( 0.f, 0.f )
, m_alpha( 255 )
, m_angle( 0 )
, m_scale( 1.f )
, m_pivot( 0.f, 0.f )
, m_flip_mode( SDL_FLIP_NONE )
, m_tint_color( 255, 255, 255, 255 )
, m_blend_mode( SDL_BLENDMODE_NONE )
, m_width( 0 )
, m_height( 0 )
{ }

//-----------------
CImage::~CImage( ) {
  destroy( );
}


//-----------------
bool CImage::loadFromFile( std::string path ) {

  destroy( );

  m_texture = CTextureManager::get( ).loadTexture( path, &m_width, &m_height );
  m_filepath = path;
  return m_texture != nullptr;
}

//-----------------
void CImage::destroy( ) {
  if( m_texture ) {
    CTextureManager::get( ).releaseTexture( m_filepath );
    m_texture = nullptr;
    m_width = 0;
    m_height = 0;
  }
}

//-----------------
void CImage::draw( ) {
  //Set rendering space and render to screen
  SDL_Rect render_quad = { 
      static_cast<int>( m_position.x )
    , static_cast<int>( m_position.y )
    , static_cast<int>( static_cast<float>( m_width ) * m_scale )
    , static_cast<int>( static_cast<float>( m_height ) * m_scale )
  };

  //Set clip rendering dimensions
  //if( clip != NULL ) {
  //  renderQuad.w = clip->w;
  //  renderQuad.h = clip->h;
  //}

  SDL_Point pivot_transformed = {
      static_cast<int>( m_pivot.x * static_cast<float>( render_quad.w ) )
    , static_cast<int>( m_pivot.y * static_cast<float>( render_quad.h ) )
  };

  // Doing some research I've found that this setter functions are quite cheap to call every frame.
  // They just add some flags to the texture header and don't perform any real changes to the texture.
  // The changes are applied in the SDL_RenderCopyEx( ) function.
  // I need to set this params here, every frame, because I'm using shared SDL_Texture* between CImages,
  // so if I change one of this parameters it affects to all CImages usign this SDL_Texture*.
  SDL_SetTextureAlphaMod( m_texture, m_alpha );
  SDL_SetTextureColorMod( m_texture, m_tint_color.r, m_tint_color.g, m_tint_color.b );
  SDL_SetTextureBlendMode( m_texture, m_blend_mode );

  //Render to screen
  int hr = SDL_RenderCopyEx( CRenderer::get( ).getRenderer( ), m_texture, nullptr, &render_quad, m_angle, &pivot_transformed, m_flip_mode );
  if( hr < 0 ) {
    printf( "CImage::SDL_RenderCopyEx FAILURE! SDL_Error: %s\n", SDL_GetError( ) );
  }
}

//-----------------
bool CImage::isValid( ) const {
  return m_texture && m_width > 0 && m_height > 0;
}

//-----------------
void CImage::setPosition( TPoint2 & new_pos ) {
  m_position = new_pos;
}

//-----------------
void CImage::setAlpha( unsigned new_alpha ) {
  m_alpha = new_alpha;
}

//-----------------
void CImage::setAngle( double new_angle ) {
  m_angle = new_angle;
}

//-----------------
void CImage::setScale( float new_scale ) {
  m_scale = new_scale;
}

//-----------------
void CImage::setPivot( TPoint2 & new_pivot ) {
  m_pivot = new_pivot;
}

//-----------------
void CImage::setFlipMode( SDL_RendererFlip new_flip_mode ) {
  m_flip_mode = new_flip_mode;
}

//-----------------
void CImage::setTintColor( SDL_Color & new_color, bool overrides_alpha ) {
  m_tint_color = new_color;
  if( overrides_alpha ) {
    setAlpha( m_tint_color.a );
  }
}

//-----------------
void CImage::setBlendMode( SDL_BlendMode new_blend_mode ) {
  m_blend_mode = new_blend_mode;
}
