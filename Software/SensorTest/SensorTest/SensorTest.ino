/*
   A02YYUW Ultrasonic Sensor
   ESP32 Version ohne SoftwareSerial
*/

class A02YYUW {
  protected:
    static const byte numChars = 4;    
    char receivedChars[numChars];      
    byte ndx = 0;                      
    boolean newData = false;           
    Stream &stream;                    
    void (*cbOnNewData)();             
    int distance = 0;                  

    void delBuffer() {
      memset(receivedChars, 0, sizeof(receivedChars));
      ndx = 0;
    }

    void parseData() {
      int result = (receivedChars[1] << 8) + receivedChars[2];
      if (result <= 4500)
        distance = result;
    }

    bool validateChecksum() {
      int sum = (receivedChars[0] + receivedChars[1] + receivedChars[2]) & 0xFF;
      return sum == (receivedChars[3] & 0xFF);
    }

    void parseLine() {
      if (validateChecksum()) {
        parseData();
        if (cbOnNewData) cbOnNewData();
      }
    }

  public:
    A02YYUW (Stream &stream) : stream(stream) {
      delBuffer();
    }

    uint16_t getDistance() {
      return distance;
    }

    void setOnNewData(void (*cbOnNewData)()) {                                            
      this->cbOnNewData = cbOnNewData;         
    }                                            
                                                 
    void update() {
      constexpr char startMarker = 0xFF;
      if (stream.available() > 0) {
        char rc = stream.read();
        if (ndx == 0) {
          if (rc == startMarker) {
            delBuffer();
            receivedChars[ndx++] = rc;
          }
        } else {
          receivedChars[ndx++] = rc;
          if (ndx >= numChars) {
            ndx = 0;
            parseLine();
          }
        }
      }
    }
};

// --- ESP32 Hardware Serial ---
HardwareSerial mySerial(1);  // UART1, RX=16, TX=17 (anpassen an dein Setup)
A02YYUW ultrasonic(mySerial);  

void output() {
  Serial.print(ultrasonic.getDistance()); 
  Serial.println(" mm");
}

void timerOutput() {
  static uint32_t previousMillis = 0;
  const uint16_t interval = 3000;
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();
    output();
  }
}

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
  //ultrasonic.setOnNewData(output);  // optional Callback
}

void loop() {
  ultrasonic.update();
  timerOutput();
}
