/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

#include "common.h"
//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "application/application.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[ ] ) {
  
  CApplication::get( ).init( "apptest", SCREEN_WIDTH, SCREEN_HEIGHT );

  CApplication::get( ).update( );

  CApplication::get( ).destroy( );

  return 0;
}