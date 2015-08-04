/*============================================================================
 * DOT.H
 *
 * MANIPULATES X,Y,Z,W POSITIONS AND OPERATIONS
 *
 *===========================================================================*/



#include "dot.h"



/************************************************************************/
/* Methods                                         
/*
/************************************************************************/

Dot::Dot()
{
   pos[0] = 0;
   pos[1] = 0;
   pos[2] = 0;
   pos[3] = 1;
}

Dot::Dot( float x, float y, float z, float w )
{
   pos[0] = x;
   pos[1] = y;
   pos[2] = z;
   pos[3] = w;
}

Dot::Dot( float *v )
{
   if(v)
   {
      pos[0] = v[0];
      pos[1] = v[1];
      pos[2] = v[2];
      pos[3] = v[3];
   }
   else
   {
      pos[0] = 0;
      pos[1] = 0;
      pos[2] = 0;
      pos[3] = 1;
   }      
}

Dot::~Dot() {}


void Dot::setPosition ( float x, float y, float z, float w )
{
   pos[0] = x;
   pos[1] = y;
   pos[2] = z;
   pos[3] = w;
}

void Dot::setPosition ( float *v ) 
{
   if(v)
   {
      pos[0] = v[0];
      pos[1] = v[1];
      pos[2] = v[2];
      pos[3] = v[3];
   }
}

void Dot::getPosition( float *x, float *y, float *z, float *w ) 
{
   *x = pos[0];
   *y = pos[1];
   *z = pos[2];
   *w = pos[3];

}

float *Dot::getPosition () 
{
   return pos;
}


void Dot::Add ( Dot a, Dot b ) 
{
   float *_a = a.getPosition();
   float *_b = b.getPosition();

   pos[0] = _a[0] + _b[0];
   pos[1] = _a[1] + _b[1];
   pos[2] = _a[2] + _b[2];
}


void Dot::Sub ( Dot a, Dot b ) 
{
   float *_a = a.getPosition();
   float *_b = b.getPosition();

   pos[0] = _a[0] - _b[0];
   pos[1] = _a[1] - _b[1];
   pos[2] = _a[2] - _b[2];
}


/*
//Retorna this . a
float Dot::ProdEsc  ( Dot a ) 
{
   float  e;
   float *_a = a.getCoord() ;

   e  = ( coord[0] * _a[0] ) ;
   e += ( coord[1] * _a[1] ) ;
   e += ( coord[2] * _a[2] ) ;
   return e ;
}

//this = a x b
void     Ponto::ProdVet  ( Ponto a, Ponto b )
{
   float *_a = a.getCoord() ;
   float *_b = b.getCoord() ;

 	coord[0] = _a[1] * _b[2] + _a[2] * _b[1] ;
	coord[1] = _a[2] * _b[0] + _a[0] * _b[2] ;
	coord[2] = _a[0] * _b[1] + _a[1] * _b[0] ;
};

//this = e * a
void     Ponto::Escala   ( float e, Ponto a )
{
   float *_a = a.getCoord() ;

 	coord[0] = e * _a[1] ;
	coord[1] = e * _a[2] ;
	coord[2] = e * _a[0] ;
};

*/