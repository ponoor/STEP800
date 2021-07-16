// Arduino Sketch for STEP800 Hardware Inspections
// target : STEP800 / Arduino Zero Native USB port
// by Kanta HORIO / Ponoor Experiments inc

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include <FlashStorage.h>
#include <Ponoor_L6470Library.h>
#include "wiring_private.h" // pinPeripheral() function


#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__
constexpr auto FIRMWARE_NAME = "STEP800_r1_hardware_test_r1.0.0";
String results;
FlashStorage(storage, String);

#define SD_CS_PIN  4u
#define SD_DETECT_PIN   A4
    #define ledPin  13u
    // L6470
    #define L6470_MISO  6u  // D6 /SERCOM3/PAD[2] miso
    #define L6470_MOSI  11u // D11/SERCOM3/PAD[0] mosi
    #define L6470_SCK 12u // D12/SERCOM3/PAD[3] sck

    #define L6470_CS_PIN A0
    #define L6470_RESET_PIN A2
    // Shift registers
    // 74HC165 +74HC595 for the dip sw input and the brake output
    #define MISO3 3u // SERCOM2/PAD[1]
    #define MOSI3   2u // SERCOM2/PAD[2]
    #define SCK3  0u // SERCOM2/PAD[3]
    #define LATCH3  A5
    // Shift registers SPI
    extern SPIClass SPI3;

    // W5500
    #define W5500_RESET_PIN A3

    #define SHIFTOUT_ENABLE_PIN 5u

const uint8_t auxPin[8] = {7u,1u,A1,6u,9u,38u,SCL,SDA};
#define NUM_OF_MOTOR   (8)
SPIClass L6470SPI(&sercom3, L6470_MISO, L6470_SCK, L6470_MOSI, SPI_PAD_0_SCK_3, SERCOM_RX_PAD_2);// MISO/SCK/MOSI pins

SPIClass SPI3(&sercom2, MISO3, SCK3, MOSI3, SPI_PAD_2_SCK_3, SERCOM_RX_PAD_1);


// L6470
AutoDriver stepper[] = {
  AutoDriver(7, L6470_CS_PIN, L6470_RESET_PIN),
  AutoDriver(6, L6470_CS_PIN, L6470_RESET_PIN),
  AutoDriver(5, L6470_CS_PIN, L6470_RESET_PIN),
  AutoDriver(4, L6470_CS_PIN, L6470_RESET_PIN),
  AutoDriver(3, L6470_CS_PIN, L6470_RESET_PIN),
  AutoDriver(2, L6470_CS_PIN, L6470_RESET_PIN),
  AutoDriver(1, L6470_CS_PIN, L6470_RESET_PIN),
  AutoDriver(0, L6470_CS_PIN, L6470_RESET_PIN)
};

// Network
byte mac[] = { 0x60, 0x95, 0xCE, 0x10, 0x02, 0x90 };
IPAddress 
    myIp(10, 0, 0, 100),
    destIp(10, 0, 0, 10),
    dns(10, 0, 0, 1),
    gateway(10, 0, 0, 1),
    subnet(255, 255, 255, 0);
EthernetUDP Udp;

// Serial Monitor out utilities
#define p(fmt, ...)  p_(F(fmt), ##__VA_ARGS__)
void p_(const __FlashStringHelper* fmt, ...)
{
    char buf[128]; // resulting string limited to 128 chars
    va_list args;
    va_start(args, fmt);
#ifdef __AVR__
    vsnprintf_P(buf, sizeof(buf), (const char*)fmt, args); // progmem for AVR
#else
    vsnprintf(buf, sizeof(buf), (const char*)fmt, args); // for the rest of the world
#endif
    va_end(args);
    SerialUSB.print(buf);
    results += String(buf);
}

void showHeader(String header) {
  p("-------------- %s --------------\n", header.c_str());
}

void showBoolResult(bool t) {
  if (t) { p("Ok\n"); }
  else { p("Failed\n");}
}
void showTestResult(bool t) {
  String res = (t) ? "Passed" : "Failed";
  p("\nTest result: %s\n\n", res.c_str());
}

// Title
void showTestTitle() {
  showHeader("STEP800 hardware test");
  p("Firmware revision: %s\n",FIRMWARE_NAME);
  p("Compiled at %s %s\n", COMPILE_DATE, COMPILE_TIME);
}
// SD card
bool sdTest() {
  bool t, result = false;
  showHeader("SD card");
  pinMode(SD_CS_PIN, OUTPUT);
  pinMode(SD_DETECT_PIN, INPUT_PULLUP);
  p("SD card initialize: ");
  t = SD.begin(SD_CHIP_SELECT_PIN);
  showBoolResult(t);
  if (t)
  {
    SD.end();
    result = !digitalRead(SD_DETECT_PIN);
    p("SD_DETECT_PIN: %d ", !result);
    showBoolResult(result);
    
  } else {
    if (digitalRead(SD_DETECT_PIN) == LOW) {
      p("The SD card and/or SD slot connection is broken.");
    } else {
      p("SD card is not inserted.");
    }
  }
  pinMode(SD_CS_PIN, INPUT);
  showTestResult(result);
  return result;
}

// Auxiliary Pins
bool auxPinTest() {
  showHeader("Auxiliary Pins");
  p("Auxiliary Pins connection state: ");
  bool t = true;
  for (uint8_t i = 0; i < 8; i++)
  {
    for (uint8_t j = 0; j < 8; j++) {
      pinMode(auxPin[j], OUTPUT);
      digitalWrite(auxPin[j], LOW);
    }
    pinMode(auxPin[i], INPUT_PULLUP);
    t &= digitalRead(auxPin[i]); // the pin has to be HIGH
    if (!t) {
      p("\nauxPin#%d connection problem found.\n", i+1);
    }
    pinMode(auxPin[i],INPUT);
  }
  showBoolResult(t);
  showTestResult(t);
  return t;
}
// Ethernet
void resetW5500() {
  pinMode(W5500_RESET_PIN, OUTPUT);
  digitalWrite(W5500_RESET_PIN, HIGH);
  delay(1);
  digitalWrite(W5500_RESET_PIN, LOW);
  delay(10);
  digitalWrite(W5500_RESET_PIN, HIGH);
  delay(10);
  //Ethernet.init(10);
  Ethernet.begin(mac, myIp);
  Udp.begin(50000);
}
bool ethernetTest() {
  uint8_t t;
  String s;
  bool result = false;
  showHeader("Ethernet");
  digitalWrite(ledPin, HIGH);
  resetW5500();
  delay(100);
  digitalWrite(ledPin, LOW);
  t = Ethernet.hardwareStatus();
  p("Ethernet hardware status: %d, ",t);
  switch (t)
  {
  case EthernetNoHardware:
    p("-EthernetNoHardware\nW5500 connection failed.\n");
    break;
  case EthernetW5100:
    p("-EthernetW5100\nWrong hardware detected.\n");
    break;
  case EthernetW5200:
    p("-EthernetW5200\nWrong hardware detected.\n");
    break;
  case EthernetW5500:
    p("-EthernetW5500 Ok\n");
    result = true;
    break;
  default:
    break;
  }
  bool linked = true;
  if (result) {
    uint8_t counter = 0;
    t = Ethernet.linkStatus();
    p("Ethernet link status: %d ", t);
    while ( Ethernet.linkStatus() != LinkON ) {
      delay(500);
      counter++;
      p(".");
      if (counter>=8) {
        p(" timeout\n");
        linked = false;
        break;
      }
    }
    if (linked) p("Ok\n");
  }
  result &= linked;
  pinMode(W5500_RESET_PIN, INPUT);
  //SPI.end();
  showTestResult(result);
  return result;
}

// L6470
bool L6470Test() {
  showHeader("L6470");
  bool result = true;
  boolean L6470_reset_pin_enable_state = HIGH;
  pinMode(L6470_RESET_PIN, OUTPUT);
  pinMode(L6470_CS_PIN, OUTPUT);
  pinMode(L6470_MOSI, OUTPUT);
  pinMode(L6470_MISO, INPUT);
  pinMode(L6470_SCK, OUTPUT);
  digitalWrite(L6470_RESET_PIN, L6470_reset_pin_enable_state);
  digitalWrite(L6470_RESET_PIN, !L6470_reset_pin_enable_state);
  delay(10);
  digitalWrite(L6470_RESET_PIN, L6470_reset_pin_enable_state);
  digitalWrite(L6470_CS_PIN, HIGH);
  L6470SPI.begin();
  pinPeripheral(L6470_MOSI, PIO_SERCOM_ALT);
  pinPeripheral(L6470_SCK, PIO_SERCOM_ALT);
  pinPeripheral(L6470_MISO, PIO_SERCOM_ALT);
  L6470SPI.setDataMode(SPI_MODE3);

  for (uint8_t i = 0; i < NUM_OF_MOTOR; i++)
  {
      stepper[i].SPIPortConnect(&L6470SPI);
      digitalWrite(ledPin, HIGH);
      delay(5);
      digitalWrite(ledPin, LOW);
      delay(5);
  }
    uint8_t i = 0;
  uint16_t status[NUM_OF_MOTOR];
  uint32_t temp = 0;

  p("L6470 SPI connection: ");
  for (i = 0; i < NUM_OF_MOTOR; i++) {
    stepper[i].resetDev();
    stepper[i].setOscMode(EXT_16MHZ_OSCOUT_INVERT); // 16MHz for the production version
    stepper[i].setVoltageComp(VS_COMP_DISABLE);
    stepper[i].setParam(ALARM_EN, 0xEF); // Enable alarms except ADC UVLO
    status[i] = stepper[i].getStatus(); // Clear Startup Flags
    stepper[i].run(FWD, 200.0); // Test motion
    status[i] = stepper[i].getStatus();
    temp += status[i];
    stepper[i].hardHiZ();
  }
  showBoolResult(temp!=0);

  if (temp != 0) {
    for ( i = 0; i < NUM_OF_MOTOR; i++)
    {
      temp = 0;
      p("L6470 ID#%d\n STATUS: 0x%02X ",i+1, status[i]);
      // OCD, active low, latched
      if ((status[i] & STATUS_OCD) == 0) {
        temp = 0x01;
      }
      // UVLO, active low
      if ((status[i] & STATUS_UVLO) == 0) {
        temp |= 0x02;
      }
      switch (temp)
      {
      case 0:
        p(" Ok\n");
        break;
      case 1:
        // OCD detected.
        p("OCD(Over Current) detected.\n");
        result = false;
        break;
      case 2:
        // ULVO detected.
        p("UVLO(Under Voltage LockOut) detected.\n");
        result = false;
        break;
      case 3:
        // OCD+ULVO detected.
        p("OCD+UVLO detected.\n");
        result = false;
        break;
      default:
        break;
      }

      // SW_F, low for open, high for close
      bool swF = (status[i] & STATUS_SW_F);
      p(" SW_F: %d ", swF);
      showBoolResult(!swF);
      if (swF == 1) {
        p("  HOME senser input closed. Check HOME connection.\n");
        result = false;
      }

      // BUSY
      bool busyF = (status[i] &STATUS_BUSY);
      p(" BUSY: %d ", busyF); // 1:NOT BUSY, 0:BUSY, should be in BUSY
      showBoolResult(!busyF);
      if (busyF == 1) {
        p("  The test motor motion command can't excute.\n");
        result = false;
      }
    }
  } else {
    result = false;
  }
  L6470SPI.end();
  showTestResult(result);
  return result;

}
uint8_t getDipSw() {
  uint8_t _id = 0;
  digitalWrite(LATCH3, LOW);
  digitalWrite(LATCH3, HIGH);
  SPI3.transfer(0); // output for the brake
  _id = SPI3.transfer(0);
  _id = ~_id;
  return _id;
}
// DIP switch
bool dipSwTest() {
  showHeader("DIP Switch");
  bool result = true;
  uint8_t t = 255, count = 0;

  // Shift Registers
  SPI3.begin();
  pinPeripheral(MISO3, PIO_SERCOM_ALT); // MISO
  pinPeripheral(MOSI3, PIO_SERCOM); // MOSI
  pinPeripheral(SCK3, PIO_SERCOM_ALT);    // SCK
  SPI3.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  pinMode(LATCH3, OUTPUT);
  digitalWrite(LATCH3, HIGH);
  pinMode(SHIFTOUT_ENABLE_PIN, OUTPUT);
  digitalWrite(SHIFTOUT_ENABLE_PIN, HIGH);

  if ( getDipSw() != 0) {
    p("Please set all digits 0(OFF): ");
    
    while ( t != 0)
    {
      t = getDipSw();
      delay(50);
      count++;
      if (count >=20 ) { p("."); count = 0;}
      if (SerialUSB.available()>0) {
        byte e = SerialUSB.read();
        if (e == 'b') {
          p("Cancelled.\n");
          result = false;
          return result;
        }
      }
    }
    p("\n");
    count = 0;
  } 
  t= 0;
  for (uint8_t i=0; i<8; i++) {
    p("Turn the digit #%d ON.", i+1);
    while ( t !=  1) {
      t = getDipSw();
      t = (t>>i) & 1;
      delay(50);
      count++;
      if (count >=20 ) { p("."); count=0;}
      if (SerialUSB.available()>0) {
        byte e = SerialUSB.read();
        if (e == 'b') {
          p("Cancelled.\n");
          result = false;
          return result;
        }
      }
    }
    p("Done.\nTurn the digit #%d OFF.", i+1);
    t = 1;
    while ( t !=  0) {
      t = getDipSw();
      t = (t>>i) & 1;
      delay(50);
      count++;
      if (count >=20 ) { p("."); count=0;}
      if (SerialUSB.available()>0) {
        byte e = SerialUSB.read();
        if (e == 'b') {
          p("Cancelled.\n");
          result = false;
          return result;
        }
      }
    }
    p("Done.\n");
  }
  showTestResult(true);
  return true;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  SerialUSB.begin(9600);
}

void hardwareTest() {
  bool testResult[5];
  bool t = true;
  results = "";
  showTestTitle();
  t &= (testResult[0] = sdTest());
  t &= (testResult[1] = auxPinTest());
  t &= (testResult[2] = ethernetTest());
  t &= (testResult[3] = L6470Test());
  t &= (testResult[4] = dipSwTest());
  showHeader("Result of Hardware Test");
  p("SD Card: ");
  showBoolResult(testResult[0]);
  p("Auxiliary Pins: ");
  showBoolResult(testResult[1]);
  p("Ethernet: ");
  showBoolResult(testResult[2]);
  p("L6470: ");
  showBoolResult(testResult[3]);
  p("DIP switch: ");
  showBoolResult(testResult[4]);
  showTestResult(t);
  storage.write(results);
}

void loadResults() {
  SerialUSB.println(F("================ Stored results ================"));
  results = storage.read();
  SerialUSB.println(results);
}

void loop() {
  if (SerialUSB.available()>0) {
    switch( SerialUSB.read() ) {
      case 't':
        hardwareTest();
        break;
      case 's':
        sdTest();
        break;
      case 'l':
        loadResults();
        break;
      case 'd':
        byte t = getDipSw();
        p("DIP SW: %d\n", t);
        break;
    }
  }
}
