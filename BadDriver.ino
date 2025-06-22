
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
#include "vec3.hpp"

ADXL345_Wrapper accelerometer = ADXL345_Wrapper();

//constants
// 1 g = 9.8 m/s^2

const int chipSelect = 10;
LiquidCrystal lcd(8, 9, 5, 6, 7, 10);

void setup(void) 
{ 

  Serial.begin(9600); 

  while(!Serial);

  lcd.begin(16, 2);
  lcd.print("Hello driver!");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
    while (true);
  }

  Serial.println("initialization done.");
  
  accelerometer.init();

   //Wyświetelnie information 
 accelerometer.displaySensorDetails(); 
 //Show additional settings 
 accelerometer.displayDataRate(); 
 accelerometer.displayRange(); 

} 
void loop(void) 
{ 
  accelerometer.displayAcceleration();

   // make a string for assembling the data to log:
  vec3 sensorValues = accelerometer.retrieveValues();

  String dataString = 
    String(sensorValues.x, 2) + "," + 
    String(sensorValues.y, 2) + "," + 
    String(sensorValues.z, 2);

    lcd.setCursor(0, 1);
    lcd.print(dataString);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

  delay(500);

} 


