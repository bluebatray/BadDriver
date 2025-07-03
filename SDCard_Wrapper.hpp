#pragma once

#include <SPI.h>
#include <SD.h>

class SDCard_Wrapper{

public:
  void init(int chipSelect);
  void writeToSdCard(String filepath, String dataString);
};