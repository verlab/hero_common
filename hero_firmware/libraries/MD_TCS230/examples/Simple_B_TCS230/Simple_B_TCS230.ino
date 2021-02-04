// TCS230 sensor reading example
//
// This is just to show basic functionality with no calibration.
// Utilises the blocking version of the reading function.
// Output uses the Serial console.
//
#include <MD_TCS230.h>
#include <FreqCount.h>

// Pin definitions
#define  S2_OUT  12
#define  S3_OUT  13
#define  OE_OUT   8    // LOW = ENABLED 

MD_TCS230  CS(S2_OUT, S3_OUT, OE_OUT);

void setup() 
{
  Serial.begin(57600);
  Serial.println("[TCS230 Simple BLOCKING Example]");
  Serial.println("Move the sensor to different color to see the value");
  Serial.println("Note: These values are being read in without sensor calibration");
  Serial.println("and are likely to be far from reality");

  CS.begin();
  CS.setEnable(true);
  CS.setFilter(TCS230_RGB_X);
  CS.setFrequency(TCS230_FREQ_HI);
  CS.setSampling(10);
}

void readSensor()
{
	uint32_t	v;
  
  v = CS.readSingle();
  Serial.print("Simple value = ");
  Serial.println(v);
}


void loop() 
{
  readSensor();
}

