/*============================================================================
 * GROUP.H                                                              
 *                    
 *                                                   
 *===========================================================================*/


#ifndef _GROUP_H_
#define _GROUP_H_

#include "node.h"

#define MAX_FILHOS 32

class Group : public Node 
{
   private:
      Item* filhos[MAX_FILHOS] ;
      int   n_filhos ;
      int   livre ;

   public:
      Group();
      ~Group();

      int   add( Item* pos ) ;
      Item* remove( int pos ) ;
      int replace( int pos, Item* children );
      Item* ponteiroFilho( int f ) ;

      int  setupCamera();
      int  setupLight(); 
      virtual void render(int passada);

};

#endif