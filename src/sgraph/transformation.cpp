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
/* M�todos                                         
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
