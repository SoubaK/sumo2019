#include "Arduino.h"
#include "BaseRoulante.hpp"
#include "StepperSumo.hpp"

BaseRoulante::BaseRoulante(float largeur, float diamRoue, int nbrStep, float freqStep, int pinStepGauche, int pinDirGauche, int pinSleepGauche, int pinStepDroite, int pinDirDroite, int pinSleepDroite) {
    m_largeur = largeur;
    m_diamRoue = diamRoue;
    m_nbrStep = nbrStep;
    m_stepperGauche = StepperSumo(pinDirGauche, pinStepGauche, pinStepGauche);
    m_stepperDroite = StepperSumo(pinDirDroite, pinStepDroite, pinSleepDroite);
    m_dureeStep = 1/m_freqStep;
}

BaseRoulante::ligneDroite(bool dir, float distance) {
  int nbrStep = (distance*m_nbrStep*10)/(3.1415*m_diamRoue);
  wake();
  m_stepperGauche.dir(not dir);
  m_stepperDroite.dir(dir);

  for (int i=0; i<nbrStep, i++) {
    m_stepperGauche.stepUp();
    m_stepperDroite.stepUp();
    delayMicroseconds(m_dureeStep*1000);
    m_stepperGauche.stepDown();
    m_stepperDroite.stepDown();
    delayMicroseconds(m_dureeStep*1000);
  }

  sleep();
}

BaseRoulante::rotation(bool trigo, float degres) {
  int nbrStep = (degres*m_largeur*m_nbrStep*10)/(2*360*m_diamRoue);
  wake();
  m_stepperDroite.dir(trigo);
  m_stepperGauche.dir(trigo);

  for (int i=0; i<nbrStep, i++) {
    m_stepperGauche.stepUp();
    m_stepperDroite.stepUp();
    delayMicroseconds(m_dureeStep*1000);
    m_stepperGauche.stepDown();
    m_stepperDroite.stepDown();
    delayMicroseconds(m_dureeStep*1000);
  }

  sleep();
}

BaseRoulante::wake() {
  m_stepperDroite.wake();
  m_stepperGauche.wake();
}

BaseRoulante::sleep() {
  m_stepperGauche.shutdown();
  m_stepperDroite.shutdown();
}
