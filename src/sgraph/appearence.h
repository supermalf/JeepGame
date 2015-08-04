/*============================================================================
 * APPEARENCE.H
 *
 * (ITEM/COMPONENT MEMBER)
 *
 * CHILDRENS:
 * - COLOR
 * - MATERIAL
 * - TEXTURE
 *===========================================================================*/


#ifndef _APPEARENCE_H_
#define _APPEARENCE_H_

#include "component.h"


class Appearence : public Component 
{
   public:
      Appearence();
      ~Appearence();

      virtual void aplica() = 0;
      virtual void desaplica();
};

#endif