/*============================================================================
 * FOG.H
 *
 * 
 *
 *===========================================================================*/


#include "Appearence.h"


class Fog : public Appearence  
{
   private:
    int fogMode;
    int initFog;

   public:
      Fog();
      ~Fog();
      void aplica();
};