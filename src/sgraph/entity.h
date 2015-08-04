/*============================================================================
 * ENTITY.H                                                             
 *                    
 *                                                   
 *===========================================================================*/


#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "group.h"
#include "appearence.h"
#include "transformation.h"
#include "shape.h"


class Entity : public Group 
{
   private:
      Transformation *transformation;
      Appearence     *appearence;
      Shape          *shape;

   public:
      Entity ();
      Entity ( Transformation* tf, Appearence*ap, Shape* fm ) ;
      ~Entity();

      void setAtributos (Transformation *tf, Appearence *ap, Shape *fm);
      void setAppearence (Appearence *ap);
      void setTransformation (Transformation *tf);
      void setShape (Shape *fm);
   
      void           getAtributos (Transformation **tf, Appearence **ap, Shape **fm);
      Transformation *getTransformation();
      Appearence     *getAppearence();
      Shape          *getShape();

      int  setupLight ();
      int  setupCamera ();
      void render ( int passada );
};

#endif