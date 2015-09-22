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
{ }

//-------------------------
void CInputManager::update( float ) {
  int n = 0;
  if( !m_old_key_states ) {
    const Uint8* tmp_key_states = SDL_GetKeyboardState( &n );
    m_cur_key_states = new Uint8[ n ];
    m_old_key_states = new Uint8[ n ];
    memcpy( ( void* ) m_cur_key_states, tmp_key_states, sizeof( Uint8 ) * n );
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
  if( m_old_key_states ) {
    return m_old_key_states[ key ] == 0 && m_cur_key_states[ key ] != 0;
  } else {
    return m_cur_key_states[ key ] != 0;
  }
}

//-------------------------
bool CInputManager::isReleased( EKeys key ) {
  return m_cur_key_states[ key ] == 0;
}

//-------------------------
bool CInputManager::becomesReleased( EKeys key ) {
  if( m_old_key_states ) {
    return m_old_key_states[ key ] != 0 && !m_cur_key_states[ key ] == 0;
  } else {
    return m_cur_key_states[ key ] == 0;
  }
}

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
