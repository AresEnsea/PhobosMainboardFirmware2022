/**
 * @file config.h
 * Ce fichier regroupe un grand nombre de constantes utilisées à diverses 
 * endroits dans le projet. Certaines permettent de configuer le fonctionnement
 * du robot, d'autres l'activation ou non des affichages de debogage dans la 
 * console via un port USB serie.
 */
#include <math.h>

typedef int bool;
#define TRUE 1
#define FALSE 0


/* Robot Select */

//#define ISPHOBOS
#define ISDEIMOS


// Config Age of bots
#define MATCH_DURATION 100


// Config AX-12A
#define ANGLE_STARTUP 110
#define ANGLE_PINCE_RELEASE 22
#define ANGLE_PINCE_CATCH 5
#define ANGLE_FLAG_REPOS 96 // 105
#define ANGLE_FLAG_DEPLOY 15
#define ANGLE_BRAS_RAISE 110
#define ANGLE_BRAS_DEPLOY 10


// Config propulsion
#define STEPS_PER_REV  200
#define MICROSTEPS     32
#define ROT_RPM_MAX    30
#define MOV_RPM_MAX    50

#ifdef ISPHOBOS
	#define WHEEL_RADIUS 38.6
#endif
#ifdef ISDEIMOS
	#define WHEEL_RADIUS 27.15
#endif

#ifdef ISPHOBOS
	#define ENTRAXE_MOTOR  120.5
#endif
#ifdef ISDEIMOS
	#define ENTRAXE_MOTOR  112.32
#endif


// Config odometry
#define TICKS_PER_REV  8192

#ifdef ISPHOBOS
	#define ODOMETRY_RADIUS 26.2255
#endif
#ifdef ISDEIMOS
	#define ODOMETRY_RADIUS 27.245
#endif
#ifdef ISPHOBOS
	#define ENTRAXE_ODOMETRY 200.165586
#endif
#ifdef ISDEIMOS
	#define ENTRAXE_ODOMETRY 182.8
#endif



// Timer names
#define R_ENCODER htim1
#define L_ENCODER htim3
#define R_MOTOR_TIMER htim8
#define L_MOTOR_TIMER htim11
