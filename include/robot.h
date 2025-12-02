#include "main.h"
#include "api.h"
#include "main.h"
#ifndef ROBOTH
#define ROBOTH

#define LF_PORT 18
#define LM_PORT 19
#define LB_PORT 20
#define RF_PORT 8
#define RM_PORT 9
#define RB_PORT 10
#define intake1_PORT 11
#define intake2_PORT 12


extern pros::Motor LF;
extern pros::Motor LM;
extern pros::Motor LB;
extern pros::Motor RF;
extern pros::Motor RM;
extern pros::Motor RB;

extern pros::Motor intake1;
extern pros::Motor intake2;

extern pros::ADIDigitalOut angleChanger;
extern pros::ADIDigitalOut scraper;
extern pros::ADIDigitalOut descore;
extern pros::ADIDigitalOut indexer;

extern pros::Controller con;
extern pros::Imu imu;

#endif