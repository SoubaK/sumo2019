#include "serialUtil.h"

extern char tempBuffer[10];
extern boolean reading;
extern int i;
extern boolean cmdAvailable;

extern int rotDir;
extern long rotTarget;
extern int linDir;
extern long linTarget;



void readSerial() {

  char c = 0;

  if(Serial.available() > 0) {
    while((c = Serial.read()) != -1 && !cmdAvailable){

      if(!reading){
        reading = (c == 'b');
      }
      else{
        if(c == 'e') {

          if(i == 10){
            cmdAvailable = true;
          }

          c = 0;
          i = 0;
          reading = false;

        }
        else{
          tempBuffer[i] = c;
          i++;
        }
      }
    }
  }
}


boolean getTarget() {

  String str(tempBuffer);
  rotTarget = str.substring(0,5).toInt() * 0.76575;
  linTarget = str.substring(5,10).toInt() * 6.00585;
  rotDir = (rotTarget > 0) - (rotTarget < 0);
  linDir = (linTarget > 0) - (linTarget < 0);
  rotTarget = abs(rotTarget);
  linTarget = abs(linTarget);

  if(rotTarget != 0 || linTarget != 0)
    return true;
  else
    return false;

}


