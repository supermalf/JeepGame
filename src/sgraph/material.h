/*============================================================================
 * MATERIAL.H                                                             
 *                    
 * (APPEARENCE MEMBER)
 *                                                    
 *===========================================================================*/


#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "appearence.h"
#include "color.h"


class Material : public Appearence
{
   private:
      Color *ambiente ;
      Color *difusa ;
      Color *especular ;
      Color *emissiva ;
      float brilho ;

   public:
      Material();
      Material( float *am, float *df, float *es, float *em, float br );
      ~Material();

   private:
      void setColor( Color *color, float *c, int modo );
      void getColor( Color *color, float c[4] );

   public:
      void setColors ( float *am, float *df, float *es, float *em, float br );
      void setAmbiente ( float *am) ;
      void setDifusa   ( float *df );
      void setEspecular( float *es );
      void setEmissiva ( float *em );
      void setBrilho   ( float br );


      void getColors( float am[4], float df[4], float es[4], float em[4], float  *br );
      void getAmbiente ( float am[4]) ;
      void getDifusa   ( float df[4] );
      void getEspecular( float es[4] );
      void getEmissiva ( float em[4] );
      float getBrilho ();

      void aplica();
      void desaplica();
};

#endif