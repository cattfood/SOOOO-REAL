#include "main.h"
#include "robot.h"
#include "pid.h"

using namespace pros; //pros library
using namespace std;

//comment 

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	forwardMove(600, 1000);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

bool arcToggle = true;
bool tankToggle = false; //sets arc to defult 
bool angleToggle = false;
bool scraperToggle = false;
bool descoreToggle = false;
bool indexerToggle = false;

int power = 0;
int turn = 0;
int left = 0;
int right = 0;

	while (true) {
		if (con.get_digital_new_press(DIGITAL_L1)){
			angleToggle = !angleToggle; 
		}
		angleChanger.set_value(angleToggle);


		if (con.get_digital_new_press(DIGITAL_L2)){
			descoreToggle = !descoreToggle; 
		}
		descore.set_value(descoreToggle);


		if (con.get_digital_new_press(DIGITAL_DOWN)){
			scraperToggle = !scraperToggle; 
		}
		scraper.set_value(scraperToggle);


		if (con.get_digital_new_press(DIGITAL_RIGHT)){
			indexerToggle = !indexerToggle; 
		}
		indexer.set_value(indexerToggle);

		
		
		if (con.get_digital(E_CONTROLLER_DIGITAL_R1)) { //if the top button has been pressed, the intake is moving forward
			intake1.move(127);
			intake2.move(127);
		}
		else if (con.get_digital(E_CONTROLLER_DIGITAL_R2)) { //if R2 is getting pressed, then the inake is move backwards
			intake1.move(-127);
			intake2.move(-127);
		}
		else { //if neigther button is beting pressed, the voltage is set to 0 and the intake stops
			intake1.move(0);
			intake2.move(0);
		}



		if (con.get_digital_new_press(DIGITAL_LEFT)) {//new_press means that it activates per press--without it, it would only toggle while the button is pressing
			arcToggle = !arcToggle; //! means oposite of
			tankToggle = !tankToggle;
		}


		if (arcToggle) {
			power = con.get_analog(ANALOG_LEFT_Y); //how much forward the bot goes (power)
			turn = con.get_analog(ANALOG_RIGHT_X); //how much the bot turns 
			left = power + turn;
			right = power - turn; //controls both sides of the chassis so that the left side goes forward and right side goes backwards
			LF.move(left);
			LM.move(left);
			LB.move(left);
			RF.move(right);
			RM.move(right);
			RB.move(right);
		}


		if (tankToggle) {
			LF.move(con.get_analog(ANALOG_LEFT_Y)); 
			LM.move(con.get_analog(ANALOG_LEFT_Y)); 
			LB.move(con.get_analog(ANALOG_LEFT_Y)); //gets input from left joystick for left motors

			RF.move(con.get_analog(ANALOG_RIGHT_Y)); 
			RM.move(con.get_analog(ANALOG_RIGHT_Y)); 
			RB.move(con.get_analog(ANALOG_RIGHT_Y)); //gets input from right joystick for right motors
		}


	}
}
