/*============================================================================
 * IMAGE.CPP
 *
 *
 *===========================================================================*/


#include <stdlib.h>
#include <stdio.h>
#include "image.h"


void le_cabecalho( FILE * f_bmp, int* largura, int* altura );


unsigned char* arqBMP24bit_p_vet32bit( char* arq_nome, int* largura, int* altura )
{
   long int i;
   unsigned char verm,
                 verd,
                 azul;

   unsigned char *imagem;

   int l ,
       a ;

   FILE *f_bmp = fopen( arq_nome, "rb");

   if( !f_bmp )
      return NULL;

   le_cabecalho( f_bmp, largura, altura );
   l = *largura ;
   a = *altura ;

   imagem = (unsigned char*) malloc( sizeof(unsigned char)*l*a*4);
   if( imagem ){
      for( i=0 ; i < l*a*4 ;i++ ) {

         fscanf( f_bmp, "%c%c%c", &azul, &verd, &verm  ) ;
         imagem[i] = verm ;i++;
         imagem[i] = verd ;i++;
         imagem[i] = azul ;i++;
         imagem[i] = 255  ; 
      }
   }
   
   fclose( f_bmp ) ;
   return imagem ;
}


unsigned char* arqBMP24bit_e_alfa_p_vet32bit( char* arq_nome, char *arq_alfa_nome, int* largura, int* altura )
{
   
   long int i;
   unsigned char verm,
                 verd,
                 azul,
				     alfa;

   unsigned char *imagem ;

   int l,a;

   FILE *f_rgb  = fopen( arq_nome, "rb" );
   FILE *f_alfa = fopen( arq_alfa_nome, "rb" );

    if( !f_rgb || !f_alfa  )
      return NULL;

   le_cabecalho( f_rgb,  largura, altura );
   le_cabecalho( f_alfa, largura, altura );
   l = *largura;
   a = *altura;

   imagem = (unsigned char*) malloc( sizeof(unsigned char)*l*a*4);
   if( imagem )
   {
      for( i=0 ; i < l*a*4 ;i++ ) 
      {

         fscanf( f_rgb,  "%c%c%c", &azul, &verd, &verm  );
         imagem[i] = verm ;i++;
         imagem[i] = verd ;i++;
         imagem[i] = azul ;i++;
		   fscanf( f_alfa, "%c%c%c", &alfa, &alfa, &alfa );
         imagem[i] = alfa; 
      }
   }
   
   fclose( f_rgb );
   fclose( f_alfa );
   return imagem;
}

void le_cabecalho( FILE * f_bmp, int* largura, int* altura )
{
   long int i;
   int l,a;

   char* aux;
   char  aux2;


   for( i=0; i<14; i++){
      fscanf(f_bmp, "%c", &aux2);
   }
   
   for( i=14; i<18; i++){
      fscanf(f_bmp, "%c", &aux2);
   }
   aux = (char *)&l ;
   for( i=18; i<22; i++){
      fscanf(f_bmp, "%c", aux);
      aux++;
   }
   aux = (char *)&a ;
   for( i=22; i<26; i++){
      fscanf(f_bmp, "%c", aux);
      aux++;
   }
   for( i=26; i<54; i++){
      fscanf(f_bmp, "%c", &aux2);
      aux++;
   }
   *largura = l;
   *altura  = a;
}
