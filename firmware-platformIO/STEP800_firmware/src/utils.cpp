// 
// 
// 

#include "utils.h"
//#include "oscListeners.h"
#include <stdarg.h>

char* p_(const __FlashStringHelper* fmt, ...)
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
	return buf;
}

uint8_t getMyId() {
    uint8_t _id = 0;
    // for (auto i = 0; i < 8; ++i)
    // {
    //     pinMode(dipSwPin[i], INPUT_PULLUP);
    //     _id |= (!digitalRead(dipSwPin[i])) << i;
    // }
#ifdef PROTOTYPE_R3
    byte shiftInByte[3];
    digitalWrite(LATCH3, LOW);
    digitalWrite(LATCH3, HIGH);
    for (uint8_t i = 0; i < 3; i++) {
        shiftInByte[i] = SPI3.transfer(0);
    }
    _id = shiftInByte[2];
#elif defined(PROTOTYPE_BLACK)
    uint32_t shiftInByte;
    digitalWrite(LATCH3, LOW);
    digitalWrite(LATCH3, HIGH);
    shiftInByte = !digitalRead(MISO3);
    for (uint8_t i = 1; i < 24; i++) {
        digitalWrite(SCK3, HIGH);
        shiftInByte |= (!digitalRead(MISO3))<<i;
        digitalWrite(SCK3, LOW);
    }
    _id = shiftInByte >> 16;
#else
    digitalWrite(LATCH3, LOW);
    digitalWrite(LATCH3, HIGH);
    SPI3.transfer(brakeOut);
    _id = SPI3.transfer(0);
    _id = ~_id;
#endif
    return _id;
}

void turnOnRXL() {
    digitalWrite(PIN_LED_RXL, LOW); // turn on
    RXL_blinkStartTime = millis();
    rxLedEnabled = true;
}

void turnOnTXL() {
    digitalWrite(PIN_LED_TXL, LOW); // turn on
    TXL_blinkStartTime = millis();
    txLedEnabled = true;
}

void resetMotorDriver(uint8_t deviceID) {
    if (MOTOR_ID_FIRST <= deviceID && deviceID <= MOTOR_ID_LAST) {
        deviceID -= MOTOR_ID_FIRST;
        stepper[deviceID].resetDev();
        stepper[deviceID].configStepMode(microStepMode[deviceID]);
        stepper[deviceID].setMaxSpeed(maxSpeed[deviceID]);
        stepper[deviceID].setLoSpdOpt(lowSpeedOptimizeEnable[deviceID]);
        if (lowSpeedOptimizeEnable[deviceID]) {
            stepper[deviceID].setMinSpeed(lowSpeedOptimizeThreshold[deviceID]); // Low speed optimization threshold
        } else {
            stepper[deviceID].setMinSpeed(minSpeed[deviceID]);
        }
        stepper[deviceID].setFullSpeed(fullStepSpeed[deviceID]);
        stepper[deviceID].setAcc(acc[deviceID]);
        stepper[deviceID].setDec(dec[deviceID]);
        stepper[deviceID].setSlewRate(slewRate[deviceID]);
        stepper[deviceID].setPWMFreq(PWM_DIV_1, PWM_MUL_0_75);
        uint16_t swMode = homeSwMode[deviceID] ? SW_USER : SW_HARD_STOP;
        stepper[deviceID].setSwitchMode(swMode);//
        stepper[deviceID].setVoltageComp(VS_COMP_DISABLE);
        stepper[deviceID].setOCThreshold(overCurrentThreshold[deviceID]); // 5A for 0.1ohm shunt resistor
        stepper[deviceID].setOCShutdown(OC_SD_ENABLE);
    #ifdef PROTOTYPE_BLACK
        stepper[deviceID].setOscMode(EXT_24MHZ_OSCOUT_INVERT);
    #else
        stepper[deviceID].setOscMode(EXT_16MHZ_OSCOUT_INVERT);
    #endif

        // if (isCurrentMode[deviceID]) {
        //     stepper[deviceID].setHoldTVAL(tvalHold[deviceID]);
        //     stepper[deviceID].setRunTVAL(tvalRun[deviceID]);
        //     stepper[deviceID].setAccTVAL(tvalAcc[deviceID]);
        //     stepper[deviceID].setDecTVAL(tvalDec[deviceID]);
        //     stepper[deviceID].setParam(T_FAST, fastDecaySetting[deviceID]);
        //     stepper[deviceID].setParam(TON_MIN, minOnTime[deviceID]);
        //     stepper[deviceID].setParam(TOFF_MIN, minOffTime[deviceID]);
        //     setCurrentMode(deviceID);
        // } else 
        {
            stepper[deviceID].setRunKVAL(kvalRun[deviceID]);
            stepper[deviceID].setAccKVAL(kvalAcc[deviceID]);
            stepper[deviceID].setDecKVAL(kvalDec[deviceID]);
            stepper[deviceID].setHoldKVAL(kvalHold[deviceID]);
            stepper[deviceID].setParam(INT_SPD, intersectSpeed[deviceID]);
            stepper[deviceID].setParam(ST_SLP, startSlope[deviceID]);
            stepper[deviceID].setParam(FN_SLP_ACC, accFinalSlope[deviceID]);
            stepper[deviceID].setParam(FN_SLP_DEC, decFinalSlope[deviceID]);
        }
        stepper[deviceID].setParam(STALL_TH, stallThreshold[deviceID]);
        stepper[deviceID].setParam(ALARM_EN, 0xEF); // Enable alarms except ADC UVLO

        delay(1);
        stepper[deviceID].getStatus(); // clears error flags
    }
}

void sendWrongDataTypeError() {
    if (reportErrors)
        sendOneDatum(F("/error/osc"),"WrongDataType");
}

int getInt(OSCMessage &msg, uint8_t offset) 
{
	int msgVal = 0;
	if (msg.isFloat(offset))
	{
		msgVal = (int) msg.getFloat(offset);
	}
	else if (msg.isInt(offset))
	{
		msgVal = msg.getInt(offset);
	}
    else {
        sendWrongDataTypeError();
    }
	return msgVal;
}

float getFloat(OSCMessage &msg, uint8_t offset)
{
	float msgVal = 0;
	if (msg.isFloat(offset))
	{
		msgVal = msg.getFloat(offset);
	}
	else if (msg.isInt(offset))
	{
		msgVal = msg.getInt(offset);
	}
    else {
        sendWrongDataTypeError();
    }
	return msgVal;
}

bool getBool(OSCMessage &msg, uint8_t offset)
{
    bool msgVal = 0;
	if (msg.isFloat(offset))
	{
		msgVal = msg.getFloat(offset) >= 1.0f;
	}
	else if (msg.isInt(offset))
	{
		msgVal = msg.getInt(offset) > 0;
	}
    else if (msg.isBoolean(offset)) 
    {
        msgVal = msg.getBoolean(offset);
    }
    else {
        sendWrongDataTypeError();
    }
	return msgVal;
    
}

void setBrake(uint8_t motorId, bool state) {
#ifdef HAS_BRAKE
    if (state) {
        bitSet(brakeOut, motorId);
    } else {
        bitClear(brakeOut, motorId);
    }
#endif
}

void sendCommandError(uint8_t motorId, uint8_t errorNum)
{
    if (reportErrors) {
        sendTwoData(F("/error/command"), commandErrorText[errorNum].c_str(), motorId);
        //if (SerialUSB)
            //p("/error/command %s %d\n", commandErrorText[errorNum].c_str(), motorId);
    }
}

bool isBrakeDisEngaged(uint8_t motorId) {
    bool state = electromagnetBrakeEnable[motorId] && (brakeStatus[motorId] != BRAKE_DISENGAGED);
    if (state) {
        sendCommandError(motorId + MOTOR_ID_FIRST, ERROR_BRAKE_ENGAGED);
    }
    return !state;
}

bool checkMotionStartConditions(uint8_t motorId, bool dir) {
    if (!isBrakeDisEngaged(motorId)) {
        return false;
    }
    else if ( isServoMode[motorId] ) {
        sendCommandError(motorId + MOTOR_ID_FIRST, ERROR_IN_SERVO_MODE);
        return false;
    }
    else if (bProhibitMotionOnHomeSw[motorId] && (dir == homingDirection[motorId])) {
        if (homeSwState[motorId]) {
            sendCommandError(motorId + MOTOR_ID_FIRST, ERROR_HOMESW_ACTIVATING);
            return false;
        }
    }
    // else if (bProhibitMotionOnLimitSw[motorId] && (dir != homingDirection[motorId])) {
    //     if (limitSwState[motorId]) {
    //         sendCommandError(motorId + MOTOR_ID_FIRST, ERROR_LIMITSW_ACTIVATING);
    //         return false;
    //     }
    // }
    return true;
}

void sendThreeInt(String address, int32_t data1, int32_t data2, int32_t data3) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes(address.c_str());
    newMes.add(data1).add(data2).add(data3);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}