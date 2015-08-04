/*============================================================================
 * 4o trabalho                                                               *
 * Curso de Visualização 3D 2005.1, prof. Waldemar Celes.                    *
 * Alunos: Mauricio Ferreira                                                 *
 *         Diogo Carneiro                                                    *
 *===========================================================================*/


/*============================================================================
 * Especificação:                                                            *
 *                                                                           *
 *  Trabalho 4: Visualização do modelo de um jeep em movimento no plano      *
 *                                                                           *
 *  Objetivo: Visualizar o modelo de um jeep em movimento sobre um plano. O  * 
 * modelo do jeep é composto por malhas de triângulos formando diversos      *
 * componentes, a saber: carroceria, bancos, alavancas de marcha, lanternas  *
 * traseiras, limpadores de parabrisa, volante, parabrisa, roda, calota e    *
 * farol. As malhas que representam esses componentes e seus respectivos     *
 * materiais são disponibilizados pelo arquivo jeep.zip. O modelo é fornecido*
 * com apenas o farol direito e apenas o conjunto roda/calota dianteiro      *
 * direito. Tanto o farol como o conjunto roda/calota devem ser              *
 * re-instanciados para a visualização completa do jeep.                     *
 *                                                                           *
 *  Dados complementares: Informações adicionais são necessárias para        *
 * visualização do modelo completo, a saber:                                 *
 *                                                                           *
 *   =>O sistema de referência local está centrado no meio do eixo traseiro, *
 *  com a origem sobre o plano de movimentação do jeep. O eixo X aponta para *
 *  a frente do jeep, o eixo Y para a esquerda e o eixo Z para cima.         *
 *                                                                           *
 *   =>O farol direito está posicionado em {2.956, 0.514, 1.074}; a distância*
 *  entre os faróis deve ser de 1,028 na direção Y.                          *
 *                                                                           *
 *   =>O conjunto roda/calota dianteiro direito está posicionado em          *
 *  {2.500, -0.644, 0.438}; a distância lateral interna entre os conjuntos   *
 *  roda/calota é de 1.288 (com espessura do pneu dada por 0.197, mas isso   *
 *  não é relevante para visualização); a distância longitudinal entre os    *
 *  eixos é de 2.500.                                                        *
 *                                                                           *
 *   =>O volante está rotacionado de 142.519o em relação ao eixo -Y; o ponto *
 *  central do volante está posicionado em {1.111, 0.495, 1.372}.            *
 *                                                                           *
 * Movimentação do jeep: A movimentação do jeep deve ser feita usando-se as  *
 *teclas de seta, a saber:                                                   *
 *                                                                           *
 *    UP:    incrementa velocidade das rodas dianteiras                      *
 *    DOWN:  decrementa velocidade das rodas dianteiras                      *
 *    LEFT:  incrementa rotação (em relação ao eixo Z) das rodas dianteiras  *
 *    RIGHT: decrementa rotação (em relação ao eixo Z) das rodas dianteiras  *
 *                                                                           *
 * Funcionalidade adicional: Deve-se prever a implementação de uma das       *
 * funcionalidades sugeridas abaixo. O aluno pode propor uma outra           *
 * funcionalidade que ache interessante para enriquecer o trabalho.          *
 *                                                                           *
 *    - Inclusão de billboard (por exemplo, colocando árvores no cenário)    *
 *    - Geração de sombra no plano do chão                                   *
 *    - Geração de reflexão no plano do chão                                 *
 *    - Uso de mapas de iluminação                                           *
 *    - Inclusão de obstáculos com detecção de colisão                       *
 *    - Implementação do algoritmo de culling                                *
 *    - Implementação do algoritmo de LOD                                    *
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
/* Métodos                                         
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


