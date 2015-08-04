/*============================================================================
 * NODE.CPP                                                              
 *                    
 * (ITEM MEMBER)
 *
 * CHILDRENS:
 * - GROUP
 * - CAMERA
 * - LIGHT                                                 
 *===========================================================================*/


#include "node.h"
#include "string.h"


/************************************************************************/
/* Methods                                        
/*
/************************************************************************/


 Node::Node()
 {
    strcpy( nome, "Node") ;
 }

 Node::Node( char* n ) 
 {
    int letra = 0 ;
    int taman = (int) strlen( n ) ;

    // nome é char[128]
    while( letra<127 && letra<taman )
    {
       nome[letra] = n[letra] ;
       letra ++ ;
    }
    nome[letra] = '\0' ;
 };

 Node::~Node() {}

 int Node::setupCamera()
 {
    return 0;
 }

 int Node::setupLight()
 {
    return 0;
 }

 void Node::render( int passada ) {}


 void Node::setType(int v) 
 {
    vez=v;
 }
