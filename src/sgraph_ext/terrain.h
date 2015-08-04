/*============================================================================
 * TERRAIN.H
 *
 * MANIPULATES TERRAINS
 *
 *===========================================================================*/


#include "shape.h"


class Terrain : public Shape  
{
   protected:
	   float terreno[512][512];
	   float normais[512][512][3];

	   int divX;
	   int divY;

	   float escalaX;
	   float escalaY;
	   float escalaZ;

	   float centroX;
	   float centroY;
	   float centroZ;

   public:
      Terrain();
      Terrain( char* filename );
      ~Terrain();
      void Gauss();
      void carrega( char *filename);
      void draw();
      void calculaNormais (void);
      float PegaAltura (float x, float y);
};
