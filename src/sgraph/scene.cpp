/*============================================================================
 * SCENE.CPP                                                              
 *                    
 * (GROUP MEMBER)
 *                                                   
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "scene.h"
#include "engine.h"      /* XXX */
#include "context.h"


/************************************************************************/
/* Methods                                         
/*
/************************************************************************/


Scene::Scene()
{
   context = new Context() ;
   engine = NULL ;
}


Scene::~Scene() 
{
   delete context;
}


void Scene::render(  ) 
{ 

  if( engine )
   {
      engine->aplica() ;
   }

   Group::setupCamera();

   Group::setupLight();

   int passada ;

   for( passada=0; passada<3 ; passada++)
   {
      context->defineContext(passada) ;
      Group::render( passada ) ;
   }
   context->defineContext(3) ;
   glutSwapBuffers();
}




/**
*  Display do glut
*/
void Scene::render( unsigned char key ) 
{
   
   if( engine )
   {
      engine->aplica( );
   }
   

/*
   //if( context ){}

   Group::setupCamera();

   Group::setupLight();


   glDisable (GL_BLEND);
   glDepthMask( GL_TRUE ) ;
   
   Group::render( 0 ) ; //opacos


   glDepthMask( GL_FALSE ) ;
   glEnable (GL_BLEND);
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   Group::render( 1 ) ; //transparentes 

*/


}



void Scene::setEngine( Engine* e) 
{
   engine = e;
}

