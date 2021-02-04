/*  HEADER FILE - TCS3200 library
 *  TCS3200 color sensor library
 *  author: Panjkrc
 *  date: 12/14/2019
 *  url: https://github.com/Panjkrc/TCS3200_library
 */

#ifndef tcs3200_h
#define tcs3200_h
 
#include <Arduino.h>

class tcs3200
{
public:
    tcs3200(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t S3, uint8_t output);
    int colorRead(char color = 'c', int scaling = 20);
    int closestColor(int distinctRGB[][3], int distinctColors[],  int num_of_colors);

 
private:
    uint8_t _S0;
    uint8_t _S1;
    uint8_t _S2;
    uint8_t _S3;
    uint8_t _output;
};
 
#endif
