#include <Arduino.h>
#include <Servo.h>
#include "poissons.h"

extern Servo servoSortie;
extern Servo servoBase;

void commandeServo(Servo servo, int angleDebut, int angleFin, int delai){
  
  if(angleFin > angleDebut){
    for(int i = angleDebut ; i < angleFin ; i++){
      servo.write(i);
      delay(delai);
    }
  }else{
    for(int i = angleDebut ; i > angleFin ; i--){
      servo.write(i);
      delay(delai);
    }
  }
  
}

void moteurAimants(int sens, int delai, int pwm){

  analogWrite(PIN_POISSONS_AIMANTS_PWM, pwm);
  
  if(sens == 1){
    digitalWrite(PIN_POISSONS_AIMANTS_1, HIGH);
    digitalWrite(PIN_POISSONS_AIMANTS_2, LOW);
    
  }else{
    digitalWrite(PIN_POISSONS_AIMANTS_1, LOW);
    digitalWrite(PIN_POISSONS_AIMANTS_2, HIGH);
  }
  
  delay(delai);
  digitalWrite(PIN_POISSONS_AIMANTS_1, LOW);
  digitalWrite(PIN_POISSONS_AIMANTS_2, LOW);

}


void moteurCable(int sens, int delai, int pwm){

  analogWrite(PIN_POISSONS_CABLE_PWM, pwm);
  
  if(sens == 1){
    digitalWrite(PIN_POISSONS_CABLE_1, HIGH);
    digitalWrite(PIN_POISSONS_CABLE_2, LOW);
    
  }else{
    digitalWrite(PIN_POISSONS_CABLE_1, LOW);
    digitalWrite(PIN_POISSONS_CABLE_2, HIGH);
  }
  
  delay(delai);
  digitalWrite(PIN_POISSONS_CABLE_1, LOW);
  digitalWrite(PIN_POISSONS_CABLE_2, LOW);

}

void initPoissons(){
  
  servoSortie.attach(PIN_POISSONS_SORTIE);
  servoSortie.write(40);
  servoBase.attach(PIN_POISSONS_BASE);
  servoBase.write(85);
  pinMode(PIN_POISSONS_AIMANTS_1, OUTPUT);
  pinMode(PIN_POISSONS_AIMANTS_2, OUTPUT);
  pinMode(PIN_POISSONS_AIMANTS_PWM, OUTPUT);
  pinMode(PIN_POISSONS_CABLE_1, OUTPUT);
  pinMode(PIN_POISSONS_CABLE_2, OUTPUT);
  pinMode(PIN_POISSONS_CABLE_PWM, OUTPUT);

}


void deployerPoissons(){
  
    // Deploiement
  commandeServo(servoSortie, 40, 140, 20);
  
  // Descente cable
  moteurCable(-1, 3000, 200);
  
  // Balayage
  for(int i = 0 ; i < 3 ; i++){
    commandeServo(servoBase, 85, 165, 10);
    commandeServo(servoBase, 165, 5, 10);
    commandeServo(servoBase, 5, 85, 10);
  }
  
  // Remontee cable
  moteurCable(1, 3000, 200);
  moteurCable(1, 1200, 150);
  
  
}

void rangerPoissons(){
  
  // Petite descente cable puis aimants
  moteurCable(-1, 2000, 150);
  moteurAimants(-1, 4500, 200);
  
  // Remontee aimants
  moteurAimants(1, 3500, 200);
  moteurAimants(1, 1000, 150);
  
  // Remontee cable
  moteurCable(1, 3000, 150);
  
  // Rangement
  commandeServo(servoSortie, 140, 40, 20);
  
  
}
