#ifndef "TestCommand.h"
#define "TestCommand.h"

#include <Arduino.h>

/// renvoie un booleen selon si le mouvement doit s'arreter(true) ou non(false)
boolean rotCommand();
/// renvoie un booleen selon si le mouvement doit s'arreter(true) ou non(false)
boolean linCommand();
/// renvoie un booleen selon si on a reussi a eviter l obstacle(ie recule) ou pas(ie attendu que l obstacle disparaisse).
boolean avoidCommand();



#endif
