/*============================================================================
 * SHAPE.H                                                              
 *                    
 *                                                   
 *===========================================================================*/

#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "component.h"

class Shape : public Component
{
   public:
      Shape();
      ~Shape() ;

      void load( char* filename ) ;
      virtual void draw() = 0;
      //virtual void write();

};

#endif