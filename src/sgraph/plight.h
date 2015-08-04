/*============================================================================
 * PLIGHT.CPP                                                              
 *                    
 * (LIGHT MEMBER)
 *                                              
 *===========================================================================*/


#ifndef _PLIGHT_H_
#define _PLIGHT_H_

#include "light.h"


#include "dot.h" /* XXX nao faz parte do grafo de cena */


class Plight : public Light
{
   protected:
      Dot position;

   public:
      Plight(); 
      Plight( int i, float x, float y, float z,
              float a_vm, float a_vd, float a_az, float a_af,
              float d_vm, float d_vd, float d_az, float d_af,
              float e_vm, float e_vd, float e_az, float e_af );
             
      Plight(int i, float *pos, float *amb, float *dif, float *esp); 

      ~Plight();
      int setupLight();
      void setPosition( float* p );
      Dot *getPosition();
};

#endif


