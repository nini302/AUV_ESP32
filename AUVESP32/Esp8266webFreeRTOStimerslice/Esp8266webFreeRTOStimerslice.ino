#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <TaskScheduler.h>
#include <Ticker.h>
#define TASK_FOREVER -1
#include "PageIndex.h"
// Define Servo PWM Driver
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVO_FREQ 50

// Define Wi-Fi parameters
const char* ssid = "ESPServo"; // Your SSID
const char* password = "12345678"; // Wi-Fi Password

WebServer server(80); // Create an instance of the web server

// Define your servo positions
int pos = 310;
int ver = 310;
int hallsensorver=0;

String SERstate1 = "OFF";

// Ticker for WiFi Timeout
Ticker wifiTimeout;

// Create a TaskScheduler object
Scheduler scheduler;

void setup() {
  Serial.begin(115200);

  // Initialize PWM Servo Driver
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  stopMotors();
  //GPIO
  pinMode(4,INPUT);
  pinMode(0,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(15,OUTPUT);

  // Configure Wi-Fi access point
  WiFi.softAP(ssid, password);

  // Get IP address of the access point
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Serve the web page
  server.on("/", HTTP_GET, handleRoot);
  server.on("/setPOS", HTTP_GET, handleServo);
  server.on("/setSER1", HTTP_GET, controlServo);
  server.on("/readSER1", HTTP_GET, statusSER);
  server.begin();

  // Create and attach tasks to the scheduler
  Task wifiTask(500, TASK_FOREVER, &wifiTaskCallback); // WiFi Task
  Task switchTask(500, TASK_FOREVER, &switchTaskCallback); // Switch Task
  Task timerTask(500, TASK_FOREVER, &timerTaskCallback); // Timer Task

  scheduler.addTask(wifiTask);
  scheduler.addTask(switchTask);
  scheduler.addTask(timerTask);

  wifiTask.enable();
  switchTask.enable();
  timerTask.enable();

  // Start the scheduler
  scheduler.startNow();

  // Set up a WiFi timeout
  wifiTimeout.attach(3.0, wifiTimeoutCallback); // Call wifiTimeoutCallback after 3 seconds of inactivity
}

void loop() {
  scheduler.execute(); // Execute the tasks in the scheduler
}

void handleRoot() {
  String s = MAIN_page; // Read HTML contents
  server.send(200, "text/html", s); // Send web page
}

void handleServo() {
  String POS = server.arg("servoPOS");
  pos = POS.toInt();
  if (ver != pos) {
    ver = pos;
  }
  delay(15);
  Serial.print("Servo Angle:");
  Serial.println(pos);
  server.send(200, "text/plain", "");
}

void controlServo() {
  String t_state = server.arg("SERstate1");
  Serial.println(t_state);
  Serial.println(pos);

  if (t_state == "1") {
    SERstate1 = pos;
    stopMotors();
  }
  else if (t_state == "2") {
    SERstate1 = pos;
    stopMotors();
    delay(500);
    forwardMotors(pos);
  }
  else if (t_state == "3") {
    SERstate1 = pos;
    stopMotors();
    delay(500);
    downwardMotors(pos);
  }
  else if (t_state == "4") {
    SERstate1 = pos;
    stopMotors();
    delay(500);
    cwRotation(pos);
  }
  else if (t_state == "5") {
    SERstate1 = pos;
    stopMotors();
    ccwRotation(pos);
  }
  else if (t_state == "6") {
    SERstate1 = pos;
    stopMotors();
    delay(500);
    testMode();
  }
  else if (t_state == "7") {
    SERstate1 = pos;
    stopMotors();
    delay(500);
    task1(pos);
  }
  else {
    SERstate1 = "OFF";
  }
  server.send(200, "text/plain", SERstate1);
}

void statusSER() {
  server.send(200, "text/plain", SERstate1);
}

void wifiTaskCallback() {
  server.handleClient();// Your WiFi task logic here
}

void switchTaskCallback() {
  int hallsensor=digitalRead(3);
  delay(10);
  if(hallsensor!=hallsensorver){
    stopMotors();
    hallsensorver=hallsensor;
  }
  Serial.print("hallsensorstate");Serial.println(hallsensor);
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
  // Your switch task logic here
}

void timerTaskCallback() {
  // Your timer task logic here
}

void wifiTimeoutCallback() {
  stopMotors(); // Execute this function if no WiFi commands are received in 3 seconds
}


