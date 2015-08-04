/*============================================================================
 * BILLBOARD.CPP
 *
 * 
 *
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/gl.h>

#include <math.h>
#include <stdio.h>
#include "billboard.h"
#include "glut.h"
#include "maths.h"
#include "engine_scene.h" /* XXX */
#include "dot.h"



BillBoard::BillBoard() {}

BillBoard::~BillBoard() {}




void BillBoard::draw() 
{
   float cam[3];

   cam[0] = 0;
   cam[1] = 0;
   cam[2] = 0;

   getCameraEye(&cam[0], &cam[1], &cam[2]);


	CheatCylindrical();
   //CheatSpherical();
   //Cylindrical(cam,pos);


   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(0.0f, 3.0f, 0.0f);
   glTexCoord2f(1,0);glVertex3f(0.0f, -3.0f, 0.0f);
   glTexCoord2f(1,1);glVertex3f(0.0f, -3.0f, 6.0f);
   glTexCoord2f(0,1);glVertex3f(0.0f, 3.0f, 6.0f);
   glEnd();
}




/* -------------------------------------------------------
The comments above apply in here as well but this is the
cylindrical version, i.e. the up vector is not changed
---------------------------------------------------------*/
void BillBoard::CheatCylindrical() 
{

	
	float modelview[16];
	int i,j;

	// save the current modelview matrix
	//glPushMatrix();

	// get the current modelview matrix
	glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
 
	// Note that a row in the C convention is a column 
	// in OpenGL convention (see the red book, pg.106 in version 1.2)
	// right vector is [1,0,0]  (1st column)
	// lookAt vector is [0,0,1] (3d column)
	// leave the up vector unchanged (2nd column)
	// notice the increment in i in the first cycle (i+=2)
	for( i=0; i<3; i+=2 ) 
		for( j=0; j<3; j+=1 ) {
			if ( i==j )
				modelview[i*1+j*1] = 1.0;
			else
				modelview[i*1+j*1] = 0.0;
		}

	// set the modelview matrix
	glLoadMatrixf(modelview);

   //glPopMatrix();
}



/*-----------------------------------------------------------------
The objects motion is restricted to a rotation on a predefined axis
The function bellow does cylindrical billboarding on the Y axis, i.e.
the object will be able to rotate on the Y axis only.
-----------------------------------------------------------------*/
void BillBoard::Cylindrical(float *cam, float *worldPos) 
{

	float lookAt[3]={0,0,1},objToCamProj[3],upAux[3],angleCosine;

// objToCamProj is the vector in world coordinates from the local origin to the camera
// projected in the XZ plane
	objToCamProj[0] = cam[0] - worldPos[0] ;
	objToCamProj[1] = 0;
	objToCamProj[2] = cam[2] - worldPos[2] ;


// normalize both vectors to get the cosine directly afterwards
	mathsNormalize(objToCamProj);

// easy fix to determine wether the angle is negative or positive
// for positive angles upAux will be a vector pointing in the 
// positive y direction, otherwise upAux will point downwards
// effectively reversing the rotation.

	mathsCrossProduct(upAux,lookAt,objToCamProj);

// compute the angle
	angleCosine = mathsInnerProduct(lookAt,objToCamProj);

// perform the rotation. The if statement is used for stability reasons
// if the lookAt and v vectors are too close together then |aux| could
// be bigger than 1 due to lack of precision
	if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
		glRotatef(acos(angleCosine)*180/3.14,upAux[0], upAux[1], upAux[2]);	
}



  void BillBoard::CheatSpherical() 
  {
	
	float modelview[16];
	int i,j;

	// save the current modelview matrix
	//glPushMatrix();

	// get the current modelview matrix
	glGetFloatv(GL_MODELVIEW_MATRIX , modelview);

	// undo all rotations
	// beware all scaling is lost as well 
	for( i=0; i<3; i++ ) 
		for( j=0; j<3; j++ ) {
			if ( i==j )
				modelview[i*1+j] = 1.0;
			else
				modelview[i*1+j] = 0.0;
		}

	// set the modelview with no rotations
	glLoadMatrixf(modelview);
}
