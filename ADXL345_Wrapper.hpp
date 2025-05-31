#pragma once

#include <Adafruit_ADXL345_U.h> //Adafruit ADXL345
#include "Vector3.hpp"

class ADXL345_Wrapper{
  public:
    ADXL345_Wrapper();
    ADXL345_Wrapper(int millisecondsPoll);
    void init(void); //fired on setup, when things are ready
    void displaySensorDetails(void);
    void displayRange(void);
    void displayDataRate(void);
    void displayAcceleration(void);

  Adafruit_ADXL345_Unified accel; 
  int millisecondsPoll;
  float MS2ToGravityMult =  0.10197162129779;  // for example: 9.53 / 9.80665 ≈ 0.972 g
  float GravityToMS2 = 9.80665;

  Vector3 highestRawMinusGravity;
  float highestG = 0;

};
