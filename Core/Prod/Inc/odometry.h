/** 
 * @file odometry.h
 */

#include "robot.h"
#include "tim.h"
#include "config.h"
#include <stdio.h>


/**
 * Lit les valeurs des codeuses puis calcule et met à jour la position du robot.
 */
void updateRobotPosition();


/**
 * Définit la position du robot.
 * @param x L'abscisse de la position du robot en millimètres.
 * @param y L'ordonnée de la position du robot en millimètres.
 */
void setRobotPosition(float x, float y);


/**
 * Définit l'angle formé entre le robot et (1, 0).
 * @param angle L'angle du robot en radians.
 */
void setRobotAngle(float angle);