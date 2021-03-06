#ifndef MotorBlock_h
#define MotorBlock_h

#define OFFSET 15
      
class MotorBlock
{
  public:
    MotorBlock(int dir,int brake,int pwm, int encoderA, int encoderB);
    void init();
    void run(double targetSpeed);
    void brake();
    void unbrake();
    void coderInterrupt();
    
    volatile long encoderPos;
    volatile double prevTime;
    volatile double currTime;
    volatile double currDirection;
    
    int pinA;
    int pinB;
    
    double currSpeed;
    
    float cmdDEBUG;
    
  private:
    int D;
    int B;
    int P;
};

       
#endif
