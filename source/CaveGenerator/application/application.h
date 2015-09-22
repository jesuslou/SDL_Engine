#ifndef _INC_APPLICATION_H_
#define _INC_APPLICATION_H_

#include "application/application_base.h"
#include "render/texture.h"
#include "fonts/texture_font.h"

class CApplication : public CApplicationBase {
public:
  static CApplication & get( );

protected:
  CApplication( );

  bool initProject( ) override;
  void updateProject( float ) override;
  void renderProject( ) override;

  void destroyProject( ) override;
};

#endif