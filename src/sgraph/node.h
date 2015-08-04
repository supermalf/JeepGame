/*============================================================================
 * NODE.H                                                              
 *                    
 * (ITEM MEMBER)
 *
 * CHILDRENS:
 * - GROUP
 * - CAMERA
 * - LIGHT                                                    
 *===========================================================================*/


#include "item.h"

#ifndef _NODE_H_
#define _NODE_H_

class Node : public Item
{
   protected:
      char nome[128];
      int vez;

   public:
      Node ();
      Node ( char* n );
      ~Node();

     
      virtual int  setupCamera();
      virtual int  setupLight(); 
      virtual void render( int passada );

      void setType(int v);
};

#endif