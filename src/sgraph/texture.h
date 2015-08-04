#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "appearence.h"
#include "material.h"


class Texture : public Appearence 
{
private:

   bool criada ;
   Material *material ; // para os casos de Modulate, blend e decal
   // TEXTURA
   GLuint id ;
   int largura ;
   int altura ;
   int profundidade ;
   int n_dimensoes ;
   int n_mipmap ;
   unsigned char** texturas ;

   // COORDENADAS
   bool coord_automatica ;
   int modo ;          /* TEX_ENV_MODE */
   int filtro_mag ;
   int filtro_min ;
   int wrap_s ;
   int wrap_t ;
// int wrap_r ;
// int wrap_q ;

   // GERACAO AUTOMATICA
   float vetor_s[4] ;
   float vetor_t[4] ;
// float vetor_r[4] ;
// float vetor_q[4] ;
   int   plano_s ;
   int   plano_t ;
// int   plano_r ;
// int   plano_q ;
   int   modo_geracao_s ;
   int   modo_geracao_t ;
// int   modo_geracao_r ;
// int   modo_geracao_q ;

   // GERAÇAO POR VETOR
   float *coordenadas ;

public:
   Texture( void ) ;
   Texture( char* arquivo, char* arq_alfa, Material* mat, int dim, int camadas, int n_mm, int md, bool auto_gen,
                 int *filtros, int *wraps, float vetores[2][4], int *planos, 
                 int* modo_gens, float*coords ) ;
   Texture( char* nome_arquivo ) ;
   void carrega_1D( char* nome_arquivo, int n_mm ) ;
   void carrega_2D( char* nome_arquivo, char* nome_arq_alfa, int n_mm ) ;
   void carrega_3D( char* nome_arquivo, int camadas, int n_mm) ;
   void cria( void ) ;
   void aplica( void ) ;
   void desaplica( void ) ;
   ~Texture( void ) ;

void carrega_2D_TGA( char* nome_arquivo, char* nome_arq_alfa, int n_mm );


} ;

#endif
