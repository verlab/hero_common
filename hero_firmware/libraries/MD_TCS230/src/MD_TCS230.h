/**
\mainpage Arduino TCS230 Library
The TCS230 Color Sensor IC
--------------------------
The TCS230 is a color light-to-frequency converter on single CMOS integrated circuit. The 
output is a square wave (50% duty cycle) with frequency directly proportional to light 
intensity (irradiance). The full-scale output frequency can be scaled by one of three 
preset values via two control input pins. Output enable (OE) places the output in the 
high-impedance state for multiple-unit sharing of a microcontroller input.

Library example code includes:
- Simple blocking read from the sensor
- Simple RGB non-blocking read
- Example incorporating sensor calibration
- Color learning and matching

If you like and use this library please consider making a small donation using [PayPal](https://paypal.me/MajicDesigns/4USD)

__IMPORTANT NOTE__

This library has a dependency on the *FreqCount* library for frequency counting 
(https://github.com/PaulStoffregen/FreqCount). FreqCount imposes limitation on which
pins can be used to measure the frequency and limits the use of other pins as follows:

Board         |Input Pin |Pins Unusable with analogWrite()
:------------:|---------:|:-------------------------------
Arduino Uno   | 5        | 3, 9, 10, 11
Arduino 2009  | 5        | 3, 9, 10, 11
Arduino Mega  | 47       | 9, 10, 44, 45, 46
Sanguino      | 1        | 12, 13, 14, 15

__Please read the setup information in the FreqCount header file or its distribution web site,
as the type of Arduino that you are running will determine which pin should be used for 
connecting to the sensor's output pin__. This is the most commonly asked question once the 
library is downloaded, so read the documentation and avoid frustration!

Topics
------
- \subpage pageHardware
- \subpage pageLibrary
- \subpage pageCalibration
- \subpage pageVersion
- \subpage pageCopyright

\page pageHardware Supported Hardware
This library supports the TCS230/TCS3200 color sensor and the more commonly available 
breakout modules available from many sources. The circuits for these modules are essentially 
identical except that the OE line may need to be modified (see below).

TCS230 IC
---------
The TCS230 IC mounted in the breakout has the following pinout.

![TCS230 IC Pinout] (TCS230_Hardware_Pinout.png "TCS230 IC Pinout")

Name  |Pin |I/O|Description                                                                           |
:----:|---:|:-:|:-------------------------------------------------------------------------------------|
GND   |4   |   |Power Supply Ground. All Voltages are referenced to this ground.                      |
Vdd   |5   |   |Supply Voltage (2.7-5.5V).                                                            |
/OE   |3   |I  |Enable f<sub>o</sub>. OE high -> OUT becomes high. Multiple sensors can share the same OUT line. |
OUT   |6   |O  |Output frequency f<sub>o</sub>.                                                                  |
S0,S1 |1,2 |I  |Output frequency scale selection inputs.                                              |
S2,S3 |7,8 |I  |Photodiode (color filter) selection inputs.                                           |

The operation of the hardware falls into two major functions, shown in the figure below. These 
different modules are controlled by setting the S0, S1, S2 and S3 pins. These settings are also shown 
in the tables below.

![TCS230 Hardware Functions] (TCS230_Hardware_Functions.png "TCS230 Hardware Functions")

S0  |S1 |Output Freq Scaling | |S2  |S3 |Photodiode Selection  |
:--:|--:|:-------------------| |:--:|--:|:---------------------|
L   |L  |Power Down          | |L   |L  |Red                   |
L   |H  |2%                  | |L   |H  |Blue                  |
H   |L  |20%                 | |H   |L  |Clear (no filter)     |
H   |H  |100%                | |H   |H  |Green                 |

TCS230 Breakout Boards
----------------------

![TCS230 Sensor Breakout] (TCS230_Sensor_Breakout.png "TCS230 Sensor Breakout")

The sensor can be purchased mounted on any number of inexpensive breakout boards, similar in 
design to that shown above. These boards extend the package connections to header pins, and 
integrate LEDs for illumination of the target object.

Many of these boards include a design ‘feature’ connecting OE directly to GND. Test with a 
multimeter by measuring the resistance between OE and GND – zero ohms reading indicates a 
direct connection.

This configuration will create problems if

- The OE line is driven HIGH by external circuitry – this creates a short circuit between 
 GND and the output of the driving circuit!
- Multiple sensors need to be connected to the same OUT, as the OUT lines cannot be 
 switched into high impedance mode.

Restoring normal function to the OE input is possible by cutting a track on the PCB. This 
is found between resistors R5 and R8, highlighted by the circle in the figure below. This may 
be different for other boards, so it is wise to follow the connections to make sure the 
correct track is cut.

![TCS230 OE Modification] (TCS230_OE_Pin_MOdification.png "TCS230 OE Modification")

Another modification to make the device readings consistent and repeatable is to shroud the 
sensor. This can be made from black card, wrapped and taped to the breakout board. The shroud 
eliminates stray light and ensures all the reflected light goes back to the sensor - use black 
so that the light reflected back into the sensor does not include color components originating 
from the shroud. My setup is shown below.

![TCS230 Sensor Shroud] (TCS230_Shrouded.jpg "TCS230 Sensor Shroud")

\page pageLibrary Using the Library
Measuring Frequency
-------------------
The sensor’s output is a square wave with 50% duty cycle (on/off equal amounts) with frequency 
directly proportional to light intensity, so accurately measuring the frequency is a fundamental 
requirement of any implementation.

To measure frequency, we need to measure the number of cycles in a fixed time period. The number 
of cycles in 1 second is measured in Hz. As long as the system is able to sample cycle transitions 
at a rate at least twice the expected frequency, we can be assured of an accurate reading. This 
rate should be easily achievable with an Arduino based implementation, even at 100% frequency scale.

Output scaling can be used to increase the resolution for a given clock rate or to maximize 
resolution as the light input changes.

The MD_TCS230 library uses a timer interrupt for the gate interval. If another interrupt is running, 
or interrupts are disabled by the main program, response to the timer could be delayed. That will 
lengthen the gate interval, perhaps leading to counting more cycles. The next gate interval will be 
shorter (if normal interrupt response occurs), so a corresponding decrease will occur in the next 
measurement. This mechanism is implemented in the __FreqCount__ library.

The longer the time period allowed for reading a value, the higher the accuracy. The library is set 
to use 1000ms, giving a value in Hz, as the basis of measurement. A divisor is applied to the time 
and the resulting count is multiplied by the divisor. Shorter sampling times are possible when the 
color differences between samples are more distinct. Higher resolution is obtained using a lower 
time divisor. There is no additional benefit counting cycles beyond 1000ms using this method.

Sensor Calibration
------------------
To calibrate the sensors, we need to measure the raw data that is returned with black and 
white test cards and then use that data to scale subsequent readings to an RGB value. This 
is described in its own section in this documentation.

It is not necessary to calibrate the sensor every time it is used. Calibration can be done 
separately from the application, and the constants determined during testing applied to the 
sensor from the code running the final application. Care should be taken to calibrate the 
sensor in a position that closely approximates final conditions.

References
----------
TAOS Inc, 'TCS230 Programmable Color Light-to-Frequency Converter', TAOS046, February 2003.

Charles Poynton, 'Sensing Color with the TAOS TCS230', TAOS Inc, 17 May 2005.

Paul J Stoffregen, 'FreqCount Library', http://www.pjrc.com/teensy/td_libs_FreqCount.html 
accessed 18 February 2013.

\page pageCalibration Calibration
Calibrating the Sensor
----------------------
The output is a square wave (50% duty cycle) with frequency (f<sub>o</sub>) directly 
proportional to light intensity:

![] (TCS230_Eq1.png)

where 

- f<sub>o</sub> is the output frequency
- f<sub>d</sub> is the output frequency for dark condition (when _Ee_ = 0)
- _Re_ is the device responsivity for a given wavelength of light in kHz/(mW/cm<sup>2</sup>)
- _Ee_ is the incident irradiance in mW/cm<sup>2</sup>.

f<sub>d</sub> is an output frequency resulting from leakage currents. As shown in the 
equation above, this frequency represents a light-independent term in the total output 
frequency f<sub>o</sub>. At very low light levels (dark colors), this dark frequency 
can be a significant portion of f<sub>o</sub>. The dark frequency is also temperature 
dependent.

As f<sub>o</sub> is directly proportional to frequency, it is possible to map between 
the frequency and RGB color value (0-255 for each of R, G and B) using linear 
interpolation.

Two points on the RGB line are well determined – pure Black (RGB 0, 0, 0) and pure 
White (255, 255, 255). The values returned by the sensor can be read using easily 
obtainable color swatches:

- A black color card gives us the dark condition constant f<sub>d</sub>. This is the 
origin (zero value) for the RGB straight line conversion.
- A white color card gives us the extreme RGB point f<sub>w</sub>, also known as white 
balance. Knowing f<sub>d</sub>, this value can be used to scale all intermediate frequencies 
to a corresponding RGB value.

The proportional relationship is expressed by the standard straight line equation _y = mx + b_ 
where

- _y_ is the reading obtained (in our case f<sub>o</sub>)
- _x_ is the normalized RGB value
- _b_ is the value of y when x is 0 (in our case f<sub>d</sub>)
- _m_ is the slope, or proportionality constant, of the line (in our case [_f<sub>w</sub> - f<sub>d</sub>_]/255.

The resulting equation is

![] (TCS230_Eq2.png)

or, rearranging to give us the desired RGB value

![] (TCS230_Eq3.png)

References
----------
Yurish, Sergey Y 2005, ‘Intelligent Opto Sensors Interfacing Based on Universal 
Frequency-to-Digital Converter’, Sensors & Transducers Magazine (S&T e-Digest), 
Vol.56, Issue 6, June 2005, pp.326-334.

TAOS Inc 2003, ‘TCS230 Programmable Color Light-to-Frequency Converter’, 
Product Datasheet TAOS046 – February 2003.

Poynton, Charles 2005, ‘Sensing Color with the TAOS TCS230’, TAOS Inc., 2005-05-17.

\page pageCopyright Copyright
Copyright (C) 2013 Marco Colli.
All rights reserved.

This library is free software; you can redistribute it and/or modify it under the terms of 
the GNU Lesser General Public License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this
library; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
Boston, MA 02110-1301  USA

\page pageVersion Revision History
Jul 2018 version 1.2.3
- Updated various text files and documentation

Feb 2018 version 1.2.1, 1.2.2
- Updated documentation to doxygen standard.

Jan 2018 version 1.2.0
- Changed scaling multiplier from 256 to 255.

Jan 2017 version 1.1.0
- Documentation update.

2013 version 1.0.0
- Initial version.
*/
#ifndef _MD_TCS230_H
#define _MD_TCS230_H

#include <Arduino.h>
#include <FreqCount.h>

/**
 * \file
 * \brief Main header file for the MD_TCS230 library
 */

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))  ///< Calculate number of elements in a array

// Frequency setting defines
const uint8_t TCS230_FREQ_HI = 0;  ///< 100% prescaler
const uint8_t TCS230_FREQ_MID = 1; ///< 20% prescaler
const uint8_t TCS230_FREQ_LO  = 2; ///< 2% prescaler
const uint8_t TCS230_FREQ_OFF = 3; ///< Prescaler off

// Indices for any RGB data/ filter selection
const uint8_t TCS230_RGB_R = 0; ///< Red detector filter selection
const uint8_t TCS230_RGB_G = 1; ///< Green detector filter selection
const uint8_t TCS230_RGB_B = 2; ///< Blue detector filter selection
const uint8_t TCS230_RGB_X = 3; ///< 'Clear' (off) detector filter selection

const uint8_t RGB_SIZE = 3;     ///< Array index counter limit for RGB components

const uint8_t NO_PIN = 0xff;    ///< Value set when no pin has been defined

/**
 * Sensor Data structure type.
 *
 * This data type contains the RGB related raw data from the sensor 
 */
typedef struct
{
  int32_t value[RGB_SIZE];  ///< One element each for R, G and B raw data readings
} sensorData;

/**
 * RGB Data structure type.
 *
 * This data type contains the RGB derived data from the sensor 
 */
typedef struct
{
  uint8_t value[RGB_SIZE];  ///< One element each for RGB evaluated color data (RGB value 0-255 or other)
} colorData;

/**
 * Core object for the MD_MAX72XX library
 * This is the only class implemented to abstract and manage the sensor.
*/
class MD_TCS230 
{
  public:
  /**
   * Class Constructor - minimal interface.
   *
   * Instantiate a new instance of the class. The parameters passed are 
   * used to connect the software to the hardware.
   *
   * The minimum required to manage the sensor are the s1 and s2 pins for 
   * color filter selection.
   *
   * \param s2  Arduino output pin connected to sensor s2 input.
   * \param s3  Arduino output pin connected to sensor s3 input.
   */
  MD_TCS230(uint8_t s2, uint8_t s3);

  /**
   * Class Constructor - minimal with multiple sensors.
   *
   * Instantiate a new instance of the class. The parameters passed are 
   * used to connect the software to the hardware.
   *
   * The minimum required to manage the sensor are the s2 and s3 pins for 
   * color filter selection. Optionally, the oe pin can be specified if 
   * multiple sensors are to be connected, however read the separate 
   * documentation on the hardware supported to ensure that the sensor module 
   * is suitably modified if control using oe is required. 
   *
   * \param s2  Arduino output pin connected to sensor s2 input.
   * \param s3  Arduino output pin connected to sensor s3 input.
   * \param oe  Arduino output pin connected to sensor oe input.
   */
  MD_TCS230(uint8_t s2, uint8_t s3, uint8_t oe);

  /**
   * Class Constructor - prescaler control interface.
   *
   * Instantiate a new instance of the class. The parameters passed are 
   * used to connect the software to the hardware.
   *
   * The minimum required to manage the sensor are the s1 and s2 pins for 
   * color filter selection. Optionally, s0 and s1 can be specified to allow
   * changes to the prescaler.
   *
   * \param s2  Arduino output pin connected to sensor s2 input.
   * \param s3  Arduino output pin connected to sensor s3 input.
   * \param s0  Arduino output pin connected to sensor s0 input.
   * \param s1  Arduino output pin connected to sensor s1 input.
   */
  MD_TCS230(uint8_t s2, uint8_t s3, uint8_t s0, uint8_t s1);

  /**
   * Class Constructor - prescaler and multiple sensors interface.
   *
   * Instantiate a new instance of the class. The parameters passed are 
   * used to connect the software to the hardware.
   *
   * The minimum required to manage the sensor are the s1 and s2 pins for 
   * color filter selection. Optionally, s0 and s1 can be specified to allow
   * changes to the prescaler. Additionally, the oe pin can be specified if 
   * multiple sensors are to be connected, however read the separate 
   * documentation on the hardware supported to ensure that the sensor module 
   * is suitably modified if control using oe is required. 
   *
   * \param s2  Arduino output pin connected to sensor s2 input.
   * \param s3  Arduino output pin connected to sensor s3 input.
   * \param s0  Arduino output pin connected to sensor s0 input.
   * \param s1  Arduino output pin connected to sensor s1 input.
   * \param oe  Arduino output pin connected to sensor oe input.
   */
  MD_TCS230(uint8_t s2, uint8_t s3, uint8_t s0, uint8_t s1, uint8_t oe);

  /**
   * Initialize the object.
   *
   * Initialize the object data. The object needs to initialize itself 
   * during using Arduino libraries and so cannot be completely initialized 
   * in the constructor. Should be called once during setup() for every 
   * object instance.
   */
  void begin(void);

  /**
   * Class Destructor.
   *
   * Released allocated memory and does the necessary to clean up once the object is
   * no longer required.
   */
  ~MD_TCS230(void);

  //--------------------------------------------------------------
  /** \name Methods for hardware and object control.
   * @{
   */
  /**
   * Set the photodiode filter.
   *
   * Set the outputs s0, s1 to match the specified photodiode filter.
   * This is one of the defined values TCS230_RGB_*.
   *
   * The read() method will automatically invoke all the filters in turn.
   *
   * \param f  The required filter, one of TCS230_RGB_*.
   */
  void setFilter(uint8_t f);

  /**
   * Set the frequency prescaler.
   *
   * Set the outputs s2, s3 to match the specified frequency prescaler.
   * This is one of the defined values TCS230_FREQ_*. 
   * 
   * Default library value is 100% prescaler (TCS23_FREQ_HI).
   *
   * This method will only work if the prescaler pins s2, s3 are specified
   * in the constructor and is ignored otherwise.
   *
   * \param f  The required filter, one of TCS230_RGB_*.
   */
  void setFrequency(uint8_t f);
  
  /**
   * Enable or disable sensor output (using OE or frequency).
   *
   * Enable (true) or disable (false) sensor output by (in order of preference):
   * 
   * 1 If the OE pin is defined, setting the OE pin to the appropriate HIGH/LOW 
   *   conditions. This is preferred mode as the high impedance mode can be used 
   *   for OUT signal isolation.
   *
   * 2 If the SO and S1 pins are defined, setting the output frequency to the 
   *   value set by the setFrequency() method or to TCS230_FREQ_OFF.
   *
   * 3 No action is taken if none of OE, S0 and S1 is defined.
   *
   * \param t  True to enable the device, false to disable.
   */
  void setEnable(bool t);

  /**
   * Set the sampling period divisor.
   *
   * The library is set for a maximum of 1000ms for a sample (divisor = 1).
   * Higher divisors create shorter sample times (eg, 5 = 200ms, 10 = 100ms, 
   * 100 = 10ms). Shorter samples are less accurate and only recommended when 
   * the range of colors to be detected are highly separated on the RGB color 
   * chart. The ‘right’ value for the divisor is dependent on the application. 
   *
   * The default value is 10 (100ms sample).
   *
   * \param t  Cycle time divisor.
   */
  void setSampling(uint8_t t);

  /**
   * Set the dark calibration data.
   *
   * Sets the values to be used as the dark calibration data.
   * These numbers can be obtained from getRaw() during the calibration process.
   *
   * \param d  Pointer to a sensorData structure containing the calibration data.
   */
  void setDarkCal(sensorData *d);

  /**
   * Set the white balance calibration data.
   *
   * Sets the values to be used as the white balance calibration data.
   * These numbers can be obtained from getRaw() during the calibration process.
   *
   * \param d  Pointer to a sensorData structure containing the calibration data.
   */
  void setWhiteCal(sensorData *d);
  /** @} */

  //--------------------------------------------------------------
  /** \name Methods for reading sensor data.
   * @{
   */
  /**
   * Start an asynchronous read cycle.
   *
   * The function will coordinate enabling the sensor, selecting the right 
   * filters in sequence and calling the FreqCount library to obtain a full 
   * color reading (all of R, G,and  B).
   */
  void read(void);

  /**
   * Determine when a sensor read has completed.
   
   * The method will return true when a value is ready for processing, 
   * at which time a call to getRGB() or getRaw() will retrieve the data 
   * for the calling program.
   *
   * \return true if data is available, false otherwise.
   */
  bool available(void);

  /**
   * Get RGB color data for the last sensor reading.
   *
   * Get the last read sensor data in RGB format into the structure *rgb.
   * The elements of RGB are retrieved using value[TCS230_RGB_*] for the 
   * Red, Green and Blue elements, respectively.
   *
   * \param rgb Pointer to a colorData structure to receive the RGB data.
   */
  void getRGB(colorData *rgb);

  /**
   * Get raw data from the last sensor reading.
   *
   * Get the last read sensor data as raw counts into the structure *d.
   * The raw counts may be retrieved using value[TCS230_RGB_*] for the 
   * Red, Green and Blue elements, respectively.
   *
   * \param d Pointer to a sensorData structure to receive the RGB data.
   */
  void getRaw(sensorData *d);

  /**
   * Synchronously read a value (blocking read)
   *
   * Initiate a blocking read of the sensor. The method returns the raw data
   * read from the sensor as a uint32_t, normalized to a value in Hz, once 
   * the read cycle is completed. How long this takes is determined by the 
   * sampling period set using setSampling(). The calling program is responsible 
   * for enabling the device using setEnable() and setting the appropriate color 
   * filter using setFilter().
   *
   * \return raw data read from the sensor in Hz.
   */
  uint32_t readSingle(void);
  /** @} */
  
  private:
  uint8_t _OE;      ///< output enable pin
  uint8_t _S0;      ///< frequency scaler S0 pin
  uint8_t _S1;      ///< frequency scaler S1 pin
  uint8_t _S2;      ///< photodiode filter selection S2 pin
  uint8_t _S3;      ///< photodiode filter selection S3 pin
  uint8_t _readDiv; ///< read cycle divisor 
  uint8_t _freqSet; ///< current TCS230_FREQ_* setting 

  sensorData _Fd;   ///< Dark calibration data if supplied
  sensorData _Fw;   ///< White balance calibration data if supplied

  sensorData _Fo;        ///< current raw sensor reading
  colorData  _rgb;       ///< color converted data for current reading
  uint8_t    _readState; ///< current state for the read() FSM

  void  initialise(void);         ///< initialize variables
  uint8_t readFSM(uint8_t s);     ///< reading values fsm
  void  RGBTransformation(void);  ///< convert raw data to RGB
  void  setFrequency2(uint8_t f); ///< internal function for frequency prescaler
};

#endif
