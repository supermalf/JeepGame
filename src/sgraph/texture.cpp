#ifdef _WIN32
#include <windows.h>
#endif


#include <stdlib.h>
#include <gl/gl.h>

#include "texture.h"
#include "material.h"
#include "image.h"


   

Texture::Texture( void ) 
{
   material = NULL ;

   // TEXTURA
   id           = 0 ;
   largura      = 0 ;
   altura       = 0 ;
   profundidade = 0 ;
   n_dimensoes  = 0 ;
   n_mipmap     = 0 ;
   texturas     = NULL ;

   // COORDENADAS
   coord_automatica = false ;
   modo = GL_REPLACE ;
   filtro_mag = GL_LINEAR ;
   filtro_min = GL_LINEAR ;
   wrap_s = GL_CLAMP ;
   wrap_t = GL_CLAMP ;

   // GERACAO AUTOMATICA
   int i ;
   for( i=0; i<4 ; i++)
   {
      vetor_s[i] = 0 ;
      vetor_t[i] = 0 ;
   }

   plano_s = GL_OBJECT_PLANE ;
   plano_t = GL_OBJECT_PLANE ;

   modo_geracao_s = GL_OBJECT_LINEAR;
   modo_geracao_t = GL_OBJECT_LINEAR;

   coordenadas = NULL ;
}
/*--    -------------------------------------------------------------------*/
Texture::Texture( char* arquivo, char *arq_alfa, Material* mat, int dim, int camadas,
                 int n_mm, int md, bool auto_gen,
                 int *filtros, int *wraps, float vetores[2][4], int *planos, 
                 int* modo_gens, float*coords  ) 
{
   id = 0 ;
   criada = false;

      switch (dim)
      {
         case 1:  carrega_1D( arquivo, n_mm ) ; break ;
         case 2:  carrega_2D( arquivo, arq_alfa, n_mm ) ; break ;
         case 3:  carrega_3D( arquivo, camadas, n_mm ) ; break ;
      }

   material = mat ;

   n_mipmap = n_mm ;

   // COORDENADAS
   coord_automatica = auto_gen ;
   modo = md ;
   filtro_mag = filtros[0] ;
   filtro_min = filtros[1] ;
   wrap_s = wraps[0] ;
   wrap_t = wraps[1] ;

   // GERACAO AUTOMATICA
   int i ;
   for( i=0; i<4 ; i++)
   {
      vetor_s[i] = vetores[0][i] ;
      vetor_t[i] = vetores[1][i] ;
   }

   plano_s = planos[0] ;
   plano_t = planos[1] ;

   modo_geracao_s = modo_gens[0] ;
   modo_geracao_t = modo_gens[1] ;

   coordenadas = coords ;
}
/*--  DESTRUTOR  ----------------------------------------------------------*/
Texture::~Texture( void ) 
{
}









/*--    -------------------------------------------------------------------*/
void Texture::carrega_1D( char* nome_arquivo, int n_mm ) 
{
   texturas = new unsigned char*[n_mm+1] ;
   texturas[0] = arqBMP24bit_p_vet32bit( nome_arquivo, &largura, &altura ) ;
   altura = 1 ;
   profundidade = 1 ;
   n_dimensoes = 1 ;
}
/*--    -------------------------------------------------------------------*/
void Texture::carrega_2D( char* nome_arquivo, char* nome_arq_alfa, int n_mm ) 
{
   texturas = new unsigned char*[n_mm+1] ;
   if( nome_arq_alfa )
      texturas[0] = arqBMP24bit_e_alfa_p_vet32bit( nome_arquivo, nome_arq_alfa,&largura, &altura ) ;
   else
      texturas[0] = arqBMP24bit_p_vet32bit( nome_arquivo, &largura, &altura ) ;
   profundidade = 1 ;
   n_dimensoes = 2 ;
}
/*--    -------------------------------------------------------------------*/
void Texture::carrega_3D( char* nome_arquivo, int camadas, int n_mm ) 
{
   texturas = new unsigned char*[n_mm+1] ;
   texturas[0] = arqBMP24bit_p_vet32bit( nome_arquivo, &largura, &altura ) ;
   altura = altura/camadas ;
   profundidade = camadas ;
   n_dimensoes = 3 ;
}
/*--    -------------------------------------------------------------------*/
void Texture::desaplica( void  )
{
   if( material )
      material->desaplica() ;
   glPopAttrib( ) ;
   glDisable( GL_TEXTURE_GEN_S );
   glDisable( GL_TEXTURE_GEN_T );
   glDisableClientState( GL_TEXTURE_COORD_ARRAY ) ;
   glDisable( GL_TEXTURE_2D ) ;
}
/*--    -------------------------------------------------------------------*/
void Texture::aplica( void  )
{
   glPushAttrib( GL_TEXTURE_BIT ) ;
   if( material )
      material->aplica( ) ;

   if( !criada )
   {
      cria() ;
      criada = true ;
   }

   glEnable( GL_TEXTURE_2D ) ;
   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, (float)modo ) ;
   glBindTexture( GL_TEXTURE_2D, id ) ; 

   if( coord_automatica )
   {
      glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, modo_geracao_s ) ;
      glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, modo_geracao_t ) ;
      glTexGenfv( GL_S, plano_s, vetor_s ) ;
      glTexGenfv( GL_T, plano_t, vetor_t ) ;
      glEnable( GL_TEXTURE_GEN_S );
      glEnable( GL_TEXTURE_GEN_T );
   }
   else
   {
      glEnableClientState( GL_TEXTURE_COORD_ARRAY ) ;
      glTexCoordPointer( 2,  GL_FLOAT, 2*sizeof(GLfloat), coordenadas ) ; 
   }   
}

/*--    -------------------------------------------------------------------*/
void Texture::cria( void )
{
   glEnable( GL_TEXTURE_2D) ;
   glGenTextures(1, &id ) ;
   glBindTexture( GL_TEXTURE_2D, id ) ;

   //glPixelStorei( GL_UNPACK_ALIGNMENT, 4 ) ;
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtro_mag ) ;
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtro_min ) ;
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s ) ;
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t ) ;

   glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, largura, altura,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, texturas[0] ) ;
}
/***************************************************************************/