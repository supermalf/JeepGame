/*============================================================================
 * PLIGHT.CPP                                                              
 *                    
 * (LIGHT MEMBER)
 *                                              
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif

#include <gl/gl.h>
#include "glut.h"

#include "light.h"
#include "plight.h"


#include "dot.h"  /* XXX */



/************************************************************************/
/* Methods                                         
/*
/************************************************************************/


Plight::Plight() 
{
   position.setPosition(0,0,0,1);
}


Plight::Plight( int i, float x, float y, float z,
                float a_vm, float a_vd, float a_az, float a_af,
                float d_vm, float d_vd, float d_az, float d_af,
                float e_vm, float e_vd, float e_az, float e_af ) : Light (i, a_vm,  a_vd,  a_az,  a_af,
                                                                             d_vm,  d_vd,  d_az,  d_af,
                                                                             e_vm,  e_vd,  e_az,  e_af )
{
   position.setPosition(x,y,z,1);
}


Plight::Plight(int i, float *pos, float *amb, float *dif, float *esp) : Light( i, amb, dif, esp ) 
{
   position.setPosition(pos[0], pos[1], pos[2], 1);
}



Plight::~Plight() {}


int Plight::setupLight()
{
   if( id >= GL_LIGHT0 )
   {
      turnOn();
      glLightfv(id, GL_POSITION, position.getPosition() );
      return 1 ;
   }

   return 0 ;
}


void Plight::setPosition( float* p )
{
   position.setPosition(p);
}


Dot *Plight::getPosition()
{
   return &position ;
}