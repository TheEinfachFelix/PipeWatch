#pragma once
#include <Arduino.h>
#include "DS18B20.h"

class TemperatureSensor
{
private:
    OneWire oneWire;
    DS18B20 sensor;
    uint8_t resolution;

public:
    TemperatureSensor(uint8_t pin, uint8_t resolution = 10);
    void begin();
    float readTemperature();
    bool isConnected();
};