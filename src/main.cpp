/*============================================================================
 * 4o trabalho                                                               *
 * Curso de Visualiza��o 3D 2005.1, prof. Waldemar Celes.                    *
 * Alunos: Mauricio Ferreira                                                 *
 *         Diogo Carneiro                                                    *
 *===========================================================================*/


/*============================================================================
 * Especifica��o:                                                            *
 *                                                                           *
 *  Trabalho 4: Visualiza��o do modelo de um jeep em movimento no plano      *
 *                                                                           *
 *  Objetivo: Visualizar o modelo de um jeep em movimento sobre um plano. O  * 
 * modelo do jeep � composto por malhas de tri�ngulos formando diversos      *
 * componentes, a saber: carroceria, bancos, alavancas de marcha, lanternas  *
 * traseiras, limpadores de parabrisa, volante, parabrisa, roda, calota e    *
 * farol. As malhas que representam esses componentes e seus respectivos     *
 * materiais s�o disponibilizados pelo arquivo jeep.zip. O modelo � fornecido*
 * com apenas o farol direito e apenas o conjunto roda/calota dianteiro      *
 * direito. Tanto o farol como o conjunto roda/calota devem ser              *
 * re-instanciados para a visualiza��o completa do jeep.                     *
 *                                                                           *
 *  Dados complementares: Informa��es adicionais s�o necess�rias para        *
 * visualiza��o do modelo completo, a saber:                                 *
 *                                                                           *
 *   =>O sistema de refer�ncia local est� centrado no meio do eixo traseiro, *
 *  com a origem sobre o plano de movimenta��o do jeep. O eixo X aponta para *
 *  a frente do jeep, o eixo Y para a esquerda e o eixo Z para cima.         *
 *                                                                           *
 *   =>O farol direito est� posicionado em {2.956, 0.514, 1.074}; a dist�ncia*
 *  entre os far�is deve ser de 1,028 na dire��o Y.                          *
 *                                                                           *
 *   =>O conjunto roda/calota dianteiro direito est� posicionado em          *
 *  {2.500, -0.644, 0.438}; a dist�ncia lateral interna entre os conjuntos   *
 *  roda/calota � de 1.288 (com espessura do pneu dada por 0.197, mas isso   *
 *  n�o � relevante para visualiza��o); a dist�ncia longitudinal entre os    *
 *  eixos � de 2.500.                                                        *
 *                                                                           *
 *   =>O volante est� rotacionado de 142.519o em rela��o ao eixo -Y; o ponto *
 *  central do volante est� posicionado em {1.111, 0.495, 1.372}.            *
 *                                                                           *
 * Movimenta��o do jeep: A movimenta��o do jeep deve ser feita usando-se as  *
 *teclas de seta, a saber:                                                   *
 *                                                                           *
 *    UP:    incrementa velocidade das rodas dianteiras                      *
 *    DOWN:  decrementa velocidade das rodas dianteiras                      *
 *    LEFT:  incrementa rota��o (em rela��o ao eixo Z) das rodas dianteiras  *
 *    RIGHT: decrementa rota��o (em rela��o ao eixo Z) das rodas dianteiras  *
 *                                                                           *
 * Funcionalidade adicional: Deve-se prever a implementa��o de uma das       *
 * funcionalidades sugeridas abaixo. O aluno pode propor uma outra           *
 * funcionalidade que ache interessante para enriquecer o trabalho.          *
 *                                                                           *
 *    - Inclus�o de billboard (por exemplo, colocando �rvores no cen�rio)    *
 *    - Gera��o de sombra no plano do ch�o                                   *
 *    - Gera��o de reflex�o no plano do ch�o                                 *
 *    - Uso de mapas de ilumina��o                                           *
 *    - Inclus�o de obst�culos com detec��o de colis�o                       *
 *    - Implementa��o do algoritmo de culling                                *
 *    - Implementa��o do algoritmo de LOD                                    *
 *    - Movimento em terreno acidentado                                      *
 *                                                                           * 
 *===========================================================================*/


#ifdef _WIN32
#include <windows.h>
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"



#include "scene.h"
#include "engine.h"
#include "engine_scene.h"
#include "dynamics.h"

/************************************************************************/
/* M�todos                                         
/*
/************************************************************************/


Scene scene;



static void reshape (int w, int h)
{
  
    glViewport(0,0,(GLint)w,(GLint)h);

}





static void display (void)
{ 
   scene.render();

}



static void idle (void)
{
   display();

}


static void keyboard (unsigned char key, int x, int y)
{
   switch (key)
   {
      case 27: exit(0); break;
   }
}

/*

void MouseClick(int button, int state, int x, int y)
{

  if (state == GLUT_DOWN)
  {
      switch (button)
		{
    	    case GLUT_LEFT_BUTTON:
               break;
          }
  }

  if (state == GLUT_UP)
	{
      switch (button)
		{
          	case GLUT_LEFT_BUTTON:
              break;
       }
  }

}

void MouseMotion(int x, int y){ }

*/



int main ( int argc, char* argv[] )
{ 
   int SCREEN_WIDTH  = 800;
	int SCREEN_HEIGHT = 600;


   MakeScene( &scene );


   // open GLUT 
   glutInit( &argc, argv ) ;
   glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB ) ;
  	
   glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); 

   // create window
   glutCreateWindow( "Trab4 - Mauricio & Diogo" ) ;
   glutReshapeFunc( reshape ) ; 
   glutDisplayFunc( display ) ; 
   glutKeyboardFunc(keyboard ) ;

   //glutMouseFunc(MouseClick);
 	//glutMotionFunc(MouseMotion);

   glutIdleFunc(idle);
   carInit();

   // interact... 
   glutMainLoop();

   return 0 ;
}


