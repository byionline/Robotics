#include <AFMotor.h>
AF_DCMotor motor1(1); // create motor #1, 64KHz pwm
AF_DCMotor motor2(2); // create motor #2, 64KHz pwm
AF_DCMotor motor3(3); // create motor #3, 64KHz pwm
AF_DCMotor motor4(4); // create motor #4, 64KHz pwm


void setup() {
  
  Serial.begin(9600);
  Serial.println("Motor test!");
  //Serial.flush();
}

void loop() {
  Serial.flush();
  // see if there's incoming serial data:
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    int incomingByte = Serial.read();
    
    // action depending on the instruction
    // as well as sending a confirmation back to the app
    switch (incomingByte) {
      case 'F':
      motor1.setSpeed(255);     // set the speed to 200/255
      motor2.setSpeed(255);     // set the speed to 200/255
      motor3.setSpeed(255);     // set the speed to 200/255
      motor4.setSpeed(255);     // set the speed to 200/255
	forward();
        Serial.println("Going forward");
        break;
      case 'R':
      motor1.setSpeed(255);     // set the speed to 200/255
      motor2.setSpeed(255);     // set the speed to 200/255
      motor3.setSpeed(255);     // set the speed to 200/255
      motor4.setSpeed(255);     // set the speed to 200/255
        right();
        Serial.println("Turning right");
        break;
      case 'L':
      motor1.setSpeed(255);     // set the speed to 200/255
      motor2.setSpeed(255);     // set the speed to 200/255
      motor3.setSpeed(255);     // set the speed to 200/255
      motor4.setSpeed(255);     // set the speed to 200/255
        left();
        Serial.println("Turning left");
        break;
      case 'B':
      motor1.setSpeed(255);     // set the speed to 200/255
      motor2.setSpeed(255);     // set the speed to 200/255
      motor3.setSpeed(255);     // set the speed to 200/255
      motor4.setSpeed(255);     // set the speed to 200/255
        backward();
        Serial.println("Going backwards");
        break;
      case 'S':
        stop();
        Serial.println("Stopping");
        break;
      default: 
        // if nothing matches, do nothing
        break;
    }
  }
  delay(10);
}

void forward()
{
     motor1.run(FORWARD);      // turn it on going forward
     motor2.run(FORWARD);      // turn it on going forward
     motor3.run(FORWARD);      // turn it on going forward
     motor4.run(FORWARD);      // turn it on going forward
      Serial.println("Motor forward!");}
void right()
{
    motor1.run(FORWARD);     // the other way
    motor2.run(RELEASE);     // the other way
    motor4.run(FORWARD);     // the other way   FORWARD RIGHT
    motor3.run(RELEASE);     // the other way
    Serial.println("Motor right!");
}
void left()
{
    motor1.run(RELEASE);     // the other way
    motor2.run(FORWARD);     // the other way
    motor4.run(RELEASE);     // the other way   FORWARD LEFT
    motor3.run(FORWARD);     // the other way
    Serial.println("Motor left!");
}
void backward()
{
     motor1.run(BACKWARD);     // the other way
     motor2.run(BACKWARD);     // the other way backward
     motor3.run(BACKWARD);     // the other way
     motor4.run(BACKWARD);     // the other way
     Serial.println("Motor backward!");}

void stop()
{
    motor1.run(RELEASE);      // stopped
    motor2.run(RELEASE);      // stopped
    motor3.run(RELEASE);      // stopped
    motor4.run(RELEASE);      // stopped
     //motor1.run(BRAKE);      // turn it on going stop BRAKE DON'T STOP THE ROBOT
     //motor2.run(BRAKE);      // turn it on going stop
    Serial.println("Motor stopping!");}

