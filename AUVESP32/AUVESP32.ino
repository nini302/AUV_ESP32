#include <Servo.h>


Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
/*  前
  4   5
  0   1
  2   3
  6   7
    後
*/
void setup() {
  
 Serial.begin(9600);
 servo0.attach(0);
 servo1.attach(1);
 servo2.attach(2);
 servo3.attach(3);
 servo4.attach(4);
 servo5.attach(5);
 servo6.attach(6);
 servo7.attach(7);
 Stop();// send "stop" signal to ESC.

 delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  Serial.println("Enter motor direction");
  while (Serial.available() == 0);
  int direction = Serial.parseInt();
  if(direction="forward"){
    Serial.println("Enter PWM signal value 1100 to 1900, 1500 to stop");
    while (Serial.available() == 0);
    int val = Serial.parseInt();
    if(val < 1100 || val > 1900){
      Serial.println("not valid");
      }
    else{
      forward(val); // Send signal to ESC.
      delay(10000);
    }
  }
  else if(direction="down"){
    Serial.println("Enter PWM signal value 1100 to 1900, 1500 to stop");
    while (Serial.available() == 0);
    int val = Serial.parseInt();
    if(val < 1100 || val > 1900){
      Serial.println("not valid");
      }
    else{
      down(val); // Send signal to ESC.
      delay(10000);
    }
  }
  else if(direction="Stop"){
    Stop();
    delay(10000);
  } 
 
  

}
void forward(int val){
  servo0.writeMicroseconds(val);
  servo1.writeMicroseconds(val);
  servo2.writeMicroseconds(val);
  servo3.writeMicroseconds(val);
}
void down(int val){
  servo4.writeMicroseconds(val);
  servo5.writeMicroseconds(val);
  servo6.writeMicroseconds(val);
  servo7.writeMicroseconds(val);
}
void Stop(){
  servo0.writeMicroseconds(1500);
  servo1.writeMicroseconds(1500);
  servo2.writeMicroseconds(1500);
  servo3.writeMicroseconds(1500);
  servo4.writeMicroseconds(1500);
  servo5.writeMicroseconds(1500);
  servo6.writeMicroseconds(1500);
  servo7.writeMicroseconds(1500);
}
void testmode(){
  val=1700;
  servo0.writeMicroseconds(val);
  servo1.writeMicroseconds(val);
  servo2.writeMicroseconds(val);
  servo3.writeMicroseconds(val);
  servo4.writeMicroseconds(val);
  servo5.writeMicroseconds(val);
  servo6.writeMicroseconds(val);
  servo7.writeMicroseconds(val);
  delay(10000);
  val=1300;
  servo0.writeMicroseconds(val);
  servo1.writeMicroseconds(val);
  servo2.writeMicroseconds(val);
  servo3.writeMicroseconds(val);
  servo4.writeMicroseconds(val);
  servo5.writeMicroseconds(val);
  servo6.writeMicroseconds(val);
  servo7.writeMicroseconds(val);
  delay(10000);
}