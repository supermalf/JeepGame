/*============================================================================
 * COLOR.CPP                                                              
 *                    
 * (APPEARENCE MEMBER)
 *                                              
 *===========================================================================*/

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <gl/gl.h>

#include "color.h"


/************************************************************************/
/* Methods                                         
/*
/************************************************************************/

Color::Color()
{
   modo = GL_AMBIENT_AND_DIFFUSE ;
   vermelho = 0.3f ;
   verde = 0.3f ;
   azul = 0.3f ;
   alfa = 1.0f ;
}

Color::Color( float *c, int m )
{
   modo = m ;
   vermelho = c[0] ;
   verde = c[1] ;
   azul = c[2] ;
   alfa = c[3] ;
}

Color::Color( float vm, float vd, float az, float af, int m ) 
{
   modo = m ;
   vermelho = vm ;
   verde = vd ;
   azul = az ;
   alfa = af ;
}

Color::~Color() {}

void Color::setColor( float *c, int m )
{
   modo = m ;
   vermelho = c[0] ;
   verde = c[1] ;
   azul = c[2] ;
   alfa = c[3] ;
}

void Color::setColor( float vm, float vd, float az, float af, int m )
{
   modo = m ;
   vermelho = vm ;
   verde = vd ;
   azul = az ;
   alfa = af ;
}

void Color::getColor(float *vm, float *vd, float *az, float *af, int *m  )
{
   *m = modo ;
   *vm = vermelho ;
   *vd = verde ;
   *az = azul ;
   *af = alfa ;
}

void Color::aplica( void )
{  
   glPushAttrib( GL_CURRENT_BIT ) ;
   float cor[4] = {vermelho, verde, azul, alfa } ;
   if( modo == GL_DIFFUSE || modo == GL_AMBIENT)
   {
      glColor4f( vermelho, verde, azul, alfa);
   }
   else
   glMaterialfv(GL_FRONT_AND_BACK, modo, cor);
}
