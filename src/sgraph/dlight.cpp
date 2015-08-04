/*============================================================================
 * DLIGHT.CPP                                                              
 *                    
 * (LIGHT MEMBER)
 *                                              
 *===========================================================================*/



#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/gl.h>

#include "dot.h"
#include "light.h"
#include "dlight.h"


Dlight::Dlight() 
{
   direcao.setPosition(  0, 0, 0, 0  ) ;

}

Dlight::Dlight( int i, float *dir, float *amb, float *dif, float *esp) : Light( i, amb, dif, esp ) 
{
   direcao.setPosition( dir[0], dir[1], dir[2], 0  ) ;

}


Dlight::Dlight( int i, float x, float y, float z,
                  float a_vm, float a_vd, float a_az, float a_af,
                  float d_vm, float d_vd, float d_az, float d_af ,
                  float e_vm, float e_vd, float e_az, float e_af ) : Light (i, a_vm,  a_vd,  a_az,  a_af,
                                                                             d_vm,  d_vd,  d_az,  d_af,
                                                                             e_vm,  e_vd,  e_az,  e_af )
{
   direcao.setPosition(  x, y, z, 0  ) ;
}

Dlight::~Dlight() {}

int Dlight::setupLight()
{
   if( id >= GL_LIGHT0 ){
      turnOn() ;


      glLightfv(id, GL_POSITION, direcao.getPosition() ) ;
      return 1 ;
   }
   return 0 ;
}

void Dlight::setDirecao( float* p )
{
   direcao.setPosition( p ) ;
}

Dot *Dlight::getDirecao( void )
{
   return &direcao ;
}


