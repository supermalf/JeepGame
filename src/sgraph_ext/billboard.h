/*============================================================================
 * BILLBOARD.H
 *
 * 
 *
 *===========================================================================*/


#include "shape.h"


class BillBoard : public Shape  
{


   public:
      BillBoard();
      ~BillBoard();
      void draw();


      void Cylindrical(float *cam, float *worldPos);
      void CheatCylindrical();
      void CheatSpherical();

};



