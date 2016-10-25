#ifndef MotorBlock_h
#define MotorBlock_h

#define OFFSET 0
      
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
    //volatile double prevTime;
    //volatile double currTime;
    
    volatile long nbTopsDone;
    
    int pinA;
    int pinB;
    
    double currSpeed;
    double dbg_targetSpeed;
    
    float cmdDEBUG;
    
  private:
    int D;
    int B;
    int P;
};

       
#endif
