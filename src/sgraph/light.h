/*============================================================================
 * LIGHT.H                                                              
 *                    
 *                                                   
 *===========================================================================*/


#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "node.h"

class Light : public Node
{
   protected:
      int id ;
      float ambiente[4] ;
      float difusa[4] ;
      float especular[4] ;
      /* XXX incluir Atenuacao linear, quadratica e constante?? */

   public:
      int lightState;
      Light();
      Light( int i, float* a, float* d , float* e  ) ;
      Light( int i, float a_vm, float a_vd, float a_az, float a_af,
                  float d_vm, float d_vd, float d_az, float d_af ,
                  float e_vm, float e_vd, float e_az, float e_af ) ;
      ~Light();

      void turnOn();
      void turnOff();
      void setLightState (int state);
      void setId( int i ) ;
      int  getId( void ) ;
      void setCores( float* a, float* d , float* e ) ;
      void getCores( float* a, float* d , float* e ) ;
};

#endif