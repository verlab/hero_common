/*
 ************************************************************************
 *  H E R O  R A N D O M  W A L K E R
 ************************************************************************
 *
 * Paulo Rezeck <rezeck@dcc.ufmg.br>
 * Hector Azpurua <hectorxxx@gmail.com>
 * 
 * HeRo Project
 * Computer Vision and Robotics Lab
 * Federal University of Minas Gerais - Brazil
 ************************************************************************/
 
#include <Servo.h>

/************************************************************************
 * Defines
 ************************************************************************/
/* Basic setup */
#define DEBUG 1
#define WHEEL_DIAMETER 4.9
#define WHEEL_SEPARATION 8
float WHEEL_CIRCUNFERENCE = 3.14 * WHEEL_DIAMETER;
#define WHEEL_R_MID 1595  // Neutral position of right motor
#define WHEEL_L_MID 1585  // Neutral position of left motor
#define PROXIMITY_THRESH 45

/* Wheel Setup */
#define WHEEL_R_PIN 16 //4 // Pin to connect right motor pin D1
#define WHEEL_L_PIN 5 // Pin to connect left motor pin D2

/* LED Setup */
#define IR1_PIN 4//0 /* Proximity sensor 1 Pin D3 */
#define IR2_PIN 13//2 /* Proximity sensor 1 Pin D4 */
#define IR3_PIN 12//14 /* Proximity sensor 1 Pin D5 */

int8_t ir1 = 0;
int8_t ir2 = 0;
int8_t ir3 = 0;
/************************************************************************/

/************************************************************************
 * Servo motor driver
 ************************************************************************/
Servo wheel_right, wheel_left;
/************************************************************************/

/************************************************************************
 * Arduino Setup
 ************************************************************************/
void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("      ___           ___           ___           ___     ");
  Serial.println("     /  /\\         /  /\\         /  /\\         /  /\\    ");
  Serial.println("    /  /:/        /  /::\\       /  /::\\       /  /::\\   ");
  Serial.println("   /  /:/        /  /:/\\:\\     /  /:/\\:\\     /  /:/\\:\\  ");
  Serial.println("  /  /::\\ ___   /  /::\\ \\:\\   /  /::\\ \\:\\   /  /:/  \\:\\ ");
  Serial.println(" /__/:/\\:\\  /\\ /__/:/\\:\\ \\:\\ /__/:/\\:\\_\\:\\ /__/:/ \\__\\:\\");
  Serial.println(" \\__\\/  \\:\\/:/ \\  \\:\\ \\:\\_\\/ \\__\\/~|::\\/:/ \\  \\:\\ /  /:/");
  Serial.println("      \\__\\::/   \\  \\:\\ \\:\\      |  |:|::/   \\  \\:\\  /:/ ");
  Serial.println("      /  /:/     \\  \\:\\_\\/      |  |:|\\/     \\  \\:\\/:/  ");
  Serial.println("     /__/:/       \\  \\:\\        |__|:|~       \\  \\::/   ");
  Serial.println("     \\__\\/         \\__\\/         \\__\\|         \\__\\/    ");
  Serial.println("");
  Serial.println("                                 The little swarm robot");
  Serial.println("");
  Serial.println("");
  Serial.println("RANDOM WALK MODE");
  Serial.println("");
  Serial.println("HeRo authors:");
  Serial.println("\t-Paulo Rezeck rezeck@dcc.ufmg.br");
  Serial.println("\t-Hector Azpurua hector.azpurua@dcc.ufmg.br");
  Serial.println("");

  /* Setup servo motor */
  if(DEBUG) Serial.println("Setup servos ...");
  wheel_right.attach(WHEEL_R_PIN);
  wheel_left.attach(WHEEL_L_PIN);
 
  wheel_right.writeMicroseconds(WHEEL_R_MID);
  wheel_left.writeMicroseconds(WHEEL_L_MID);

  /* Connect the proximities sensors */
  if(DEBUG) Serial.println("Setup proximity sensors ...");
  pinMode(IR1_PIN, INPUT); 
  pinMode(IR2_PIN, INPUT);
  pinMode(IR3_PIN, INPUT);

  randomSeed(analogRead(A0));

  /* Setup complete LED message */
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i=0; i<= 6; i++){
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);                   
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);        
  }
  if(DEBUG) Serial.println("Setup finished");
  delay(1000);
}
/************************************************************************/

/************************************************************************
 * M A I N  L O 0 P
 ************************************************************************/
void loop(){
  ir1 = (int8_t) readIR(IR1_PIN);
  ir2 = (int8_t) readIR(IR2_PIN);
  ir3 = (int8_t) readIR(IR3_PIN);

  if(DEBUG){
    Serial.print("L1:");
    Serial.print(ir1);
    Serial.print(" ");
    Serial.print("L2:");
    Serial.print(ir2);
    Serial.print(" ");
    Serial.print("L3:");
    Serial.print(ir3);
    Serial.print(" ");
    Serial.println("");
  }

  updateVelocities(abs(ir3), abs(ir2), abs(ir1));
  
  delay(100);
}

void updateVelocities(int left, int center, int right){
    int rn2 = random(200, 600);
    if(DEBUG){
      Serial.print("ms turnover:");
      Serial.println(rn2);
    }
    
    if(left <= PROXIMITY_THRESH){
      wheel_right.writeMicroseconds(int(WHEEL_R_MID) - 100);
      wheel_left.writeMicroseconds(int(WHEEL_L_MID) - 100);      
      delay(rn2);
    }
    else if(right <= PROXIMITY_THRESH){
      wheel_right.writeMicroseconds(int(WHEEL_R_MID) + 100);
      wheel_left.writeMicroseconds(int(WHEEL_L_MID) + 100);      
      delay(rn2);
    }
    else if(center <= PROXIMITY_THRESH){
      int rn1 = random(0, 9);
      if(rn1 < 5){
        wheel_right.writeMicroseconds(int(WHEEL_R_MID) + 100);
        wheel_left.writeMicroseconds(int(WHEEL_L_MID) + 100);
      }
      else{
        wheel_right.writeMicroseconds(int(WHEEL_R_MID) - 100);
        wheel_left.writeMicroseconds(int(WHEEL_L_MID) - 100);
      }
      delay(rn2);
    }
    
    wheel_right.writeMicroseconds(int(WHEEL_R_MID) - 200);
    wheel_left.writeMicroseconds(int(WHEEL_L_MID) + 200);
    delay(20);
}

int readIR(int pin){
  analogWrite(pin, 1024);  // lit the diode
  delayMicroseconds(400);  // diode should power up in 100 us  
  int data = analogRead(A0);
  analogWrite(pin, 0);  // dim the diode
  return data;
}
/************************************************************************/
/* T H E  E N D */
/************************************************************************/
