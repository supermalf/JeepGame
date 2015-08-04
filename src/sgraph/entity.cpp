/*============================================================================
 * ENTITY.CPP                                                              
 *                    
 *                                                   
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <gl/gl.h>

#include "entity.h"
#include "appearence.h"
#include "transformation.h"
#include "shape.h"

#include "msh.h"

/************************************************************************/
/* Methods                                         
/*
/************************************************************************/


Entity::Entity()
{
   transformation = NULL;
   appearence     = NULL;
   shape          = NULL;
}

Entity::Entity( Transformation *tf, Appearence *ap, Shape *fm ) 
{
   transformation = tf;
   appearence     = ap;
   shape          = fm;
}

Entity::~Entity() {}

void Entity::setAtributos( Transformation *tf, Appearence *ap, Shape *fm )
{
   transformation = tf;
   appearence     = ap;
   shape          = fm;
}

void Entity::setTransformation( Transformation *tf ) 
{
   transformation = tf;
  
}

void Entity::setAppearence( Appearence *ap ) 
{
   appearence = ap;
}

void Entity::setShape( Shape *fm )
{
   shape = fm;
}

void Entity::getAtributos( Transformation **tf, Appearence **ap, Shape **fm ) 
{
   *tf = transformation;
   *ap = appearence;
   *fm = shape;
}


Transformation *Entity::getTransformation() 
{ 
   return transformation;
}

Appearence *Entity::getAppearence() 
{
   return appearence;
}

Shape *Entity::getShape() 
{
   return shape;
}

int Entity::setupLight() 
{
   if( transformation )
      transformation->aplica();

   int l = Group::setupLight();

   if( transformation )
      transformation->desaplica() ;

   return l ;
}

int Entity::setupCamera() 
{
   int c = Group::setupCamera() ;

   if( transformation && c )
      transformation->aplicaInversa() ;

   return c ;
}


void Entity::render( int passada ) 
{

   if( transformation )
      transformation->aplica();

   if( appearence )
      appearence->aplica();

   if( shape && (passada == vez) )
      shape->draw();

   Group::render( passada );

   if( appearence )
   appearence->desaplica();

   if( transformation )
   transformation->desaplica();


   //if(shape)
      //shape->write();

}
