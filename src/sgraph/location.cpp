/*============================================================================
 * LOCATION.CPP
 *
 * (ITEM/COMPONENT/TRANSFORM MEMBER)
 *
 *===========================================================================*/




#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/gl.h>
#include <stdio.h>
#include "transformation.h"
#include "location.h"



/************************************************************************/
/* Methods                                         
/*
/************************************************************************/


Location::Location() 
{
   dx = dy = dz  = 0 ;
   ang = ang_rad = 0 ;
   rx = ry = rz  = 1 ;
   refx = refy = refz = 0 ;
   modo_rotacao = USAR_GL_ROTATE ;
}

Location::Location( float trans_x, float trans_y, float trans_z, 
         float rot_ang,
         float rot_x, float rot_y, float rot_z ,
         float rotpos_x, float rotpos_y, float rotpos_z )
{   
   dx = trans_x ;
   dy = trans_y ;
   dz = trans_z ;
   ang = rot_ang ;
   rx = rot_x ;
   ry = rot_y ;
   rz = rot_z  ;
   refx = rotpos_x ;
   refy = rotpos_y ;
   refz = rotpos_z ;
   modo_rotacao = USAR_GL_ROTATE ;
}

Location::Location( float trans_x, float trans_y, float trans_z, 
                  float  ang_e_eixos[16] ,
                  float rotpos_x, float rotpos_y, float rotpos_z )
{   
   dx = trans_x ;
   dy = trans_y ;
   dz = trans_z ;
   int i;
   for(i=0;i<16;i++)
      rot[i]=ang_e_eixos[i] ;
   refx = rotpos_x ;
   refy = rotpos_y ;
   refz = rotpos_z ;
   modo_rotacao = USAR_GL_MULT_MATRIX ;
}

Location::~Location() {}

void Location::setRotacao( float rot_ang,
                  float rot_x, float rot_y, float rot_z ,
                  float rotpos_x, float rotpos_y, float rotpos_z )
{
   ang = rot_ang ;
   rx = rot_x ;
   ry = rot_y ;
   rz = rot_z  ;
   refx = rotpos_x ;
   refy = rotpos_y ;
   refz = rotpos_z ;
   modo_rotacao = USAR_GL_ROTATE ;
}

void Location::setRotacao( float  ang_e_eixos[16] ,
                          float rotpos_x, float rotpos_y, float rotpos_z )
{
   int i;
   for(i=0;i<16;i++)
      rot[i]=ang_e_eixos[i] ;
   refx = rotpos_x ;
   refy = rotpos_y ;
   refz = rotpos_z ;
   modo_rotacao = USAR_GL_MULT_MATRIX ;
}
void Location::setTranslacao( float trans_x, float trans_y, float trans_z )
{
   dx = trans_x ;
   dy = trans_y ;
   dz = trans_z ;
}

void Location::getRotacao( float *ang_e_eixos,
                          float *rotpos_x, float *rotpos_y, float *rotpos_z )
{
   int i;
   for(i=0;i<16;i++)
      ang_e_eixos[i]= rot[i] ;
   *rotpos_x = refx ;
   *rotpos_y = refy ;
   *rotpos_z = refz ;
}

void Location::getRotacao( float *rot_ang,
                  float *rot_x, float *rot_y, float *rot_z ,
                  float *rotpos_x, float *rotpos_y, float *rotpos_z )
{
   *rot_ang = ang ;
   *rot_x = rx ;
   *rot_y = ry ;
   *rot_z = rz ;
   *rotpos_x = refx ;
   *rotpos_y = refy ;
   *rotpos_z = refz ;
}

void Location::getTranslacao( float *trans_x, float *trans_y, float *trans_z )
{
   *trans_x = dx ;
   *trans_y = dy ;
   *trans_z = dz ;
}

void Location::aplica( void )
{
   glPushMatrix() ;
   glTranslatef( dx+refx, dy+refy, dz+refz ) ;
   if( modo_rotacao == USAR_GL_ROTATE )
   {
      glRotatef( ang, rx, ry, rz ) ;
   }
   else
   {
      glMultMatrixf( rot ) ;       
   }
   glTranslatef( -refx, -refy, -refz ) ;

}

void Location::aplicaInversa( void )
{
   /*  inv(PQS) = inv(S)inv(Q)inv(P) */
   glTranslatef( refx, refy, refz ) ;
   if( modo_rotacao == USAR_GL_ROTATE )
   {
      glRotatef( -ang, rx, ry, rz ) ;
   }
   else
   {
      glMultMatrixf( rot ) ;       
   }
   glTranslatef( -dx-refx, -dy-refy, -dz-refz ) ;
}
