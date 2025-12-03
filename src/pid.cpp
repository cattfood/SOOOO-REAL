#include "main.h"
#include "robot.h"
#include "pid.h"
#include "timer.hpp"


pidConstants t_consts;
double error = 0;
double prevError = 0;
double integral = 0;
double derivative = 0;
double power = 0;
double error2 = 0;
double prevError2 = 0;
double integral2 = 0;
double derivative2 = 0;
double power2 = 0;
double error3 = 0;
double prevError3 = 0;
double integral3 = 0;
double derivative3 = 0;
double power3 = 0;

void setConstants(pidConstants constants) {
    t_consts = constants;
}
double getTrueError(double target, double input) {
    double error = target - input;

    while(error > 180){
        error -= 360;
    }

    while(error < -180) {
        error += 360;
    }

    return error;
}
float calc (float target, float input, float integralKI, int maxI) {
prevError = error;
error = target - input;

if (std::abs(error) < integralKI) {
    integral += error;
}
else {
    integral = 0;
}
if (integral >= 0){
    integral = std:: min(integral,maxI);
}
else{
    integral = std::max(integral, -maxI);
}// preventing I build up from being too large
derivative = error - prevError;

power = t_consts.p*error + t_consts.i*integral + t_consts.d*derivative;

return power;
}

float calc2 (float target, float input, float integralKI, int maxI) {
prevError2 = error2;
error2 = target - input;

if (std::abs(error2) < integralKI) {
    integral2 += error2;
}
else {
    integral2 = 0;
}
if (integral2 >= 0){
    integral2 = std:: min(integral2,maxI);
}
else{
    integral2 = std::max(integral2, -maxI);
}
derivative2 = error2 - prevError2;

power2 = t_consts.p*error2 + t_consts.i*integral2 + t_consts.d*derivative2;

return power2;
}

float calc3 (float target, float input, float integralKI, int maxI) {
prevError3 = error3;
error3 = target - input;

if (std::abs(error3) < integralKI) {
    integral3 += error3;
}
else {
    integral3 = 0;
}
if (integral3 >= 0){
    integral3 = std:: min(integral3,maxI);
}
else{
    integral3 = std::max(integral3, -maxI);
}
derivative3 = error3 - prevError3;

power3 = t_consts.p*error3 + t_consts.i*integral3 + t_consts.d*derivative3;

return power3;
}

void resetEncoders() {
    LF.tare_position();
    LM.tare_position();
    LB.tare_position();
    RF.tare_position();
    RM.tare_position();
    RB.tare_position();
}
void chassisMove(int left, int right) {
    LF.move(left);
    LM.move(left);
    LB.move(left);
    RF.move(right);
    RM.move(right);
    RB.move(right);

}


void forwardMove(float target, float timeout, pidConstants constants) {
    error = 0;
    prevError = 0;
    integral = 0;
    derivative = 0;
    power = 0;
    setConstants(constants);
    double startPosition = imu.get_heading(); //degrees
    
    Timer t1;
     float voltage;
    float encoder_avg;
    int count = 0;




resetEncoders();
while(t1.time() <= timeout) {
    
    encoder_avg = (lf.get_position() + rf.get_position()) / 2;
    voltage = calc(target, encoder_avg, 200, 20);

     double currentPosition = imu.get_heading();

    double baseCorrect = getTrueError(startPosition, currentPosition);
    double headingP = 0.0; //tuning heading correction

    double headingCorrect = baseCorrect*headingP;
    con.print(1, 0, "%f", error );

    chassisMove(voltage + headingCorrect, voltage - headingCorrect);
    pros::delay(10);
     if (abs(error) < 5) count++;

        if(count > 5) {
           // break;
        }
   
pros::delay(10);
    
}
chassisMove(0,0);
}
void turnpid(float target, float timeout, pidConstants constants) {
    prevError = 0;
    float voltage;
    float position;
    setConstants(constants);
    Timer t1;

int count = 0;

    position = imu.get_rotation();

    //while(t1.time() < timeout) {
    while(true){
        voltage = calc(target, position, 5, 100);
        pros::delay(10);
        if (abs(error) < 5) count++;

        chassisMove(voltage, -voltage);
        if(count > 5) {
          //  break;
        }
    }
chassisMove(0,0);
   
}

void drivearcl(double theta, double radius, int timeout) {
    setConstants({0,0,0});//straight pid

    Timer t1;

    double totalError = 0;

    double ltarget = 0;
    double rtarget = 0;
    double pi = 3.14159265359;
    double chasd = 300;
    int count = 0;
    resetEncoders();

    ltarget = double((theta / 360)* 2 * pi * radius);
    rtarget = double((theta / 360)* 2 * pi * (radius + chasd));

    while(t1.time() < timeout) {
        double encoder_avg_l = (LF.get_position() + LB.get_position()) / 2;
        double encoder_avg_r = (RF.get_position() + RB.get_position()) / 2;
        double leftcorrect = -(encoder_avg_l * 360 / (2 * pi *radius));

        double position = imu.get_heading();

        setConstants({0,0,0});
        int voltagel = calc(ltarget, encoder_avg_l, 200, 20);
        int voltager = calc2(rtarget, encoder_avg_r, 200, 20);

        setConstants({0,0,0}); //turn pid
        int fix = calc3(leftcorrect, position, 200, 20);

        chassisMove(voltagel + leftcorrect, voltager - leftcorrect);

        if(abs(error) < 5) {
            count++;
        
        }
        if (count > 10) {
        break;
        }
    }
chassisMove(0,0);
}
