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
  m_old_key_states = m_cur_key_states;
  m_cur_key_states = SDL_GetKeyboardState( nullptr );
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
