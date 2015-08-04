/*============================================================================
 * TERRAIN.CPP
 *
 * MANIPULATES TERRAINS
 *
 *===========================================================================*/



#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/gl.h>


#include <stdio.h>
#include "image.h"
#include "terrain.h"

#include <math.h>

Terrain::Terrain()
{
	escalaX = 1.0f;
	escalaY = 1.0f;
	escalaZ = 0.25;   

	centroX = 0.0f;
	centroY = 0.0f;
	centroZ = 0.0f;
}

Terrain::Terrain( char* filename )
{
   escalaX = 1.0f;
	escalaY = 1.0f;
	escalaZ = 20.0f;   

	centroX = 0.0f;
	centroY = 0.0f;
	centroZ = 0.0f;
   carrega( filename );

}


Terrain::~Terrain() {}


float Terrain::PegaAltura (float x, float y)
{
	float fIndiceX, fIndiceY;
	int indiceX, indiceY;

	
	fIndiceX = x / escalaX;
	fIndiceY = y / escalaY;

	
	if ( (fIndiceX>255.0f) || (fIndiceX<1.0f) || (fIndiceY>255.0f) || (fIndiceY<1.0f))
		return 0.0f;


	indiceX = (int)( fIndiceX + 0.5f );
	indiceY = (int)( fIndiceY + 0.5f );

	return terreno[indiceX][indiceY];
}





void Terrain::Gauss()
{
   int width=512, height=512;
   int Gauss [3][3];

   int x, y;
   float v0,v1,v2,v3,v4,v5,v6,v7,v8;

   Gauss[0][0] = 1; Gauss[0][1] = 2; Gauss[0][2] = 1;
   Gauss[1][0] = 2; Gauss[1][1] = 4; Gauss[1][2] = 2;
   Gauss[2][0] = 1; Gauss[2][1] = 2; Gauss[2][2] = 1;

      for (y=0;y<height;y++){
          for (x=0;x<width;x++) {

              /* Edges pixels case */
              if(y == 0 && x == 0)
              {
                  v0 = terreno[x+1][y];
                  v1 = terreno[x][y+1];
                  v2 = terreno[x+1][y+1];
                  v3 = terreno[x][y];

                  terreno[x][y] = (v3*(float) Gauss[1][1] + v0*(float) Gauss[1][2] +
                                 v1*(float) Gauss[2][1] + v2*(float) Gauss[2][2])/16.0F;
              }

              if(x == width - 1 && y == 0)
              {
                  v0 = terreno[x-1][y];
                  v1 = terreno[x-1][y+1];
                  v2 = terreno[x][y+1];
                  v3 = terreno[x][y];

                  terreno[x][y] = (v3*(float) Gauss[1][1] + v0*(float) Gauss[1][2] +
                                 v1*(float) Gauss[2][1] + v2*(float) Gauss[2][2])/16.0F;
              }

              if(x == width - 1 && y == height - 1)
              {
                  v0 = terreno[x-1][y-1];
                  v1 = terreno[x][y-1];
                  v2 = terreno[x-1][y];
                  v3 = terreno[x][y];

                  terreno[x][y] = (v3*(float) Gauss[1][1] + v0*(float) Gauss[1][2] +
                                 v1*(float) Gauss[2][1] + v2*(float) Gauss[2][2])/16.0F;
              }

              if(y == height - 1 && x == 0)
              {
                  v0 = terreno[x][y-1];
                  v1 = terreno[x+1][y-1];
                  v2 = terreno[x+1][y];
                  v3 = terreno[x][y];

                  terreno[x][y] = (v3*(float) Gauss[1][1] + v0*(float) Gauss[1][2] +
                                 v1*(float) Gauss[2][1] + v2*(float) Gauss[2][2])/16.0F;
              }

              if(x == width - 1 && y > 0 && y < height - 1)
              {
                  v0 = terreno[x-1][y-1];
                  v1 = terreno[x][y-1];
                  v2 = terreno[x-1][y];
                  v3 = terreno[x-1][y+1];
                  v4 = terreno[x][y+1];
                  v5 = terreno[x][y];

                  terreno[x][y] = (v5*(float) Gauss[1][1] + v0*(float) Gauss[0][0] + v1*(float) Gauss[0][1] +
                                 v2*(float) Gauss[1][0] + v4*(float) Gauss[2][1] + v3*(float) Gauss[2][0])/16.0F;
              }

              if(x == 0 && y > 0 && y < height - 1)
              {
                  v0 = terreno[x][y-1];
                  v1 = terreno[x+1][y-1];
                  v2 = terreno[x+1][y];
                  v3 = terreno[x][y+1];
                  v4 = terreno[x+1][y+1];
                  v5 = terreno[x][y];

                  terreno[x][y] = (v5*(float) Gauss[1][1] + v0*(float) Gauss[0][1] + v1*(float) Gauss[0][2] +
                                 v2*(float) Gauss[1][2] + v3*(float) Gauss[2][1] + v4*(float) Gauss[2][2])/16.0F;
              }

              if(y == 0 && x > 0 && x < width - 1)
              {
                  v0 = terreno[x-1][y];
                  v1 = terreno[x+1][y];
                  v2 = terreno[x-1][y+1];
                  v3 = terreno[x][y+1];
                  v4 = terreno[x+1][y+1];
                  v5 = terreno[x][y];

                  terreno[x][y] = (v5*(float) Gauss[1][1] + v0*(float) Gauss[1][0] + v1*(float) Gauss[1][2] +
                                 v2*(float) Gauss[2][0] + v3*(float) Gauss[2][1] + v4*(float) Gauss[2][2])/16.0F;
              }

              if(y == height - 1 && x > 0 && x < width - 1)
              {
                  v0 = terreno[x-1][y-1];
                  v1 = terreno[x][y-1];
                  v2 = terreno[x+1][y-1];
                  v3 = terreno[x-1][y];
                  v4 = terreno[x][y];
                  v5 = terreno[x+1][y];

                  terreno[x][y] = (v4*(float) Gauss[1][1] + v0*(float) Gauss[0][0] + v1*(float) Gauss[0][1] +
                                 v2*(float) Gauss[0][2] + v3*(float) Gauss[1][0] + v5*(float) Gauss[1][2])/16.0F;
              }

              /* Central Pixels */
              if( x != 0 && y != 0 && y != height - 1 && x != width - 1)
              {
                  v0 = terreno[x-1][y-1];
                  v1 = terreno[x][y-1];
                  v2 = terreno[x+1][y-1];
                  v3 = terreno[x-1][y];
                  v4 = terreno[x][y];
                  v5 = terreno[x+1][y];
                  v6 = terreno[x-1][y+1];
                  v7 = terreno[x][y+1];
                  v8 = terreno[x+1][y+1];

                  terreno[x][y] = (v0*(float) Gauss[0][0] + v1*(float) Gauss[0][1] + v2*(float) Gauss[0][2] +
                                 v3*(float) Gauss[1][0] + v4*(float) Gauss[1][1] + v5*(float) Gauss[1][2] +
                                 v6*(float) Gauss[2][0] + v7*(float) Gauss[2][1] + v8*(float) Gauss[2][2] )/16.0F;
              }
          }
      }
 }


void Terrain::carrega( char *filename)
{

	int i, j;
	int indice = 0;
	unsigned char * buff;


	buff = arqBMP24bit_p_vet32bit ( filename, &divX, &divY);



	if (buff == NULL)
		return ;

	
	for (i=0; i<divX; i++)
	{
		for (j=0; j<divY; j++)
		{
			terreno[i][j] = (float)buff[indice] / escalaZ;
			indice += 4;
			
		}

	}

   //Gauss();
	calculaNormais();

	return;
}


void Terrain::draw()
{
	float posX = 0.0f;
	float posY = 0.0f;
	int i, j;

  
  glBegin( GL_LINES) ;
  glVertex3f( 0, -10, 0);
  glVertex3f(0, 10, 0) ;
  glEnd();

	for( i=0 ; i<divX - 1 ; i++)
	{
   		glBegin (GL_QUAD_STRIP);
			posY = 0.0f;
			for (j=0; j<divY; j++)
			{	
				glNormal3f (normais[i][j][0], normais[i][j][1], normais[i][j][2]);
				glVertex3f ( posX           , posY            , terreno[i  ][j  ]) ;

				glNormal3f (normais[i+1][j][0], normais[i][j][1], normais[i][j][2]);
				glVertex3f ( posX + escalaX   , posY           ,terreno[i+1][j  ]) ;

			// Incrementa 
			posY += escalaY;
			}
		glEnd();
      // Incrementa a coluna
		posX += escalaX;
	}
	glPopMatrix();
}


void Terrain::calculaNormais (void)
{
	int i,j;

	float nx, ny;
	float norma ;
	float f0, f1;


/*
	for (i=0; i<divX; i++)
	{
		normais[i][0][0] = 0.0f;
		normais[i][0][1] = 0.0f;
		normais[i][0][2] = 1.0f;

		normais[i][divY][0] = 0.0f;
		normais[i][divY][1] = 0.0f;
		normais[i][divY][2] = 1.0f;

		normais[0][i][0] = 0.0f;
		normais[0][i][1] = 0.0f;
		normais[0][i][2] = 1.0f;

		normais[divX][i][0] = 0.0f;
		normais[divX][i][1] = 0.0f;
		normais[divX][i][2] = 1.0f;
	}
*/
	
	for (i=1; i<divX - 1; i++)
	{
		for (j=1; j<divY-1; j++)
		{	

			f0 = terreno[i][j+1];
			f1 = terreno[i][j-1];
			ny = (f1-f0)/ (2.0f * escalaY);

			f0 = terreno[i+1][j];
			f1 = terreno[i-1][j];
			nx = (f1-f0)/(2.0f * escalaX);

			norma = (float) sqrt(nx*nx * ny*ny + 1.0f);
			nx    = nx /norma;
			ny    = ny /norma;


			normais[i][j][0] = nx ;
			normais[i][j][1] = ny ;
			normais[i][j][2] = 1.0f /norma;
		}
	}

}


