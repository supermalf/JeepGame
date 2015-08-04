/*============================================================================
 * DOT.H
 *
 * MANIPULATES X,Y,Z,W POSITIONS AND OPERATIONS
 *
 *===========================================================================*/


#ifndef _DOT_H_
#define _DOT_H_

class Dot
{
   private:
      float    pos[4] ;

   public:
      

      Dot();
      Dot( float x, float y, float z, float w );
      Dot( float *v );
      ~Dot();

      void setPosition ( float x, float y, float z, float w );
      void setPosition ( float *v ); 
      void getPosition( float *x, float *y, float *z, float *w ); 
      float *getPosition (); 
      void Add ( Dot a, Dot b );
      void Sub ( Dot a, Dot b );
};

#endif



