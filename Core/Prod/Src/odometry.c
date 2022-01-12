#include "odometry.h"


extern Robot robot;


int16_t getRightEncoderCount(){
	return (int16_t) R_ENCODER.Instance->CNT;
}


int16_t getLeftEncoderCount(){
	return -1 * (int16_t) L_ENCODER.Instance->CNT;
}


void resetRightEncoderCount(){
	R_ENCODER.Instance->CNT = 0;
}


void resetLeftEncoderCount(){
	L_ENCODER.Instance->CNT = 0;
}


void updateRobotPosition(){
	//printf("x: %.1fmm, y: %.1fmm, angle: %.1fdeg\r\n", robot.position.x, robot.position.y, robot.angle/2/M_PI*360);

	int valCodG = getLeftEncoderCount();
	int valCodD = getRightEncoderCount();

	resetRightEncoderCount();
	resetLeftEncoderCount();

	float r =  (valCodG*COEFF_CODEUR_L + valCodD*COEFF_CODEUR_R)/2;
	float alpha = (valCodD*COEFF_CODEUR_R - valCodG*COEFF_CODEUR_L)/ENTRAXE_ODOMETRY;

	robot.position.x += r * cos(robot.angle + alpha/2);
	robot.position.y += r * sin(robot.angle + alpha/2);
	robot.angle += alpha;

	if (robot.angle > M_PI)
		robot.angle = robot.angle - M_TWOPI;
	else if (robot.angle < -M_PI)
		robot.angle = robot.angle + M_TWOPI;
}


void setRobotPosition(float x, float y){
	robot.position.x = x;
	robot.position.y = y;
}


void setRobotAngle(float angle){
	robot.angle = angle;
}
