#include "adc.hpp"

ADS1115<TwoWire> ads(Wire);

void setupADC(int SDA_PIN, int SCL_PIN) {
    // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  Wire.begin(SDA_PIN, SCL_PIN);
  ads.begin();
  ads.setGain(Gain::TWOTHIRDS_6144MV);
  ads.setDataRate(Rate::ADS1115_250SPS);

}

bool ADCready()
{
  try
  {
    int16_t data = ads.getLastConversionResults();
    return true;
  }
  catch(const std::exception& e)
  {
    return false;
  }
  
}

float readADC(int channel) {
  int16_t adcValue = ads.readADCSingleEnded(channel);
  float voltage = ads.computeVolts(adcValue);
  return voltage;
}