/*============================================================================
 * TRANSFORMATION.H
 *
 *
 *===========================================================================*/


#ifndef _TRANSFORMATION_H_
#define _TRANSFORMATION_H_

#include "component.h"

class Transformation : public Component
{
   public:
      Transformation();
      ~Transformation();

      virtual void aplica();
      void desaplica();
      virtual void aplicaInversa();
};

#endif