// loadConfig.h

#ifndef _LOADCONFIG_h
#define _LOADCONFIG_h
#pragma once
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include "globals.h"
#include "utils.h"

void loadConfig();
uint8_t checkConfigVersion();
enum {
	CONFIG_VERSION_UNDEFINED = 0,
	CONFIG_VERSION_NOTLOADED,
	CONFIG_VERSION_OLD,
	CONFIG_VERSION_APPLICABLE,
	CONFIG_VERSION_NEW
};
#endif

