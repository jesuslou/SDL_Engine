#ifndef _INC_APPLICATION_H_
#define _INC_APPLICATION_H_

#include "application/application_base.h"
#include "render/image.h"

class CApplication : public CApplicationBase {
public:
  static CApplication & get( );

protected:
  CApplication( );

  CImage img_1;
  CImage img_2;
  CImage img_1b;

  bool initProject( ) override;
  void updateProject( float ) override;
  void renderProject( ) override;

  void destroyProject( ) override;
};

#endif