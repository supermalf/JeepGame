/*============================================================================
 * CONTEXT.CPP
 *
 *
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "context.h"



/************************************************************************/
/* Methods                                         
/*
/************************************************************************/

Context::Context() 
{
   iniciado = 0;
}

Context::~Context() {}

void Context::defineContext( int passada )
{
   if( !iniciado )
   {
      init() ;
      iniciado = 1;
   }

   switch( passada )
   {
      //Opacos
      case 0:
         glClearColor (0.0, 0.2, 0.6, 0.0);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         glDisable (GL_BLEND);
         glDisable(GL_ALPHA_TEST);
         glDepthMask( GL_TRUE );
         break;

      //Transp
      case 1:
         glDepthMask( GL_FALSE );
         glEnable (GL_BLEND);
         glDisable(GL_ALPHA_TEST);
         glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         break;

     //BillBoard
     case 2:
         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         glEnable(GL_ALPHA_TEST);
         glAlphaFunc(GL_GREATER, 0);
         break;

      //Finalizacao
      case 3:
         glDisable (GL_BLEND);
         glDepthMask( GL_TRUE );
         break;
                     

   }
}

void Context::init()
{
   glClearColor(0,0,0,1); 
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glEnable(GL_COLOR_MATERIAL);
   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);
}