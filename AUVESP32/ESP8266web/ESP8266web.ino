#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>  //Include the Servo Library
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <Scheduler.h>
#include <Task.h>
#include <LeanTask.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#include "PageIndex.h" //--> Include the contents of the User Interface Web page from website, stored in the same folder as the .ino file  
// Select a Timer Clock


  //--> Defining Servo Port

int pos=310;
int ver=310;
//Make a wifi name and password as access point

const char* ssid = "ESPServo";  // your SSID

const char* password = "12345678"; //WIFI Password




ESP8266WebServer server(80);  //--> Server on port 80
//IP: 192.168.4.1
String SERstate1 = "OFF";

//This routine is executed when you open NodeMCU ESP8266 IP Address in browser

void handleRoot() {

  String s = MAIN_page; //Read HTML contents

  server.send(200, "text/html", s); //Send web page

}
void Forward(double val){
  pwm.setPWM(4, 0, val);
  pwm.setPWM(5, 0, val);
  pwm.setPWM(6, 0, val);
  pwm.setPWM(7, 0, val);
  
}
void Downward(int val){
  pwm.setPWM(0, 0, val);
  pwm.setPWM(1, 0, val);
  pwm.setPWM(2, 0, val);
  pwm.setPWM(3, 0, val);
  
}
void CWrotation(double val){
  double nval=620-val;
  pwm.setPWM(4, 0, val);
  pwm.setPWM(5, 0, nval);
  pwm.setPWM(6, 0, val);
  pwm.setPWM(7, 0, nval);
  
}
void CCWrotation(double val){
  double nval=620-val;
  pwm.setPWM(4, 0, nval);
  pwm.setPWM(5, 0, val);
  pwm.setPWM(6, 0, nval);
  pwm.setPWM(7, 0, val);
  
}
void Stop(){
  int val=310;
  for(int i=0;i<8;i++){
  pwm.setPWM(i, 0, val);
  }
  
}
void task1(double val){
  Downward(330);
  Forward(val);
  delay(3000);
  Stop();
}
void testmode(){
  int val=330;
  for(int i=0;i<8;i++){
  pwm.setPWM(i, 0, val);
  delay(2000);
  //pwm.setPWM(i, 280, 0);
  }
  val=310;
  for(int i=0;i<8;i++){
  pwm.setPWM(i, 0, val);
  delay(2000);
  //pwm.setPWM(i, 280, 0);
  }
  delay(1000);
  val=290;
  for(int i=0;i<8;i++){
  pwm.setPWM(i, 0, val);
  delay(2000);
  //pwm.setPWM(i, 280, 0);
  }
}

void setServoPulse(uint8_t n, double pulse) {
  double basic=4.8828;
  pulse/=basic;
   
  pwm.setPWM(n, 0, pulse);
}
//Procedure for handling servo control
//----------------------------------------------------------------------------------------------------------
void handleServo() {
  String POS = server.arg("servoPOS");
  pos = POS.toInt();
  if(ver!=pos){
    ESP.wdtFeed();
    ver=pos;
  }
  
  //myservo.write(pos);   //--> Move the servo motor according to the POS value
  delay(15);
  Serial.print("Servo Angle:");
  Serial.println(pos);
  server.send(200, "text/plane", "");
}


void controlServo() {
  String t_state = server.arg("SERstate1");
  Serial.println(t_state);
  Serial.println(pos);
  if (t_state == "1") {
    
    SERstate1 = pos;
    Stop();
    
    
  }
  else if (t_state == "2") {
    SERstate1 = pos;
    
    Stop();
    delay(500);
    Forward(pos);
    
  }
  else if (t_state == "3") {
    SERstate1 = pos;
    
    Stop();
    delay(500);
    Downward(pos);
    
  }
  else if (t_state == "4") {
    SERstate1 = pos;
    
    Stop();
    delay(500);
    CWrotation(pos);
    
  }
  else if (t_state == "5") {
    SERstate1 = pos;
    
    Stop();
    CCWrotation(pos);
    
  }
  else if (t_state == "6") {
    SERstate1 = pos;
    
    Stop();
    delay(500);
    testmode();
    
  }
  else if (t_state == "7") {
    SERstate1 = pos;
    
    Stop();
    delay(500);
    task1(pos);
    
  }
  else {
    SERstate1 = "OFF";
  }
  server.send(200, "text/plane", "");
  server.send(200, "text/plane", SERstate1);
}

void statusSER() {
  server.send(200, "text/plane", SERstate1);
}



//---------------------------------------------------------------------------------------------------------
void setup() {

  Serial.begin(115200);
  delay(500);
  pwm.begin();
  pwm.setPWMFreq(50);

  
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);


  //Initialize Webserver
  server.on("/", handleRoot); //--> Routine to handle at root location. This is to display web page.
  server.on("/setPOS", handleServo); //--> Sets servo position from Web request
  server.on("/setSER1", controlServo);
  server.on("/readSER1", statusSER);
  server.begin();

  Serial.println("HTTP server started");
  Stop();

  
  pinMode(3,INPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  
}


void loop() {
  int hallsensor=digitalRead(3);
  delay(10);
  Serial.println(hallsensor);
  //S pole is high
  if(hallsensor==1){
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
  }
  else{
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
  }
  
  //testmode();
  server.handleClient();

}




