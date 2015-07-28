#ifndef _INC_CONTROL_KEYS_DATA_H_
#define _INC_CONTROL_KEYS_DATA_H_

#include "input/input_manager.h"

struct TControlKeys {
  EKeys key_up;
  EKeys key_down;
  EKeys key_left;
  EKeys key_right;
  EKeys key_shoot;
  EKeys key_pause;

  TControlKeys( ) { }
  TControlKeys( EKeys k_up, EKeys k_down, EKeys k_left, EKeys k_right, EKeys k_shoot, EKeys k_pause )
    : key_up( k_up ), key_down( k_down ), key_left( k_left ), key_right( k_right ), key_shoot( k_shoot ), key_pause( k_pause ) 
  { }
};
#endif