#pragma once
#include <Arduino.h>
#include "LIS3DHTR.h"
#include <Wire.h>
#include "SPI.h"
#include "conf.hpp"



struct Acceleration {
    float x;
    float y;
    float z;
};

void MSUsetup();
bool MSUready();
int16_t MSUtemp();
Acceleration MSUread();