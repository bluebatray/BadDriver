
/*-------------------------------
Libraries (Arduino Library manager)
Adafruit ADXL345
-------------------------------
*/

//Libraries
#include "ADXL345_Wrapper.hpp"


ADXL345_Wrapper wrapper = ADXL345_Wrapper(100);

//constants
// 1 g = 9.8 m/s^2


void setup(void) 
{ 

  Serial.begin(9600); 

  while(!Serial);

  wrapper.init();

   //Wyświetelnie information 
 wrapper.displaySensorDetails(); 
 //Show additional settings 
 wrapper.displayDataRate(); 
 wrapper.displayRange(); 

} 
void loop(void) 
{ 
  wrapper.displayAcceleration();
} 


