#include "odometry.h"


extern Robot robot;


int16_t getRightEncoderCount(){
	int16_t count = (int16_t) R_ENCODER.Instance->CNT;
	R_ENCODER.Instance->CNT = 0;
	return count;
}


int16_t getLeftEncoderCount(){
	int16_t count = -1 * (int16_t) L_ENCODER.Instance->CNT;
	L_ENCODER.Instance->CNT = 0;
	return count;
}

//float leftTotal = 0;
//float rightTotal = 0;

void odometry_updatePosition(){
	//printf("x: %.1fmm, y: %.1fmm, angle: %.1f\r\n", robot.position.x, robot.position.y, robot.angle/2/M_PI*360);

	float coeff = M_TWOPI * ODOMETRY_RADIUS / TICKS_PER_REV;
	float leftMov = getLeftEncoderCount() * coeff;
	float rightMov = getRightEncoderCount() * coeff;



	//leftTotal += leftMov;
	//rightTotal += rightMov;

	//printf("left: %.1fmm, right: %.1fmm\n", leftTotal, rightTotal);

	float r =  (leftMov + rightMov)/2;
	float alpha = (leftMov - rightMov)/ENTRAXE_ODOMETRY;

	float deltaX = r * cos(robot.angle + alpha/2);
	float deltaY = r * sin(robot.angle + alpha/2);

	robot.position.x += deltaX;
	robot.position.y += deltaY;
	robot.angle += alpha;
	robot.measuredSpeed = vector2_norm(vector2_new(deltaX, deltaY));

	if (robot.angle > M_PI)
		robot.angle = robot.angle - M_TWOPI;
	else if (robot.angle < -M_PI)
		robot.angle = robot.angle + M_TWOPI;
}


void odometry_setPosition(float x, float y){
	robot.position.x = x;
	robot.position.y = y;
}


void odometry_setAngle(float angle){
	robot.angle = angle;
}
