#pragma once

#include <Adafruit_ADXL345_U.h> //Adafruit ADXL345

#include "vec3.hpp"

class ADXL345_Wrapper{
  public:
    ADXL345_Wrapper();
    void init(void); //fired on setup, when things are ready
    void displaySensorDetails(void);
    void displayRange(void);
    void displayDataRate(void);
    void displayAcceleration(void);
    vec3 retrieveValues(void);

  Adafruit_ADXL345_Unified accel; 
};
