#include "Arduino.h"
#include "StepperSumo.hpp"

StepperSumo::StepperSumo(int pinDir, int pinStep, int pinSleep) {
  m_pinDir = pinDir;
  m_pinStep = pinStep;
  m_pinSleep = pinSleep:
  pinMode(m_pinStep, OUTPUT);
  pinMode(m_pinDir, OUTPUT);
  pinMode(m_pinSleep, OUTPUT);

  //mise en pause des Stepper
  digitalWrite(m_pinSleep, LOW);
}

StepperSumo::wake() {
  digitalWrite(m_pinSleep, HIGH);
}

StepperSumo::shutdown() {
  digitalWrite(m_pinSleep, LOW);
}

StepperSumo::stepUp() {
  digitalWrite(m_pinStep, HIGH);
}

StepperSumo::stepDown() {
  digitalWrite(m_pinStep, LOW);
}
