#include <Servo.h> 
#include <NewPing.h>
#include <AFMotor.h>
#define TRIGGER_PIN  A4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A5 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int distance;
AF_DCMotor motor1(1, MOTOR12_1KHZ); // create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor2(2, MOTOR12_1KHZ); // create motor #2, using M2 output, set to 1kHz PWM frequency
AF_DCMotor motor3(3, MOTOR12_1KHZ); // create motor #1 using M3 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor4(4, MOTOR12_1KHZ); // create motor #2, using M4 output, set to 1kHz PWM frequency
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int pos = 50;    // variable to store the servo position 

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
   motor1.setSpeed(155);     // set the speed to 200/255
   motor2.setSpeed(155);     // set the speed to 200/255
   motor3.setSpeed(155);     // set the speed to 200/255
   motor4.setSpeed(155);     // set the speed to 200/255
   myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
}

void loop() {
  Serial.flush();                     
  readPing();
  //myservo.write(50);
  //delay(120);
  for(pos = 50; pos < 130; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);    // waits 15ms for the servo to reach the position 
    readPing();
    if(pos >= 50 && distance>1 && distance<20) {  // testing for left turn
    while (pos >= 50 && distance>1 && distance<20){
     
      left();  
      readPing();
    }
}
} 

  for(pos = 130; pos>=51; pos-=1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
    readPing();
    if(pos<=130 && distance>1 && distance<20) {  // testing for right turn
    while (pos<=130 && distance>1 && distance<20){
     
      right();  
      readPing();
    }
}
}

forward(); // Default movement is forward.
}

int readPing() { // read the ultrasonic sensor distance
  delay(50);     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  distance=(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println(distance);
  return distance;
}
void Stop() {
    motor1.run(RELEASE);      // stopped
    motor2.run(RELEASE);      // stopped
    motor3.run(RELEASE);      // stopped
    motor4.run(RELEASE);      // stopped
  }  // stop the motors.
//-------------------------------------------------------------------------------------------------------------------------------------
void forward() {
    
     motor1.run(FORWARD);      // turn it on going forward
     motor2.run(FORWARD);      // turn it on going forward
     motor3.run(FORWARD);      // turn it on going forward
     motor4.run(FORWARD);      // turn it on going forward    
  
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Backward() {
    
     motor1.run(BACKWARD);     // the other way
     motor2.run(BACKWARD);     // the other way backward
     motor3.run(BACKWARD);     // the other way
     motor4.run(BACKWARD);     // the other way
     delay(1500);
     Stop();
}  
void left() {
    Backward();  
    motor1.setSpeed(255);     // set the speed to 200/255
    motor4.setSpeed(255);     // set the speed to 200/255
    motor1.run(FORWARD);     // the other way
    motor2.run(RELEASE);     // the other way
    motor4.run(FORWARD);     // the other way   FORWARD LEFT
    motor3.run(RELEASE);     // the other way
    delay(1200);             // run motors this way for 1200ms
 
}  
void right() {
    Backward();
    motor2.setSpeed(255);     // set the speed to 200/255
    motor3.setSpeed(255);     // set the speed to 200/255
    motor1.run(RELEASE);     // the other way
    motor2.run(FORWARD);     // the other way
    motor4.run(RELEASE);     // the other way   FORWARD LEFT
    motor3.run(FORWARD);     // the other way
    delay(1200);             // run motors this way for 1200ms
 
}
