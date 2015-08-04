/*============================================================================
 * FOG.CPP
 *
 * 
 *
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/gl.h>

#include <stdio.h>
#include "fog.h"
#include "glut.h"
#include "engine_scene.h" /* XXX */


Fog::Fog() 
{
   initFog = 1;
}

Fog::~Fog() {}

void Fog::aplica() 
{
   glEnable(GL_DEPTH_TEST);
   
   glPushAttrib( GL_CURRENT_BIT ) ;
   GLfloat mat[3] = {0.1745, 0.01175, 0.01175};	
   glMaterialfv (GL_FRONT, GL_AMBIENT, mat);
   mat[0] = 0.61424; mat[1] = 0.04136; mat[2] = 0.04136;	
   glMaterialfv (GL_FRONT, GL_DIFFUSE, mat);
   mat[0] = 0.727811; mat[1] = 0.626959; mat[2] = 0.626959;
   glMaterialfv (GL_FRONT, GL_SPECULAR, mat);
   glMaterialf (GL_FRONT, GL_SHININESS, 0.6*128.0);
   
   glEnable(GL_FOG);
   {
      GLfloat fogColor[4] = {0.0, 0.2, 0.6, 1.0};
      
      //tipos de fog
      fogMode = GL_LINEAR;
      //fogMode = GL_EXP;
      //fogMode = GL_EXP2;
      
      glFogi (GL_FOG_MODE, fogMode);
      glFogfv (GL_FOG_COLOR, fogColor);
      glFogf (GL_FOG_DENSITY, 0.35);
      glHint (GL_FOG_HINT, GL_DONT_CARE);
      glFogf (GL_FOG_START, 100.0);
      glFogf (GL_FOG_END, 140.0);
   }


}