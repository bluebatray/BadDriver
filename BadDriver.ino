
/*-------------------------------
Libraries (Arduino Library manager)
Adafruit ADXL345

Libraries (build-in)
SPI
SD

Pin   Device  Pin   Wire Color
---   ------  ---   ----------  
5V    Bread         Red
GND   Bread         Black

A4    Accel   SDA   Blue
A5    Accel   SCL   Yellow

D4    SD Card CS    Yellow
D11   SD CARD MOSI  Blue
D12   SD CARD MISO  Green
D13   SD CARD SCK   Orange


-------------------------------
*/

//Libraries
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>

#include "ADXL345_Wrapper.hpp"
#include "SDCard_Wrapper.hpp"
#include "vec3.hpp"

ADXL345_Wrapper accelerometer = ADXL345_Wrapper();
SDCard_Wrapper sdCard = SDCard_Wrapper();
//constants
// 1 g = 9.8 m/s^2

const int chipSelect = 4; 
LiquidCrystal lcd(8, 9, 5, 6, 7, 10);

void setup(void) 
{ 

  Serial.begin(9600); 
  while(!Serial);

  sdCard.init(chipSelect);

  lcd.begin(16, 2);
  lcd.print("Hello driver!");

  Serial.println("initialization done.");
  
  accelerometer.init();

 accelerometer.displaySensorDetails(); 
 accelerometer.displayDataRate(); 
 accelerometer.displayRange(); 

} 
void loop(void) 
{ 
  // accelerometer.displayAcceleration();

   // make a string for assembling the data to log:
  vec3 sensorValues = accelerometer.retrieveValues();

  String dataString = 
    
    String(sensorValues.x, 2) + "," + 
    String(sensorValues.y, 2) + "," + 
    String(sensorValues.z, 2);

    lcd.setCursor(0, 1);
    lcd.print(dataString);

  sdCard.writeToSdCard("datalog.txt", dataString);

  // delay(500);

} 


