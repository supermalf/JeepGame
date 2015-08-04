/*============================================================================
 * CAMERA.H
 *
 *
 *===========================================================================*/


#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "node.h"

#include "dot.h"  /* XXX */

class Camera : public Node 
{
   private:
      Dot Eye;
      Dot Center;
      Dot Up;

   public:
      Camera(); 
      Camera( float *eye, float *cen, float *up ); 
      Camera( float eye_x, float eye_y, float eye_z,
                      float cen_x, float cen_y, float cen_z, 
                      float  up_x, float  up_y,  float up_z);

      ~Camera();


      void TurnOn();
      void setPosition( float* eye,  float* cen,  float* up ); 
      void getPosition( Dot** eye, Dot** cen, Dot** up ); 
};

#endif


