/*============================================================================
 * IMAGE.H
 *
 *
 *===========================================================================*/


#ifndef AUX_BMP_H
#define AUX_BMP_H

   
unsigned char* arqBMP24bit_p_vet32bit( char* arq_nome, int *largura, int *altura );
unsigned char* arqBMP24bit_e_alfa_p_vet32bit( char* arq_nome, char *arq_alfa_nome,
                                              int* largura, int* altura );

#endif
