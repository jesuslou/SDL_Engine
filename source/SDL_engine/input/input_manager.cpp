#include "common.h"
#include "input_manager.h"

//-------------------------
CInputManager & CInputManager::get( ) {
  static CInputManager cim;
  return cim;
}

//-------------------------
CInputManager::CInputManager( )
: m_cur_key_states( nullptr )
, m_old_key_states( nullptr )
, m_mouse_mov_dir( EMouseMovementDir::MMD_NONE )
, m_mouse_pos( 0.f, 0.f )
{ }

//-------------------------
void CInputManager::destroy( ) {
  if( m_old_key_states ) {
    delete[ ] m_old_key_states;
    m_old_key_states = nullptr;
  }

  if( m_cur_key_states ) {
    delete[ ] m_cur_key_states;
    m_cur_key_states = nullptr;
  }
}

// ---------------------------
// Keyboard Input
// ---------------------------

//-------------------------
void CInputManager::updateKeyboard( ) {
  int n = 0;
  if( !m_old_key_states ) {
    const Uint8* tmp_key_states = SDL_GetKeyboardState( &n );
    m_cur_key_states = new Uint8[ n ];
    m_old_key_states = new Uint8[ n ];
    memcpy( ( void* ) m_cur_key_states, tmp_key_states, sizeof( Uint8 ) * n );
    memset( ( void* ) m_old_key_states, 0x0, sizeof( Uint8 ) * n );
  } else {
    const Uint8* tmp_key_states = SDL_GetKeyboardState( &n );
    memcpy( ( void* ) m_old_key_states, m_cur_key_states, sizeof( Uint8 ) * n );
    memcpy( ( void* ) m_cur_key_states, tmp_key_states, sizeof( Uint8 ) * n );
  }
}

//-------------------------
bool CInputManager::isPressed( EKeys key ) {
  return m_cur_key_states[ key ] != 0;
}

//-------------------------
bool CInputManager::becomesPressed( EKeys key ) {
  return m_old_key_states[ key ] == 0 && m_cur_key_states[ key ] != 0;
}

//-------------------------
bool CInputManager::isReleased( EKeys key ) {
  return m_cur_key_states[ key ] == 0;
}

//-------------------------
bool CInputManager::becomesReleased( EKeys key ) {
  return m_old_key_states[ key ] != 0 && !m_cur_key_states[ key ] == 0;
}

// ---------------------------
// Mouse Input
// ---------------------------

//-------------------------
void CInputManager::updateMouse( SDL_Event & e ) {
  if( e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP ) {
    m_cur_mouse_state[ e.button.button ] = ( e.type == SDL_MOUSEBUTTONDOWN );
  } else if( e.type == SDL_MOUSEMOTION ) {
    m_mouse_pos = TPoint2( e.motion.x, e.motion.y );

    if( e.motion.xrel < 0 ) {
      m_mouse_mov_dir = MMD_LEFT;
    } else if( e.motion.xrel > 0 ) {
      m_mouse_mov_dir = MMD_RIGHT;
    } else if( e.motion.yrel < 0 ) {
      m_mouse_mov_dir = MMD_UP;
    } else if( e.motion.yrel > 0 ) {
      m_mouse_mov_dir = MMD_DOWN;
    } else {
      m_mouse_mov_dir = MMD_NONE;
    }
  }
}

//-------------------------
void CInputManager::setupMouseState( ) {
  for( size_t i = 0; i < N_MOUSE_BUTTONS; ++i ) {
    m_old_mouse_state[ i ] = m_cur_mouse_state[ i ];
  }
  m_mouse_mov_dir = MMD_NONE;
}

//-------------------------
bool CInputManager::isPressed( EMouseButtons btn ) {
  return m_cur_mouse_state[ btn ];
}

//-------------------------
bool CInputManager::becomesPressed( EMouseButtons btn ) {
  return !m_old_mouse_state[ btn ] && m_cur_mouse_state[ btn ];
}

//-------------------------
bool CInputManager::isReleased( EMouseButtons btn ) {
  return !m_cur_mouse_state[ btn ];
}

//-------------------------
bool CInputManager::becomesReleased( EMouseButtons btn ) {
  return m_old_mouse_state[ btn ] && !m_cur_mouse_state[ btn ];
}
