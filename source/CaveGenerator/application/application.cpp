#include "common.h"
#include "application.h"
#include "render/renderer.h"
#include "audio/audio_manager.h"
#include "input/input_manager.h"
#include "fonts/font_manager.h"
#include "utils/interpolators.h"

float random( ) {
  return std::rand( ) / static_cast<float>( RAND_MAX );
}

int randomRange( int low, int high ) {
  int range = high - low;
  return static_cast< int >( random( ) * range ) + low;
}


//-----------------
CApplication & CApplication::get( ) {
  static CApplication ca;
  return ca;
}

//-----------------
CApplication::CApplication( ) {
}

static const int X_CELLS = 160; // max 240 // shadows 120
static const int Y_CELLS = 90; // max 135  // shadows 70
static const int WIDTH = 8;

static bool use_generator = false;


float percentage_of_rocks = 0.6f;
unsigned n_cellular_automata_generations = 2;
unsigned n_cellular_automata_generations_2 = 1;
unsigned n_cellular_automata_generations_3 = 1;
unsigned neighborhood_threshold = 5;
int n_neighborhood_cells = 1;
unsigned n_stairs = 20;



int margin_x = 1;
int margin_y = 1;

class CCell {
public:
  CTexture t;
  CTexture t_shadow;
  bool is_rock;
  bool is_wall;
  bool is_stair;
  bool is_treasure;
  bool must_convert_into_rock;
  bool must_convert_into_ground;

  CCell( ) : is_rock( false ), must_convert_into_rock( false ), must_convert_into_ground( false ) { }

  void init( unsigned x, unsigned y ) {
    t.loadFromFile( "data/textures/blank.png" );
    t.setPosition( TPoint2( x * WIDTH, y * WIDTH ) );

    t_shadow.loadFromFile( "data/textures/blank.png" );
    t_shadow.setPosition( TPoint2( x * WIDTH, y * WIDTH ) );
    t_shadow.setBlendMode( SDL_BlendMode::SDL_BLENDMODE_BLEND );
    t_shadow.setTintColor( SDL_Color( 0, 0, 0, 255 ) );
    t_shadow.setAlpha( 128 );
  }

  void turnIntoRock( ) {
    is_rock = true;
    if( !use_generator ) {
      if( random( ) < 0.5f ) {
        t.setTintColor( SDL_Color( 113, 70, 26, 255 ) );
      } else {
        t.setTintColor( SDL_Color( 88, 49, 10, 255 ) );
      }
    } else {
      t.setTintColor( SDL_Color( 64, 64, 64, 255 ) );
    }
  }

  void turnIntoGround( ) {
    is_rock = false;
    if( !use_generator ) {
      float rnd = random( );
      if( rnd < 0.33f ) {
        t.setTintColor( SDL_Color( 213, 148, 79, 255 ) );
      } else if( rnd < 0.66f ) {
        t.setTintColor( SDL_Color( 191, 127, 60, 255 ) );
      } else {
        t.setTintColor( SDL_Color( 233, 176, 116, 255 ) );
      }
    } else {
      t.setTintColor( SDL_Color( 0, 255, 0, 255 ) );
    }
  }

  void turnIntoWall( ) {
    is_wall = true;
    if( !use_generator ) {
      t.setTintColor( SDL_Color( 67, 42, 14, 255 ) );
    } else {
      t.setTintColor( SDL_Color( 255, 0, 0, 255 ) );
    }
  }

  void turnIntoStairs( ) {
    is_stair = true;
    t.setTintColor( SDL_Color( 255, 255, 0, 255 ) );
  }

  void turnIntoTreasure( ) {
    is_treasure = true;
    t.setTintColor( SDL_Color( 0, 255, 0, 255 ) );
  }
};

class CMap {
public:

  void init( ) {
    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t y = 0; y < Y_CELLS; ++y ) {
        table[ x ][ y ].init( x, y );
      }
    }
  }

  void stepOne( ) {
    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t y = 0; y < Y_CELLS; ++y ) {
        float rnd = random( );
        if( random( ) <= percentage_of_rocks ) {
          table[ x ][ y ].turnIntoRock( );
        } else {
          table[ x ][ y ].turnIntoGround( );
        }
      }
    }

    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t margin = 0; margin < margin_x; ++margin ) {
        table[ x ][ 0 ].turnIntoRock( );
        table[ x ][ Y_CELLS - 1 - margin ].turnIntoRock( );
      }
    }

    for( size_t y = 0; y < Y_CELLS; ++y ) {
      for( size_t margin = 0; margin < margin_y; ++margin ) {
        table[ margin ][ y ].turnIntoRock( );
        table[ X_CELLS - 1 - margin ][ y ].turnIntoRock( );
      }
    }
  }

  void stepTwo( ) {
    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t y = 0; y < Y_CELLS; ++y ) {

        unsigned n_neighbors = 0;
        for( int i = -n_neighborhood_cells; i <= n_neighborhood_cells; ++i ) {
          for( int j = -n_neighborhood_cells; j <= n_neighborhood_cells; ++j ) {
            int n_x = x + i;
            int n_y = y + j;
            if( n_x < 0 || n_y < 0 || n_x >= X_CELLS || n_y >= Y_CELLS || ( x == n_x && y == n_y ) ) {
              ++n_neighbors;
              continue;
            }
            if( table[ n_x ][ n_y ].is_rock ) {
              ++n_neighbors;
            }
          }
        }

        if( n_neighbors >= neighborhood_threshold &&  table[ x ][ y ].is_rock ) {
          table[ x ][ y ].must_convert_into_rock = true;
        }
      }
    }

    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t y = 0; y < Y_CELLS; ++y ) {
        CCell & c = table[ x ][ y ];
        if( c.must_convert_into_rock ) {
          c.turnIntoRock( );
        } else {
          c.turnIntoGround( );
        }
        c.must_convert_into_rock = false;
      }
    }
  }

  void stepThree( ) {
    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t y = 0; y < Y_CELLS; ++y ) {

        unsigned n_neighbors = 0;
        for( int i = -n_neighborhood_cells; i <= n_neighborhood_cells; ++i ) {
          for( int j = -n_neighborhood_cells; j <= n_neighborhood_cells; ++j ) {
            int n_x = x + i;
            int n_y = y + j;
            if( n_x < 0 || n_y < 0 || n_x >= X_CELLS || n_y >= Y_CELLS || ( x == n_x && y == n_y ) ) {
              if( x != n_x || y != n_y ) {
                ++n_neighbors;
              }
              continue;
            }
            if( table[ n_x ][ n_y ].is_rock ) {
              ++n_neighbors;
            }
          }
        }

        if( n_neighbors >= neighborhood_threshold &&  !table[ x ][ y ].is_rock ) {
          table[ x ][ y ].must_convert_into_rock = true;
        }
      }
    }

    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t y = 0; y < Y_CELLS; ++y ) {
        CCell & c = table[ x ][ y ];
        if( c.must_convert_into_rock ) {
          c.turnIntoRock( );
        }
        c.must_convert_into_rock = false;
      }
    }
  }

  void stepFour( ) {
    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t y = 0; y < Y_CELLS; ++y ) {
        unsigned n_neighbors = 0;
        for( int i = -1; i <= 1; ++i ) {
          for( int j = -1; j <= 1; ++j ) {
            int n_x = x + i;
            int n_y = y + j;
            if( n_x < 0 || n_y < 0 || n_x >= X_CELLS || n_y >= Y_CELLS || ( x == n_x && y == n_y ) ) {
              if( x != n_x || y != n_y ) {
                ++n_neighbors;
              }
              continue;
            }
            if( table[ n_x ][ n_y ].is_rock ) {
              ++n_neighbors;
            }
          }
        }
        if( n_neighbors < 8 && table[ x ][ y ].is_rock ) {
          table[ x ][ y ].turnIntoWall( );
        }
      }
    }
  }

  void stepFive( ) {
    for( size_t x = 1; x < X_CELLS - 1; ++x ) {
      for( size_t y = 1; y < Y_CELLS - 1; ++y ) {

        if( table[ x ][ y ].is_wall ) {
          if( ( x - 1 >= 0 && x + 1 < X_CELLS && !table[ x - 1 ][ y ].is_rock && !table[ x + 1 ][ y ].is_rock )
              || ( y - 1 >= 0 && y + 1 < Y_CELLS && !table[ x ][ y - 1 ].is_rock && !table[ x ][ y + 1 ].is_rock )
              ) {
            table[ x ][ y ].must_convert_into_rock = true;
          }

          if( ( x - 1 >= 0 && x + 1 < X_CELLS && x + 2 < X_CELLS && !table[ x - 1 ][ y ].is_rock && table[ x + 1 ][ y ].is_wall && !table[ x + 2 ][ y ].is_rock )
              || ( x - 1 >= 0 && x + 1 < X_CELLS && x - 2 >= 0 && !table[ x + 1 ][ y ].is_rock && table[ x - 1 ][ y ].is_wall && !table[ x - 2 ][ y ].is_rock )
              || ( y - 1 >= 0 && y + 1 < Y_CELLS && y + 2 < Y_CELLS && !table[ x ][ y - 1 ].is_rock && table[ x ][ y + 1 ].is_wall && !table[ x ][ y + 2 ].is_rock )
              || ( y - 1 >= 0 && y + 1 < Y_CELLS && y - 2 >= 0 && !table[ x ][ y + 1 ].is_rock && table[ x ][ y - 1 ].is_wall && !table[ x ][ y - 2 ].is_rock )
              ) {
            table[ x ][ y ].must_convert_into_rock = true;
          }
        }
      }
    }

    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t y = 0; y < Y_CELLS; ++y ) {
        CCell & c = table[ x ][ y ];
        if( c.must_convert_into_rock ) {
          c.turnIntoGround( );
        }
        c.must_convert_into_rock = false;
      }
    }

    stepFour( );
  }

  void generate( ) {
    stepOne( );
    for( size_t i = 0; i < n_cellular_automata_generations; ++i ) {
      stepTwo( );
    }
    for( size_t i = 0; i < n_cellular_automata_generations_2; ++i ) {
      stepThree( );
    }
    stepFour( );
    for( size_t i = 0; i < n_cellular_automata_generations_3; ++i ) {
      stepFive( );
    }
  }

  void render( ) {
    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t y = 0; y < Y_CELLS; ++y ) {
        table[ x ][ y ].t.render( );
        table[ x ][ y ].t_shadow.render( );
      }
    }
  }

  void destroy( ) {
    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t y = 0; y < Y_CELLS; ++y ) {
        table[ x ][ y ].t.destroy( );
        table[ x ][ y ].t_shadow.destroy( );
      }
    }
  }

CCell table[ X_CELLS ][ Y_CELLS ];

};

CCell table[ X_CELLS ][ Y_CELLS ];

const int MAX_LEVELS = 2;
CMap maps[ MAX_LEVELS ];

unsigned cur_table = 0;

void stepOne( );
void placeStairs( unsigned n_stairs );
void placeTreasures( CMap & map, unsigned n_treasures );

//-----------------
bool CApplication::initProject( ) {
  /*img_1.loadFromFile( "data/textures/test1.png" );
  img_2.loadFromFile( "data/textures/test2.png" );
  img_1b.loadFromFile( "data/textures/target.png" );*/

  if( !use_generator ) {

    for( size_t x = 0; x < MAX_LEVELS; ++x ) {
      maps[ x ].init( );
      maps[ x ].generate( );
    }
    placeStairs( n_stairs );
    placeTreasures( maps[ 0 ], 50 );
    placeTreasures( maps[ 1 ], 100 );

  } else {
    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t y = 0; y < Y_CELLS; ++y ) {
        table[ x ][ y ].init( x, y );
      }
    }
  }

  CRenderer::get( ).setClearColor( SDL_Color( 0, 128, 255, 255 ) );

  return true;
}

void stepOne( ) {
  for( size_t x = 0; x < X_CELLS; ++x ) {
    for( size_t y = 0; y < Y_CELLS; ++y ) {
      float rnd = random( );
      if( random( ) <= percentage_of_rocks ) {
        table[ x ][ y ].turnIntoRock( );
      } else {
        table[ x ][ y ].turnIntoGround( );
      }
    }
  }

  for( size_t x = 0; x < X_CELLS; ++x ) {
    for( size_t margin = 0; margin < margin_x; ++margin ) {
      table[ x ][ 0 ].turnIntoRock( );
      table[ x ][ Y_CELLS - 1 - margin ].turnIntoRock( );
    }
  }

  for( size_t y = 0; y < Y_CELLS; ++y ) {
    for( size_t margin = 0; margin < margin_y; ++margin ) {
      table[ margin ][ y ].turnIntoRock( );
      table[ X_CELLS - 1 - margin ][ y ].turnIntoRock( );
    }
  }
}

void stepTwo( ) {
  for( size_t x = 0; x < X_CELLS; ++x ) {
    for( size_t y = 0; y < Y_CELLS; ++y ) {
      
      unsigned n_neighbors = 0;
      for( int i = -n_neighborhood_cells; i <= n_neighborhood_cells; ++i ) {
        for( int j = -n_neighborhood_cells; j <= n_neighborhood_cells; ++j ) {
          int n_x = x + i;
          int n_y = y + j;
          if( n_x < 0 || n_y < 0 || n_x >= X_CELLS || n_y >= Y_CELLS || ( x == n_x && y == n_y ) ) {
            ++n_neighbors;
            continue;
          }
          if( table[ n_x ][ n_y ].is_rock ) {
            ++n_neighbors;
          }
        }
      }

      if( n_neighbors >= neighborhood_threshold && !table[ x ][ y ].is_rock ) {
        table[ x ][ y ].must_convert_into_rock = true;
      } else if( n_neighbors < neighborhood_threshold && table[ x ][ y ].is_rock ) {
        table[ x ][ y ].must_convert_into_rock = false;
        table[ x ][ y ].must_convert_into_ground = true;
      }
    }
  }

  for( size_t x = 0; x < X_CELLS; ++x ) {
    for( size_t y = 0; y < Y_CELLS; ++y ) {
      CCell & c = table[ x ][ y ];
      if( c.must_convert_into_rock ) {
        c.turnIntoRock( );
      } else if( c.must_convert_into_ground ) {
        c.turnIntoGround( );
      }
      c.must_convert_into_rock = false;
      c.must_convert_into_rock = false;
    }
  }
}

void stepThree( ) {
  for( size_t x = 0; x < X_CELLS; ++x ) {
    for( size_t y = 0; y < Y_CELLS; ++y ) {

      unsigned n_neighbors = 0;
      for( int i = -n_neighborhood_cells; i <= n_neighborhood_cells; ++i ) {
        for( int j = -n_neighborhood_cells; j <= n_neighborhood_cells; ++j ) {
          int n_x = x + i;
          int n_y = y + j;
          if( n_x < 0 || n_y < 0 || n_x >= X_CELLS || n_y >= Y_CELLS || ( x == n_x && y == n_y ) ) {
            if( x != n_x || y != n_y ) {
              ++n_neighbors;
            }
            continue;
          }
          if( table[ n_x ][ n_y ].is_rock ) {
            ++n_neighbors;
          }
        }
      }

      if( n_neighbors >= neighborhood_threshold &&  !table[ x ][ y ].is_rock ) {
        table[ x ][ y ].must_convert_into_rock = true;
      }
    }
  }

  for( size_t x = 0; x < X_CELLS; ++x ) {
    for( size_t y = 0; y < Y_CELLS; ++y ) {
      CCell & c = table[ x ][ y ];
      if( c.must_convert_into_rock ) {
        c.turnIntoRock( );
      }
      c.must_convert_into_rock = false;
    }
  }
}

void stepFour( ) {
  for( size_t x = 0; x < X_CELLS; ++x ) {
    for( size_t y = 0; y < Y_CELLS; ++y ) {
      unsigned n_neighbors = 0;
      for( int i = -1; i <= 1; ++i ) {
        for( int j = -1; j <= 1; ++j ) {
          int n_x = x + i;
          int n_y = y + j;
          if( n_x < 0 || n_y < 0 || n_x >= X_CELLS || n_y >= Y_CELLS || ( x == n_x && y == n_y ) ) {
            if( x != n_x || y != n_y ) {
              ++n_neighbors;
            }
            continue;
          }
          if( table[ n_x ][ n_y ].is_rock ) {
            ++n_neighbors;
          }
        }
      }
      if( n_neighbors < 8 && table[ x ][ y ].is_rock ) {
        table[ x ][ y ].turnIntoWall( );
      }
    }
  }
}

void stepFive( ) {
  for( size_t x = 1; x < X_CELLS-1; ++x ) {
    for( size_t y = 1; y < Y_CELLS-1; ++y ) {
      
      if( table[ x ][ y ].is_wall ) {
        if( ( !table[ x - 1 ][ y ].is_rock && !table[ x + 1 ][ y ].is_rock )
            || ( !table[ x ][ y - 1 ].is_rock && !table[ x ][ y + 1 ].is_rock )
            ) {
          table[ x ][ y ].must_convert_into_rock = true;
        }

        if( ( !table[ x - 1 ][ y ].is_rock && table[ x + 1 ][ y ].is_wall && !table[ x + 2 ][ y ].is_rock )
            || ( !table[ x + 1 ][ y ].is_rock && table[ x - 1 ][ y ].is_wall && !table[ x - 2 ][ y ].is_rock )
            || ( !table[ x ][ y - 1 ].is_rock && table[ x ][ y + 1 ].is_wall && !table[ x ][ y + 2 ].is_rock )
            || ( !table[ x ][ y + 1 ].is_rock && table[ x ][ y - 1 ].is_wall && !table[ x ][ y - 2 ].is_rock )
            ) {
          table[ x ][ y ].must_convert_into_rock = true;
        }
      }
    }
  }

  for( size_t x = 0; x < X_CELLS; ++x ) {
    for( size_t y = 0; y < Y_CELLS; ++y ) {
      CCell & c = table[ x ][ y ];
      if( c.must_convert_into_rock ) {
        c.turnIntoGround( );
      }
      c.must_convert_into_rock = false;
    }
  }

  stepFour( );
}

float distance( float x, float y, float ratio ) {
  return sqrt( ( pow( y * ratio, 2 ) ) + pow( x, 2 ) );
};

float filled( float x, float y, float radius, float ratio ) {
  return distance( x, y, ratio ) <= radius;
};

void placeStairs( unsigned n_stairs ) {
  for( size_t i = 0; i < n_stairs; ++i ) {

    int x = 0;
    int y = 0;

    bool valid = false;
    do {
      x = randomRange( 0, X_CELLS );
      y = randomRange( 0, Y_CELLS );

      valid = !maps[ 0 ].table[ x ][ y ].is_rock && !maps[ 0 ].table[ x ][ y ].is_rock;
      unsigned n_neighbors_1 = 0;
      unsigned n_neighbors_2 = 0;
      for( int _x = -1; _x <= 1; ++_x ) {
        for( int _y = -1; _y <= 1; ++_y ) {

          int n_x = x + _x;
          int n_y = y + _y;

          if( x == n_x && y == n_y ) {
            continue;
          } else if( n_x < 0 || n_y < 0 || n_x >= X_CELLS || n_y >= Y_CELLS ) {
            ++n_neighbors_1;
            ++n_neighbors_2;
            continue;
          }

          if( maps[ 0 ].table[ n_x ][ n_y ].is_rock || maps[ 0 ].table[ n_x ][ n_y ].is_stair ) {
            ++n_neighbors_1;
          }
          if( maps[ 1 ].table[ n_x ][ n_y ].is_rock || maps[ 1 ].table[ n_x ][ n_y ].is_stair ) {
            ++n_neighbors_2;
          }
        }
      }

      valid &= n_neighbors_1 == 0 && n_neighbors_2 == 0;
    } while( !valid );

    maps[ 0 ].table[ x ][ y ].turnIntoStairs( );
    maps[ 1 ].table[ x ][ y ].turnIntoStairs( );



    int light_rad = 25;
    int width_r = light_rad / 2;
    int height_r = light_rad / 2;
    float ratio = width_r / height_r;

    int maxblocks_x = 0;
    int maxblocks_y = 0;

    float ifilled = 0;

    if( ( width_r * 2 ) % 2 == 0 ) {
      maxblocks_x = ceil( width_r - 0.5f ) * 2 + 1;
    } else {
      maxblocks_x = ceil( width_r ) * 2;
    }

    if( ( height_r * 2 ) % 2 == 0 ) {
      maxblocks_y = ceil( height_r - .5 ) * 2 + 1;
    } else {
      maxblocks_y = ceil( height_r ) * 2;
    }

    for( int _y = -maxblocks_y / 2 + 1; _y <= maxblocks_y / 2 - 1; _y++ ) {
      for( int _x = -maxblocks_x / 2 + 1; _x <= maxblocks_x / 2 - 1; _x++ ) {
        int n_x = x + _x;
        int n_y = y + _y;
        if( n_x < 0 || n_y < 0 || n_x >= X_CELLS || n_y >= Y_CELLS ) {
          continue;
        }

        if( filled( _x, _y, width_r, ratio ) ) {
          maps[ 0 ].table[ n_x ][ n_y ].t_shadow.setAlpha( 0 );
        }

      }
    }
  }
}

void placeTreasures( CMap & map, unsigned n_treasures ) {
  for( size_t i = 0; i < n_treasures; ++i ) {

    unsigned x = 0;
    unsigned y = 0;

    bool valid = false;
    do {
      x = randomRange( 0, X_CELLS );
      y = randomRange( 0, Y_CELLS );

      valid = !map.table[ x ][ y ].is_rock && !map.table[ x ][ y ].is_treasure;
      unsigned n_neighbors = 0;
      for( int _x = -1; _x <= 1; ++_x ) {
        for( int _y = -1; _y <= 1; ++_y ) {

          int n_x = x + _x;
          int n_y = y + _y;

          if( x == n_x && y == n_y ) {
            continue;
          } else if( n_x < 0 || n_y < 0 || n_x >= X_CELLS || n_y >= Y_CELLS ) {
            ++n_neighbors;
            continue;
          }

          if( map.table[ n_x ][ n_y ].is_rock ) {
            ++n_neighbors;
          }
        }
      }

      valid &= n_neighbors >= 3;
    } while( !valid );


    map.table[ x ][ y ].turnIntoTreasure( );
  }
}


int steps = -1;
int n_automatas_generated = 0;

//-----------------
void CApplication::updateProject( float elapsed ) {

  if( CInputManager::get( ).becomesPressed( VK_ENTER ) ) {

    if( steps == -1 ) {
      stepOne( );
      ++steps;
    } else if( steps == 0 ) {
      stepTwo( );
      ++n_automatas_generated;
      if( n_automatas_generated == n_cellular_automata_generations ) {
        n_automatas_generated = 0;
        ++steps;
      }
    } else if( steps == 1 ) {
      stepThree( );
      ++n_automatas_generated;
      if( n_automatas_generated == n_cellular_automata_generations_2 ) {
        ++steps;
      }
    } else if( steps == 2 ) {
      stepFour( );
      ++steps;
      n_automatas_generated = 0;
    } else if( steps == 3 ) {
      stepFive( );
      ++n_automatas_generated;
      if( n_automatas_generated == n_cellular_automata_generations_3 ) {
        ++steps;
      }
    } else if( steps == 4 ) {
      steps = 0;
      n_automatas_generated = 0;
      stepOne( );
    }
  }

  if( !use_generator ) {
    if( CInputManager::get( ).becomesPressed( VK_DOWN ) ) {
      cur_table = ( cur_table + 1 ) % MAX_LEVELS;
    }
  }
}

//-----------------
void CApplication::renderProject( ) { 
  if( !use_generator ) {
    maps[ cur_table ].render( );
  } else {
    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t y = 0; y < Y_CELLS; ++y ) {
       table[ x ][ y ].t.render( );
      }
    }
  }
}

//-----------------
void CApplication::destroyProject( ) { 
  if( use_generator ) {
    for( size_t x = 0; x < X_CELLS; ++x ) {
      for( size_t y = 0; y < Y_CELLS; ++y ) {
        table[ x ][ y ].t.destroy( );
      }
    }
  } else {
    for( size_t x = 0; x < MAX_LEVELS; ++x ) {
      maps[ x ].destroy( );
    }
  }
}
