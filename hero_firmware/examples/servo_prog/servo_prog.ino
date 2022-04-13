#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//#define USE_SLIDE_CONTROLLER_0
#define USE_SLIDE_CONTROLLER_1

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

/* PINOUT */

#define POT_PIN A3

#define BUTTON_LEFT_PIN 0
#define BUTTON_RIGHT_PIN 4

int btnLeftStatus = 1;
int btnRightStatus = 1;

#define DIGIT_4 9
#define DIGIT_3 8
#define DIGIT_2 7
#define DIGIT_1 6
#define DIGIT_0 5

#define SEGMENT_A 10
#define SEGMENT_B 16
#define SEGMENT_C 14
#define SEGMENT_D 15
#define SEGMENT_E 18
#define SEGMENT_F 19
#define SEGMENT_G 20

unsigned int currentMotor = 0;
unsigned int motorsPWM[16] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};

void setup()
{
  //  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);

  pinMode(DIGIT_0, OUTPUT);
  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);

  digitalWrite(DIGIT_0, LOW);
  digitalWrite(DIGIT_1, LOW);
  digitalWrite(DIGIT_2, LOW);
  digitalWrite(DIGIT_3, LOW);
  digitalWrite(DIGIT_4, LOW);

  pinMode(SEGMENT_A, OUTPUT);
  pinMode(SEGMENT_B, OUTPUT);
  pinMode(SEGMENT_C, OUTPUT);
  pinMode(SEGMENT_D, OUTPUT);
  pinMode(SEGMENT_E, OUTPUT);
  pinMode(SEGMENT_F, OUTPUT);
  pinMode(SEGMENT_G, OUTPUT);

  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, HIGH);
  digitalWrite(SEGMENT_F, HIGH);
  digitalWrite(SEGMENT_G, HIGH);

  pinMode(LED_BUILTIN_TX, INPUT);
  pinMode(LED_BUILTIN_RX, INPUT);

  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);
}

//We average the analog reading to elminate some of the noise
float averageAnalog(int pin, int samples) {
  float v = 0;
  for (int i = 0; i < samples; i++) v += analogRead(pin);
  return v / samples;
}

unsigned long timer = 0;

float map_f(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void displayClear() {
  /* Clear all digits */
  digitalWrite(DIGIT_0, LOW);
  digitalWrite(DIGIT_1, LOW);
  digitalWrite(DIGIT_2, LOW);
  digitalWrite(DIGIT_3, LOW);
  digitalWrite(DIGIT_4, LOW);
}

void displaySet(char val, int digit, long int dur) {
  int pin;
  switch (digit) {
    case 0: pin = DIGIT_0; break;
    case 1: pin = DIGIT_1; break;
    case 2: pin = DIGIT_2; break;
    case 3: pin = DIGIT_3; break;
    case 4: pin = DIGIT_4; break;
    default: pin = DIGIT_0; break;
  }

  switch (val) {
    case '0':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, LOW);
      digitalWrite(SEGMENT_B, LOW);
      digitalWrite(SEGMENT_C, LOW);
      digitalWrite(SEGMENT_D, LOW);
      digitalWrite(SEGMENT_E, LOW);
      digitalWrite(SEGMENT_F, LOW);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case '1':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, LOW);
      digitalWrite(SEGMENT_C, LOW);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case '2':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, LOW);
      digitalWrite(SEGMENT_B, LOW);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, LOW);
      digitalWrite(SEGMENT_E, LOW);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, LOW);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case '3':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, LOW);
      digitalWrite(SEGMENT_B, LOW);
      digitalWrite(SEGMENT_C, LOW);
      digitalWrite(SEGMENT_D, LOW);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, LOW);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case '4':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, LOW);
      digitalWrite(SEGMENT_C, LOW);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, LOW);
      digitalWrite(SEGMENT_G, LOW);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case '5':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, LOW);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, LOW);
      digitalWrite(SEGMENT_D, LOW);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, LOW);
      digitalWrite(SEGMENT_G, LOW);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case '6':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, LOW);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, LOW);
      digitalWrite(SEGMENT_D, LOW);
      digitalWrite(SEGMENT_E, LOW);
      digitalWrite(SEGMENT_F, LOW);
      digitalWrite(SEGMENT_G, LOW);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case '7':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, LOW);
      digitalWrite(SEGMENT_B, LOW);
      digitalWrite(SEGMENT_C, LOW);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case '8':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, LOW);
      digitalWrite(SEGMENT_B, LOW);
      digitalWrite(SEGMENT_C, LOW);
      digitalWrite(SEGMENT_D, LOW);
      digitalWrite(SEGMENT_E, LOW);
      digitalWrite(SEGMENT_F, LOW);
      digitalWrite(SEGMENT_G, LOW);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case '9':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, LOW);
      digitalWrite(SEGMENT_B, LOW);
      digitalWrite(SEGMENT_C, LOW);
      digitalWrite(SEGMENT_D, LOW);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, LOW);
      digitalWrite(SEGMENT_G, LOW);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case 'A':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, LOW);
      digitalWrite(SEGMENT_B, LOW);
      digitalWrite(SEGMENT_C, LOW);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, LOW);
      digitalWrite(SEGMENT_F, LOW);
      digitalWrite(SEGMENT_G, LOW);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case 'B':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, LOW);
      digitalWrite(SEGMENT_D, LOW);
      digitalWrite(SEGMENT_E, LOW);
      digitalWrite(SEGMENT_F, LOW);
      digitalWrite(SEGMENT_G, LOW);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case 'C':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, LOW);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, LOW);
      digitalWrite(SEGMENT_E, LOW);
      digitalWrite(SEGMENT_F, LOW);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case 'D':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, LOW);
      digitalWrite(SEGMENT_C, LOW);
      digitalWrite(SEGMENT_D, LOW);
      digitalWrite(SEGMENT_E, LOW);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, LOW);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case 'E':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, LOW);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, LOW);
      digitalWrite(SEGMENT_E, LOW);
      digitalWrite(SEGMENT_F, LOW);
      digitalWrite(SEGMENT_G, LOW);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    case 'F':
      digitalWrite(pin, HIGH);
      digitalWrite(SEGMENT_A, LOW);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, LOW);
      digitalWrite(SEGMENT_F, LOW);
      digitalWrite(SEGMENT_G, LOW);
      delayMicroseconds(dur);
      digitalWrite(pin, LOW);
      digitalWrite(SEGMENT_A, HIGH);
      digitalWrite(SEGMENT_B, HIGH);
      digitalWrite(SEGMENT_C, HIGH);
      digitalWrite(SEGMENT_D, HIGH);
      digitalWrite(SEGMENT_E, HIGH);
      digitalWrite(SEGMENT_F, HIGH);
      digitalWrite(SEGMENT_G, HIGH);
      delayMicroseconds(100);
      break;
    default: break;
  }
}


long int timing = 0;
long int timer_ = 1000;

void loop()
{
  /* Slide-controller #0 */
#ifdef USE_SLIDE_CONTROLLER_0
  float pot_val = map_f(averageAnalog(POT_PIN, 100), 0, 1023.0, -1.0, 1.0);
  float freq = 50;
  if (fabs(pot_val) > 0.6) {
    freq = 2;
  }
  if (fabs(pot_val) > 0.9) {
    freq = 1;
  }

  if ((fabs(pot_val) > 0.1) && (millis() - timing) > freq / fabs(pot_val)) {
    timing = millis();
    motorsPWM[currentMotor] += fabs(pot_val) / pot_val;
    motorsPWM[currentMotor] = min(max(motorsPWM[currentMotor], 700), 2300);
    pwm.writeMicroseconds(currentMotor, (uint16_t)motorsPWM[currentMotor]);
  }
#endif

  /* Slide-controller #1 */
#ifdef USE_SLIDE_CONTROLLER_1
  static float pot_val = 1500;
  //  float pot_val = map_f(averageAnalog(POT_PIN, 100), 0, 1023.0, 700.0, 2300.0);
  if (fabs(pot_val - map_f(averageAnalog(POT_PIN, 100), 0, 1023.0, 700.0, 2300.0)) > 5) {
    motorsPWM[currentMotor] = pot_val = map_f(averageAnalog(POT_PIN, 100), 0, 1023.0, 700.0, 2300.0);
    pwm.writeMicroseconds(currentMotor, (uint16_t)motorsPWM[currentMotor]);
  }
#endif

  String digits = String((int)motorsPWM[currentMotor]);
  if ((int) motorsPWM[currentMotor] > 1000) {
    displaySet((char)digits[0], 3, timer_);
    displaySet((char)digits[1], 2, timer_);
    displaySet((char)digits[2], 1, timer_);
    displaySet((char)digits[3], 0, timer_);
  } else {
    displaySet((char)digits[0], 2, timer_);
    displaySet((char)digits[1], 1, timer_);
    displaySet((char)digits[2], 0, timer_);
  }

  int currentBtnLeft = digitalRead(BUTTON_LEFT_PIN);
  int currentBtnRight = digitalRead(BUTTON_RIGHT_PIN);

  if (btnLeftStatus == 1 && currentBtnLeft == 0) {
    currentMotor = (currentMotor - 1) % 16;
    btnLeftStatus = currentBtnLeft;
  }
  if (btnLeftStatus == 0 && currentBtnLeft == 1) {
    btnLeftStatus = currentBtnLeft;
  }

  if (btnRightStatus == 1 && currentBtnRight == 0) {
    currentMotor = (currentMotor + 1) % 16;
    btnRightStatus = currentBtnRight;
  }
  if (btnRightStatus == 0 && currentBtnRight == 1) {
    btnRightStatus = currentBtnRight;
  }

  if (currentMotor < 10) {
    String motorSet = String(currentMotor);
    displaySet((char)motorSet[0], 4, timer_);
  } else {
    switch (currentMotor) {
      case 10: displaySet('A', 4, timer_); break;
      case 11: displaySet('B', 4, timer_); break;
      case 12: displaySet('C', 4, timer_); break;
      case 13: displaySet('D', 4, timer_); break;
      case 14: displaySet('E', 4, timer_); break;
      case 15: displaySet('F', 4, timer_); break;
    }
  }

}
