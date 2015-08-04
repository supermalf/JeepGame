/*============================================================================
 * MATERIAL.CPP                                                              
 *                    
 * (APPEARENCE MEMBER)
 *                                                    
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <gl/gl.h>

#include "material.h"
#include "color.h"


/************************************************************************/
/* Methods                                         
/*
/************************************************************************/

Material::Material()
{
   ambiente  = NULL;
   difusa    = NULL;
   especular = NULL;
   emissiva  = NULL;
   brilho    = 0;
}

Material::Material( float *am, float *df, float *es, float *em, float br )
{
   if( am )
      ambiente = new Color( am, GL_AMBIENT ) ;
   else
      ambiente = NULL ;

   if( df )
      difusa = new Color( df, GL_DIFFUSE ) ;
   else
      difusa = NULL ;

  if( es )
      especular = new Color( es, GL_SPECULAR ) ;
   else
      especular = NULL ;

  if( em )
      emissiva = new Color( em, GL_EMISSION ) ;
   else
      emissiva = NULL ;

   brilho = br ;
}

Material::~Material() 
{
   delete ambiente ;
   delete difusa ;
   delete especular ;
   delete emissiva ;
}

void Material::setColor( Color *color, float *c, int modo )
{
   if( color && c )
      color->setColor( c, modo ) ;
   else
   {
      if( c )
         color = new Color( c, modo ) ;
      else
      {
         delete color ; 
         color = NULL ;
      }
   }
}

void Material::setAmbiente( float *am) 
{
   setColor( ambiente, am, GL_AMBIENT ) ;
}

void Material::setDifusa( float *df )
{
   setColor( difusa, df, GL_DIFFUSE ) ;
}

void Material::setEspecular( float *es )
{
   setColor( especular, es, GL_SPECULAR ) ;
}

void Material::setEmissiva( float *em )
{
   setColor( emissiva, em, GL_EMISSION ) ;
}

void Material::setBrilho( float br )
{
   brilho = br ;
}   

void Material::setColors( float *am, float *df, float *es, float *em,
                         float br )
{
   setColor( ambiente, am, GL_AMBIENT ) ;
   setColor( difusa, df, GL_DIFFUSE ) ;
   setColor( especular, es, GL_SPECULAR ) ;
   setColor( emissiva, em, GL_EMISSION ) ;
   brilho = br ;
}

void Material::getColor( Color *color, float c[4] )
{
   int m ;
   if( color )
      color->getColor( &c[0], &c[1], &c[2], &c[3], &m ) ;
   else
   {
      c[0] = -1.0f ;
      c[1] = -1.0f ;
      c[2] = -1.0f ;
      c[3] = -1.0f ;
   }
}

void Material::getColors( float am[4], float df[4], float es[4], float em[4],
                         float  *br )
{
   getColor( ambiente, am ) ;
   getColor( difusa, df ) ;
   getColor( especular, es) ;
   getColor( emissiva, em) ;
   *br = brilho ;
}


void Material::getAmbiente( float am[4]) 
{
   getColor( ambiente, am ) ;
}


void Material::getDifusa( float df[4] )
{
   getColor( difusa, df ) ;
}


void Material::getEspecular( float es[4] )
{
   getColor( especular, es ) ;
}


void Material::getEmissiva( float em[4] )
{
   getColor( emissiva, em ) ;
}


float Material::getBrilho( void )
{
   return brilho ;
}  


void Material::aplica( void )
{
   glPushAttrib( GL_CURRENT_BIT ) ;

   if( ambiente )
      ambiente->aplica() ;

   if( difusa )
      difusa->aplica() ;

   if( especular )
      especular->aplica() ;

   if( emissiva )
      emissiva->aplica() ;

   if( brilho )
      glMaterialf( GL_FRONT, GL_SHININESS, brilho) ; 
} 


void Material::desaplica( void )
{
   if( emissiva )
      emissiva->desaplica() ;

   if( especular )
      especular->desaplica() ;

   if( difusa )
      difusa->desaplica() ;

   if( ambiente )
      ambiente->desaplica() ;

   glPopAttrib( ) ;
}  
