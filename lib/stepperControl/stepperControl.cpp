#include <Arduino.h>
#include <stepperControl.h>

void initStepper(int dir_pin, int step_pin){
    pinMode(dir_pin, OUTPUT);
    pinMode(step_pin, OUTPUT);
}

void moveStep_primitive(int dir_pin, int step_pin, int step, int dir, int speed){
    digitalWrite(dir_pin, dir);
    int i;

    for(i = 0; i < step; ++i){
        digitalWrite(step_pin, 1);
        delayMicroseconds(2);
        digitalWrite(step_pin, 0);
        delayMicroseconds(speed);
    }
}

void moveStepLinear_primitive(int dir_pin, int step_pin, int step, int dir){
    int half_step = step / 2;
    
    float ARRAY_DELAY[half_step];
    float c0 = 5000;
    float c_n = 0;
    float high_speed = 100;
    
    int i;
    for(i = 0; i < half_step; ++i){
        float d =c0;
        if(i > 0){
            d = c_n - ((2 * c_n) / (4*i+1));
        }
        if(d<high_speed){
            d = high_speed;
        }
        ARRAY_DELAY[i] = d;
        c_n = d;
    }


    //rotate

    digitalWrite(dir_pin, dir);

    for(i = 0; i < half_step; ++i){
        digitalWrite(step_pin, 1);
        delayMicroseconds(ARRAY_DELAY[i]);
        digitalWrite(step_pin, 0);
        delayMicroseconds(2);
    }

    for(i = 0; i < half_step; ++i){
        digitalWrite(step_pin, 1);
        delayMicroseconds(ARRAY_DELAY[half_step - i - 1]);
        digitalWrite(step_pin, 0);
        delayMicroseconds(2);
    }
}
