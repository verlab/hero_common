#include <Wire.h>
#include <LSM303.h>
#include <L3G.h>
#include <SFE_BMP180.h>

#define SENSORS_DPS_TO_RADS           (0.017453293F) /**< Degrees/s to rad/s multiplier */
#define SENSORS_GAUSS_TO_TESLA        (0.0001)         /**< Gauss to micro-Tesla multiplier */
#define SENSORS_GRAVITY_EARTH         (9.80665F)              /**< Earth's gravity in m/s^2 */

#define GYRO_SENSITIVITY_250DPS       (0.00875F)
#define ACC_SENSITIVITY_2G            (0.000061F)
#define MAG_SENSITIVITY_4GAUS         (0.000160F)

SFE_BMP180 pressure;
LSM303 compass;
L3G gyro;

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5);

  //gyro.init();
  //gyro.enableDefault();
  //delayMicroseconds(50);
  
  compass.init();
  compass.enableDefault();
  delayMicroseconds(50);
  
}

char report[80];
void loop() {
  /*gyro.read();
  Serial.print("G ");
  Serial.print("X: ");
  Serial.print((float)gyro.g.x*GYRO_SENSITIVITY_250DPS*SENSORS_DPS_TO_RADS);
  Serial.print(" Y: ");
  Serial.print((float)gyro.g.y*GYRO_SENSITIVITY_250DPS*SENSORS_DPS_TO_RADS);
  Serial.print(" Z: ");
  Serial.println((float)gyro.g.z*GYRO_SENSITIVITY_250DPS*SENSORS_DPS_TO_RADS);*/

  delayMicroseconds(100);

  compass.read();
  snprintf(report, sizeof(report), "A: %6f %6f %6f | M: %6f %6f %6f",
    (float)compass.a.x*ACC_SENSITIVITY_2G * SENSORS_GRAVITY_EARTH, (float)compass.a.y*ACC_SENSITIVITY_2G * SENSORS_GRAVITY_EARTH, (float)compass.a.z*ACC_SENSITIVITY_2G * SENSORS_GRAVITY_EARTH,
    (float)compass.m.x*MAG_SENSITIVITY_4GAUS * SENSORS_GAUSS_TO_TESLA, (float)compass.m.y*MAG_SENSITIVITY_4GAUS * SENSORS_GAUSS_TO_TESLA, (float)compass.m.z*MAG_SENSITIVITY_4GAUS * SENSORS_GAUSS_TO_TESLA);
  Serial.println(report);
  delay(100);
}


