#include "ADXL345_Wrapper.hpp"

ADXL345_Wrapper::ADXL345_Wrapper() : accel(12345),millisecondsPoll(250){}

ADXL345_Wrapper::ADXL345_Wrapper(int _millisecondsPoll) : accel(12345), millisecondsPoll(_millisecondsPoll){}

void ADXL345_Wrapper::init() {

 //Initialize the module 
 if(!accel.begin()) 
 { 
  //Connection error 
  Serial.println("failed sensor -- Check connection!"); 
  while(1); 
 } 

 //Select the range 
 //accel.setRange(ADXL345_RANGE_16_G); 
  accel.setRange(ADXL345_RANGE_8_G); 
 // accel.setRange(ADXL345_RANGE_4_G); 
 // accel.setRange(ADXL345_RANGE_2_G); 
 
 delay(1000); //needed to let it init


}

void ADXL345_Wrapper::displayRange() {
  Serial.print("Range: +/- ");
  switch (accel.getRange()) {
    case ADXL345_RANGE_16_G: Serial.print("16 "); break;
    case ADXL345_RANGE_8_G: Serial.print("8 "); break;
    case ADXL345_RANGE_4_G: Serial.print("4 "); break;
    case ADXL345_RANGE_2_G: Serial.print("2 "); break;
    default: Serial.print("?? "); break;
  }
  Serial.println(" g");
}

void ADXL345_Wrapper::displaySensorDetails(void) 
{ 
 sensor_t sensor; 
 accel.getSensor(&sensor); 
 Serial.println("------------------------------------"); 
 Serial.print ("Sensor "); Serial.println(sensor.name); 
 Serial.print ("driver Version: "); Serial.println(sensor.version); 
 Serial.print ("ID: "); Serial.println(sensor.sensor_id); 
 Serial.print ("maximum Value: "); Serial.print(sensor.max_value); Serial.println(" m/s^2"); 
 Serial.print ("minimum Value: "); Serial.print(sensor.min_value); Serial.println(" m/s^2"); 
 Serial.print ("Resolution: "); Serial.print(sensor.resolution); Serial.println(" m/s^2"); 
 Serial.println("------------------------------------"); 
 Serial.println(""); 
 
 delay(500); 
} 

void ADXL345_Wrapper::displayDataRate() {
  Serial.print("Speed: ");
  switch (accel.getDataRate()) {
    case ADXL345_DATARATE_3200_HZ: Serial.print("3200 "); break;
    case ADXL345_DATARATE_1600_HZ: Serial.print("1600 "); break;
    case ADXL345_DATARATE_800_HZ: Serial.print("800 "); break;
    case ADXL345_DATARATE_400_HZ: Serial.print("400 "); break;
    case ADXL345_DATARATE_200_HZ: Serial.print("200 "); break;
    case ADXL345_DATARATE_100_HZ: Serial.print("100 "); break;
    case ADXL345_DATARATE_50_HZ: Serial.print("50 "); break;
    case ADXL345_DATARATE_25_HZ: Serial.print("25 "); break;
    case ADXL345_DATARATE_12_5_HZ: Serial.print("12.5 "); break;
    case ADXL345_DATARATE_6_25HZ: Serial.print("6.25 "); break;
    case ADXL345_DATARATE_3_13_HZ: Serial.print("3.13 "); break;
    case ADXL345_DATARATE_1_56_HZ: Serial.print("1.56 "); break;
    case ADXL345_DATARATE_0_78_HZ: Serial.print("0.78 "); break;
    case ADXL345_DATARATE_0_39_HZ: Serial.print("0.39 "); break;
    case ADXL345_DATARATE_0_20_HZ: Serial.print("0.20 "); break;
    case ADXL345_DATARATE_0_10_HZ: Serial.print("0.10 "); break;
    default: Serial.print("???? "); break;
  }
  Serial.println(" Hz");
}

void ADXL345_Wrapper::displayAcceleration(void){
 sensors_event_t event; 
 accel.getEvent(&event);

  Vector3 rawValues = Vector3(
    abs(event.acceleration.x), 
    abs(event.acceleration.y), 
    abs(event.acceleration.z-GravityToMS2));
  
  Vector3 gValues = Vector3(
    rawValues.x * MS2ToGravityMult,
    rawValues.y * MS2ToGravityMult,
    rawValues.z * MS2ToGravityMult);

  // if(xRaw > xHigh)
  //   xHigh = xRaw;

  //  if(yRaw > yHigh)
  //   yHigh = yRaw;

  // if(zRaw > zHigh)
  //   zHigh = zRaw;

 //Output in m/sec^2) 
//  Serial.print("X: "); Serial.print(xRaw); Serial.print(" "); 
//  Serial.print("Y: "); Serial.print(yRaw); Serial.print(" "); 
//  Serial.print ("Z: "); Serial.print(zRaw); Serial.print(" ");
//  Serial.print("m/s^2 "); 

//  Serial.print("gX: "); Serial.print(xG); Serial.print(" "); 
//  Serial.print("gY: "); Serial.print(yG); Serial.print(" "); 
//  Serial.print ("gZ: "); Serial.print(zG); Serial.print(" ");
//  Serial.print("Gs "); 

//  Serial.print("xHigh: "); Serial.print(xHigh);Serial.print(" "); 
//  Serial.print("yHigh: "); Serial.print(yHigh);Serial.print(" "); 
//  Serial.print("zHigh: "); Serial.print(zHigh);Serial.print(" "); 

float totalG = gValues.magnitude();

Serial.print("Total G: "); Serial.print(totalG); Serial.print(" "); 

  if(totalG > highestG){
    highestG = totalG;
  }

Serial.print("Highest G: "); Serial.print(highestG); Serial.print(" "); 

 Serial.println(""); 

 delay(millisecondsPoll); 
}
