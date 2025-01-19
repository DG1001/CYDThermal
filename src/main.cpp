#include <Arduino.h>
#include <Wire.h>
#include <TFT_eSPI.h>
#include <Adafruit_AMG88xx.h>

TFT_eSPI tft = TFT_eSPI();
Adafruit_AMG88xx amg;

#define MINTEMP 10
#define MAXTEMP 40
#define PIXEL_SIZE 25
#define GRID_OFFSET_X 20
#define GRID_OFFSET_Y 20

uint16_t colorPalette(float val) {
  float normalized = (val - MINTEMP) / (MAXTEMP - MINTEMP);
  if (normalized < 0) normalized = 0;
  if (normalized > 1) normalized = 1;

  if (normalized < 0.33) {
    return tft.color565(0, normalized * 3 * 255, 255 * (1 - normalized * 3));
  } else if (normalized < 0.66) {
    normalized = (normalized - 0.33) * 3;
    return tft.color565(255 * normalized, 255 * (1 - normalized), 0);
  } else {
    normalized = (normalized - 0.66) * 3;
    return tft.color565(255, 255 * normalized, 255 * normalized);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Start Setup");
  
  // Display-Setup
  tft.init();
  Serial.println("TFT initialized");
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  Serial.println("Display setup complete");
  
  // I2C-Setup
  Wire.begin(27, 22);
  Serial.println("I2C initialized");
  
  // Sensor-Setup
  Serial.println("Initializing AMG8833...");
  if (!amg.begin()) {
    Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
    tft.drawString("Sensor Error!", 10, 10, 2);
    while (1);
  }
  Serial.println("AMG8833 found and initialized");
  
  delay(100);
}

void loop() {
  float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
  
  // Sensor auslesen
  amg.readPixels(pixels);
  


  // Min/Max Temperatur finden für Debug
  float maxTemp = pixels[0];
  float minTemp = pixels[0];
  for (int i = 1; i < AMG88xx_PIXEL_ARRAY_SIZE; i++) {
    if (pixels[i] > maxTemp) maxTemp = pixels[i];
    if (pixels[i] < minTemp) minTemp = pixels[i];
  }

  
  // clear text area
  tft.fillRect(240, 10, 320, 50, TFT_BLACK);

  // print out min and max temp
  char tempStr[18];
  tft.setTextColor(TFT_WHITE);
  sprintf(tempStr, "Min: %.1f C", minTemp);
  tft.drawString(tempStr, 240, 20, 2);
  sprintf(tempStr, "Max: %.1f C", maxTemp);
  tft.drawString(tempStr, 240, 40, 2);

  
  // Pixel zeichnen
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      float temp = pixels[i * 8 + j];
      
      tft.fillRect(
        GRID_OFFSET_X + j * PIXEL_SIZE,
        GRID_OFFSET_Y + i * PIXEL_SIZE,
        PIXEL_SIZE - 2,
        PIXEL_SIZE - 2,
        colorPalette(temp)
      );
      
      char tempStr[6];
      sprintf(tempStr, "%.0f", temp);
      tft.setTextColor(TFT_WHITE);
      tft.drawString(tempStr,
        GRID_OFFSET_X + j * PIXEL_SIZE + 4,
        GRID_OFFSET_Y + i * PIXEL_SIZE + PIXEL_SIZE/3,
        1
      );
    }
  }
  
  delay(100); 
}