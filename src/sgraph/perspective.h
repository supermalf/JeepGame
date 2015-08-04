/*============================================================================
 * PERSPECTIVE.H                                                              
 *                    
 * (CAMERA MEMBER)
 *                                              
 *===========================================================================*/



#ifndef _PERSPECTIVE_H_
#define _PERSPECTIVE_H_

#include "camera.h"

/* XXX Colocar eye, center e up ??!?*/

class Perspective : public Camera
{
   private:
      float fovy;
      float zNear;
      float zFar;

   public:
      Perspective();
      Perspective(float fy, float zn, float zf, float *eye, float *cen, float *up);

      Perspective( float fy, float zn, float zf,
                   float eye_x, float eye_y, float eye_z,
                   float cen_x, float cen_y, float cen_z, 
                   float  up_x, float  up_y, float  up_z );


      ~Perspective();

      int setupCamera();

      void  setFovy( float fy ); 
      float getFovy(); 

      void  setzNear( float zn );
      float getzNear();

      void  setzFar( float zf );
      float getzFar();
};

#endif




