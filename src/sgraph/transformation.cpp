/*============================================================================
 * TRANSFORMATION.H
 *
 *
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif

#include <gl/gl.h>

#include "transformation.h"



/************************************************************************/
/* Métodos                                         
/*
/************************************************************************/


Transformation::Transformation() {}

Transformation::~Transformation() {}

void Transformation::aplica() {}

void Transformation::desaplica()
{
   glPopMatrix() ;
}

void Transformation::aplicaInversa() {}
