#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>
// 默认地址 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
byte servoPin = 9;
Servo servo;

#define SERVO_0  290 
#define SERVO_45  310 
#define SERVO_90  320 
#define SERVO_135  330 
#define SERVO_180  340 

// our servo # counter
uint8_t servonum = 0;
char comchar;

void setup() {
  Serial.begin(115200);
  Serial.println("8 channel Servo test!");

  //pwm.begin();
  //pwm.setPWMFreq(50);  // 50HZ更新频率，相当于20ms的周期


   servo.attach(servoPin);
  servo.writeMicroseconds(1500); 
  
  delay(10);
}

void loop() {
    while(Serial.available()>0){
    comchar = Serial.read();//读串口第一个字节
    switch(comchar)
    {
      case '0':
      servo.writeMicroseconds(1500);
      //pwm.setPWM(0, 0, SERVO_0);
      Serial.write(comchar);
      break;
      case '1':
      servo.writeMicroseconds(1520);
      //pwm.setPWM(0, 0, SERVO_45);
      Serial.write(comchar);
      break;
      case '2':
      servo.writeMicroseconds(1530);
      //pwm.setPWM(0, 0, SERVO_90);
      Serial.write(comchar);
      break;
      case '3':
      servo.writeMicroseconds(1700);
      //pwm.setPWM(0, 0, SERVO_135);
      Serial.write(comchar);
      break;       
      case '4':
      servo.writeMicroseconds(1350);
      //pwm.setPWM(0, 0, SERVO_180);
      Serial.write(comchar);
      break;
      default:    //匹配失败
      Serial.write(comchar);
      break;                  
    }
  }
}

