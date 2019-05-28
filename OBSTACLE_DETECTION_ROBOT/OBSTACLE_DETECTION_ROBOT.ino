#include <AFMotor.h>
AF_DCMotor motor1(3);
AF_DCMotor motor2(2);
int analogPin1 = A0;     // Infrared Sensor (Right lead) connected to analog pin A0 right hand side

int analogPin2 = A1;     // Infrared Sensor (Right lead) connected to analog pin A1 left hand side
int threshold = 255;
                                   
int val1 = 0;                  // variable to store the value read from A0 
int val2 = 0;                  // variable to store the value read from A1
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
  motor1.setSpeed(70); 
  motor2.setSpeed(70);   // set the speed to 200/255
}
/*void loop()
{
  /*val1 = analogRead(analogPin1);    // read the input pin
  float voltage1= val1*(5.0/1023.0);  
  Serial.println("val1");                           // debug value

  //Serial.println(val1);                           // debug value
  Serial.println(voltage1);


  val2 = analogRead(analogPin2);    // read the input pin
  float voltage2=val2*(5.0/1023.0);
  Serial.println("val2");
  //Serial.println(val2);                           // debug value
  // debug value
  Serial.println(voltage2);*/
    void loop()
    
{  
  val1 = analogRead(analogPin1);    // read the input pin
  
  val2 = analogRead(analogPin2);    // read the input pin
    if(val1<threshold && val2>threshold) {  // testing for left turn
    while (val1<threshold && val2>threshold){
     
      right();  
      val1 = analogRead(analogPin1);    // read the input pin   
      val2 = analogRead(analogPin2);  
    }
}
  else if(val1>threshold && val2<threshold){  // tesing for right turn
    while (val1>threshold && val2<threshold){
      
      left();
      val1 = analogRead(analogPin1);
      val2 = analogRead(analogPin2);
    }
 }
forward(); // Default movement is forward.
}

void forward()
{
motor1.run(BACKWARD);      // turn it on going forward WIRE ARE IN REVERSE POLARITY
     motor2.run(BACKWARD);      // turn it on going forward
      Serial.println("Motor FORWARD!");
    
  }
void right()
{
  //  back(); 
    motor2.run(BACKWARD);      
    motor1.run(FORWARD);
    delay(10);
    Serial.println("Motor right!");
          
}
void left()
{
   // back();
    motor1.run(BACKWARD);      
    motor2.run(FORWARD); 
    delay(10);
    Serial.println("Motor left!");
}
 
/*void back()
{
  
motor2.run(FORWARD);      
    motor1.run(FORWARD); 
    delay(10);
    Serial.println("Motor Backward!");
} 
*/
