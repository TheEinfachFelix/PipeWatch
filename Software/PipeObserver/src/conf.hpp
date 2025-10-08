#pragma once

// ADC
#define ADC_SDA_PIN 14
#define ADC_SCL_PIN 21

// Temperature Sensors
#define INNER_TEMP_PIN 2   // GPIO pin for inner temperature sensor
#define OUTER_TEMP_PIN 38  // GPIO pin for outer temperature sensor
#define TEMP_RESOLUTION 10 // 9, 10, 11, or 12 bits

// Button
#define BUTTON_PIN 20 // GPIO pin for button

// LED Strip
#define LED_PIN 1        // GPIO pin for LED strip
#define NUM_LEDS 4      // Number of LEDs in the strip

// MSU
#define MSU_INT1_PIN 3 // GPIO pin for MSU INT1
#define MSU_INT2_PIN 9 // GPIO pin for MSU INT2
#define MSU_CS_PIN 10  // GPIO pin for MSU CS
#define MSU_SAO_PIN 11 // GPIO pin for MSU SAO
#define MSU_SDI_PIN 12 // GPIO pin for MSU SDI
#define MSU_SPC_PIN 13 // GPIO pin for MSU SPC