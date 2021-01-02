#define SD_ADAPTER_PIN 10
#define ROOT_CARD_MIN_SIZE 100
#define ROOT_CARD_MAX_SIZE 20000

#include <SPI.h>
#include <SD.h>

Sd2Card card;
SdVolume volume;
File root;
String buffer;

void setup() {
  Serial.begin(115200);
  Serial.print("\nИнициализация карты памяти...");
  if (!card.init(SPI_HALF_SPEED, SD_ADAPTER_PIN))
  {
    Serial.println("Карта памяти не обнаружена!");
    while (1);
  }
  else
  {
    Serial.println("Карта памяти обнаружена!");
  }
  if (!volume.init(card)) {
    Serial.println("Ошибка инициализации!");
    while (1);
  }
  uint32_t volumesize;
  if (!(volume.fatType() == 32)) {
    Serial.println("Карта памяти неверно отформатирована!");
    while (1);
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
    Serial.println("Инициализация прошла не успешно");
    return;
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
