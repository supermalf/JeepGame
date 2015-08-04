/*============================================================================
 * APPEARENCE.CPP
 *
 * (ITEM/COMPONENT MEMBER)
 *
 * CHILDRENS:
 * - COLOR
 * - MATERIAL
 * - TEXTURE
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <gl/gl.h>

#include "Appearence.h"
#include "component.h"


/************************************************************************/
/* Methods                                         
/*
/************************************************************************/


Appearence::Appearence() {}

Appearence::~Appearence() {}

void Appearence::desaplica()
{
   glPopAttrib() ;
}
