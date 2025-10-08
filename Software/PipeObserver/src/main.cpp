#include <Arduino.h>
#include "temp.hpp"
#include "conf.hpp"
#include "adc.hpp"

TemperatureSensor innerSensor(INNER_TEMP_PIN, TEMP_RESOLUTION);
TemperatureSensor outerSensor(OUTER_TEMP_PIN, TEMP_RESOLUTION);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  innerSensor.begin();
  outerSensor.begin();
  setupADC(ADC_SDA_PIN, ADC_SCL_PIN);
}

void loop() {
  float innerTemp = innerSensor.readTemperature();
  float outerTemp = outerSensor.readTemperature();
  Serial.print("Inner Temperature: ");
  Serial.print(innerTemp);
  Serial.print(" °C, Outer Temperature: ");
  Serial.print(outerTemp);
  Serial.println(" °C");
  for (int channel = 0; channel < 4; channel++) {
    float voltage = readADC(channel);
    Serial.print("ADC Channel ");
    Serial.print(channel);
    Serial.print(": ");
    Serial.print(voltage);
    Serial.println(" V");
  }

  delay(2000);
}
