/* Configuration */
#define MUX_A_PIN 15   /* PIN D8 */
#define MUX_B_PIN 13   /* PIN D7 */
#define MUX_C_PIN 12   /* PIN D6 */
#define MUX_EN_PIN 2   /* PIN D4 */
#define SENSOR_COUNT 8 /* MUX number of channels */

const int real_pos[8] = { 0, 1, 2, 7, 3, 6, 4, 5 }; /* Sort proximity sensors*/
float sensor_readings[SENSOR_COUNT];

#define SERIAL_DATA false

struct __attribute__((packed)) Data_t {
  uint16_t ir_0 = 0;
  uint16_t ir_1 = 0;
  uint16_t ir_2 = 0;
  uint16_t ir_3 = 0;
  uint16_t ir_4 = 0;
  uint16_t ir_5 = 0;
  uint16_t ir_6 = 0;
  uint16_t ir_7 = 0;
};


Data_t data_;

void setup() {
  Serial.begin(115200);
  /* Setup Analog Multiplexer Pins */
  pinMode(MUX_A_PIN, OUTPUT);
  pinMode(MUX_B_PIN, OUTPUT);
  pinMode(MUX_C_PIN, OUTPUT);
  pinMode(MUX_EN_PIN, OUTPUT);
  analogWrite(MUX_EN_PIN, 0);
}


void selectInput(int input) {
  int r0 = input & 0x01;
  int r1 = (input >> 1) & 0x01;
  int r2 = (input >> 2) & 0x01;
  digitalWrite(MUX_A_PIN, r0);
  digitalWrite(MUX_B_PIN, r1);
  digitalWrite(MUX_C_PIN, r2);
}

float readSensor() {
  /* Photodiode needs sleep for while since all the emissors are turned on at same time
      1. Read A0 sensor light
      2. Turn on the emissors and wait 100 us
      3. Read A0 sensor proximity
      4. Wait until A1 Espera até A1 desaturate and repeat for A1 {until A7}
      PS. It seems that the darker emissors recover faster than the light ones during over the saturation
  */
  delayMicroseconds(500);  // Photodiode needs sleep for a while since all the emitters are turned on at the same time
  float env = (float)analogRead(A0);

  analogWrite(MUX_EN_PIN, 1023);  // Turn on all diodes and enable mux
  delayMicroseconds(100);         // Diodes should power up in 100 us -> 180 us

  float sensor_reading = (float)analogRead(A0) - env;

  analogWrite(MUX_EN_PIN, 0);  // Turn off all diodes and disable mux
  delayMicroseconds(80);

  return sensor_reading;
}


void readSensors() {
  for (int sensor = 0; sensor < SENSOR_COUNT; sensor++) {
    /* Select the input  */
    selectInput(sensor);
    sensor_readings[real_pos[sensor]] = readSensor();
  }
}


void loop() {
  readSensors();
    // Serial.write((byte*)&data_, sizeof(data_));
    // delayMicroseconds(500000);
  Serial.printf("%f,",  sensor_readings[0]);
  Serial.printf("%f,",  sensor_readings[1]);
  Serial.printf("%f,",  sensor_readings[2]);
  Serial.printf("%f,",  sensor_readings[3]);
  Serial.printf("%f,",  sensor_readings[4]);
  Serial.printf("%f,",  sensor_readings[5]);
  Serial.printf("%f,",  sensor_readings[6]);
  Serial.printf("%f\n", sensor_readings[7]);
  delayMicroseconds(100000);
  // }
}
