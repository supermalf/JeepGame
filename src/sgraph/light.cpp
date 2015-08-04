/*============================================================================
 * LIGHT.CPP                                                              
 *                    
 *                                                   
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif

#include <gl/gl.h>

#include "light.h"


/************************************************************************/
/* Methods                                         
/*
/************************************************************************/

Light::Light()
{
   id = -1 ;
   ambiente[0] = 0 ;
   ambiente[1] = 0 ;
   ambiente[2] = 0 ;
   ambiente[3] = 0 ;
   difusa[0] = 0 ;
   difusa[1] = 0 ;
   difusa[2] = 0 ;
   difusa[3] = 0 ;
   especular[0] = 0 ;
   especular[1] = 0 ;
   especular[2] = 0 ;
   especular[3] = 0 ;
};

Light::Light( int i, float* a, float* d , float* e  )
{
   id = i ;
   ambiente[0] = a[0] ;
   ambiente[1] = a[1] ;
   ambiente[2] = a[2] ;
   ambiente[3] = a[3] ;
   difusa[0] = d[0] ;
   difusa[1] = d[1] ;
   difusa[2] = d[2] ;
   difusa[3] = d[3] ;
   especular[0] = e[0] ;
   especular[1] = e[1] ;
   especular[2] = e[2] ;
   especular[3] = e[3] ;
};

Light::Light( int i, float a_vm, float a_vd, float a_az, float a_af,
              float d_vm, float d_vd, float d_az, float d_af ,
              float e_vm, float e_vd, float e_az, float e_af ) 
{
   id = i ;
   ambiente[0] = a_vm ;
   ambiente[1] = a_vd ;
   ambiente[2] = a_az ;
   ambiente[3] = a_af ;
   difusa[0] = d_vm ;
   difusa[1] = d_vd ;
   difusa[2] = d_az ;
   difusa[3] = d_af ;
   especular[0] = e_vm ;
   especular[1] = e_vd ;
   especular[2] = e_az ;
   especular[3] = e_af ;
};


Light::~Light() {}


void Light::setId( int i )
{
   id = i ;
}

int  Light::getId( void ) 
{
   return id ;
}
void Light::setCores( float* a, float* d , float* e ) 
{
   ambiente[0] = a[0] ;
   ambiente[1] = a[1] ;
   ambiente[2] = a[2] ;
   ambiente[3] = a[3] ;
   difusa[0] = d[0] ;
   difusa[1] = d[1] ;
   difusa[2] = d[2] ;
   difusa[3] = d[3] ;
   especular[0] = e[0] ;
   especular[1] = e[1] ;
   especular[2] = e[2] ;
   especular[3] = e[3] ;
}

void Light::getCores( float* a, float* d , float* e ) 
{
   a[0] = ambiente[0] ;
   a[1] = ambiente[1] ;
   a[2] = ambiente[2] ;
   a[3] = ambiente[3] ;
   d[0] = difusa[0] ;
   d[1] = difusa[1] ;
   d[2] = difusa[2] ;
   d[3] = difusa[3] ;
   e[0] = especular[0] ;
   e[1] = especular[1] ;
   e[2] = especular[2] ;
   e[3] = especular[3] ;
}

void Light::turnOn()
{
   glEnable( id );
   glLightfv( id, GL_AMBIENT,  ambiente);
   glLightfv( id, GL_DIFFUSE,  difusa);
   glLightfv( id, GL_SPECULAR, especular);
}

void Light::turnOff()
{
   glDisable( id );
   //glLightfv( id, GL_AMBIENT,  ambiente);
   //glLightfv( id, GL_DIFFUSE,  difusa);
   //glLightfv( id, GL_SPECULAR, especular);
}

void Light::setLightState (int state)
{
   lightState = state;
   return;
}