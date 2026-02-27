#include <Arduino.h>
#include "temp.hpp"
#include "conf.hpp"
#include "adc.hpp"
#include "led.hpp"
#include <ArduinoJson.h>

void SendSensorData();
String getSensorData();
void sendError(String ErrorMsg);
void sendMsg(String type, String data);

//TemperatureSensor innerSensor(INNER_TEMP_PIN, TEMP_RESOLUTION);
TemperatureSensor outerSensor(15, TEMP_RESOLUTION);//15

String status = STATUS_START;

void setup() {

  /////////////////////// Setup ///////////////////////
  Serial.begin(115200);
  Serial1.begin(115200);

  // ADC
  setupADC(ADC_SDA_PIN, ADC_SCL_PIN);

  // LED
  //SetupLED();

  // MSU

  // Temp
  //innerSensor.begin();
  outerSensor.begin();

  delay(5000);

  /////////////////////// check running ///////////////////////

  // ADC

  // MSU
  
  // Temp
  if (!outerSensor.isConnected())
    sendError("OuterSensor not Connected");
  //if (!innerSensor.isConnected())
  //  sendError("InnerSensor not Connected");

  // Button
  pinMode(BUTTON_PIN, INPUT); //TODO: wo für nutze ich den?

  status = STATUS_RUN;
}

void loop() {
  SendSensorData();
  delay(2000);
}

void SendSensorData()
{
  sendMsg(JSON_MSG_TYPE_DATA, getSensorData());
}

String getSensorData()
{
  StaticJsonDocument<256> doc;

  doc["WaterPresure"] = readADC(ADC_CH_Pressure);
  doc["WaterLevel"] = readADC(ADC_CH_WaterLvl);
  doc["Lightlevel"] = readADC(ADC_CH_Photores);
  // MSU

  // Temp
  if(outerSensor.isConnected())
    doc["Temp_Out"] = outerSensor.readTemperature();
  //if(innerSensor.isConnected())
  //  doc["Temp_Inside"] = innerSensor.readTemperature();

  String jsonString;
  serializeJson(doc, jsonString);
  return jsonString;
}



void sendError(String ErrorMsg)
{
  sendMsg(JSON_MSG_TYPE_ERROR, ErrorMsg);
}

void sendMsg(String type, String data)
{
  Serial1.println("{\"version\":"+(String)JSON_VERSION+",\"device\":\""+JSON_DEVICE_NAME+"\", \"uptime\":"+millis()+", \"state\":\""+status+"\", \"data\":\""+data+"\"}");
}