#include "led.hpp"

Adafruit_NeoPixel strip(NUM_LEDS, 2, NEO_GRB + NEO_KHZ800);

void SetupLED() {
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    strip.setBrightness(255);
}

void setColor(uint8_t r, uint8_t g, uint8_t b) {
    uint32_t color = strip.Color(r, g, b);
    
    strip.fill(color, 0, NUM_LEDS);
    strip.setPixelColor(0,100,0,0);
    strip.show();
}