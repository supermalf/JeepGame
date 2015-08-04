/*============================================================================
 * PERSPECTIVE.CPP                                                              
 *                    
 * (CAMERA MEMBER)
 *                                              
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/gl.h>
#include <gl/glu.h>


#include "camera.h"
#include "perspective.h"
//#include "ponto.h"



/************************************************************************/
/* Methods                                         
/*
/************************************************************************/


Perspective::Perspective()
{
   fovy  =  90.0f;
   zNear =   1.0f;
   zFar  = 100.0f;
}


Perspective::Perspective(float fy, float zn, float zf, float *eye, float *cen, float *up) : Camera(eye, cen, up)
{
   fovy  = fy;
   zNear = zn;
   zFar  = zf;
}


Perspective::Perspective( float fy, float zn, float zf,
                          float eye_x, float eye_y, float eye_z,
                          float cen_x, float cen_y, float cen_z, 
                          float  up_x, float  up_y, float  up_z ): Camera( eye_x, eye_y, eye_z,
                                                                           cen_x, cen_y, cen_z, 
                                                                            up_x,  up_y,  up_z )
{
   fovy  = fy;
   zNear = zn;
   zFar  = zf;
}

Perspective::~Perspective() {}


int Perspective::setupCamera()
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluPerspective( fovy, 800.0f/600.0f, zNear, zFar ) ;  /* XXX VAR GLOBAL PARA JANELA*/
   TurnOn();
   return 1;
}


void Perspective::setFovy( float fy ) 
{
   fovy = fy ;
}


float Perspective::getFovy() 
{
   return fovy;
}


void Perspective::setzNear( float zn )
{
   zNear = zn ;
}


float Perspective::getzNear()
{
   return zNear ;
}


void Perspective::setzFar( float zf )
{
   zFar = zf ;
}


float Perspective::getzFar()
{
   return zFar ;
}
