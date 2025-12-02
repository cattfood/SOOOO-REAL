#include "main.h"
#include "robot.h"
#ifndef PIDH
#define PIDH

struct pidConstants{
    float p;
    float i;
    float d;
};

extern void forwardMove(float target, float timeout, pidConstants constants = {0.4,0,0});
extern void turnpid(float target, float timeout, pidConstants constants);
extern void drivearcl(double theta, double radius, int timeout);
#endif