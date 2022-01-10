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
	drv8825_setDirection(robot.leftMotor, (left < 0)?NEGATIVE:POSITIVE);
    drv8825_moveMotorLineSpeed(robot.leftMotor, fabs(left));

    drv8825_setDirection(robot.rightMotor, (right < 0)?NEGATIVE:POSITIVE);
    drv8825_moveMotorLineSpeed(robot.rightMotor, fabs(right));
}
