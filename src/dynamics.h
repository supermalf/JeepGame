/*============================================================================
 * DYNAMICS.H
 *
 * CAR DYNAMICS / PHYSICS
 *
 *===========================================================================*/


#ifndef _DYNAMICS_H_
#define _DYNAMICS_H_



void carUpdate (void);
void carInit(void);
float carGetsteerangle (void);
float carGetAngle (void);
void carGetPos (float *x, float *y);
void carSetSteerAngle (float valor);
void carSetThrottle (float valor);
void carBreak (void);
void carSetSlip (int front, int rear);
void carStop (void);
void carSetPos (float x, float y);
void getCarPos (float *x, float *y);
void carCrashY (void);
void carCrashX (void);
void carCrash (void);

#endif 