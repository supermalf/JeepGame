/*============================================================================
 * FONT.CPP
 *
 * DISPLAYS FONTS
 *
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/gl.h>

#include <stdio.h>
#include "font.h"
#include "glut.h"


Font::Font() {}

Font::~Font() {}


void Font::draw()
{
   DefaultHelpMenu();
}


void Font::write() {}


void Font::putstring (char* s, float x, float y)
{
   int i;
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);

   glColor3f(1.0f,1.0f,1.0f);
   glRasterPos3d(x,y,0.8);
   
   for (i=0; s[i]; i++)
     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}

void Font::DefaultHelpMenu()
{
   char  *s;
   s= mFPS ();

   putstring("****  Help Menu  ****",-0.95,-0.38);
   putstring(s,-0.95,-0.46);
   putstring("F1: Camera 1",-0.95,-0.51);
   putstring("F2: Camera 2",-0.95,-0.56);
   putstring("F3: Camera 3",-0.95,-0.61);
   putstring("F4: Camera 4",-0.95,-0.66);
   putstring("F5: Camera 5",-0.95,-0.71);
   putstring("Arrow keys: control car",-0.95,-0.76);
   putstring("Space: Break",-0.95,-0.81);
   putstring("L: Turn ON/OFF car headlight",-0.95,-0.86);
   putstring("Q: HandBrake",-0.95,-0.91);
   putstring("ESC: exit",-0.95,-0.96);
}


char* Font::mFPS ()
{

   fpsFrame++;
   fpsTempo = glutGet(GLUT_ELAPSED_TIME);

   if(fpsTempo - fpsTempoBase > 1000)
   {
      FPS          = fpsFrame*1000.0/(fpsTempo - fpsTempoBase);
	   fpsTempoBase = fpsTempo;
	   fpsFrame     = 0;

      sprintf(fpsString,"FPS: %4.2f", FPS);
   }

   return fpsString;
}
