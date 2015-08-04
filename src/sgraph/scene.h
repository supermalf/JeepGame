/*============================================================================
 * SCENE.H                                                              
 *                    
 *                                                   
 *===========================================================================*/


#ifndef _SCENE_H_
#define _SCENE_H_

#include "group.h"
#include "engine.h"
#include "context.h"

class Scene : public Group 
{
   private:
      Context* context ;
      Engine*  engine;
      int n_engines ;

   public:
      Scene();
      ~Scene() ;
      void render();
      void render( unsigned char key );
      void setEngine(Engine* e);
};

#endif