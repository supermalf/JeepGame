/*============================================================================
 * ENGINE.CPP
 *
 * KEYBOARD ACTIONS, CAR FUNCTIONS, CAMERA UPDATE, COLLISIONS
 *
 *===========================================================================*/



#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <gl/gl.h>
#include "glut.h"


#include "engine.h"
#include "engine_scene.h"
#include "entity.h"
#include "location.h"
#include "dynamics.h"
#include "wheels.h"



Engine::Engine()
{
   int n ;

   for( n=0 ; n<MAX_ENODES ; n++ )
   {
      Enodes[n] = NULL ;
   }

   Free = 0 ;
   NNodes = 0 ;
   velocidade = 0 ;
   rad_angRoda = 0;
   angMerg=0;

   initCar=1;

   cam1=cam2=cam3=cam4=0;
   cam0=1;

}


Engine::~Engine() {}


int Engine::adicionaNo(Item* node) 
{
   if(NNodes < MAX_FILHOS )
   {
      int n ;
      for( n=Free+1 ; n!=Free ; n=(n+1)%MAX_FILHOS )
      {
         if( !Enodes[n-1] )
         {
            Enodes[n-1] = node ;
            NNodes++;
            Free = n ;
            return n-1 ;
         }
      }
   }
   return -1 ;
}


Item* Engine::retiraNo( int n )
{
   if( n>0 && n<MAX_FILHOS) 
   {
      Item* no = Enodes[n] ;
      Enodes[n] = NULL ;
      NNodes -- ;
      return no ;
   }
   return NULL ;
}


void Engine::setCarInitPos()
{

   if(initCar)
      carSetPos(18,137);

   initCar=0;
}


int Engine::getCameraNumber()
{
   if(cam0)
      return 0;

   else if(cam1)
      return 1;

   else if(cam2)
      return 2;

   else if(cam3)
      return 3;

   else if(cam4)
      return 4;

   else
   {
      printf("\n** Error: Invalid Camera Id! **");
      return -1; //Error!
   }
}


void Engine::aplica(void)
{

   if (( GetKeyState (VK_F1) < 0 ) && (cam0 == 0))
   {

      cam0 = 1;
      cam1 = 0;
      cam2 = 0;
      cam3 = 0;
      cam4 = 0;

      setCamera(0);
    
   }

   if (( GetKeyState (VK_F2) < 0 ) && (cam1 == 0))
   {

      cam0 = 0;
      cam1 = 1;
      cam2 = 0;
      cam3 = 0;
      cam4 = 0;

      setCamera(1);

   }

   if (( GetKeyState (VK_F3) < 0 ) && (cam2 == 0))
   {

      cam0 = 0;
      cam1 = 0;
      cam2 = 1;
      cam3 = 0;
      cam4 = 0;

      setCamera(2);

   }

   if (( GetKeyState (VK_F4) < 0 ) && (cam3 == 0))
   {

      cam0 = 0;
      cam1 = 0;
      cam2 = 0;
      cam3 = 1;
      cam4 = 0;

      setCamera(3);

   }

   if (( GetKeyState (VK_F5) < 0 ) && (cam4 == 0))
   {

      cam0 = 0;
      cam1 = 0;
      cam2 = 0;
      cam3 = 0;
      cam4 = 1;

      setCamera(4);

   }

   if ( GetKeyState ('L') > 0 )
   {
      TurnOnFrontLights();
   }

   else
   {
      TurnOffFrontLights();
   }






	// Pega a entrada de dados pelo teclado
   if ( GetKeyState (VK_UP) < 0 )
   {  // Acelerador
		velocidade +=70.0f ;  

      if(velocidade >700.0f )
		   velocidade = 700.0f ;

     
   }
   else
   {  //Solto
		velocidade *= 0.975f;
   }
		
	if( GetKeyState (VK_RIGHT) < 0 )
   {
      rad_angRoda += 0.05f ;
      if( rad_angRoda > PI/4.0f )
         rad_angRoda = PI/4.0f ;
   }
   else
	{
		rad_angRoda *= 0.96f ;
	}
	if ( GetKeyState (VK_LEFT) < 0 )
   {
      rad_angRoda -= 0.05f ;
      if( rad_angRoda <  -PI/4.0f )
         rad_angRoda = -PI/4.0f  ;
   }
   else
	{
		rad_angRoda *= 0.96f ;
	}


	carSetThrottle (velocidade);
	carSetSteerAngle (rad_angRoda);


	if (GetKeyState (VK_DOWN) < 0 )
	{
		  if(velocidade < 1)
        {
         velocidade-=300.0f;
        }

         if(velocidade < -600.0f )
		      velocidade = -600.0f;
     
	}
	
 

	if (GetKeyState (VK_SPACE) < 0 )
	{
       carBreak ();
       TurnOnBrakeLights(); 
	}
	
   else
      TurnOffBrakeLights();



   if ((  GetKeyState ('Q') < 0 ) )
   {
      carStop ();
   }


   if ((  GetKeyState ('D') < 0 ) )
   {
      float x; 
      float y;
      getCarPos(&x,&y);
      float angle = carGetAngle();

      //printf("POS: %f,%f\n",x,y);
      //printf("ANGLE: %f,\n",angle);

      //if ()

     // getTerrainCollision(x,y);

   }


    //colisao
   float x, y;
   int terrainSide=0;
   getCarPos(&x,&y);

   if((getTerrainCollision(x,y,&terrainSide))) //||(getTerrainOutCollision(x,y)))
   {
      if(terrainSide==1) //Frente
         carCrashY ();

      else if(terrainSide==0) //Lateral
         carCrashX ();

      else if(terrainSide==2)//terreno
         carCrash ();
      






   }

  

	// Calcula os parametros do carro
   carUpdate();
	
  moveCar();

  //Set init position
  setCarInitPos();

}


void Engine::moveCar()
{


   Location* t;
   	float trans_x, trans_y, trans_z ;
      float  rot_ang, rot_x, rot_y, rot_z , rotpos_x, rotpos_y, rotpos_z ;

  float ang ,vx  ,vy; 

  // Pega a possição do Carro
  t = (Location*)((Entity*)Enodes[0])->getTransformation() ;
  t->getTranslacao( &trans_x, &trans_y, &trans_z ) ;
  t->getRotacao   ( &rot_ang, &rot_x, &rot_y, &rot_z ,
                    &rotpos_x, &rotpos_y, &rotpos_z ) ;


   // Pega Posiçao nova do Jeep
  ang = carGetAngle()* (-180.0f/(float)PI)+ 90.0f;   
  carGetPos (&vx, &vy);

  // Atualiza Jeep
  t->setTranslacao ( vx, vy, trans_z);
  t->setRotacao    ( ang,
                     0, 0, 1 ,
                     rotpos_x, rotpos_y, rotpos_z ) ;


   // Camera
  t = (Location*)((Entity*)Enodes[1])->getTransformation() ;

  t->getRotacao   ( &rot_ang, &rot_x, &rot_y, &rot_z ,
                    &rotpos_x, &rotpos_y, &rotpos_z ) ;

    // Amortiza câmera
  rot_ang = rot_ang + (ang - rot_ang ) * 0.025f;

  // Atualiza Camera
  t->setTranslacao( vx, vy, trans_z ) ;
  t->setRotacao   ( rot_ang, rot_x, rot_y, rot_z ,
                   rotpos_x, rotpos_y, rotpos_z ) ;


  angMerg += velocidade*25.0f/3.14f ;

  // Rodas
  if( Enodes[2] && Enodes[3] && Enodes[4] && Enodes[5] )
  {
     transforma_rodas(  angMerg, rad_angRoda,
                       (Location*)((Entity*)Enodes[2])->getTransformation(),
                       (Location*)((Entity*)Enodes[3])->getTransformation(),
                       (Location*)((Entity*)Enodes[4])->getTransformation(),
                       (Location*)((Entity*)Enodes[5])->getTransformation()
                      );
  }


  // Volante
  if( Enodes[6] )
  {
     Location* t_vol = (Location*)((Entity*)Enodes[6])->getTransformation() ;
     t_vol->setRotacao( rad_angRoda*180/PI, -cos(-142.519f*PI/180),0,sin(-142.519f*PI/180),1.111f, 0.495f, 1.372f) ;
  }
}


