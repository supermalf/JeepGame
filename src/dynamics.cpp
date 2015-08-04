/*============================================================================
 * DYNAMICS.CPP
 *
 * CAR DYNAMICS / PHYSICS
 *
 *===========================================================================*/


#include "dynamics.h"

#include <stdio.h>
#include <math.h>
#include <memory.h>


float Dx=0.0f;
float Dy=0.0f;
float Posx=0.0f;
float Posz=0.0f;

/* Defines
 */
#define DELTA_T	0.01		/* time between integration steps in physics modelling */
#define DIST2		1.5			/* Diferencia (distancia ao quadrado)minima entre um possição e outra do rastro */


/* Typedefs
 */

typedef struct VEC2
{
	float 	x,y;
} VEC2;


typedef struct CARTYPE
{
	float	wheelbase;		// wheelbase in m
	float	b;				// in m, distance from CG to front axle
	float	c;				// in m, idem to rear axle
	float	h;				// in m, height of CM from ground
	float	mass;			// in kg
	float	inertia;		// in kg.m
	float	length,width;
	float	wheellength,wheelwidth;
} CARTYPE;

typedef struct CAR
{
	CARTYPE	*cartype;		// pointer to static car data
	
	VEC2	position_wc;		// position of car centre in world coordinates
	VEC2	velocity_wc;		// velocity vector of car in world coordinates

	float	angle;				// angle of car body orientation (in rads)
	float	angularvelocity;

	float	steerangle;			// angle of steering (input)
	float	throttle;			// amount of throttle (input)
	float	brake;				// amount of braking (input)
} CAR;

// Carro global
CAR			car; 

typedef struct TRAILPOINT
{
	float	x,y;
	float	angle;
	float   steerangle;
} TRAILPOINT;

/* Globals
*/

CARTYPE		cartypes[1];
VEC2			screen_pos;
float			scale;
char			str[80];
volatile int 	ticks = 1;			// ticks of DELTA_T second
volatile int 	iticks = 1;			// ticks of INPUT_DELTA_T second


/* Lots of globals, so their value may be printed on screen
 * normally most of these variables should be private to the physics function.
*/
	VEC2	velocity;
	VEC2	acceleration_wc;
	double	rot_angle;
	double	sideslip;
	double	slipanglefront;
	double	slipanglerear;
	VEC2	force;
	int		rear_slip;
	int		front_slip;
	VEC2	resistance;
	VEC2	acceleration;
	double	torque;
	double	angular_acceleration;
	double	sn, cs;
	double	yawspeed;
	double	weight;
	VEC2	ftraction;
	VEC2	flatf, flatr;

/* Functions
 */
float MIN (float a, float b)
{
	if (a <= b)
		return a;
	else
		return b;
}

float MAX (float a, float b)
{
	if (a >= b)
		return a;
	else
		return b;
}





/*
 * Physics module
*/
void init_cartypes( void )
{
	CARTYPE	*cartype;

	cartype = &cartypes[0];
	cartype->b = 1.0f;					// m							
	cartype->c = 1.0f;					// m
	cartype->wheelbase = cartype->b + cartype->c;
	cartype->h = 1.0f;					// m
	cartype->mass = 1500.0f;			// kg			
	cartype->inertia = 1500.0f;   	// kg.m			
	cartype->width = 1.5f;				// m
	cartype->length = 3.0f;				// m, must be > wheelbase
	cartype->wheellength = 0.7f;
	cartype->wheelwidth = 0.3f;
}

void init_car( CAR *car, CARTYPE *cartype )
{
	car->cartype = cartype;
	
	car->position_wc.x = 0.0f;
	car->position_wc.y = 0.0f;
	car->velocity_wc.x = 0.0f;
	car->velocity_wc.y = 0.0f;

	car->angle = 0.0f;
	car->angularvelocity = 0.0f;

	car->steerangle = 0.0f;
	car->throttle = 0.0f;
	car->brake = 0.0f;
}

// These constants are arbitrary values, not realistic ones.

#define	DRAG		5.0		 		/* factor for air resistance (drag) 	*/
#define	RESISTANCE	30.0			/* factor for rolling resistance */
#define CA_R		-9.20			/* cornering stiffness */
#define CA_F		-7.0			/* cornering stiffness */
#define MAX_GRIP	7.86			/* maximum (normalised) friction force, =diameter of friction circle */

void do_physics( CAR *car, float delta_t)
{
	float sinal;
	sn = sin(car->angle);
	cs = cos(car->angle);

	// SAE convention: x is to the front of the car, y is to the right, z is down
	
	// transform velocity in world reference frame to velocity in car reference frame
	velocity.x =  (float)  cs * car->velocity_wc.y + (float)sn * car->velocity_wc.x;
	velocity.y =  (float) -sn * car->velocity_wc.y + (float)cs * car->velocity_wc.x;

   // Lateral force on wheels
   //	
	// Resulting velocity of the wheels as result of the yaw rate of the car body
	// v = yawrate * r where r is distance of wheel to CG (approx. half wheel base)
	// yawrate (ang.velocity) must be in rad/s
	//
	yawspeed = car->cartype->wheelbase * 2.5f * car->angularvelocity;	

	if( velocity.x == 0 )		// TODO: fix singularity
		rot_angle = 0;
	else
		rot_angle = atan2( (float)yawspeed, velocity.x);

	// Calculate the side slip angle of the car (a.k.a. beta)
	if( velocity.x == 0 )		// TODO: fix singularity
		sideslip = 0;
	else
		sideslip = atan2( velocity.y, velocity.x);		

	// Calculate slip angles for front and rear wheels (a.k.a. alpha)
	slipanglefront = sideslip + rot_angle - car->steerangle;
	slipanglerear  = sideslip - rot_angle;

	// weight per axle = half car mass times 1G (=9.8m/s^2) 
	weight = car->cartype->mass * 9.8 * 0.5;	
	
	// lateral force on front wheels = (Ca * slip angle) capped to friction circle * load
	flatf.x = 0.0f;
	flatf.y = (float)(CA_F * slipanglefront);
	flatf.y = MIN((float)MAX_GRIP, (float)flatf.y);
	flatf.y = MAX((float)-MAX_GRIP, (float)flatf.y);
	flatf.y *= (float)weight;
	if(front_slip)
		flatf.y *= 0.5;

	// lateral force on rear wheels
	flatr.x = 0;
	flatr.y = (float)(CA_R * slipanglerear);
	flatr.y = (float)MIN((float)MAX_GRIP, flatr.y);
	flatr.y = (float)MAX((float)-MAX_GRIP, flatr.y);
	flatr.y *=(float)weight;
	if(rear_slip)
		flatr.y *= 0.5f;

	// longtitudinal force on rear wheels - very simple traction model
	if (velocity.x > 0.0f)
		sinal = 1.0f;
	else
		sinal = -1.0f;

	ftraction.x = 100.0f*(car->throttle - car->brake*sinal);	
	ftraction.y = 0.0f;
	if(rear_slip)
		ftraction.x *= 0.5f;

// Forces and torque on body
	
	// drag and rolling resistance
	resistance.x = -( (float)RESISTANCE*velocity.x + (float)DRAG*velocity.x*(float)fabs(velocity.x) );
	resistance.y = -( (float)RESISTANCE*velocity.y + (float)DRAG*velocity.y*(float)fabs(velocity.y) );

	// sum forces
	force.x = ftraction.x + (float)sin(car->steerangle) * flatf.x + flatr.x + resistance.x;
	force.y = ftraction.y + (float)cos(car->steerangle) * flatf.y + flatr.y + resistance.y;	

	// torque on body from lateral forces
	torque = car->cartype->b * flatf.y - car->cartype->c * flatr.y;

// Acceleration
	
	// Newton F = m.a, therefore a = F/m
	acceleration.x = force.x/car->cartype->mass;
	acceleration.y = force.y/car->cartype->mass;
	
	angular_acceleration = torque / car->cartype->inertia;

// Velocity and position
	
	// transform acceleration from car reference frame to world reference frame
	acceleration_wc.x = (float)  cs * acceleration.y + (float)sn * acceleration.x;
	acceleration_wc.y = (float) -sn * acceleration.y + (float)cs * acceleration.x;

	// velocity is integrated acceleration
	//
	car->velocity_wc.x += delta_t * acceleration_wc.x;
	car->velocity_wc.y += delta_t * acceleration_wc.y;

	// position is integrated velocity
	//
	car->position_wc.x += delta_t * car->velocity_wc.x;
	car->position_wc.y += delta_t * car->velocity_wc.y;


// Angular velocity and heading

	// integrate angular acceleration to get angular velocity
	//
	car->angularvelocity += delta_t * (float)angular_acceleration;

	// integrate angular velocity to get angular orientation
	//
/*
   
   if (car->angle >= 360.0f)
      car->angle = 0.0f;

   if (car->angle <= 0.0f)
      car->angle = 360.0f;
*/

	car->angle += delta_t * car->angularvelocity ;

}
	
/*
 * End of Physics module
 */




void carSetPos (float x, float y)
{
	car.position_wc.x = x;
	car.position_wc.y = y;
}

void getCarPos (float *x, float *y)
{
	*x = car.position_wc.x;
	*y = car.position_wc.y;
}

void carInit (void)
{
	init_cartypes();
	init_car( &car, &cartypes[0] );	
}

void  carUpdate (void)
{
	do_physics(&car, (float)DELTA_T);
}

float carGetsteerangle (void)
{
	return car.steerangle ;
}


float carGetAngle (void)
{
	return car.angle;
}

void carGetPos (float *x, float *y)
{
	*x = car.position_wc.x ;
	*y = car.position_wc.y ;
}


void carSetSteerAngle (float valor)
{
	car.steerangle = valor;
}



void carSetThrottle (float valor)
{
	car.throttle = valor;
	car.brake    = 0;
}



void carBreak (void)
{
	car.brake    = 400;
	car.throttle = 0  ;
}


void carStop (void)
{
	//car.brake    = 400;
	//car.throttle = 0;
   car.velocity_wc.x = 0;
   car.velocity_wc.y = 0;
}

void carCrashY (void)
{
   car.velocity_wc.x = (car.velocity_wc.x/1.0f);
   car.velocity_wc.y = (-car.velocity_wc.y/2.0f);
}


void carCrashX (void)
{
   car.velocity_wc.x = (-car.velocity_wc.x/2.0f);
   car.velocity_wc.y = (car.velocity_wc.y/1.0f);
}

void carCrash (void)
{
   if(car.throttle > 100)
   {
      car.velocity_wc.x = (-car.velocity_wc.x/2.0f);
      car.velocity_wc.y = (-car.velocity_wc.y/2.0f);
   }
   else
   {
      car.velocity_wc.x = (-car.velocity_wc.x/1.0f);
      car.velocity_wc.y = (-car.velocity_wc.y/1.0f);
   }
}

void carSetSlip (int front, int rear)
{
	front_slip = front;
	rear_slip  = rear ;
}






