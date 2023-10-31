#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <TaskScheduler.h>
#include <Ticker.h>
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
int hallsensorver = 0;

String SERstate1 = "OFF";

// Ticker for WiFi Timeout
Ticker wifiTimeout;

// Core 0 functions
void setupWiFi()
{
  // Initialize PWM Servo Driver
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  // Configure Wi-Fi access point
  WiFi.softAP(ssid, password);

  // Get IP address of the access point
  //192.168.4.1
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
}

void WiFiTask(void* pvParameters)
{
  while (1)
  {
    server.handleClient();
    vTaskDelay(10); // Delay to allow other tasks to run
  }
}

// Core 1 functions
void SwitchTask(void* pvParameters)
{
  int hallsensor = 0;

  pinMode(34, INPUT);
  pinMode(35, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);

  while (1)
  {
    hallsensor = digitalRead(34);
    vTaskDelay(10);
    if (hallsensor != hallsensorver)
    {
      stopMotors();// Do something when the hall sensor state changes
      hallsensorver = hallsensor;
    }
    // Your switch task logic here
    Serial.print("hallsensorstate");
    Serial.println(hallsensor);

    // S pole is high
    if (hallsensor == 1)
    {
      digitalWrite(35, HIGH);
      digitalWrite(32, HIGH);
      digitalWrite(33, HIGH);
    }
    else
    {
      digitalWrite(35, LOW);
      digitalWrite(32, LOW);
      digitalWrite(33, LOW);
    }
    vTaskDelay(100); // Delay for the switch task
  }
}


void setup()
{
  Serial.begin(115200);

  setupWiFi();

  // Serve the web page
  server.on("/", HTTP_GET, handleRoot);
  server.on("/setPOS", HTTP_GET, handleServo);
  server.on("/setSER1", HTTP_GET, controlServo);
  server.on("/readSER1", HTTP_GET, statusSER);
  server.begin();

  xTaskCreatePinnedToCore(WiFiTask, "WiFi Task", 8192, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(SwitchTask, "Switch Task", 8192, NULL, 1, NULL, 1);

  wifiTimeout.attach(3.0, wifiTimeoutCallback); // Call wifiTimeoutCallback after 3 seconds of inactivity
}

void loop()
{
  // Empty loop
}

void handleRoot()
{
  String s = MAIN_page; // Read HTML contents
  server.send(200, "text/html", s); // Send web page
}

void handleServo()
{
  String POS = server.arg("servoPOS");
  pos = POS.toInt();
  if (ver != pos)
  {
    ver = pos;
  }
  delay(15);
  Serial.print("Servo Angle:");
  Serial.println(pos);
  server.send(200, "text/plain", "");
}

void controlServo()
{
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
  else
  {
    SERstate1 = "OFF";
  }
  server.send(200, "text/plain", SERstate1);
}

void statusSER()
{
  server.send(200, "text/plain", SERstate1);
}

void wifiTimeoutCallback()
{
  stopMotors(); // Execute this function if no WiFi commands are received in 3 seconds
}
