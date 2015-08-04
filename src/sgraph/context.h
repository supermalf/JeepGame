/*============================================================================
 * CONTEXT.H
 *
 *
 *===========================================================================*/


#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "component.h"


class Context : public Component 
{
   private:
   int iniciado;

   public:
      Context();
      ~Context();

      void defineContext(int passada) ;
      void init();
};

#endif