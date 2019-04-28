/*
 * EEPROM Read
 *
 * Reads the value of each byte of the EEPROM and prints it
 * to the computer.
 * This example code is in the public domain.
 */

#include <EEPROM.h>

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

void setup()
{
  // initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  delay(500);
  Serial.print("Chip ID: ");
  Serial.println(ESP.getFlashChipId(), HEX);
 
  Serial.print("Chip Real Size: ");
  Serial.println(ESP.getFlashChipRealSize());
 
  Serial.print("Chip Size: ");
  Serial.println(ESP.getFlashChipSize());
 
  Serial.print("Chip Speed: ");
  Serial.println(ESP.getFlashChipSpeed());
 
  Serial.print("Chip Mode: ");
  Serial.println(ESP.getFlashChipMode());
  EEPROM.begin(8);
  // write a 0 to all 512 bytes of the EEPROM
  //for (int i = 0; i < 512; i++)
  //  EEPROM.write(i, 0);
  //EEPROM.end();

   /* Setup complete esp LED message */
  Serial.print("Mode:");
  Serial.println(EEPROM.read(0));
   
  pinMode(LED_BUILTIN, OUTPUT);
  EEPROM.write(0, 1);
  EEPROM.commit();
  for(int i = 0; i <= 20; i++){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // blink led
    delay(100);                   
  }
  EEPROM.write(0, 0);
  EEPROM.commit();

}

void loop()
{
  // read a byte from the current address of the EEPROM
  value = EEPROM.read(address);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();

  // advance to the next address of the EEPROM
  address = address + 1;

  // there are only 512 bytes of EEPROM, from 0 to 511, so if we're
  // on address 512, wrap around to address 0
  if (address == 8)
    address = 0;

  delay(500);
}
