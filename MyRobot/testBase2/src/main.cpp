#include <Arduino.h>
#include "MotorBlock.h"
#include "SimpleTimer.h"




SimpleTimer * timerAsser;
MotorBlock * M_L, * M_R;
float tRef;

void asser(){
    M_L->run();
    M_R->run();
}

void setup(){
    M_L = new MotorBlock(12,21,8,2,6);
    M_R = new MotorBlock(13,22,9,3,7);
    timerAsser = new SimpleTimer();
    M_L->init();
    M_R->init();

    Serial.begin(115200);

    timerAsser->setInterval(20, asser);

    tRef = millis();

}

void loop(){
    timerAsser->run();
}
