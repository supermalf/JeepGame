/*============================================================================
 * MSH.CPP
 *
 * MANIPULATES .msh FILES AND DRAW OBJECTS
 *
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/gl.h>

#include <stdio.h>
#include "msh.h"
#include "glut.h"

Msh::Msh()
{
   NVertexes  = 0;
   NTriangles = 0;
   Vertexes   = NULL;
   Normals    = NULL;
   Ids        = NULL;
}


Msh::Msh( char* filename )
{
   loadFile( filename );
}


Msh::~Msh()
{
   delete Vertexes;
   delete Ids;      
}


void Msh::loadFile( char *filename)
{
   FILE *file;
   int id;

   file = fopen( filename, "rt");

   if( !file )
   {
      printf("** Error: Could't open the %s file! **\n", filename);
      return;
   }

   if( fscanf(file, "%d %d\n", &NVertexes, &NTriangles) == 2)
   {
      Vertexes = new float[3*NVertexes];
      Normals  = new float[3*NVertexes]; /* XXX */
      Ids      = new unsigned int[3*NTriangles];

      if( Vertexes && Normals && Ids )
      {
         int j ;
         for( j=0 ; j<NVertexes ; j++ )
         {
            fscanf(file, "%d %f %f %f %f %f %f\n", &id, &Vertexes[j*3], &Vertexes[j*3+1], &Vertexes[j*3+2],
                                                        &Normals[j*3],  &Normals[j*3+1] , &Normals[j*3+2] );
         }
         
         for( j=0 ; j<NTriangles ; j++ )
         {
            fscanf(file, "%d %d %d %d\n",&id, &Ids[j*3], &Ids[j*3+1], &Ids[j*3+2] );
         }

         fclose( file );

         return;
      }      
   }

   fclose( file );

   NVertexes  = 0;
   NTriangles = 0;
   delete Vertexes;   
   delete Normals;
   delete Ids;
   Vertexes   = NULL;
   Normals    = NULL;
   Ids        = NULL;
}


void Msh::draw()
{
   glVertexPointer( 3, GL_FLOAT, 3*sizeof(float), Vertexes );
   glNormalPointer(    GL_FLOAT, 3*sizeof(float), Normals  );

   glEnable( GL_VERTEX_ARRAY );
   glEnable( GL_NORMAL_ARRAY );

   glDrawElements( GL_TRIANGLES, 3*NTriangles, GL_UNSIGNED_INT, Ids );

   //write();
}
   


void Msh::write()
{
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);
   
   glColor3f(1.0f,1.0f,1.0f);

   glRasterPos3d(0.3,-0.61,0.8);
   char*s="==Msh==";
      for (int i=0; s[i]; i++)
     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}
