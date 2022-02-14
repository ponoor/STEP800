// utils.h

#ifndef _UTILS_h
#define _UTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "globals.h"
#include <OSCMessage.h>
#include <Ethernet.h>

char* p_(const __FlashStringHelper* fmt, ...);
#define p(fmt, ...)	 p_(F(fmt), ##__VA_ARGS__)

uint8_t getMyId();

void turnOnRXL();
void turnOnTXL();
void resetMotorDriver(uint8_t deviceID);
void sendThreeInt(String address, int32_t data1, int32_t data2, int32_t data3);

int getInt(OSCMessage &msg, uint8_t offset);
float getFloat(OSCMessage &msg, uint8_t offset);
bool getBool(OSCMessage &msg, uint8_t offset);

void setBrake(uint8_t motorId, bool state);
bool isBrakeDisEngaged(uint8_t motorId);
void clearHomingStatus(uint8_t motorId);
bool checkMotionStartConditions(uint8_t motorId, bool dir, bool checkHomingStatus = true);
void sendCommandError(uint8_t motorID, uint8_t errorNum);

template <class T>
void sendOneDatum(String address, T data) {
	if (!isDestIpSet) { return; }
    OSCMessage newMes(address.c_str());
    newMes.add(data);;
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

template <class T, class U>
void sendTwoData(String address, T data1, U data2) {
	if (!isDestIpSet) { return; }
    OSCMessage newMes(address.c_str());
    newMes.add(data1).add(data2);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void sendAllData(String address, int32_t *data);
#endif