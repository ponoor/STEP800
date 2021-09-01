// oscListeners.h

#ifndef _OSCLISTENERS_h
#define _OSCLISTENERS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "globals.h"
#include <OSCMessage.h>

// 'motorID' : 1-8, 255
// 'motorId' : 0-7

void OSCMsgReceive();
bool isCorrectMotorId(uint8_t motorID);

void activate(uint8_t motorId, bool state);
void free(uint8_t motorId);

// config_commands_osc_listener
void setDestIp(OSCMessage& msg, int addrOffset);
void getVersion(OSCMessage& msg, int addrOffset);
void getConfigName(OSCMessage& msg, int addrOffset);
void getConfigRegister(uint8_t deviceId);
void getConfigRegister(OSCMessage& msg, int addrOffset);
void resetMotorDriver(OSCMessage& msg, int addrOffset);
void reportError(OSCMessage& msg, int addrOffset);
//void getAdcVal(OSCMessage& msg, int addrOffset);
void resetDev(OSCMessage& msg, int addrOffset);
void enableBusyReport(OSCMessage& msg, int addrOffset);
void enableHizReport(OSCMessage& msg, int addrOffset);
void enableHomeSwReport(OSCMessage& msg, int addrOffset);
//void enableLimitSwReport(OSCMessage& msg, int addrOffset);
void enableDirReport(OSCMessage& msg, int addrOffset);
void enableMotorStatusReport(OSCMessage& msg, int addrOffset);
void enableSwEventReport(OSCMessage& msg, int addrOffset);
void enableUvloReport(OSCMessage& msg, int addrOffset);
void enableThermalStatusReport(OSCMessage& msg, int addrOffset);
void enableOverCurrentReport(OSCMessage& msg, int addrOffset);
void enableStallReport(OSCMessage& msg, int addrOffset);
void getHomeSw(OSCMessage& msg, int addrOffset);
void getHomeSw(uint8_t motorId);
// void getLimitSw(OSCMessage& msg, int addrOffset);
// void getLimitSw(uint8_t motorId);
void getBusy(OSCMessage& msg, int addrOffset);
void getDir(OSCMessage& msg, int addrOffset);
void getHiZ(OSCMessage& msg, int addrOffset);
void getUvlo(OSCMessage& msg, int addrOffset);
void getMotorStatus(OSCMessage& msg, int addrOffset);
void getThermalStatus(OSCMessage& msg, int addrOffset);
void getStatus(OSCMessage& msg, int addrOffset);
void getStatusList(OSCMessage& msg, int addrOffset);
void setMicrostepMode(OSCMessage& msg, int addrOffset);
void getMicrostepMode(OSCMessage& msg, int addrOffset);
void getHomeSwMode(OSCMessage& msg, int addrOffset);
void setHomeSwMode(OSCMessage& msg, int addrOffset);
// void getLimitSwMode(OSCMessage& msg, int addrOffset);
// void setLimitSwMode(OSCMessage& msg, int addrOffset);
void getHomingStatus(OSCMessage& msg, int addrOffset); 
// STALL_TH register is 5bit in PowerSTEP01, 7bit in L6470
void setStallThreshold(OSCMessage& msg, int addrOffset);
void getStallThreshold(uint8_t motorId);
void getStallThreshold(OSCMessage& msg, int addrOffset);
// OCD_TH register is 5bit in PowerSTEP01, 4bit in L6470
void setOverCurrentThreshold(OSCMessage& msg, int addrOffset);
void getOverCurrentThreshold(uint8_t motorId);
void getOverCurrentThreshold(OSCMessage& msg, int addrOffset);
void setLowSpeedOptimizeThreshold(OSCMessage& msg, int addrOffset);
void getLowSpeedOptimizeThreshold(OSCMessage& msg, int addrOffset);
void getLowSpeedOptimizeThreshold(uint8_t motorId);
void setBemfParam(OSCMessage& msg, int addrOffset);
void getBemfParam(OSCMessage& msg, int addrOffset);
void getBemfParam(uint8_t motorId);
// void setDecayModeParam(OSCMessage& msg, int addrOffset);
// void getDecayModeParam(OSCMessage& msg, int addrOffset);
// void getDecayModeParam(uint8_t motorId);
void enableElectromagnetBrake(uint8_t motorId, bool bEnable);
void enableElectromagnetBrake(OSCMessage& msg, int addrOffset);
void setBrakeTransitionDuration(OSCMessage& msg, int addrOffset);
void getBrakeTransitionDuration(OSCMessage& msg, int addrOffset);
void setGoUntilTimeout(OSCMessage& msg, int addrOffset);
void getGoUntilTimeout(OSCMessage& msg, int addrOffset);
void setReleaseSwTimeout(OSCMessage& msg, int addrOffset);
void getReleaseSwTimeout(OSCMessage& msg, int addrOffset);
void setHomingDirection(OSCMessage& msg, int addrOffset);
void getHomingDirection(OSCMessage& msg, int addrOffset);
void setHomingSpeed(OSCMessage& msg, int addrOffset);
void getHomingSpeed(OSCMessage& msg, int addrOffset);
void setProhibitMotionOnHomeSw(OSCMessage& msg, int addrOffset);
void getProhibitMotionOnHomeSw(OSCMessage& msg, int addrOffset);
// void setProhibitMotionOnLimitSw(OSCMessage& msg, int addrOffset);
// void getProhibitMotionOnLimitSw(OSCMessage& msg, int addrOffset);

//  kval_commands_osc_listener
void setKval(OSCMessage& msg, int addrOffset);
void setHoldKval(OSCMessage& msg, int addrOffset);
void setRunKval(OSCMessage& msg, int addrOffset);
void setAccKval(OSCMessage& msg, int addrOffset);
void setDecKval(OSCMessage& msg, int addrOffset);
void getKval(OSCMessage& msg, int addrOffset);
void getKval(uint8_t motorId);

// tval_commands_osc_listener
// void setTval(OSCMessage& msg, int addrOffset);
// void setHoldTval(OSCMessage& msg, int addrOffset);
// void setRunTval(OSCMessage& msg, int addrOffset);
// void setAccTval(OSCMessage& msg, int addrOffset);
// void setDecTval(OSCMessage& msg, int addrOffset);
// void getTval(OSCMessage& msg, int addrOffset);
// void getTval(uint8_t motorId);
// float TvalToCurrent(uint8_t tval);
// void getTval_mA(uint8_t motorId);
// void getTval_mA(OSCMessage& msg, int addrOffset);

// speed_commands_osc_listener
void setSpeedProfile(OSCMessage& msg, int addrOffset);
void setMaxSpeed(OSCMessage& msg, int addrOffset);
void setFullstepSpeed(OSCMessage& msg, int addrOffset);
void getFullstepSpeed(OSCMessage& msg, int addrOffset);
void setAcc(OSCMessage& msg, int addrOffset);
void setDec(OSCMessage& msg, int addrOffset);
void setSpeedProfileRaw(OSCMessage& msg, int addrOffset);
void setMaxSpeedRaw(OSCMessage& msg, int addrOffset);
void setMinSpeedRaw(OSCMessage& msg, int addrOffset);
void setFullstepSpeedRaw(OSCMessage& msg, int addrOffset);
void setAccRaw(OSCMessage& msg, int addrOffset);
void setDecRaw(OSCMessage& msg, int addrOffset);
void getSpeed(OSCMessage& msg, int addrOffset);
void getSpeedProfile(OSCMessage& msg, int addrOffset);
void getSpeedProfile(uint8_t motorId);
void getSpeedProfileRaw(OSCMessage& msg, int addrOffset);
void getSpeedProfileRaw(uint8_t motorId);

// operational_commands_osc_listener
void getPosition(OSCMessage& msg, int addrOffset);
void getMark(OSCMessage& msg, int addrOffset);
void run(OSCMessage& msg, int addrOffset);
void runRaw(OSCMessage& msg, int addrOffset);
void move(OSCMessage& msg, int addrOffset);
void goTo(OSCMessage& msg, int addrOffset);
void goToDir(OSCMessage& msg, int addrOffset);
void homing(uint8_t motorId);
void homing(OSCMessage& msg, int addrOffset);
void goUntil(uint8_t motorId, bool action, bool dir, float stepsPerSec);
void goUntil(OSCMessage& msg, int addrOffset);
void goUntilRaw(OSCMessage& msg, int addrOffset);
void releaseSw(uint8_t motorId, bool action, bool dir);
void releaseSw(OSCMessage& msg, int addrOffset);
void goHome(OSCMessage& msg, int addrOffset);
void goMark(OSCMessage& msg, int addrOffset);
void setMark(OSCMessage& msg, int addrOffset);
void setPosition(OSCMessage& msg, int addrOffset);
void resetPos(OSCMessage& msg, int addrOffset);
void softStop(OSCMessage& msg, int addrOffset);
void hardStop(OSCMessage& msg, int addrOffset);
void softHiZ(OSCMessage& msg, int addrOffset);
void hardHiZ(OSCMessage& msg, int addrOffset);
void activate(OSCMessage& msg, int addrOffset);
void free(OSCMessage& msg, int addrOffset);

// servo_commands_osc_listener
void setTargetPosition(OSCMessage& msg, int addrOffset);
void setTargetPositionList(OSCMessage& msg, int addrOffset);
void enableServoMode(OSCMessage& msg, int addrOffset);
void setServoParam(OSCMessage& msg, int addrOffset);
void getServoParam(uint8_t motorId);
void getServoParam(OSCMessage& msg, int addrOffset);

// PowerSTEP01_config_osc_listener
// void setVoltageMode(uint8_t motorId);
// void setVoltageMode(OSCMessage& msg, int addrOffset);
// void setCurrentMode(uint8_t motorId);
// void setCurrentMode(OSCMessage& msg, int addrOffset);
void setElPos(OSCMessage& msg, int addrOffset);
void getElPos(OSCMessage& msg, int addrOffset);
#endif

