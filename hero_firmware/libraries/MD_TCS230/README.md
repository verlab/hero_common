# MD_TCS230

The TCS230 is a color light-to-frequency converter on single CMOS integrated circuit. The output is a square wave (50% duty cycle) with frequency directly proportional to light intensity (irradiance). The full-scale output frequency can be scaled by one of three preset values via two control input pins. Output enable (OE) places the output in the high-impedance state for multiple-unit sharing of a microcontroller input.

Library example code includes:
* Simple blocking read from the sensor
* Simple RGB non-blocking read
* Example incorporating sensor calibration
* Color learning and matching

If you like and use this library please consider making a small donation using [PayPal](https://paypal.me/MajicDesigns/4USD)

[Library Documentation](https://majicdesigns.github.io/MD_TCS230/)

## IMPORTANT NOTE
This library has a dependency on the __FreqCount__ library for frequency counting (https://github.com/PaulStoffregen/FreqCount).

__Please read the setup information in the FreqCount header file or its distribution web site.__ The type of Arduino that you are running will determine which pin should be used for connecting to the sensor's output pin. __This is the most commonly asked question once the library is downloaded, so read the documentation and avoid frustration!__

