#include "api.h"
#include "main.h"
#include "robot.h"

#define LF_PORT 18
#define LM_PORT 19
#define LB_PORT 20
#define RF_PORT 8
#define RM_PORT 9
#define RB_PORT 10
#define intake1_PORT 11
#define intake2_PORT 12


pros::Motor LF(20, pros:: E_MOTOR_GEARSET_06, true, pros:: E_MOTOR_ENCODER_DEGREES);
pros::Motor LM(18, pros:: E_MOTOR_GEARSET_06, true, pros:: E_MOTOR_ENCODER_DEGREES); 
pros::Motor LB(19, pros:: E_MOTOR_GEARSET_06, true, pros:: E_MOTOR_ENCODER_DEGREES);

pros::Motor RF(8, pros:: E_MOTOR_GEARSET_06, false, pros:: E_MOTOR_ENCODER_DEGREES); 
pros::Motor RM(9, pros:: E_MOTOR_GEARSET_06, false, pros:: E_MOTOR_ENCODER_DEGREES); 
pros::Motor RB(10, pros:: E_MOTOR_GEARSET_06, false, pros:: E_MOTOR_ENCODER_DEGREES); 

pros::Motor intake1(intake1_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor intake2(intake2_PORT, pros::E_MOTOR_GEARSET_06, false);

pros::ADIDigitalOut angleChanger('A');
pros::ADIDigitalOut scraper('B');
pros::ADIDigitalOut descore('F');
pros::ADIDigitalOut indexer('G');

pros::Controller con(pros::E_CONTROLLER_MASTER);
pros::Imu imu(15);
