#include <AFMotor.h>
#include <Servo.h>
Servo servo;
#define trigPin  A0  
#define echoPin  A1  

AF_DCMotor LF(1);
AF_DCMotor LB(2);
AF_DCMotor RF(3);
AF_DCMotor RB(4);


void setup()
  {
    servo.attach(10);
    pinMode(trigPin, OUTPUT);         
    pinMode(echoPin, INPUT);          
    LF.setSpeed(200);
    LB.setSpeed(200);
    RF.setSpeed(200);
    RB.setSpeed(200);
  }

void loop()
  {
    float distance = 0.00;
    float RightDistance = 0.00;
    float LeftDistance = 0.00;    
    distance = search();  
        
    if(distance <= 30) 
      {
          RobotStop(); 
          delay(100);
          servo.write(5);
          delay(300);
          RightDistance = search();
          delay(100);
          servo.write(180);
          delay(300);
          LeftDistance = search();
          delay(100);
          servo.write(90);
          delay(300);
         if(LeftDistance > RightDistance)
           { 
              RobotBackward();
              delay(100);
              RobotStop();
              delay(100);
              RobotLeft();
              delay(500);
              RobotStop();
              delay(100);  
           }
          else 
            {
              RobotBackward();
              delay(100);
              RobotStop();
              delay(100);
              RobotRight();
              delay(500); 
              RobotStop();
              delay(100);             
            }
      }
   else
   {
     RobotForward();
   }
}


float search(void)
  {
    float duration = 0.00;             
    float CM = 0.00;      
    digitalWrite(trigPin, LOW);        
    delayMicroseconds(2);                
    digitalWrite(trigPin, HIGH);      
    delayMicroseconds(10);             
    digitalWrite(trigPin, LOW);           
    duration = pulseIn(echoPin, HIGH);
    CM = (duration / 58.82);    
    return CM;
  }

void RobotForward()
  {
    LF.run(FORWARD);
    RF.run(FORWARD);
    LB.run(FORWARD);
    RB.run(FORWARD);
  }
void RobotBackward()
  {
    LF.run(BACKWARD);
    LB.run(BACKWARD);
    RF.run(BACKWARD);
    RB.run(BACKWARD);
  }
void RobotLeft()
  {
    LF.run(BACKWARD);
    LB.run(BACKWARD);
    RF.run(FORWARD);
    RB.run(FORWARD);
  }
void RobotRight()
  {
    LF.run(FORWARD);
    LB.run(FORWARD);
    RF.run(BACKWARD);
    RB.run(BACKWARD);
  }
void RobotStop()
  {
    LF.run(RELEASE);
    LB.run(RELEASE);
    RF.run(RELEASE);
    RB.run(RELEASE);
  }

  
