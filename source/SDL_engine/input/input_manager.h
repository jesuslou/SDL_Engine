#ifndef _INC_INPUT_MANAGER_H_
#define _INC_INPUT_MANAGER_H_

#include <SDL.h>

struct SDL_Texture;

enum EKeys {
    VK_SPACE = SDL_SCANCODE_SPACE
  , VK_ENTER = SDL_SCANCODE_RETURN
  , VK_UP = SDL_SCANCODE_UP
  , VK_DOWN = SDL_SCANCODE_DOWN
  , VK_LEFT = SDL_SCANCODE_LEFT
  , VK_RIGHT = SDL_SCANCODE_RIGHT
};

class CInputManager {
public:

  static CInputManager & get( );

  void update( float elapsed );

  bool isPressed( EKeys key );
  bool becomesPressed( EKeys key );
  bool isReleased( EKeys key );
  bool becomesReleased( EKeys key );

private:
  CInputManager( );

  const Uint8* m_cur_key_states;
  const Uint8* m_old_key_states;

};

#endif