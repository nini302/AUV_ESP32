void forwardMotors(double val) {
  for (int i = 4; i <= 7; i++) {
    pwm.setPWM(i, 0, val);
  }
}

void downwardMotors(int val) {
  for (int i = 0; i <= 3; i++) {
    pwm.setPWM(i, 0, val);
  }
}

void cwRotation(double val) {
  for (int i = 4; i <= 5; i++) {
    pwm.setPWM(i, 0, val);
  }
  for (int i = 6; i <= 7; i++) {
    pwm.setPWM(i, 0, 620 - val);
  }
}

void ccwRotation(double val) {
  for (int i = 4; i <= 5; i++) {
    pwm.setPWM(i, 0, 620 - val);
  }
  for (int i = 6; i <= 7; i++) {
    pwm.setPWM(i, 0, val);
  }
}

void stopMotors() {
  int val = 310;
  for (int i = 0; i <= 7; i++) {
    pwm.setPWM(i, 0, val);
  }
}

void task1(double val) {
  downwardMotors(330);
  forwardMotors(val);
  delay(3000);
  stopMotors();
}

void testMode() {
  int val = 330;
  for (int i = 0; i <= 7; i++) {
    pwm.setPWM(i, 0, val);
  }
  delay(2000);
  val = 310;
  for (int i = 0; i <= 7; i++) {
    pwm.setPWM(i, 0, val);
  }
  delay(1000);
  val = 290;
  for (int i = 0; i <= 7; i++) {
    pwm.setPWM(i, 0, val);
  }
}