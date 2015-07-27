#include "common.h"
#include "texture.h"
#include "renderer.h"
#include "texture_manager.h"

//-----------------
CTexture::CTexture( ) 
: m_texture( nullptr )
, m_position( 0.f, 0.f )
, m_alpha( 255 )
, m_angle( 0 )
, m_scale( 1.f )
, m_pivot( 0.f, 0.f )
, m_flip_mode( SDL_FLIP_NONE )
, m_tint_color( 255, 255, 255, 255 )
, m_blend_mode( SDL_BLENDMODE_NONE )
, m_pixels( nullptr )
, m_pitch( 0 )
, m_width( 0 )
, m_height( 0 )
{ }

//-----------------
CTexture::~CTexture( ) {
  destroy( );
}


//-----------------
bool CTexture::loadFromFile( std::string path ) {

  destroy( );

  m_texture = CTextureManager::get( ).loadTexture( path, &m_width, &m_height );
  m_filepath = path;

  m_clip.x = 0;
  m_clip.y = 0;
  m_clip.w = m_width;
  m_clip.h = m_height;

  return m_texture != nullptr;
}

//-----------------
bool CTexture::loadFromFileEditable( std::string path ) {

  destroy( );

  m_texture = CTextureManager::get( ).loadEditableTexture( path, &m_width, &m_height, &m_pitch );
  m_filepath = path;

  m_clip.x = 0;
  m_clip.y = 0;
  m_clip.w = m_width;
  m_clip.h = m_height;

  return m_texture != nullptr;
}


//-----------------
void CTexture::destroy( ) {
  if( m_texture ) {
    CTextureManager::get( ).releaseTexture( m_filepath );
    m_texture = nullptr;
    m_width = 0;
    m_height = 0;
  }
}

//-----------------
void CTexture::draw( ) {
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

  render_quad.w = m_clip.w;
  render_quad.h = m_clip.h;

  SDL_Point pivot_transformed = {
      static_cast<int>( m_pivot.x * static_cast<float>( render_quad.w ) )
    , static_cast<int>( m_pivot.y * static_cast<float>( render_quad.h ) )
  };

  // Doing some research I've found that this setter functions are quite cheap to call every frame.
  // They just add some flags to the texture header and don't perform any real changes to the texture.
  // The changes are applied in the SDL_RenderCopyEx( ) function.
  // I need to set this params here, every frame, because I'm using shared SDL_Texture* between CTextures,
  // so if I change one of this parameters it affects to all CTextures usign this SDL_Texture*.
  SDL_SetTextureAlphaMod( m_texture, m_alpha );
  SDL_SetTextureColorMod( m_texture, m_tint_color.r, m_tint_color.g, m_tint_color.b );
  SDL_SetTextureBlendMode( m_texture, m_blend_mode );

  //Render to screen
  int hr = SDL_RenderCopyEx( CRenderer::get( ).getRenderer( ), m_texture, &m_clip, &render_quad, m_angle, &pivot_transformed, m_flip_mode );
  if( hr < 0 ) {
    printf( "CTexture::SDL_RenderCopyEx FAILURE! SDL_Error: %s\n", SDL_GetError( ) );
  }
}

//-----------------
bool CTexture::isValid( ) const {
  return m_texture && m_width > 0 && m_height > 0;
}

//-----------------
void CTexture::setPosition( TPoint2 & new_pos ) {
  m_position = new_pos;
}

//-----------------
void CTexture::setAlpha( unsigned new_alpha ) {
  m_alpha = new_alpha;
}

//-----------------
void CTexture::setAngle( double new_angle ) {
  m_angle = new_angle;
}

//-----------------
void CTexture::setScale( float new_scale ) {
  m_scale = new_scale;
}

//-----------------
void CTexture::setPivot( TPoint2 & new_pivot ) {
  m_pivot = new_pivot;
}

//-----------------
void CTexture::setFlipMode( SDL_RendererFlip new_flip_mode ) {
  m_flip_mode = new_flip_mode;
}

//-----------------
void CTexture::setTintColor( SDL_Color & new_color, bool overrides_alpha ) {
  m_tint_color = new_color;
  if( overrides_alpha ) {
    setAlpha( m_tint_color.a );
  }
}

//-----------------
void CTexture::setBlendMode( SDL_BlendMode new_blend_mode ) {
  m_blend_mode = new_blend_mode;
}

//-----------------
void CTexture::setClip( SDL_Rect & new_clip ) {
  m_clip = new_clip;
}

//-----------------
unsigned CTexture::getPixel32( unsigned int x, unsigned int y ) {
  //Convert the pixels to 32 bit
  unsigned *pixels = ( unsigned* ) m_pixels;
  //Get the pixel requested
  return pixels[ ( y * ( m_pitch / 4 ) ) + x ];
}

//-----------------
bool CTexture::lockTexture( ) {
  //Texture is already locked
  if( m_pixels != nullptr ) {
    printf( "Texture is already locked!\n" );
    return false;
  }
  //Lock texture
  else {
    if( SDL_LockTexture( m_texture, NULL, &m_pixels, &m_pitch ) != 0 ) {
      printf( "Unable to lock texture! %s\n", SDL_GetError( ) );
      return false;
    }
  }

  return true;
}

//-----------------
bool CTexture::unlockTexture( ) {
  bool success = true;

  //Texture is not locked
  if( m_pixels == nullptr ) {
    printf( "Texture is not locked!\n" );
    success = false;
  }
  //Unlock texture
  else {
    SDL_UnlockTexture( m_texture );
    m_pixels = nullptr;
    m_pitch = 0;
  }

  return success;
}