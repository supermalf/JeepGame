/*============================================================================
 * ENGINE.H
 *
 * KEYBOARD ACTIONS, CAR FUNCTIONS, CAMERA UPDATE, COLLISIONS
 *
 *===========================================================================*/



#ifndef _ENGINE_H_
#define _ENGINE_H_

   
#include "component.h"


#define _USE_MATH_DEFINES
#define MAX_ENODES 128
#define PI 3.1415



class Engine : public Component 
{
   private:
      Item *Enodes[MAX_ENODES];
      int Free;
      int NNodes;

   // jipe
      float velocidade;
      float rad_angRoda;
      float angMerg;
      int   initCar;

      //Cameras
      int cam0;
      int cam1;
      int cam2;
      int cam3;
      int cam4;
    
      //testes
      int m;
      int tempo;

   public:
      
      Engine();
      ~Engine();
 

      int   Engine::adicionaNo( Item* no );
      Item* Engine::retiraNo( int n );
      void  aplica();
      void  aplica( unsigned char key );
      void  moveCar();
      void  setCarInitPos();
      int   getCameraNumber();
};

#endif