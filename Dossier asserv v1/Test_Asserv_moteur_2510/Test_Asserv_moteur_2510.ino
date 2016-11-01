
int MotorADirection=12
int BrakeA=9
int MotorSpeedA=3
int MotorBDirection=13
int BrakeB=8
int MotorBSpeed=11


void setup() {
  // put your setup code here, to run once:
pinMode(MotorADirection,OUTPUT);
pinMode(BrakeA,OUTPUT);
pinMode(MotorBDirection,OUTPUT);
pinMode(BrakeB,OUTPUT);
   // Serial.begin(9600);
    

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(MotorADirection,1);
digitalWrite(BrakeA,0);
analogWrite(MotorSpeed,100);

  //fonction rampe pour le démarrage du moteur : ajuster les paramètres en testant sur le robot

}

int Rampe(int pente, int maxi){
  
  int i=0;
  while(i<= maxi)
  {
    i = i + pente/40;
    analogWrite(MotorSpeed,i);

    delay(int(50))
  }
  

  
}
















