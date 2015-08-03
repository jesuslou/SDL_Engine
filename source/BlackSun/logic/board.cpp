#include "common.h"
#include "board.h"
#include <cstdio>

//-------------------------
CBoard::CBoard( ) 
: m_render_offset( 0.f, 0.f )
, m_partner_board( nullptr )
{ }

//-------------------------
bool CBoard::init( int _cells_x, int _cells_y, const char* img_path, const TPoint2 & _render_offset, const TPoint2 & bullets_offset, int max_bullets, TControlKeys ct_keys, CBoard *partner_board ) {
  m_render_offset = _render_offset;
  m_cells_x = _cells_x;
  m_cells_y = _cells_y;
  m_keys = ct_keys;
  m_partner_board = partner_board;

  for( int x = 0; x < m_cells_x; ++x ) {
    for( int y = 0; y < m_cells_y; ++y ) {
      TCell cell( x, y );
      CTexture & img = cell.texture;
      img.loadFromFile( img_path );
      TPoint2 cell_pos;
      cell_pos.x = x * img.getWidth( );
      cell_pos.y = y * img.getHeight( );
      cell_pos += m_render_offset;
      img.setPosition( cell_pos );
      img.setBlendMode( SDL_BlendMode::SDL_BLENDMODE_BLEND );
      CTexture & dbg_img = cell.debug_texture;
      dbg_img.loadFromFile( "data/textures/bullet.png" );
      dbg_img.setPosition( cell_pos );
      dbg_img.setBlendMode( SDL_BlendMode::SDL_BLENDMODE_BLEND );
      m_board.push_back( cell );
    }
  }

  m_target_cursor.init( TPoint2( m_cells_x, m_cells_y ), TPoint2( rand( ) % m_cells_x, rand( ) % m_cells_y ), m_render_offset, "data/textures/target.png" );
  m_target_cursor.setControlKeys( ct_keys );

  m_bullets.init( max_bullets, bullets_offset );

  return true;
}

//-------------------------
void CBoard::destroy( ) {
  for( auto & cell : m_board ) {
    cell.texture.destroy( );
    cell.debug_texture.destroy( );
  }

  for( auto & enemy : m_enemies ) {
    enemy->destroy( );
    delete enemy;
  }
  m_enemies.clear( );

  m_target_cursor.destroy( );
  m_bullets.destroy( );
}


//-------------------------
void CBoard::update( float elapsed ) {
  m_target_cursor.update( elapsed );

  for( auto & enemy : m_enemies ) {
    enemy->update( elapsed );
  }
  updateEnemiesInCells( );

}

//-------------------------
void CBoard::render( ) {
  for( auto & cell : m_board ) {
    cell.texture.render( );
    if( cell.has_enemy )
      cell.debug_texture.render( );
  }

  for( auto & enemy : m_enemies ) {
    enemy->render( );
  }

  m_target_cursor.render( );
  m_bullets.render( );
}

//-------------------------
void CBoard::reset( ) {
  for( auto & cell : m_board ) {
    cell.has_enemy = false;
  }
  for( auto & enemy : m_enemies ) {
    enemy->destroy( );
    delete enemy;
  }
  m_enemies.clear( );

  m_target_cursor.setBoardPos( TPoint2( rand( ) % m_cells_x, rand( ) % m_cells_y ) );

}


//-------------------------
bool CBoard::canShoot( ) const {
  return m_bullets.canShoot( );
}

//-------------------------
int CBoard::onShoot( ) {
  m_bullets.addBullets( -1 );
  TPoint2 cursor_pos = m_target_cursor.getBoardPos( );
  TCell * cell = getCell( cursor_pos );
  if( m_partner_board &&  cell->has_enemy ) {
    m_partner_board->m_bullets.addBullets( 1 );
    destroyEnemy( cursor_pos );
    return 1;
  }
  return 0;
}

//-------------------------
void CBoard::addEnemy( CEnemy *enemy ) {
  m_enemies.push_back( enemy );
}

//-------------------------
CBoard::TCell * CBoard::getCell( TPoint2 pos ) {
  for( auto & cell : m_board ) {
    if( cell.x == pos.x && cell.y == pos.y ) {
      return &cell;
    }
  }
  return nullptr;
}

//-------------------------
CEnemy * CBoard::getEnemy( TPoint2 pos ) {
  for( auto & enemy : m_enemies ) {
    if( enemy->getBoardPos( ) == pos ) {
      return enemy;
    }
  }
  return nullptr;
}

//-------------------------
CBoard::VEnemies::iterator CBoard::getEnemyIterator( TPoint2 pos ) {
  VEnemies::iterator it;
  for( it = m_enemies.begin( ); it != m_enemies.end( ); ++it ) {
    if( ( *it )->getBoardPos( ) == pos ) {
      return it;
    }
  }
  return m_enemies.end( );
}


//-------------------------
void CBoard::updateEnemiesInCells( ) {
  for( auto & cell : m_board ) {
    cell.has_enemy = false;
  }

  std::vector<TPoint2> enemies_to_destroy;
  for( auto & enemy : m_enemies ) {
    TPoint2 enemy_pos = enemy->getBoardPos( );
    TCell *cell = getCell( enemy_pos );
    if( cell ) {
      cell->has_enemy = true;
    }

    if( enemy_pos.y > 5 ) {
      enemies_to_destroy.push_back( enemy_pos );
    }
  }

  for( auto & pos : enemies_to_destroy ) {
    destroyEnemy( pos );
  }
}

//-------------------------
void CBoard::destroyEnemy( TPoint2 pos ) {
  VEnemies::iterator enemy = getEnemyIterator( pos );
  if( enemy != m_enemies.end( ) ) {
    ( *enemy )->destroy( );
    delete ( *enemy );
  }
  m_enemies.erase( enemy );
}
