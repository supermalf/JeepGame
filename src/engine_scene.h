/*============================================================================
 * ENGINE_SCENE.H
 *
 * 
 *
 *===========================================================================*/



#include "Scene.h"
#include "dot.h"


void MakeScene ( Scene  *scene );
void setCamera(int camera);
void TurnOnBrakeLights();
void TurnOffBrakeLights();
void TurnOnFrontLights();
void TurnOffFrontLights();
void getCameraEye(float *eyeX, float *eyeY, float *eyeZ);

bool getTerrainCollision(float x, float y, int *terrainSide);
bool getTerrainOutCollision(float x, float y);