#include "MotorBlock.h"
#include "command.h"

extern MotorBlock M_L;
extern MotorBlock M_R;
extern int asserMode;

extern int rotDir;
extern long rotTarget;

extern int linDir;
extern long linTarget;

extern float distAtAvoid;

float lastTimeKv = 0.0;

extern boolean blocked;
extern float timeBlocked;


boolean rotCommand() {
  
  M_L.setK(200);
  M_R.setK(200);

  float dst = abs( (M_L.encoderPos + M_R.encoderPos)) / 2.0;
  boolean fin = false;

  if(30 < abs(rotTarget - dst)) {

    float d_rot = M_L.encoderPos - M_R.encoderPos;
    float currTime = millis();

    if(dst >= rotTarget * (1.0/5.0)) {
  
      if(abs(M_L.currSpeed) < 0.0005 && abs(M_R.currSpeed) < 0.0005 && (currTime - lastTimeKv) > 100 && abs(M_L.currSpeed) < abs(M_L.targetSpeed) && abs(M_R.currSpeed) < abs(M_R.targetSpeed)){
        M_L.addToKv(0.1);
        M_R.addToKv(0.1);
        lastTimeKv = currTime;
        
      }
      
      float vit = max(rotTarget - dst, 0.0) * (5.0 / 4.0) * 0.22 / rotTarget + 0.05; // Commande en trapèze FTW
      M_L.setSpeed(vit * rotDir - d_rot/2500.0);
      M_R.setSpeed(vit * rotDir + d_rot/2500.0);
      
    } 
    else {
      M_L.setSpeed(0.27 * rotDir - d_rot/2500.0);
      M_R.setSpeed(0.27 * rotDir + d_rot/2500.0);
    }

  } 
  else {
    fin = true;
  }
  
  if(abs(M_L.currSpeed) < 0.0005 && abs(M_R.currSpeed) < 0.0005){
    if(!blocked){
      timeBlocked = millis();
      blocked = true;
    }
  }else{
   blocked = false;
  }
  
  if(blocked && millis() - timeBlocked > 1000){
    fin = true;
  }
  
  
  if(fin){
    M_L.setKv(1);
    M_R.setKv(1);
    M_L.setSpeed(0);
    M_R.setSpeed(0);
    blocked = false;
    return true;
  }else{
    return false;
  }
  
}


boolean linCommand() {
  
  M_L.setK(200);
  M_R.setK(200);
  
  float dst = abs( (M_R.encoderPos - M_L.encoderPos)) / 2.0;
  boolean fin = false;

  if(20 < abs(linTarget - dst)) {

    float d_lin = M_R.encoderPos + M_L.encoderPos;
    float currTime = millis();

    if(dst >= linTarget * (4.0/5.0)) {
      
       if(abs(M_L.currSpeed) < 0.0005 && abs(M_R.currSpeed) < 0.0005 && (currTime - lastTimeKv) > 100 && abs(M_L.currSpeed) < abs(M_L.targetSpeed) && abs(M_R.currSpeed) < abs(M_R.targetSpeed)){
        M_L.addToKv(0.12);
        M_R.addToKv(0.12);
        lastTimeKv = currTime;
      }
      
      
      float vit = max(linTarget - dst, 0.0) * (5.0 / 1.0) * 0.36 / linTarget + 0.1; // Commande en trapèze FTW
      
      float diffK = 250;
      
      if(dst >= linTarget * (7.0/8.0))
        diffK = 1000;
      else
        diffK = 250;
      
      M_L.setSpeed(-vit * linDir - d_lin/diffK);
      M_R.setSpeed(vit * linDir - d_lin/diffK);
    } 
    else {
      M_L.setSpeed(-0.46 * linDir - d_lin/250.0);
      M_R.setSpeed(0.46 * linDir - d_lin/250.0);
    }
  } 
  else {
    fin = true;
  }
  
  if(abs(M_L.currSpeed) < 0.0005 && abs(M_R.currSpeed) < 0.0005){
    if(!blocked){
      timeBlocked = millis();
      blocked = true;
    }
  }else{
   blocked = false;
  }
  
  if(blocked && millis() - timeBlocked > 1000){
    fin = true;
  } 
  
  if(fin){
    M_L.setKv(1);
    M_R.setKv(1);
    M_L.setSpeed(0);
    M_R.setSpeed(0);
    blocked = false;
    return true;
  }else{
    return false;
  }
}


boolean avoidCommand() {
  
  float dst = abs( (M_R.encoderPos - M_L.encoderPos)) / 2.0;

  if(dst > 50) {
    float d_lin = M_R.encoderPos + M_L.encoderPos;
    M_L.setSpeed(0.3 * linDir - d_lin/250.0);
    M_R.setSpeed(-0.3 * linDir - d_lin/250.0);
    
    return false;
  } 
  else {
    M_L.setSpeed(0);
    M_R.setSpeed(0);
    delay(100);
    
    return true;
  }
}

