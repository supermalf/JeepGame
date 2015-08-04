/*============================================================================
 * SLIGHT.CPP                                                              
 *                    
 * (LIGHT MEMBER)
 *                                              
 *===========================================================================*/



#ifndef _SLIGHT_H_
#define _SLIGHT_H_

#include "dot.h"
#include "light.h"



class Slight : public Light
{
   private :
      Dot direcao;
      int light;
      GLfloat cutoff;

   public:
      Slight();
      Slight( int i, float *dir, float *amb, float *dif, float *esp, GLfloat spot_cutoff) ;
      Slight( int i, float x, float y, float z,
               float a_vm, float a_vd, float a_az, float a_af,
               float d_vm, float d_vd, float d_az, float d_af ,
               float e_vm, float e_vd, float e_az, float e_af, GLfloat spot_cutoff ) ;
     ~Slight();

      int setupLight();
      void setDirecao( float* p ) ;
      Dot *getDirecao();
      void MakeSpotLight (float x, float y, GLfloat spot_cutoff);
};

#endif