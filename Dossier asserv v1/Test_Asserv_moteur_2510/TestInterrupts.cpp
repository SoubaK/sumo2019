#include <Arduino.h>
#include "MotorBlock.h"
#include "interrupts.h"

extern MotorBlock M_L;
extern MotorBlock M_R;

void coderL()
{
  if (digitalRead(M_L.pinA) == digitalRead(M_L.pinB)) {        /// cette condition sert a determiner dans quel sens tourne la roue.
    M_L.encoderPos--;                                          /// Si les deux detecteurs ont la meme valeur, la roue tourne vers l'avant. Regarder le fonctionnement d'un codeur incremental.
    M_L.nbTopsDone--;
  } else {
    M_L.encoderPos++;
    M_L.nbTopsDone++;
  }
}

void coderR()
{
  if (digitalRead(M_R.pinA) == digitalRead(M_R.pinB)) {
    M_R.encoderPos++;
    M_R.nbTopsDone++;
  } else {
    M_R.encoderPos--;
    M_R.nbTopsDone--;
  }
}


/// nbTopsDone correspond au nombre de Pulses.
/// Les deux roues ne sont pas installées dans le même sens. Quand le robot avance,
///cela signifie que du point de vue des moteurs, les roues ne tournent pas dans le meme sens.
