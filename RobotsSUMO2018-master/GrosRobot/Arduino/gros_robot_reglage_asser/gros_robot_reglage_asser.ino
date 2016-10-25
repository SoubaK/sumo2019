#include <Arduino.h>
#include "SimpleTimer.h"
#include "MotorBlock.h"
#include "interrupts.h"

SimpleTimer timerDebug;
SimpleTimer timerAsser;


MotorBlock M_L(12,9,3, 21, 7);
MotorBlock M_R(13,8,11, 2, 4);

float tRef;

void setup() {
  M_L.init();
  M_R.init();

  attachInterrupt(2, coderL, CHANGE);
  attachInterrupt(0, coderR, CHANGE);
  Serial.begin(115200);
  timerDebug.setInterval(50, serialDebug);
  timerDebug.setInterval(20, asser);

  tRef = millis();

}

void loop() {

  timerDebug.run();
  timerAsser.run();
  

}


void asser(){
  M_R.run(0.3);
  M_L.run(-0.3);
}

void serialDebug()
{
  Serial.println(String((int)(1000*M_L.currSpeed)) + "/" + String((int)(1000*M_L.dbg_targetSpeed)) + " " + String((int)(1000*M_R.currSpeed)) + "/" + String((int)(1000*M_R.dbg_targetSpeed)));
  //Serial.println(String((int)(1000*M_R.currSpeed)) + " " + String((int)(1000*M_L.currSpeed)));
  //Serial.println(String((int)M_L.cmdDEBUG));
}
