#include "msu.hpp"


/*
#include <Arduino.h>
#include "LIS3DHTR.h"
#include "SPI.h"
#include "conf.hpp"  // <-- config einbinden

// LIS über SPI
LIS3DHTR<SPIClass> LIS;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // SPI starten mit MSU Pins aus config.hpp
  SPI.begin(MSU_SPC_PIN, MSU_SAO_PIN, MSU_SDI_PIN); // CLK, MISO, MOSI
  LIS.begin(SPI, MSU_CS_PIN);                        // CS Pin aus config.hpp

  LIS.openTemp();         // ADC3 Temp Enable/Disable
  delay(100);

  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
}

void loop() {
    if (!LIS) {
        Serial.println("LIS3DHTR didn't connect.");
        while (1);
        return;
    }

    // Temperatur auslesen
    Serial.print("temp:"); 
    Serial.println(LIS.getTemperature());
    delay(500);
}

*/