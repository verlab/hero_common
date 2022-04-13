

/* Laser Configuration */
#define MUX_A 15              /* PIN D8 */
#define MUX_B 13              /* PIN D7 */
#define MUX_C 12              /* PIN D6 */
#define MUX_EN 2              /* PIN D4 */
const int real_pos[8] = {0, 1, 2, 7, 3, 6, 4, 5}; /* Sort proximity sensors*/


struct __attribute__ ((packed)) Data_t {
  uint16_t ir_0;
  uint16_t ir_1;
  uint16_t ir_2;
  uint16_t ir_3;
  uint16_t ir_4;
  uint16_t ir_5;
  uint16_t ir_6;
  uint16_t ir_7;
};


Data_t data_;

void setup()
{
  Serial.begin(115200);
    /* Setup Analog Multiplexer Pins */
  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);
  pinMode(MUX_C, OUTPUT);
  pinMode(MUX_EN, OUTPUT);
  analogWrite(MUX_EN, 0);
}


void readSensor() {
  for (int count = 0; count <= 7; count++) {
    /* Select the input  */
    int r0 = count & 0x01;
    int r1 = (count >> 1) & 0x01;
    int r2 = (count >> 2) & 0x01;
    digitalWrite(MUX_A, r0);
    digitalWrite(MUX_B, r1);
    digitalWrite(MUX_C, r2);
    /* Photodiode needs sleep for while since all the emissors are turned on at same time
      1. Read A0 sensor light
      2. Turn on the emissors and wait 100 us
      3. Read A0 sensor proximity
      4. Wait until A1 Espera até A1 desaturate and repeat for A1 {until A7}
      PS. It seems that the darker emissors recover faster than the light ones during over the saturation
    */
    delayMicroseconds(500);  // diode should power up in 100 us
    float env = (float) analogRead(A0);
    analogWrite(MUX_EN, 1024); // turn on all diode and enable mux
    delayMicroseconds(100);  // diode should power up in 100 us -> 180 us

    switch (real_pos[count]){
      case 0: data_.ir_0 =  (uint16_t)analogRead(A0) - (uint16_t)env;
      break;
      case 1: data_.ir_1 = (uint16_t)analogRead(A0) - (uint16_t)env; 
      break;
      case 2: data_.ir_2 = (uint16_t)analogRead(A0) - (uint16_t)env;
      break;
      case 3: data_.ir_3 = (uint16_t)analogRead(A0) - (uint16_t)env;
      break;
      case 4: data_.ir_4 = (uint16_t)analogRead(A0) - (uint16_t)env;
      break;
      case 5: data_.ir_5 = (uint16_t)analogRead(A0) - (uint16_t)env;
      break;
      case 6: data_.ir_6 = (uint16_t)analogRead(A0) - (uint16_t)env;
      break;
      case 7: data_.ir_7 = (uint16_t)analogRead(A0) - (uint16_t)env;
      break;
      }
    analogWrite(MUX_EN, 0); /* Turn off all diode and enable mux */
  }
}


void loop()
{
  readSensor();
  Serial.write((byte*)&data_, sizeof(data_));
  delayMicroseconds(500000);
}
