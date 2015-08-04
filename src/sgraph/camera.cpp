/*============================================================================
 * CAMERA.CPP
 *
 *
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/gl.h>
#include <gl/glu.h>

#include "camera.h"
#include "dot.h" /* XXX */



/************************************************************************/
/* Methods                                         
/*
/************************************************************************/


Camera::Camera() 
{
   Eye.setPosition   (0,0,0,1);
   Center.setPosition(0,0,0,1);
   Up.setPosition    (0,0,0,1);
}


Camera::Camera( float *eye, float *cen, float *up ) 
{
   Eye.setPosition   ( eye[0], eye[1], eye[2], 1);
   Center.setPosition( cen[0], cen[1], cen[2], 1);
   Up.setPosition    (  up[0],  up[1],  up[2], 1);
}


Camera::Camera( float eye_x, float eye_y, float eye_z,
                float cen_x, float cen_y, float cen_z, 
                float  up_x, float  up_y,  float up_z)
{
   Eye.setPosition   ( eye_x, eye_y, eye_z, 1 );
   Center.setPosition( cen_x, cen_y, cen_z, 1 );
   Up.setPosition    (  up_x,  up_y,  up_z, 1 );
}

Camera::~Camera() {}


void Camera::TurnOn()
{
   float* eye = Eye.getPosition();
   float* cen = Center.getPosition();
   float* up  = Up.getPosition();

   glMatrixMode( GL_MODELVIEW ) ;
   glLoadIdentity( ) ;
   gluLookAt( eye[0], eye[1], eye[2],
              cen[0], cen[1], cen[2],
               up[0],  up[1],  up[2]);
}

void Camera::setPosition( float* eye,  float* cen,  float* up ) 
{
   Eye.setPosition   ( eye[0], eye[1], eye[2], 1);
   Center.setPosition( cen[0], cen[1], cen[2], 1);
   Up.setPosition    (  up[0],  up[1],  up[2], 1);
}

void Camera::getPosition( Dot** eye, Dot** cen, Dot** up ) 
{
   *eye = &Eye ;
   *cen = &Center ;
   *up  = &Up ;
}
