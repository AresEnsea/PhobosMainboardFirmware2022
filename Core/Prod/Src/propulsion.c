#include "propulsion.h"


extern Robot robot;


void propulsion_initialize() {
	robot.leftMotor = (Stepper*) malloc(sizeof(Stepper));
	robot.rightMotor = (Stepper*) malloc(sizeof(Stepper));

	drv8825_init(
		robot.leftMotor,
		L_MOTOR_EN_Pin, L_MOTOR_EN_GPIO_Port, 
		L_MOTOR_DIR_Pin, L_MOTOR_DIR_GPIO_Port, 
		&L_MOTOR_TIMER, TIM_CHANNEL_1
	);
	drv8825_init(
		robot.rightMotor,
		R_MOTOR_EN_Pin, R_MOTOR_EN_GPIO_Port, 
		R_MOTOR_DIR_Pin, R_MOTOR_DIR_GPIO_Port, 
		&R_MOTOR_TIMER, TIM_CHANNEL_4
	);
}


void propulsion_enableMotors() {
	drv8825_enable(robot.leftMotor);
	drv8825_enable(robot.rightMotor);
}


void propulsion_disableMotors() {
	drv8825_disable(robot.leftMotor);
	drv8825_disable(robot.rightMotor);
}


void propulsion_setSpeeds(float left, float right) {
	robot.leftSpeed = left;
	drv8825_setDirection(robot.leftMotor, (left < 0)?NEGATIVE:POSITIVE);
	drv8825_setRotationSpeed(robot.leftMotor, 60 * fabsf(left) / (2*M_PI*WHEEL_RADIUS));

	robot.rightSpeed = right;
    drv8825_setDirection(robot.rightMotor, (right < 0)?NEGATIVE:POSITIVE);
	drv8825_setRotationSpeed(robot.rightMotor, 60 * fabsf(right) / (2*M_PI*WHEEL_RADIUS));
}


void propulsion_updatePosition(float dt) {
	float left = robot.leftSpeed * dt;
	float right = robot.rightSpeed * dt;

	float r =  (left + right)/2;
	float alpha = (right - left)/ENTRAXE_MOTOR;

	robot.position.x += r * cos(robot.angle + alpha/2);
	robot.position.y += r * sin(robot.angle + alpha/2);
	robot.angle += alpha;

	if (robot.angle > M_PI)
		robot.angle = robot.angle - M_TWOPI;
	else if (robot.angle < -M_PI)
		robot.angle = robot.angle + M_TWOPI;
}

float propulsion_followBezier(Bezier* b, Direction dir) {
	// Paramètre qui correspond au point de la courbe le plus proche du robot
	// Autrement dit, la valeur t qui minimise distance(b(t), robot.position)
    float t = bezier_project(b, robot.position, 0.0001);

    // Le point de la courbe le plus proche du robot, b(t)
    Vector2 pointOnCurve = bezier_eval(b, t);

    // La tangente à la courbe en b(t)
    Vector2 tangent = bezier_deriv1(b, t);

    // L'écart entre le robot et b(t)
    Vector2 displacement = vector2_diff(robot.position, pointOnCurve);

    // Le côté de la courbe du quel le robot se trouve
    float sign = vector2_cross(displacement, tangent);

    // Distance signée à la courbe (négatif d'un coté, positif de l'autre)
    float signedDistance;
    if (sign == 0)
    	signedDistance = 0;
    else
    	signedDistance = sign / fabs(sign) * vector2_norm(displacement);

    //
    float angleError = (vector2_angle(tangent) - atan(signedDistance / 400.0)) - (robot.angle + (dir==BACKWARD?M_PI:0));
    angleError = standardAngle(angleError);

    //printf("t = %f, e = %.1f, rel-dist = %.1f \n", t, signedAngleError, signedDistance);

    if (t > 0.999) {
    	propulsion_setSpeeds(0, 0);
    	return t;
    }

    float k = bezier_curvature(b, t);

    float correctionSlowDownFactor = 1 - fabs(angleError/M_PI)*10;
    correctionSlowDownFactor = correctionSlowDownFactor>0?correctionSlowDownFactor:0;

    float v = (4*(1-t) + 80*t*(1-t)*(1-t) + 50*t*t*(1-t) + 3*t) * 15;
    v *= correctionSlowDownFactor;
    v *= (dir==BACKWARD?-1:1);
    //if (fabs(v) > robot.measuredSpeed + 5) {
    //	v = (robot.measuredSpeed + 5) * fabs(v) / v;
    //}

    //printf("v: %f, sdf: %f, ae: %f\r\n", v, correctionSlowDownFactor, angleError);

    float v_g = v*(1+ENTRAXE_MOTOR*k/2);
    float v_d = v*(1-ENTRAXE_MOTOR*k/2);

    float maxCorrection = 40;

    float correction = -angleError*100;

    if (fabs(correction) > maxCorrection) {
    	correction = maxCorrection * correction / abs(correction);
    }

    printf("t = %f, x: %.1fmm, y: %.1fmm, angle: %.1fdeg, dist: %fmm, corr: %.2f\r\n", t, robot.position.x, robot.position.y, robot.angle / M_PI / 2 * 360, signedDistance, correction);
    //printf("angle: %.1fdeg, corr: %.2f\r\n", robot.angle / M_PI / 2 * 360, correction);


    propulsion_setSpeeds(v_g - correction, v_d + correction);

    //printf("v_g: %.1fmm/s, v_d: %.2fmm/s\r\n", v_g, v_d);
    //propulsion_setSpeeds(v_g, v_d);

    //propulsion_setSpeeds(-50, -50);

    return t;
}

float standardAngle(float angle) {
	return fmod(fmod(angle + M_PI, M_TWOPI) + M_TWOPI, M_TWOPI) - M_PI;
}







