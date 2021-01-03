#define AX 201
#define BX 202
#define CX 203
#define DX 204
#define SD_ADAPTER_PIN 10
#define ROOT_CARD_MIN_SIZE 100
#define ROOT_CARD_MAX_SIZE 16000

#include <SPI.h>
#include <SD.h>
#include <StackArray.h>

Sd2Card card;
SdVolume volume;
File root;
String buffer;

// Обьявляем стеки
StackArray <int> stack;
StackArray <int> stack2;

// Обьявляем регистры
int ax = 0, bx = 0, cx = 0, dx = 0;

void error(String errorText) {
  log(errorText);
  kill();
}

void setup() {
  Serial.begin(9600);
  /*
  int* a = reg("ax");
  *a = 10;
   */
  log("\nИнициализация карты памяти...");
  //log(String(*a));
  if (!card.init(SPI_HALF_SPEED, SD_ADAPTER_PIN))
  {
    error("MEMORY_CARD_ERROR");
  }
  else
  {
    log("Карта памяти обнаружена!");
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
  log("Обнаруженный обьем (Mb):  ");
  volumesize /= 1024;
  log((int)volumesize);
  if (SD.begin(SD_ADAPTER_PIN)) {
    log("Инициализация прошла успешно");
  }
  else {
    error("Инициализация прошла не успешно");
  }
  if (!SD.exists("system.dat"))
  {
    SD.open("system.dat", FILE_WRITE).close();
    log("FREE_ROOT_FILE_ERROR");
  }
  root = SD.open("system.dat", FILE_READ);
  if (!root.available() > 0) {  
    log("FREE_ROOT_FILE_ERROR");
  }
}

void execute() {
  
}

void loop(void) {
  if (root.available() > 0)
  {
    buffer = root.readStringUntil('\n');
    log(buffer);
  }
  else
  {
    log("EOF");
    root.close();
    log("STOP");
    kill();
  }
}
