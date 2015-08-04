/*============================================================================
 * LOCATION.H
 *
 * (ITEM/COMPONENT/TRANSFORM MEMBER)
 *
 *===========================================================================*/




#ifndef _LOCATION_H
#define _LOCATION_H

#define USAR_GL_ROTATE 0
#define USAR_GL_MULT_MATRIX 1

#include "transformation.h"

class Location : public Transformation 
{
   private:
      float ex, ey, ez ;   // escala
      float dx, dy, dz ;   // translado
      float ang, ang_rad ; // rotacao por 1 eixo
      float rx, ry, rz ;
      float rot[16] ;      // rotacao por varios eixos
      float refx, refy, refz ; // centro de rotacao

   /*   enum {
         USAR_GL_ROTATE,
         USAR_GL_MULT_MATRIX,
      } */
      int modo_rotacao ;


   public:
      Location( void ) ;
      Location( float trans_x, float trans_y, float trans_z, 
               float rot_ang,
               float rot_x, float rot_y, float rot_z ,
               float rotpos_x, float rotpos_y, float rotpos_z ) ;
      Location( float trans_x, float trans_y, float trans_z, 
               float ang_e_eixos[16],
               float rotpos_x, float rotpos_y, float rotpos_z ) ;
      ~Location( void ) ;

      void setRotacao( float rot_ang,
                       float rot_x, float rot_y, float rot_z ,
                       float rotpos_x, float rotpos_y, float rotpos_z ) ;
     void setRotacao( float  ang_e_eixos[16],
                      float rotpos_x, float rotpos_y, float rotpos_z ) ;
      void setTranslacao( float trans_x, float trans_y, float trans_z ) ;

      void getRotacao( float *rot_ang,
                       float *rot_x, float *rot_y, float *rot_z ,
                       float *rotpos_x, float *rotpos_y, float *rotpos_z ) ;
      void getRotacao( float *ang_e_eixos,
                       float *rotpos_x, float *rotpos_y, float *rotpos_z ) ;
      void getTranslacao( float *trans_x, float *trans_y, float *trans_z ) ;

      void aplica( void );
      void aplicaInversa( void ) ;
};


#endif