#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "conf.hpp"

void SetupLED();

void setColor(uint8_t r, uint8_t g, uint8_t b);