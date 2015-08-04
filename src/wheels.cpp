/*============================================================================
 * WHEELS.CPP
 *
 *===========================================================================*/



#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <gl/gl.h>

#include "location.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif


void transforma_rodas( float rad_ang_mergulho, float rad_ang_giro,
                       Location *t_dd, Location *t_td, 
                       Location *t_de, Location *t_te )
{
   float rot_pos_x =  2.500f ,
         rot_pos_y = -0.644f ,
         rot_pos_z =  0.438f ;

   float sen_ang_merg = (float)sin( rad_ang_mergulho );
   float cos_ang_merg = (float)cos( rad_ang_mergulho );
   float sen_ang_giro = (float)sin( rad_ang_giro );
   float cos_ang_giro = (float)cos( rad_ang_giro );


   float m_dd[16] = { cos_ang_giro*cos_ang_merg, -sen_ang_giro*cos_ang_merg, -sen_ang_merg, 0.0f,
                                 sen_ang_giro,               cos_ang_giro,          0.0f, 0.0f,
                     cos_ang_giro*sen_ang_merg, -sen_ang_giro*sen_ang_merg,  cos_ang_merg, 0.0f, 
                                          0.0f,                       0.0f,          0.0f, 1.0f
                    };

   float m_td[16] = { cos_ang_merg, 0.0f, -sen_ang_merg, 0.0f,
                              0.0f, 1.0f,          0.0f, 0.0f,
                     sen_ang_merg, 0.0f,  cos_ang_merg, 0.0f,
                              0.0f, 0.0f,          0.0f, 1.0f
                    };

   float m_de[16] = { cos_ang_giro*cos_ang_merg, -sen_ang_giro*cos_ang_merg,  sen_ang_merg, 0.0f,
                                  -sen_ang_giro,              -cos_ang_giro,          0.0f, 0.0f,
                      cos_ang_giro*sen_ang_merg, -sen_ang_giro*sen_ang_merg, -cos_ang_merg, 0.0f,
                                           0.0f,                       0.0f,          0.0f, 1.0f
                    };

   float m_te[16] = { cos_ang_merg,  0.0f,  sen_ang_merg, 0.0f,
                              0.0f, -1.0f,          0.0f, 0.0f,
                      sen_ang_merg,  0.0f, -cos_ang_merg, 0.0f,
                              0.0f,  0.0f,          0.0f, 1.0f
                    };

   t_dd->setRotacao( m_dd, rot_pos_x, rot_pos_y, rot_pos_z );
   t_td->setRotacao( m_td, rot_pos_x, rot_pos_y, rot_pos_z );
   t_de->setRotacao( m_de, rot_pos_x, rot_pos_y, rot_pos_z );
   t_te->setRotacao( m_te, rot_pos_x, rot_pos_y, rot_pos_z );
}

