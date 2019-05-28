#include <AFMotor.h>
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
//#define LS A0     // left sensor
//#define RS A1    // right sensor
int LS = A0;     // Infrared Sensor (Right lead) connected to analog pin 3

int RS = A1;     // Infrared Sensor (Right lead) connected to analog pin 3
                      


//AF_DCMotor motor(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
  motor1.setSpeed(200); 
  motor2.setSpeed(200);   // set the speed to 200/255
}

  void loop()
{
  if((analogRead(LS==0)) && ((analogRead(RS==0))))     // Move Forward
  {
     motor1.run(FORWARD);      // turn it on going forward
     motor2.run(FORWARD);      // turn it on going forward
      Serial.println("Motor forward!");
  
  }
  
  if((analogRead(LS==0)) && analogRead(RS==1))     // Turn right
  {
    motor1.run(FORWARD);      
    motor2.run(BRAKE); 
 Serial.println("Motor right!");    
    //digitalWrite(LM1, LOW);
    //digitalWrite(LM2, LOW);
    //digitalWrite(RM1, HIGH);
    //digitalWrite(RM2, LOW);
  }
  
  if(analogRead(LS==1) && (analogRead(RS==0)))     // turn left
  {
    motor1.run(BRAKE);      
    motor2.run(FORWARD); 
     Serial.println("Motor left!");
    //digitalWrite(LM1, HIGH);
    //digitalWrite(LM2, LOW);
    //digitalWrite(RM1, LOW);
    //digitalWrite(RM2, LOW);
  }
  
  if((analogRead(LS==1)) && (analogRead(RS==1)))     // stop
  {
    motor1.run(BRAKE);      
    motor2.run(BRAKE); 
     Serial.println("Motor stop!");
    //digitalWrite(LM1, LOW);
    //digitalWrite(LM2, LOW);
    //digitalWrite(RM1, LOW);
    //digitalWrite(RM2, LOW);
  }
}
