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

// Fonctions du robot


/* Module Debug */


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


// Config Vitesses
#define STEPS_PER_REV  200
#define MICROSTEPS     32
#define ROT_RPM_MAX    30
#define MOV_RPM_MAX    50


// Config Odométrie
#define COEFF_CODEUR_L 0.0405726153
#define COEFF_CODEUR_R 0.0403868872
#define ENTRAXE 251


// Timer names
#define R_ENCODER htim1
#define L_ENCODER htim3
#define R_MOTOR_TIMER htim8
#define L_MOTOR_TIMER htim11
