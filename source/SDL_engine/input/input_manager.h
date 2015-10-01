#ifndef _INC_INPUT_MANAGER_H_
#define _INC_INPUT_MANAGER_H_

#include <SDL.h>

enum EKeys {
    VK_SPACE = SDL_SCANCODE_SPACE
  , VK_ENTER = SDL_SCANCODE_RETURN
  , VK_UP = SDL_SCANCODE_UP
  , VK_DOWN = SDL_SCANCODE_DOWN
  , VK_LEFT = SDL_SCANCODE_LEFT
  , VK_RIGHT = SDL_SCANCODE_RIGHT
  , VK_W = SDL_SCANCODE_W
  , VK_A = SDL_SCANCODE_A
  , VK_S = SDL_SCANCODE_S
  , VK_D = SDL_SCANCODE_D
};

enum EMouseButtons {
    MB_INVALID  = 0
  , MB_LEFT     = SDL_BUTTON_LEFT
  , MB_MIDDLE   = SDL_BUTTON_MIDDLE
  , MB_RIGHT    = SDL_BUTTON_RIGHT
  , MB_X1       = SDL_BUTTON_X1
  , MB_X2       = SDL_BUTTON_X2
  , N_MOUSE_BUTTONS
};

enum EMouseMovementDir {
    MMD_NONE = 0
  , MMD_UP
  , MMD_DOWN
  , MMD_LEFT
  , MMD_RIGHT
};

class CInputManager {
public:

  static CInputManager & get( );

  void destroy( );

  // Keyboard
  void updateKeyboard( );
  bool isPressed( EKeys key );
  bool becomesPressed( EKeys key );
  bool isReleased( EKeys key );
  bool becomesReleased( EKeys key );

  // Mouse
  void updateMouse( SDL_Event & e );
  void setupMouseState( );
  bool isPressed( EMouseButtons btn );
  bool becomesPressed( EMouseButtons btn );
  bool isReleased( EMouseButtons btn );
  bool becomesReleased( EMouseButtons btn );

  const TPoint2 getMousePosition( ) const { return m_mouse_pos; }
  const EMouseMovementDir getMouseMovementDir( ) const { return m_mouse_mov_dir; }

private:
  CInputManager( );

  const Uint8* m_cur_key_states;
  const Uint8* m_old_key_states;

  bool m_cur_mouse_state[ N_MOUSE_BUTTONS ];
  bool m_old_mouse_state[ N_MOUSE_BUTTONS ];

  EMouseMovementDir m_mouse_mov_dir;
  TPoint2           m_mouse_pos;

};

#endif