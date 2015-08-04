/*============================================================================
 * DLIGHT.CPP                                                              
 *                    
 * (LIGHT MEMBER)
 *                                              
 *===========================================================================*/



#ifndef _DLIGHT_H_
#define _DLIGHT_H_

#include "dot.h"
#include "light.h"

class Dlight : public Light
{
   private :
      Dot direcao;

   public:
      Dlight();
      Dlight( int i, float *dir, float *amb, float *dif, float *esp) ;
      Dlight( int i, float x, float y, float z,
               float a_vm, float a_vd, float a_az, float a_af,
               float d_vm, float d_vd, float d_az, float d_af ,
               float e_vm, float e_vd, float e_az, float e_af ) ;
     ~Dlight();

      int setupLight();
      void setDirecao( float* p ) ;
      Dot *getDirecao( void ) ;
};

#endif