#include <Arduino.h>
// STEP800 LED test

#include <Ponoor_L6470Library.h>
#include "wiring_private.h" // pinPeripheral() function


#define ledPin  13u
// L6470
#define L6470_MISO  6u  // D6 /SERCOM3/PAD[2] miso
#define L6470_MOSI  11u // D11/SERCOM3/PAD[0] mosi
#define L6470_SCK 12u // D12/SERCOM3/PAD[3] sck

#define L6470_CS_PIN A0
#define L6470_RESET_PIN A2

#define NUM_OF_MOTOR   (8)
SPIClass L6470SPI(&sercom3, L6470_MISO, L6470_SCK, L6470_MOSI, SPI_PAD_0_SCK_3, SERCOM_RX_PAD_2);// MISO/SCK/MOSI pins

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
}

void showHeader(String header) {
  p("-------------- %s --------------\n", header.c_str());
}


void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  SerialUSB.begin(9600);
  // setup L6470
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
      // digitalWrite(ledPin, HIGH);
      // delay(5);
      // digitalWrite(ledPin, LOW);
      stepper[i].getStatus();
      delay(5);
  }

}

void flagLED() {
  for (uint8_t i = 0; i < NUM_OF_MOTOR; i++)
  {
    stepper[i].hardStop();
    stepper[i].setParam(INT_SPD, 0); // this should cause an NOTPREF_CMD flag.
  }
}

void busyLED() {
  for (uint8_t i = 0; i < NUM_OF_MOTOR; i++)
  {
    stepper[i].getStatus(); // clear the busy flags
    stepper[i].goUntil(0, FWD, 100.0); // make the driver busy
  }
}

void clearLED() {
  for (uint8_t i = 0; i < NUM_OF_MOTOR; i++)
  {
    stepper[i].hardHiZ();
    stepper[i].getStatus();
  }
}

void loop() {
  if (SerialUSB.available()>0) {
    switch( SerialUSB.read() ) {
      case 'f':
        flagLED();
        break;
      case 'b':
        busyLED();
        break;
      case 'c':
        clearLED();
        break;
    }
  }
}
