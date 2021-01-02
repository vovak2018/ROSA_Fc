#define SD_ADAPTER_PIN 10
#define ROOT_CARD_MIN_SIZE 100
#define ROOT_CARD_MAX_SIZE 20000

#include <SPI.h>
#include <SD.h>
#include <StackArray.h>

Sd2Card card;
SdVolume volume;
File root;
String buffer;
StackArray <int> stack;
StackArray <int> stack2;

void error(String errorText) {
  Serial.println(errorText);
  while (1);
}

void setup() {
  Serial.begin(9600);
  Serial.print("\nИнициализация карты памяти...");
  if (!card.init(SPI_HALF_SPEED, SD_ADAPTER_PIN))
  {
    error("MEMORY_CARD_ERROR");
  }
  else
  {
    Serial.println("Карта памяти обнаружена!");
  }
  if (!volume.init(card)) {
    error("CARD_INITIALIZATION_ERROR");
  }
  uint32_t volumesize;
  if (!(volume.fatType() == 32)) {
    error("CARD_FORMAT_TYPE_ERROR_WANT_FAT32");
  }

  volumesize = volume.blocksPerCluster();
  volumesize *= volume.clusterCount();
  volumesize /= 2;
  Serial.print("Обнаруженный обьем (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  if (SD.begin(SD_ADAPTER_PIN)) {
    Serial.println("Инициализация прошла успешно");
  }
  else {
    error("Инициализация прошла не успешно");
  }
  if (!SD.exists("system.dat"))
  {
    SD.open("system.dat", FILE_WRITE).close();
    Serial.println("FREE_ROOT_FILE_ERROR");
  }
  root = SD.open("system.dat", FILE_READ);
  if (!root.available() > 0) {  
    Serial.println("FREE_ROOT_FILE_ERROR");
  }
}

void loop(void) {
  if (root.available() > 0)
  {
    buffer = root.readStringUntil('\n');
    Serial.println(buffer);
  }
  else
  {
    Serial.println("EOF");
    root.close();
    Serial.println("STOP");
    while (1);
  }
}
