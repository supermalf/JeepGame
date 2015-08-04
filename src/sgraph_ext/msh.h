/*============================================================================
 * MSH.CPP
 *
 * MANIPULATES .msh FILES AND DRAW OBJECTS
 *
 *===========================================================================*/


#include "shape.h"


class Msh : public Shape  
{
   protected:
      int NVertexes;
      int NTriangles;
      float *Vertexes;
      float *Normals;
      unsigned int *Ids;

   public:
      Msh();
      Msh( char* filename );
      ~Msh();

      void loadFile( char *filename);
      void draw();
      void write();

};



