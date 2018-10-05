#include <NeoPixelBus.h>
#include <NeoPixelBrightnessBus.h>
const uint16_t PixelCount = 30; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 16;  // make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 128

//NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PixelCount, PixelPin);
NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PixelCount, PixelPin);
RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor yellow(255, 255, 50);
RgbColor green2(73, 153, 0);
RgbColor pink(255, 0, 127);
RgbColor black(0);

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    while (!Serial); // wait for serial attach
    Serial.println();
    Serial.println("Initializing...");
    Serial.flush();

    // this resets all the neopixels to an off state
    strip.Begin();
    strip.Show();
    for(int i = 0; i < 1; i++){
      strip.SetPixelColor(i, red);
      }
      strip.SetBrightness(64);
      strip.Show();
      
}

void loop() {
  // put your main code here, to run repeatedly:

    for(int i = 0; i < PixelCount; i++){
       strip.SetPixelColor(i, white);
      }
      strip.SetBrightness(255);
      strip.Show();
      delay(5000);

    for(int i = 0; i < PixelCount; i++){
      strip.SetPixelColor(i, red);
      }
      strip.SetBrightness(255);
      strip.Show();
      delay(5000);

    for(int i = 0; i < PixelCount; i++){
      strip.SetPixelColor(i, green);
      }
      strip.SetBrightness(255);
      strip.Show();
      delay(5000);

    for(int i = 0; i < PixelCount; i++){
      strip.SetPixelColor(i, blue);
      }
      strip.SetBrightness(255);
      strip.Show();
      delay(5000);


    for(int i = 0; i < PixelCount; i++){
       strip.SetPixelColor(i, white);
      }
      strip.SetBrightness(128);
      strip.Show();
      delay(5000);

    for(int i = 0; i < PixelCount; i++){
      strip.SetPixelColor(i, red);
      }
      strip.SetBrightness(128);
      strip.Show();
      delay(5000);

    for(int i = 0; i < PixelCount; i++){
      strip.SetPixelColor(i, green);
      }
      strip.SetBrightness(128);
      strip.Show();
      delay(5000);

    for(int i = 0; i < PixelCount; i++){
      strip.SetPixelColor(i, blue);
      }
      strip.SetBrightness(128);
      strip.Show();
      delay(5000);


     for(int i = 0; i < PixelCount; i++){
       strip.SetPixelColor(i, white);
      }
      strip.SetBrightness(64);
      strip.Show();
      delay(5000);

    for(int i = 0; i < PixelCount; i++){
      strip.SetPixelColor(i, red);
      }
      strip.SetBrightness(64);
      strip.Show();
      delay(5000);

    for(int i = 0; i < PixelCount; i++){
      strip.SetPixelColor(i, green);
      }
      strip.SetBrightness(64);
      strip.Show();
      delay(5000);

    for(int i = 0; i < PixelCount; i++){
      strip.SetPixelColor(i, blue);
      }
      strip.SetBrightness(64);
      strip.Show();
      delay(5000);



   
}
