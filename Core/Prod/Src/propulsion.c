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

void propulsion_followBezier(Bezier* b) {
    float t = bezier_project(b, robot.position, 0.0001);

    Vector2 pointOnCurve = bezier_eval(b, t);
    float dist = vector2_dist(robot.position, pointOnCurve);

    printf("t = %f, x: %.1fmm, y: %.1fmm, angle: %.1fdeg, dist: %fmm\r\n", t, robot.position.x, robot.position.y, robot.angle / M_PI / 2 * 360, dist);

    if (t > 0.99) {
    	propulsion_setSpeeds(0, 0);
    	return;
    }

    float k = bezier_curvature(b, t);
    //let slow = 1/(1 + pow(abs(k), 2)*10000)
    float v = (100*t*(1-t) + 8 *(1-t) + 8*t) * 2 * 10;
    float v_g = v*(1-ENTRAXE_MOTOR*k/2);
    float v_d = v*(1+ENTRAXE_MOTOR*k/2);

    propulsion_setSpeeds(v_g, v_d);
}









