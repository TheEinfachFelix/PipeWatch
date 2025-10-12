#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "ADS1X15.h"

using namespace ADS1X15;



void setupADC(int SDA_PIN, int SCL_PIN);
float readADC(int channel);