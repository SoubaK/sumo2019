#include <Arduino.h>
#include "AsservissementMascart.h"
#include "SimpleTimer.h"




SimpleTimer * timerAsser;
AsservissementMascart * M_L, * M_R;
float tRef;

void asser(){
    M_L->run(0.3);
    M_R->run(0.3);
}

void setup(){
    M_L = new AsservissementMascart(12,21,8,2,6);
    M_R = new AsservissementMascart(13,22,9,3,7);
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
