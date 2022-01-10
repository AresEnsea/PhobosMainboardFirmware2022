/** 
 * @file propulsion.h
 */
#include "gpio.h"
#include "tim.h"
#include "robot.h"


/**
 * Initialse les deux moteurs pas-à-pas du bloc de propulsion.
 */
void propulsion_initialize();


/**
 * Met sous tension les moteurs pas-à-pas du bloc de propulsion.
 */
void propulsion_enableMotors();


/**
 * Met hors tension des moteurs pas-à-pas. Ils tournent alors librement.
 */
void propulsion_disableMotors();


/**
 * Configure la vitesse absolue et le sens des moteurs en fonction des deux
 * vitesses signées données en argument.
 * @param left Vitesse du moteur gauche.
 * @param right Vitesse du moteur droit.
 */
void propulsion_setSpeeds(float left, float right);