#include "common.h"
#include "bullet_storage.h"

//-----------------
CBulletStorage::CBulletStorage( )
: m_render_offset( 0.f, 0.f )
, m_max_bullets( 0 )
, m_n_bullets( 0 )
{ }

//-----------------
bool CBulletStorage::init( int max_bullets, TPoint2 render_offset ) {
  m_max_bullets = max_bullets;
  m_n_bullets = m_max_bullets;
  m_render_offset = render_offset;

  m_background.loadFromFile( "data/textures/bullet_storage.png" );
  m_background.setPosition( render_offset );

  setupBulletTextures( );
  return true;
}

//-----------------
void CBulletStorage::destroy( ) {
  m_background.destroy( );
}

//-----------------
void CBulletStorage::update( float elapsed ) {

}

//-----------------
void CBulletStorage::render( ) {
  m_background.render( );

  for( int i = m_max_bullets - m_n_bullets; i < m_max_bullets; ++i ) {
    m_bullet_textures[ i ].render( );
  }
}

//-----------------
void CBulletStorage::addBullets( int amount ) {
  m_n_bullets += amount;
  m_n_bullets = ( m_n_bullets < 0 ? 0 : ( m_n_bullets > m_max_bullets ? m_max_bullets : m_n_bullets ) );
}

//-----------------
void CBulletStorage::setupBulletTextures( ) {

  float height = m_background.getHeight( );
  height /= m_max_bullets;

  for( int i = 0; i < m_max_bullets; ++i ) {
    CTexture bullet;
    bullet.loadFromFile( "data/textures/bullet.png" );
    bullet.setBlendMode( SDL_BlendMode::SDL_BLENDMODE_BLEND );
    bullet.setPivot( TPoint2( 0.5f, 0.5f ) );
    TPoint2 bullet_pos = m_render_offset;
    bullet_pos.x += m_background.getWidth( ) / 2;
    bullet_pos.x -= bullet.getWidth( ) / 2;
    bullet_pos.y += i * height + ( height / 2 );
    bullet_pos.y -= bullet.getHeight( ) / 2;
    bullet.setPosition( bullet_pos );

    m_bullet_textures.push_back( bullet );
  }
}
