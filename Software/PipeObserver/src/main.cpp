#include <Arduino.h>
#include "temp.hpp"
#include "conf.hpp"
#include "adc.hpp"
#include "led.hpp"
#include "msu.hpp"
#include <ArduinoJson.h>
#include <cmath>

void SendSensorData();
String getSensorData();
void sendError(String ErrorMsg);
void sendMsg(String type, String data);

TemperatureSensor innerSensor(INNER_TEMP_PIN, TEMP_RESOLUTION);
TemperatureSensor outerSensor(15, TEMP_RESOLUTION);//15

String status = STATUS_START;

void setup() {

  /////////////////////// Setup ///////////////////////
  // Serial
  Serial.begin(115200);
  Serial1.begin(38400, 134217756U,47,48);

  // ADC
  setupADC(ADC_SDA_PIN, ADC_SCL_PIN);

  // LED
  //SetupLED();

  // MSU
  MSUsetup();

  // Temp
  innerSensor.begin();
  outerSensor.begin();

  Serial.println("Waiting");
  delay(25000);

  /////////////////////// check running ///////////////////////
  // ADC
  if (!ADCready())
    sendError("ADC not ready");

  // MSU
  if (!MSUready())
    sendError("MSU not ready");

  // Temp
  if (!outerSensor.isConnected())
    sendError("OuterSensor not ready");
  if (!innerSensor.isConnected())
    sendError("InnerSensor not ready");

  // Button
  pinMode(BUTTON_PIN, INPUT); //TODO: wo für nutze ich den?

  status = STATUS_RUN;
}

void loop() {
  SendSensorData();
  delay(30000);
}

void SendSensorData()
{
  sendMsg(JSON_MSG_TYPE_DATA, getSensorData());
}

String getSensorData()
{
  StaticJsonDocument<256> doc;

  // ADC - Rundung auf 3 Stellen und Fixierung als Zahl
  doc["WaterPresure"] = serialized(String(readADC(ADC_CH_Pressure), 3));
  doc["WaterLvl"]     = serialized(String(readADC(ADC_CH_WaterLvl), 3));
  doc["Lightlvl"]     = serialized(String(readADC(ADC_CH_Photores), 3));

  // MSU
  Acceleration MSUdata = MSUread();
  doc["AccX"] = serialized(String(MSUdata.x, 3));
  doc["AccY"] = serialized(String(MSUdata.y, 3));
  doc["AccZ"] = serialized(String(MSUdata.z, 3));

  // Temp
  if(outerSensor.isConnected())
    doc["Temp_Out"] = serialized(String(outerSensor.readTemperature(), 3));
  if(innerSensor.isConnected())
    doc["Temp_Inside"] = serialized(String(innerSensor.readTemperature(), 3));

  String jsonString;
  serializeJson(doc, jsonString);
  return jsonString;
}

void sendError(String ErrorMsg)
{
  sendMsg(JSON_MSG_TYPE_ERROR, ErrorMsg);
  delay(5000);
}

void sendMsg(String type, String data)
{
  data.replace("\"","\\\"");
  String OutStr = "{\"v\":"+(String)JSON_VERSION+",\"d\":\""+JSON_DEVICE_NAME+"\", \"uT\":"+millis()+", \"state\":\""+status+"\", \"data\":\""+data+"\"}";
  Serial.println(OutStr);
  Serial1.println(OutStr);
}