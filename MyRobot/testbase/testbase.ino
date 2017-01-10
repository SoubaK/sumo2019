
#include <Arduino.h>
#include "MotorBlock.h"
#include "SimpleTimer.h"




SimpleTimer timerAsser;

MotorBlock * M_L, * M_R;
float tRef;

void setup(){
    M_L = new MotorBlock(12,42,9,22,30);
    M_R = new MotorBlock(13,2,8,4,7);
    M_L->init();
    M_R->init();

    attachInterrupt(4,coderL,CHANGE);
    attachInterrupt(6,coderR,CHANGE);

    Serial.begin(115200);

    timerAsser.setInterval(20, asser);

    tRef = millis();

}

void loop(){
    timerAsser.run();
}

void asser(){
    M_L->run();
    M_R->run();
}
