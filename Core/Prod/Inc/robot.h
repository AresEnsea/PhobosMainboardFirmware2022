/**
 * @file robot.h
 * Ce fichier définit une structure Robot permettant de stocker les états
 * du robot ainsi que des structures liées au fonctionnement de certains de ses
 * systèmes.
 */
#ifndef _ROBOT_
#define _ROBOT_

#include "vector2.h"
#include "drv8825.h"


/** 
 * La structure Robot permet de stocker les états du robot ainsi que des 
 * structures liées au fonctionnement de certains de ses systèmes.
 */
typedef struct {
    /** Vecteur représentant la position du robot en millimètres. */
    Vector2 position;

    /** Angle du robot en radians. */
    float angle;

    /** Stucture associée au moteur propulsif gauche. */
    Stepper* leftMotor;
    float leftSpeed;

    /** Stucture associée au moteur propulsif droit. */
    Stepper* rightMotor;
    float rightSpeed;
} Robot;

/**
 * Variable globale représentant le robot.
 */
Robot robot;

#endif
