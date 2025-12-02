#include "main.h"
#pragma once

class Timer {
    int start;
    public:
    Timer() {
        reset();
    }
    void reset(){
        start = pros::millis();

    }
    int time() {
        return(pros::millis() - start);
    }
    };
