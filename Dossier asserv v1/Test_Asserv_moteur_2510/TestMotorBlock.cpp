#include <Arduino.h>
#include "TestMotorBlock.h"

MotorBlock::MotorBlock (int dir, int brake, int pwm, int encoderA, int encoderB : D(dir),B(brake),P(pwm),pinA(encoderA),pinB(encoderB)) {}

void MotorBlock::init(){
    pinMode(B,OUTPUT);       /// brake force a arreter le moteur, sinon il peut tourner dans le vide.
    pinMode(D,OUTPUT);       /// dir change le sens du moteur
    pinMode(P,OUTPUT);       /// pwm entraine le moteur
}


void MotorBlock setTargetSpeed(requiredTargetSpeed){
    targetSpeed = requiredTargetSpeed;
}

///"cette constante se regle a l'arrache" dixit SoubaK et Mascart
void Motorblock::setK(requiredK)){
    K = requiredK;
}

/// ----------> comprendre à quoi sert cette constante
void MotorBlock::setKv(requiredKv) {
    Kv = requiredKv;
}
/// Pourquoi incremente-t-on la constante Kv ?
void MotorBlock::addtoKv(delta){
    Kv += delta;
}

void MotorBlock::run(){                 /// pour chaque moteur, cette fonction se fait tous les cycles de timer (ici 20 ms)
    currSpeed = nbTopsDone * 0,3330/(50);           /// Une valeur est le passage de degres a radians (?) et l'autre le nombre de crans du codeur
    nbTopsDone = 0;

    float cmd = (targetSpeed - currSpeed)*K;

    /// A quoi sert cet offset ?  ----------------> fait partie des trucs a changer/ameliorer cette annee
    //Offset
    cmd += ((cmd > 0)- (cmd < 0)) * constrain(OFFSET*Kv,50,90);     /// les booleens sont traduits automatiquement en int par la soustraction

    //Saturation
    cmd = constrain(cmd,-255,255);
    /// trouver a quoi ca sert.
    cmdDEBUG = cmd;

    digitalWrite(D, cmd > 0 ? LOW : HIGH); /// si cmd > 0 alors on envoie LOW sinon HIGH
    analogWrite(P,abs(cmd));
}
