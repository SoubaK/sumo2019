
int MotorDirectionA=12;
int BrakeA=9;
int MotorSpeedA=3;
int MotorDirectionB=13;
int BrakeB=8;
int MotorSpeedB=11;

int i=0;
int j=0;
int prevmillisA=0;
int prevmillisB=0;
int currentmillisA=0;
int currentmillisB=0;
int tx_raffraichissement = 20;
void setup() 
{
  // put your setup code here, to run once:
pinMode(MotorDirectionA,OUTPUT);
pinMode(BrakeA,OUTPUT);
pinMode(MotorSpeedA,OUTPUT); 
pinMode(MotorDirectionB,OUTPUT);
pinMode(BrakeB,OUTPUT);
pinMode(MotorSpeedB,OUTPUT);    

}

void loop() 
{
  // put your main code here, to run repeatedly:
  MoteurB(50,1);
}


void MoteurB( int maxi,int sens)
{
  digitalWrite(MotorDirectionB,sens);
    //pente : pourcentage par seconde
  int currentmillisB=millis();  
  if(currentmillisB-prevmillisB>= tx_raffraichissement)  
  {
    prevmillisB=currentmillisB;
    i++;
    analogWrite(MotorSpeedB,i);
    delay(int(tx_raffraichissement));
  }
}

void MoteurA(int maxi,int sens)
{
   digitalWrite(MotorDirectionA,sens);
  int currentmillisA=millis();  
  if(currentmillisA-prevmillisA>= tx_raffraichissement)  
  {
    j++;
    prevmillisA=currentmillisA;
    analogWrite(MotorSpeedA,j);
    delay(int(tx_raffraichissement));
  }
}
