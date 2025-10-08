#include "temp.hpp"


TemperatureSensor::TemperatureSensor(uint8_t pin, uint8_t resolution)
    : oneWire(pin), sensor(&oneWire), resolution(resolution)
{
}

void TemperatureSensor::begin()
{
    Serial.println("Initializing DS18B20...");
    sensor.begin();
    sensor.setResolution(resolution);
}

float TemperatureSensor::readTemperature()
{
    sensor.requestTemperatures();

    while (!sensor.isConversionComplete())
    {
        delay(1);
    }

    return sensor.getTempC();
}

bool TemperatureSensor::isConnected()
{
    return sensor.isConnected();
}