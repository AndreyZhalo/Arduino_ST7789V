#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <SD.h>

// Определение пинов
#define TFT_CS    10
#define TFT_DC    8
#define TFT_RST   9
#define SD_CS     4

// Инициализация дисплея
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);
  
  // Инициализация дисплея
  tft.init(240, 320);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  tft.invertDisplay(false); 
  
  // Инициализация SD-карты
  if (!SD.begin(SD_CS)) {
    Serial.println("SD card initialization failed!");
    tft.setCursor(10, 100);
    tft.print("SD Card Error!");
    while(1);
  }
  Serial.println("SD card initialized.");
  
  // Вывод изображения
   drawImage("image1.bmp");  // Укажите имя вашего файла
  }

void loop() {

}

// Функция для отрисовки изображения
void drawImage(const char *filename) {
  File bmpFile = SD.open(filename);
  if (!bmpFile) {
    Serial.println("Image not found");
    return;
  }

  // Пропуск заголовка BMP файла (первые 54 байта)
  bmpFile.seek(54);

  // Чтение и отображение пикселей
  for (int y = 0; y < 320; y++) {
    for (int x = 239; x >= 0; x--) {  // Изменено: рисуем справа налево
      // Чтение цветовых компонентов (в порядке BGR)
      byte b = bmpFile.read();
      byte g = bmpFile.read();
      byte r = bmpFile.read();

      // Отображение пикселя на экране
      tft.drawPixel(x, y, tft.color565(r, g, b));
    }
  }
  bmpFile.close();
}
