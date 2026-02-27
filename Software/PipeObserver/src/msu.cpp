#include "msu.hpp"

LIS3DHTR<SPIClass> LIS;

void MSUsetup() {
  // SPI starten mit MSU Pins aus config.hpp
  SPI.begin(MSU_SPC_PIN, MSU_SAO_PIN, MSU_SDI_PIN); // CLK, MISO, MOSI
  LIS.begin(SPI, MSU_CS_PIN);                        // CS Pin aus config.hpp

  LIS.openTemp();         // ADC3 Temp Enable/Disable
  delay(100);

  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
}

bool MSUready()
{
    if (!LIS)
        return false;
    if (!LIS.available())
        return false;
    if (!LIS.isConnection())
        return false;

    return true;
}


int16_t MSUtemp()
{
    return LIS.getTemperature();
}



Acceleration MSUread() {
    Acceleration acc;
    LIS.getAcceleration(&acc.x, &acc.y, &acc.z);
    return acc;
}

