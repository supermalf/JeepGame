/*============================================================================
 * GROUP.CPP                                                              
 *                    
 *                                                   
 *===========================================================================*/


#include <stdlib.h>
#include <stdio.h>
#include "group.h"
#include "entity.h"


/************************************************************************/
/* Methods                                         
/*
/************************************************************************/

Group::Group() 
{
   int f ;
   for( f=0 ; f<MAX_FILHOS ; f++ )
   {
      filhos[f] = NULL ;
   }
   livre    = 0 ;
   n_filhos = 0 ;
}

int Group::add(Item* pos) 
{
   if(n_filhos < MAX_FILHOS )
   {
      int f ;
      for( f=livre+1 ; f!=livre ; f=(f+1)%MAX_FILHOS )
      {
         if( !filhos[f-1] )
         {
            filhos[f-1] = pos ;
            n_filhos ++ ;
            livre = f ;
            return f-1 ;
         }
      }
   }
   return -1 ;
}


Item* Group::remove( int pos )
{
   if( (pos>=0) && (pos<MAX_FILHOS) && (pos<=n_filhos) ) 
   {
      Item* children = filhos[pos];
      filhos[pos]    = NULL;
      n_filhos -- ;

      return children;
   }

   return NULL;
}


int Group::replace( int pos, Item* children )
{
   if( (pos>=0) && (pos<MAX_FILHOS) && (pos<=n_filhos)) 
   {
      //remove(pos);

      if(n_filhos < MAX_FILHOS )
      {
         filhos[pos] = children;

         //printf("Replaced: %d", pos);
         return pos;

      }
   }

   return -1;
}


Item* Group::ponteiroFilho( int f )
{
   if( f>0 && f<MAX_FILHOS) 
   {
      return filhos[f] ;
   }
   return NULL ;
}

Group:: ~Group(){}

int Group::setupLight()
{
   int n = 0;
   int f ;
   for( f=0 ; f<n_filhos ; f++ )
   {
      if( filhos[f] )
         n += ((Node*)filhos[f])->setupLight() ;
   }
   return n ;
}

int Group::setupCamera()
{
   int f;
   for( f=0 ; f<n_filhos ; f++ )
   {
      if( filhos[f] )
      {
         if( ((Node*)filhos[f])->setupCamera() )
            return 1;
      }
   }
   return 0;
}

void Group::render( int passada )
{
   int f ;
   for( f=0 ; f<MAX_FILHOS ; f++)
   {
      if( filhos[f] )
         ((Node*)filhos[f])->render( passada ) ;
   }
}