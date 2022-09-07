// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 7; 
int servoPin2 = 6;
// Create a servo object 
Servo Servo1; 
// Assigning integer variables that will be used to change servo angles
int servo_ang = 0;

void setup() { 
   Serial.begin(9600);
   // Attach the servo to the used pin number 
   Servo1.attach(servoPin); 
   // Servo set up
   for(int i_Pos = 130; i_Pos>=0; i_Pos-=1) { // goes from 180 degrees to 0 degrees
     Servo1.write(i_Pos); // tell servo to go to position in variable 'i_Pos'
     int i_Val = Servo1.read();
//     Serial.print("i_Val = ");
//     Serial.println(i_Val);
     delay(5); // waits 15ms for the servo to reach the position
   }
}

void loop(){ 
  if (Serial.available() > 0) {
    // Sends message back if servo ang is pushing beyond 0-90
    if (servo_ang < 0 || servo_ang > 90) {
      Serial.println("You've gone beyond the telescope's working angle, go back");
    } else {
    // Move the servo according to input received
      int data = Serial.read() - '0';
      if (data == 1) {
        servo_ang = servo_ang + 10;
        Servo1.write(servo_ang); 
      }
      if (data == 2) {
        servo_ang = servo_ang - 10;
        Servo1.write(servo_ang); 
      }
      if (data == 11) {
        servo_ang = servo_ang + 20;
        Servo1.write(servo_ang);  
      }
      if (data == 22) {
        servo_ang = servo_ang - 20;
        Servo1.write(servo_ang); 
      }
    }
  }
}
