/*============================================================================
 * SLIGHT.CPP                                                              
 *                    
 * (LIGHT MEMBER)
 *                                              
 *===========================================================================*/



#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/gl.h>

#include <math.h>
#include "dot.h"
#include "light.h"
#include "slight.h"
#include "dynamics.h"  /* XXX */


Slight::Slight() 
{
   direcao.setPosition(  0, 0, 0, 0  ) ;
   light=0;
   cutoff = 0.0f;

}

Slight::Slight( int i, float *dir, float *amb, float *dif, float *esp, GLfloat spot_cutoff) : Light( i, amb, dif, esp ) 
{
   direcao.setPosition( dir[0], dir[1], dir[2], 0  ) ;
   light = i;
   cutoff = spot_cutoff;

}


Slight::Slight( int i, float x, float y, float z,
                  float a_vm, float a_vd, float a_az, float a_af,
                  float d_vm, float d_vd, float d_az, float d_af ,
                  float e_vm, float e_vd, float e_az, float e_af, GLfloat spot_cutoff ) : Light (i, a_vm,  a_vd,  a_az,  a_af,
                                                                             d_vm,  d_vd,  d_az,  d_af,
                                                                             e_vm,  e_vd,  e_az,  e_af )
{
   direcao.setPosition(  x, y, z, 0  ) ;
   light = i;
   cutoff = spot_cutoff;
}

Slight::~Slight() {}


int Slight::setupLight()
{
   if( lightState == 0)
   {
      turnOff();
      return 1;
   }

   else if( id >= GL_LIGHT0 )
   {
      turnOn();

      float x; 
      float y;
      getCarPos(&x,&y);

      MakeSpotLight(x,y,cutoff);

      return 1;
   }
   return 0 ;
}

void Slight::setDirecao( float* p )
{
   direcao.setPosition( p ) ;
}

Dot *Slight::getDirecao( void )
{
   return &direcao ;
}

void Slight::MakeSpotLight (float x, float y, GLfloat spot_cutoff )
{
   GLfloat carSize=0.0f;

   x+=carSize;
   y+=carSize;

   GLfloat angle = carGetAngle();

	//GLfloat spot_cutoff         = 90.0f;
	GLfloat constant_attenuation  = 0.15f;
	GLfloat linear_attenuation    = 0.05f;
	GLfloat quadratic_attenuation = 0.02f;
	GLfloat spot_expoent          = 1.66f;
   
	GLfloat lightPosition [] = { x,  y, 4.0f, 1.0f};
	GLfloat spot_direction[] = {x*(float)sin(angle),  y*(float)cos(angle), 0.0f, 1.0f};


   glLightfv(light, GL_POSITION, lightPosition);
	glLightf (light, GL_SPOT_CUTOFF, spot_cutoff);
	glLightfv(light, GL_SPOT_DIRECTION, spot_direction);
	glLightf (light, GL_CONSTANT_ATTENUATION, constant_attenuation);
	glLightf (light, GL_LINEAR_ATTENUATION, linear_attenuation);
	glLightf (light, GL_QUADRATIC_ATTENUATION, quadratic_attenuation);
	glLightf (light, GL_SPOT_EXPONENT, spot_expoent);

    return;
}


