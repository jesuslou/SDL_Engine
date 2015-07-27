#ifndef _INC_SDL_APPLICATION_H_
#define _INC_SDL_APPLICATION_H_

struct SDL_Window;
struct SDL_Surface;

class CApplicationBase {
public:
  CApplicationBase( );
  bool init( const char *app_title, unsigned x_res, unsigned y_res );
  void update( );
  void destroy( );

protected:
  virtual bool initProject( ) { return true; }
  virtual void updateProject( float ) { }
  virtual void renderProject( ) { }
  virtual void destroyProject( ) { }
  
  float elapsed;
};

#endif