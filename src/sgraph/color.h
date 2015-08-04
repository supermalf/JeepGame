/*============================================================================
 * COLOR.H
 *
 * (APPEARENCE MEMBER)
 *  
 *===========================================================================*/


#ifndef _COLOR_H_
#define _COLOR_H_

#include "appearence.h"


class Color : public Appearence 
{
   private:
      unsigned int modo ;
      float vermelho ;
      float verde ;
      float azul ;
      float alfa ;

   public:
      Color();
      Color( float *c, int m ) ;
      Color( float vm, float vd, float az, float af, int m ) ;
      ~Color();
      void setColor( float *c, int m ) ;
      void setColor( float vm, float vd, float az, float af, int m ) ;
      void getColor(float *vm, float *vd, float *az, float *af, int *m  ) ;
      void aplica();
};



#endif
