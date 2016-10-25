#include "MotorBlock.h"
#include "command.h"

extern MotorBlock M_L;
extern MotorBlock M_R;
extern int asserMode;

extern int rotDir;
extern long rotTarget;

extern int linDir;
extern long linTarget;


boolean rotCommand() {

  float dst = abs( (M_L.encoderPos + M_R.encoderPos)) / 2.0;

  if(dst < rotTarget) {

    float d_rot = M_L.encoderPos - M_R.encoderPos;

    if(dst >= rotTarget * (4.0/5.0)) {
      float vit = max(rotTarget - dst, 0.0) * 5.0 * 0.17 / rotTarget + 0.23; // Commande en trapèze FTW
      M_L.run(vit * rotDir - d_rot/200.0);
      M_R.run(vit * rotDir + d_rot/200.0);
    } 
    else {
      M_L.run(0.4 * rotDir - d_rot/200.0);
      M_R.run(0.4 * rotDir + d_rot/200.0);
    }
    return false;
  } 
  else {
    M_L.brake();
    M_R.brake();
    delay(1000);
    M_L.unbrake();
    M_R.unbrake();
    
    return true;
  }

}


boolean linCommand() {
  
  float dst = abs( (M_R.encoderPos - M_L.encoderPos)) / 2.0;

  if(dst < linTarget) {

    float d_lin = M_R.encoderPos + M_L.encoderPos;

    if(dst >= linTarget * (4.0/5.0)) {
      float vit = max(linTarget - dst, 0.0) * 5.0 * 0.18 / linTarget + 0.22; // Commande en trapèze FTW
      M_L.run(-vit * linDir - d_lin/250.0);
      M_R.run(vit * linDir - d_lin/250.0);
    } 
    else {
      M_L.run(-0.4 * linDir - d_lin/250.0);
      M_R.run(0.4 * linDir - d_lin/250.0);
    }
    return false;
  } 
  else {
    M_L.brake();
    M_R.brake();
    delay(1000);
    M_L.unbrake();
    M_R.unbrake();
    
    return true;
  }
}


boolean avoidCommand() {
  
  float dst = abs( (M_R.encoderPos - M_L.encoderPos)) / 2.0;

  if(dst > 50) {
    float d_lin = M_R.encoderPos + M_L.encoderPos;
    M_L.run(0.4 * linDir - d_lin/250.0);
    M_R.run(-0.4 * linDir - d_lin/250.0);
    
    return false;
  } 
  else {
    M_L.brake();
    M_R.brake();
    delay(1000);
    M_L.unbrake();
    M_R.unbrake();
    
    return true;
  }
}

