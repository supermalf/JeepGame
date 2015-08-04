/*============================================================================
 * ENGINE_SCENE.CPP
 *
 *
 *===========================================================================*/



#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>

#include "engine_scene.h"
#include "msh.h"
#include "font.h"
#include "location.h"
#include "scene.h"
#include "plight.h"
#include "slight.h"
#include "dlight.h"
#include "perspective.h"
#include "entity.h"
#include "material.h"
#include "terrain.h"
#include "texture.h"
#include "billboard.h"
#include "engine.h"
#include "dot.h"
#include "fog.h"
#include "dynamics.h"

#define _LIGHT         0
#define _ALAVANCAS     1
#define _RODA          2
#define _PAINEL        3
#define _BANCO         4
#define _CARROCERIA    5
#define _CALOTA        6
#define _VOLANTE       7
#define _LIMPADOR      8
#define _PARABRISA     9
#define _LANTERNAS    10
#define _LANTERNAS_ON 11
#define _FAROL        12
#define _FAROL_ON     13



/************************************************************************/
/* Cameras Definitions                                         
/*
/************************************************************************/

Entity      *e_cameras; 
Perspective *camera0;
Perspective *camera1;
Perspective *camera2;
Perspective *camera3;
Perspective *camera4;


float eye[5][4]    ={{ -15.00f,  00.00f, 08.00f, 01.00f },
                     {  15.00f,  00.00f, 08.00f, 01.00f },
                     { -10.00f,  28.00f, 08.00f, 01.00f },
                     { -10.00f, -28.00f, 08.00f, 01.00f },
                     { -15.00f,  00.00f, 03.00f, 01.00f } };

float center[5][4] ={{  00.00f,  00.00f, 01.00f, 01.00f },
                     {  00.00f,  00.00f, 01.00f, 01.00f },
                     {  00.00f,  03.00f, 01.50f, 01.00f }, 
                     {  00.00f, -03.00f, 01.50f, 01.00f },
                     {  00.00f,  00.00f, 01.00f, 01.00f } };

float up[5][4]     ={{  03.00f,  00.00f, 01.00f, 01.00f },
                     { -03.00f,  00.00f, 01.00f, 01.00f },
                     {  01.00f, -02.80f, 01.00f, 01.00f },
                     {  01.00f,  02.80f, 01.00f, 01.00f },
                     {  01.00f,  00.00f, 00.00f, 01.00f } };

float fovy [5]     = {  60.00f, 
                        40.00f,
                        10.00f,
                        10.00f,
                        30.00f };

float zNear [5] =    {  01.00f,
                        01.00f,
                        01.00f,
                        01.00f,
                        01.00f };

float zFar [5]  =    {  500.00f,
                        500.00f,
                        500.00f,
                        500.00f,
                        500.00f };



/************************************************************************/
/* Light Definitions                                         
/*
/************************************************************************/
Entity *e_lights;
Plight *light0;
Slight *light1;

float Position[3][4]   =  { { 10000.000000f ,100000.000000f ,10000.0000f, 1.0f },
                              { 2.000000f ,0.000000f ,150.0000f, 1.0f },
                              { -100.0f ,-100.000000f ,-5050.0000f, 1.0f }};




/************************************************************************/
/* Colors Definitions                                         
/*
/************************************************************************/
                          

//Ambient
float Amb[4]=        { 0.20f ,0.20f ,0.20f, 1.00f };

//Diffuse
float Dif[14][4] = { { 0.60f ,0.60f ,0.60f, 0.30f },  //_LIGHT
                     { 0.30f ,0.30f ,0.30f, 1.00f },  //_ALAVANCAS
                     { 0.11f ,0.11f ,0.11f, 1.00f },  //_RODA
                 	   { 0.57f ,0.48f ,0.34f, 1.00f },  //_PAINEL
                 	   { 0.57f ,0.48f ,0.34f, 1.00f },  //_BANCO
                 	   { 0.22f ,0.20f ,0.72f, 1.00f },  //_CARROCERIA
                 	   { 0.70f ,0.70f ,0.70f, 1.00f },  //_CALOTA
                     { 0.30f ,0.30f ,0.30f, 1.00f },  //_VOLANTE
                     { 0.60f ,0.60f ,0.60f, 1.00f },  //_LIMPADOR
                     { 0.60f ,0.60f ,0.60f, 0.30f },  //_PARABRISA
                     { 0.50f ,0.20f ,0.20f, 0.80f },  //_LANTERNAS
                     { 5.90f ,0.20f ,0.20f, 0.80f },  //_LANTERNAS_ON
                     { 0.50f ,0.50f ,0.20f, 0.80f },  //_FAROL
                     { 7.90f ,7.90f ,0.20f, 0.80f }}; //_FAROL_ON

//Specular
float Spe[14][4] = { { 0.20f ,0.20f ,0.20f, 1.0f },   //_LIGHT
                     { 0.10f ,0.10f ,0.10f, 1.0f },   //_ALAVANCAS
                     { 0.10f ,0.10f ,0.10f, 1.0f },   //_RODA
                     { 0.50f ,0.50f ,0.00f, 1.0f },   //_PAINEL
                     { 0.50f ,0.50f ,0.00f, 1.0f },   //_BANCO
                     { 0.90f ,0.90f ,0.90f, 1.0f },   //_CARROCERIA
                     { 0.15f ,0.15f ,0.15f, 1.0f },   //_CALOTA
                     { 0.10f ,0.10f ,0.10f, 0.0f },   //_VOLANTE
                     { 0.20f ,0.20f ,0.20f, 1.0f },   //_LIMPADOR
                     { 0.20f ,0.20f ,0.20f, 1.0f },   //_PARABRISA
                     { 0.80f ,0.80f ,0.80f, 1.0f },   //_LANTERNAS
                     { 0.80f ,0.80f ,0.80f, 1.0f },   //_LANTERNAS_ON
                     { 0.90f ,0.90f ,0.90f, 1.0f },   //_FAROL
                     { 0.90f ,0.90f ,0.90f, 1.0f }};  //_FAROL_ON

//Shininess
float Shi[14] =      { 0.00f,    //_LIGHT
                       0.00f,    //_ALAVANCAS
                       0.82f,    //_RODA
                       0.18f,    //_PAINEL
                       0.10f,    //_BANCO
                       0.31f,    //_CARROCERIA
                       0.80f,    //_CALOTA
                       0.00f,    //_VOLANTE
                       0.00f,    //_LIMPADOR
                       0.00f,    //_PARABRISA
                       0.31f,    //_LANTERNAS
                       0.31f,    //_LANTERNAS_ON
                       0.31f,    //_FAROL
                       0.31f };  //_FAROL_ON


/************************************************************************/
/* Public                                         
/*
/************************************************************************/

Engine *engine;
Entity *e_jeep; 
Entity *e_Lanternas_ON;
Entity *e_Lanternas_OFF;
Entity *e_Farol_d_ON;
Entity *e_Farol_d_OFF;
Entity *e_Farol_e_ON;
Entity *e_Farol_e_OFF;
Terrain *Ter_Track;

 

int   filtros[2]     = { GL_LINEAR, GL_LINEAR } ; 
int   wraps[2]       = { GL_CLAMP,  GL_CLAMP  } ; 
float vetores[2][4]  = { {0, 1.0f/256.0f, 0, 0},
                         {1.0f/256.0f, 0, 0, 0} } ;

int   planos[2]      = { GL_OBJECT_PLANE,  GL_OBJECT_PLANE  } ;
int   modo_gens[2]   = { GL_OBJECT_LINEAR, GL_OBJECT_LINEAR } ;

int   wraps2[2]       = { GL_REPEAT,  GL_REPEAT  } ; 
int   planosp[2]      = { GL_OBJECT_PLANE,  GL_OBJECT_PLANE  } ;
int   modo_gensp[2]   = { GL_OBJECT_LINEAR, GL_OBJECT_LINEAR } ; 

float vetores2[2][4]  = { {0,  1.0f/6.0f,0, 0}, {0, 0, 1.0f/6.0f,   0} 
                        };

float vetores3[2][4]  = {  {0,  1.0f/6.0f,0, 0},
                           {0, 0, 1.0f/4.0f,   0} } ;


int   filtros_tree[2]     = { GL_NEAREST, GL_LINEAR } ; 

int   filtrosp[2]     = { GL_LINEAR, GL_LINEAR } ; 
int   wrapsp[2]       = { GL_REPEAT,  GL_REPEAT  } ; 
float vetoresp[2][4]  = { {0, 1.0f/.02, 0, .500},
                         { 0, 0,1.0f/.02, .500} } ;

/************************************************************************/
/* Methods                                         
/*
/************************************************************************/


void setCamera(int camera)
{
   if(camera == 0)
      e_cameras->replace(0,camera0);

   if(camera == 1)
      e_cameras->replace(0,camera1);

   if(camera == 2)
      e_cameras->replace(0,camera2);

   if(camera == 3)
      e_cameras->replace(0,camera3);

   if(camera == 4)
      e_cameras->replace(0,camera4);
}


void getCameraEye(float *eyeX, float *eyeY, float *eyeZ)
{
   int camera = engine->getCameraNumber();
   
     Dot *Eye;
     Dot *Center;
     Dot *Up;

   
   if(camera == 0)
      camera0->getPosition(&Eye, &Center, &Up);

   else if(camera == 1)
      camera1->getPosition(&Eye, &Center, &Up);

   else if(camera == 2)
      camera2->getPosition(&Eye, &Center, &Up);

   else if(camera == 3)
      camera3->getPosition(&Eye, &Center, &Up);

   else if(camera == 4)
      camera4->getPosition(&Eye, &Center, &Up);  

   else
      return;
   
   float x,y,z,w;
   Eye->getPosition(&x,  &y, &z, &w);

   *eyeX = x;
   *eyeY = y;
   *eyeZ= z;


}


bool getTerrainCollision(float x, float y, int *terrainSide)
{
   float z = Ter_Track->PegaAltura(x,y);

   //Frente
   if(((x>5.0f)&&(x<9.0f)) || ((x>235.0f)&&(x<255.0f)))
      *terrainSide = 0;

   //Lateral
   else if(((y>5.0f)&&(y<9.0f)) || ((y>235.0f)&&(y<255.0f)))
      *terrainSide = 1;

   //Terrain
   else
      *terrainSide = 2;

      //printf("X: %f [=] Y: %f\n",x,y);

   if (z>0.0f)
   {  
      return true;
   }


   //bug
   if (((x>242.0f)||(x<4.5f))||((y>242.0f)||(y<8.5f)))
   {

      
      *terrainSide = 0;
      return true;

   }





  return false;

      //printf("Altura: %f", z);
}

bool getTerrainOutCollision(float x, float y)
{


   if ((x>0.0f)||(x<6.4f)||(y<0.0f)||(y>1024.0f))
      return true;

   else
      return false;

      //printf("Altura: %f", z);
}



void TurnOnBrakeLights()
{
   e_jeep->replace(0,e_Lanternas_ON);     
}

void TurnOffBrakeLights()
{
   e_jeep->replace(0,e_Lanternas_OFF);   
}

void TurnOnFrontLights()
{
   e_jeep->replace(1,e_Farol_e_ON);
   e_jeep->replace(2,e_Farol_d_ON);

   light1->setLightState(1); //Off
}

void TurnOffFrontLights()
{
   e_jeep->replace(1,e_Farol_e_OFF);
   e_jeep->replace(2,e_Farol_d_OFF);

   light1->setLightState(0); //Off
}



void MakeScene ( Scene *scene )
{

   //Creating Perspective Cameras
   camera0 = new Perspective(fovy[0], zNear[0], zFar[0], eye[0], center[0], up[0]);
   camera1 = new Perspective(fovy[1], zNear[1], zFar[1], eye[1], center[1], up[1]);
   camera2 = new Perspective(fovy[2], zNear[2], zFar[2], eye[2], center[2], up[2]);
   camera3 = new Perspective(fovy[3], zNear[3], zFar[3], eye[3], center[3], up[3]);
   camera4 = new Perspective(fovy[4], zNear[4], zFar[4], eye[4], center[4], up[4]);



   //Creating Light

   //Ambient Light
  light0 = new Plight(GL_LIGHT0, Position[0], Amb, Dif[_LIGHT], Spe[_LIGHT]);

  //Car HeadLight
  light1 = new Slight(GL_LIGHT1, Position[1], Amb, Dif[_LIGHT], Spe[_LIGHT], 90.0f);
 
 
   //Msh
   Msh *Msh_Carroceria = new Msh( "msh/Carroceria.msh");
   Msh *Msh_Banco      = new Msh( "msh/Banco.msh");
   Msh *Msh_Lanternas  = new Msh( "msh/Lanternas.msh");
   Msh *Msh_Alavancas  = new Msh( "msh/Alavancas.msh");
   Msh *Msh_Roda       = new Msh( "msh/Roda.msh");
   Msh *Msh_Limpador   = new Msh( "msh/Limpador.msh");
   Msh *Msh_Volante    = new Msh( "msh/Volante.msh");
   Msh *Msh_Farol      = new Msh( "msh/Farol.msh");
   Msh *Msh_Parabrisa  = new Msh( "msh/Parabrisa.msh");
   Msh *Msh_Painel     = new Msh( "msh/Painel.msh");
   Msh *Msh_Calota     = new Msh( "msh/Calota.msh");
   //Msh *Msh_Tree     = new Msh( "msh/Tree.msh");

   //Font
   Font *Fnt_HelpMenu = new Font();


   //Matetial
   Material *Mat_Carroceria   = new Material(NULL, Dif[_CARROCERIA]   , Spe[_CARROCERIA]   , NULL, Shi[_CARROCERIA]);
   Material *Mat_Banco        = new Material(NULL, Dif[_BANCO]        , Spe[_BANCO]        , NULL, Shi[_BANCO]);
   Material *Mat_Lanternas    = new Material(NULL, Dif[_LANTERNAS]    , Spe[_LANTERNAS]    , NULL, Shi[_LANTERNAS]);
   Material *Mat_Lanternas_ON = new Material(NULL, Dif[_LANTERNAS_ON] , Spe[_LANTERNAS_ON] , NULL, Shi[_LANTERNAS_ON]);
   Material *Mat_Alavancas    = new Material(NULL, Dif[_ALAVANCAS]    , Spe[_ALAVANCAS]    , NULL, Shi[_ALAVANCAS]);
   Material *Mat_Roda         = new Material(NULL, Dif[_RODA]         , Spe[_RODA]         , NULL, Shi[_RODA]);
   Material *Mat_Limpador     = new Material(NULL, Dif[_LIMPADOR]     , Spe[_LIMPADOR]     , NULL, Shi[_LIMPADOR]);
   Material *Mat_Volante      = new Material(NULL, Dif[_VOLANTE]      , Spe[_VOLANTE]      , NULL, Shi[_VOLANTE]);
   Material *Mat_Farol        = new Material(NULL, Dif[_FAROL]        , Spe[_FAROL]        , NULL, Shi[_FAROL]);
   Material *Mat_Farol_ON     = new Material(NULL, Dif[_FAROL_ON]     , Spe[_FAROL_ON]     , NULL, Shi[_FAROL_ON]);
   Material *Mat_Parabrisa    = new Material(NULL, Dif[_PARABRISA]    , Spe[_PARABRISA]    , NULL, Shi[_PARABRISA]);
   Material *Mat_Painel       = new Material(NULL, Dif[_PAINEL]       , Spe[_PAINEL]       , NULL, Shi[_PAINEL]);
   Material *Mat_Calota       = new Material(NULL, Dif[_CALOTA]       , Spe[_CALOTA]       , NULL, Shi[_CALOTA]);
   Material *Mat_Track        = new Material(NULL, Dif[_CALOTA]      , Spe[_CALOTA]      , NULL, Shi[_CALOTA]);
   Material *Mat_Tree          = new Material(NULL, Dif[_PARABRISA]      , Spe[_PARABRISA]      , NULL, Shi[_PARABRISA]);
   

   //BillBoard
   BillBoard *Bil_Tree = new BillBoard(); 
   

   //Fog
   Fog *fog = new Fog();
         

   //Track Terrain
   Ter_Track = new Terrain( "tex/pistaBump.bmp" );

   
   //Textures
   Texture *Tex_Track = new Texture("tex/pista.bmp", NULL, Mat_Track, 2, 0 ,0, 
     GL_MODULATE,  true, filtros, wraps, vetores, planos, modo_gens, NULL ); 
     
  

   float coords[4][2]={{-1,-1},{0,1},{1,0},{1,0}};
   GLfloat coords2[8]={0,0,1,0,1,1,0,1};



Texture *Tex_Tree  = new Texture("tex/tree.bmp","tex/tree_alfa.bmp",  NULL, 2, 0 ,0, 
    GL_MODULATE, false, filtrosp, wrapsp, vetores2, planosp, modo_gensp, coords2 ) ; 
 	         
  

   //Locations
   Location *Loc_Jeep      = new Location( 0,     0,      0,  0,  0, 0, 1,  1.25, 0, 0 );
   Location *Loc_Camera    = new Location( 0,     0,      0,  0,  0, 0, 1,  0,    0, 0 );
   Location *Loc_Roda_dd   = new Location( 0,     0,      0,  0,  0, 0, 1,  0,    0, 0 );
   Location *Loc_Roda_de   = new Location( 0,     1.288f, 0,  0,  0, 0, 1,  0,    0, 0 );
   Location *Loc_Roda_td   = new Location( -2.5f, 0,      0,  0,  0, 0, 1,  0,    0, 0 );
   Location *Loc_Roda_te   = new Location( -2.5f, 1.288f, 0,  0,  0, 0, 1,  0,    0, 0 );
   Location *Loc_Volante   = new Location(  0,    0,      0,  0,  0, 0, 1,  0,    0, 0 );
   Location *Loc_Farol_e   = new Location(  0,    1,      0,  0,  0, 0, 1,  0,    0, 0 );
   Location *Loc_Tree      = new Location( 50,   150,     0,  0,  0, 0, 1,  0,    0, 0 );


   //Entity    
   Entity *e_Fog           = new Entity( NULL, fog, NULL);
   Entity *e_Track         = new Entity( NULL, Tex_Track, Ter_Track);
   Entity *e_Tree          = new Entity( Loc_Tree,  Tex_Tree,    Bil_Tree );
   Entity *e_HelpMenu      = new Entity( NULL,           NULL,             Fnt_HelpMenu );
   Entity *e_Carroceria    = new Entity( NULL,           Mat_Carroceria,   Msh_Carroceria );
   Entity *e_Banco         = new Entity( NULL,           Mat_Banco,        Msh_Banco );
   Entity *e_Alavancas     = new Entity( NULL,           Mat_Alavancas,    Msh_Alavancas );
   Entity *e_Roda_dd       = new Entity( Loc_Roda_dd,    Mat_Roda,         Msh_Roda );
   Entity *e_Roda_de       = new Entity( Loc_Roda_de,    Mat_Roda,         Msh_Roda );
   Entity *e_Roda_td       = new Entity( Loc_Roda_td,    Mat_Roda,         Msh_Roda );
   Entity *e_Roda_te       = new Entity( Loc_Roda_te,    Mat_Roda,         Msh_Roda );
   Entity *e_Limpador      = new Entity( NULL,           Mat_Limpador,     Msh_Limpador );
   Entity *e_Volante       = new Entity( Loc_Volante,    Mat_Volante,      Msh_Volante );
   Entity *e_Parabrisa     = new Entity( NULL,           Mat_Parabrisa,    Msh_Parabrisa );
   Entity *e_Painel        = new Entity( NULL,           Mat_Painel,       Msh_Painel );
   Entity *e_Calota_dd     = new Entity( NULL,           Mat_Calota,       Msh_Calota );
   Entity *e_Calota_de     = new Entity( NULL,           Mat_Calota,       Msh_Calota );
   Entity *e_Calota_td     = new Entity( NULL,           Mat_Calota,       Msh_Calota );
   Entity *e_Calota_te     = new Entity( NULL,           Mat_Calota,       Msh_Calota ); 
           e_Farol_d_ON    = new Entity( NULL,           Mat_Farol_ON,     Msh_Farol );
           e_Farol_d_OFF   = new Entity( NULL,           Mat_Farol,        Msh_Farol );
           e_Farol_e_ON    = new Entity( Loc_Farol_e,    Mat_Farol_ON,     Msh_Farol );
           e_Farol_e_OFF   = new Entity( Loc_Farol_e,    Mat_Farol,        Msh_Farol );
           e_Lanternas_ON  = new Entity( NULL,           Mat_Lanternas_ON, Msh_Lanternas );
           e_Lanternas_OFF = new Entity( NULL,           Mat_Lanternas,    Msh_Lanternas );  
           e_cameras       = new Entity( Loc_Camera,     NULL,             NULL );
           e_jeep          = new Entity( Loc_Jeep,       NULL,             NULL );
           e_lights        = new Entity( NULL,           NULL,             NULL );


   //Engine
   engine = new Engine();
   engine->adicionaNo(e_jeep);      /*00*/
   engine->adicionaNo(e_cameras);   /*01*/
   engine->adicionaNo(e_Roda_dd );  /*02*/
   engine->adicionaNo(e_Roda_td );	/*03*/
   engine->adicionaNo(e_Roda_de );	/*04*/
   engine->adicionaNo(e_Roda_te );	/*05*/
   engine->adicionaNo(e_Volante );	/*06*/   
   engine->adicionaNo(e_lights );	/*07*/   
   scene->setEngine(engine);

   


   //Graph
   scene->add( e_cameras );         /*00*/
   scene->add( e_lights );          /*01*/
   scene->add( e_jeep );            /*02*/
   scene->add( e_Track );           /*03*/   e_Track->setType(0);
   scene->add( e_Tree );            /*04*/   e_Tree->setType(2); 
   scene->add( e_Fog );             /*05*/
   scene->add( e_HelpMenu );        /*06*/   e_HelpMenu->setType(1);


   //Lights
   e_lights->add( light0 );         /*00*/
   e_lights->add( light1 );         /*01*/

  //Camera
   e_cameras->add( camera0 );       /*00*/


   //Jeep
                                             e_Lanternas_ON->setType(0);
   e_jeep->add( e_Lanternas_OFF );  /*00*/   e_Lanternas_OFF->setType(0);
                                             e_Farol_e_ON->setType(1);
   e_jeep->add( e_Farol_e_OFF);     /*01*/   e_Farol_e_OFF->setType(1);
                                             e_Farol_d_ON->setType(1);
   e_jeep->add( e_Farol_d_OFF );    /*02*/   e_Farol_d_OFF->setType(1);
   e_jeep->add( e_Painel );         /*03*/   e_Painel->setType(0);
   e_jeep->add( e_Volante );        /*04*/   e_Volante->setType(0);
   e_jeep->add( e_Banco );          /*05*/   e_Banco->setType(0);
   e_jeep->add( e_Carroceria );     /*06*/   e_Carroceria->setType(0);
   e_jeep->add( e_Alavancas );      /*07*/   e_Alavancas->setType(0);
   e_jeep->add( e_Roda_dd );        /*08*/   e_Roda_dd->setType(0);
   e_jeep->add( e_Roda_de );        /*09*/   e_Roda_de->setType(0);
   e_jeep->add( e_Roda_td );        /*10*/   e_Roda_td->setType(0);
   e_jeep->add( e_Roda_te );        /*11*/   e_Roda_te->setType(0);
   e_jeep->add( e_Limpador );       /*12*/   e_Limpador->setType(0);
   e_jeep->add( e_Parabrisa  );     /*12*/   e_Parabrisa->setType(1);
   e_jeep->setType(0);


   //Calotas
   e_Roda_dd->add( e_Calota_dd );   /*00*/   e_Calota_dd->setType(0);
   e_Roda_de->add( e_Calota_de );   /*00*/   e_Calota_de->setType(0);
   e_Roda_td->add( e_Calota_td );   /*00*/   e_Calota_td->setType(0);
   e_Roda_te->add( e_Calota_te );   /*00*/   e_Calota_te->setType(0);
   
}




