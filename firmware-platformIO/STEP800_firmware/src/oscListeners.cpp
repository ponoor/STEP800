// 
// 
// 

#include "oscListeners.h"
#include "utils.h"

void OSCMsgReceive() {
    bool bMsgHasError = false, bMsgRouted = false;
    OSCMessage msgIN;
    int size;
    if ((size = Udp.parsePacket()) > 0) {
        while (size--)
            msgIN.fill(Udp.read());

        bMsgHasError = msgIN.hasError();
        if (!bMsgHasError) {
            // some possible frequent messages
            bMsgRouted |= msgIN.route("/setTargetPosition", setTargetPosition);
            bMsgRouted |= msgIN.route("/setTargetPositionList", setTargetPositionList);
            bMsgRouted |= msgIN.route("/getPosition", getPosition);
            bMsgRouted |= msgIN.route("/getSpeed", getSpeed);
            bMsgRouted |= msgIN.route("/run", run);
            bMsgRouted |= msgIN.route("/runRaw", runRaw);

            // motion
            bMsgRouted |= msgIN.route("/move", move);
            bMsgRouted |= msgIN.route("/goTo", goTo);
            bMsgRouted |= msgIN.route("/goToDir", goToDir);
            bMsgRouted |= msgIN.route("/goUntil", goUntil);
            bMsgRouted |= msgIN.route("/goUntilRaw", goUntilRaw);
            bMsgRouted |= msgIN.route("/releaseSw", releaseSw);
            bMsgRouted |= msgIN.route("/goHome", goHome);
            bMsgRouted |= msgIN.route("/goMark", goMark);
            bMsgRouted |= msgIN.route("/setMark", setMark);
            bMsgRouted |= msgIN.route("/getMark", getMark);
            bMsgRouted |= msgIN.route("/setPosition", setPosition);
            bMsgRouted |= msgIN.route("/resetPos", resetPos);
            bMsgRouted |= msgIN.route("/resetDev", resetDev);
            bMsgRouted |= msgIN.route("/softStop", softStop);
            bMsgRouted |= msgIN.route("/hardStop", hardStop);
            bMsgRouted |= msgIN.route("/softHiZ", softHiZ);
            bMsgRouted |= msgIN.route("/hardHiZ", hardHiZ);
            bMsgRouted |= msgIN.route("/activate", activate);
            bMsgRouted |= msgIN.route("/free", free);
            bMsgRouted |= msgIN.route("/homing", homing);
            // servo mode
            bMsgRouted |= msgIN.route("/enableServoMode", enableServoMode);
            bMsgRouted |= msgIN.route("/setServoParam", setServoParam);
            bMsgRouted |= msgIN.route("/getServoParam", getServoParam);

            // speed
            bMsgRouted |= msgIN.route("/setSpeedProfile", setSpeedProfile);
            bMsgRouted |= msgIN.route("/setMaxSpeed", setMaxSpeed);
            bMsgRouted |= msgIN.route("/setMinSpeed", setMinSpeed);
            bMsgRouted |= msgIN.route("/getMinSpeed", getMinSpeed);
            bMsgRouted |= msgIN.route("/setFullstepSpeed", setFullstepSpeed);
            bMsgRouted |= msgIN.route("/getFullstepSpeed", getFullstepSpeed);
            bMsgRouted |= msgIN.route("/setAcc", setAcc);
            bMsgRouted |= msgIN.route("/setDec", setDec);
            bMsgRouted |= msgIN.route("/getSpeedProfile", getSpeedProfile);

            // Kval
            bMsgRouted |= msgIN.route("/setKval", setKval);
            bMsgRouted |= msgIN.route("/setAccKval", setAccKval);
            bMsgRouted |= msgIN.route("/setDecKval", setDecKval);
            bMsgRouted |= msgIN.route("/setRunKval", setRunKval);
            bMsgRouted |= msgIN.route("/setHoldKval", setHoldKval);
            bMsgRouted |= msgIN.route("/getKval", getKval);

            //TVAL
            // bMsgRouted |= msgIN.route("/setTval", setTval);
            // bMsgRouted |= msgIN.route("/setAccTval", setAccTval);
            // bMsgRouted |= msgIN.route("/setDecTval", setDecTval);
            // bMsgRouted |= msgIN.route("/setRunTval", setRunTval);
            // bMsgRouted |= msgIN.route("/setHoldTval", setHoldTval);
            // bMsgRouted |= msgIN.route("/getTval", getTval);
            // bMsgRouted |= msgIN.route("/getTval_mA", getTval_mA);

            // config
            bMsgRouted |= msgIN.route("/setDestIp", setDestIp);
            bMsgRouted |= msgIN.route("/getVersion", getVersion);
            bMsgRouted |= msgIN.route("/getConfigName", getConfigName);
            bMsgRouted |= msgIN.route("/getConfigRegister", getConfigRegister);
            bMsgRouted |= msgIN.route("/getStatus", getStatus);
            bMsgRouted |= msgIN.route("/getStatusList", getStatusList);
            bMsgRouted |= msgIN.route("/reportError", reportError);
            bMsgRouted |= msgIN.route("/getHomeSw", getHomeSw);
            bMsgRouted |= msgIN.route("/getBusy", getBusy);
            bMsgRouted |= msgIN.route("/getDir", getDir);
            bMsgRouted |= msgIN.route("/getHiZ", getHiZ);
            bMsgRouted |= msgIN.route("/getUvlo", getUvlo);
            bMsgRouted |= msgIN.route("/getMotorStatus", getMotorStatus);
            bMsgRouted |= msgIN.route("/getThermalStatus", getThermalStatus);
            bMsgRouted |= msgIN.route("/resetMotorDriver", resetMotorDriver);
            bMsgRouted |= msgIN.route("/enableBusyReport", enableBusyReport);
            bMsgRouted |= msgIN.route("/enableHizReport", enableHizReport);
            bMsgRouted |= msgIN.route("/enableHomeSwReport", enableHomeSwReport);
            bMsgRouted |= msgIN.route("/enableDirReport", enableDirReport);
            bMsgRouted |= msgIN.route("/enableMotorStatusReport", enableMotorStatusReport);
            bMsgRouted |= msgIN.route("/enableSwEventReport", enableSwEventReport);
            bMsgRouted |= msgIN.route("/enableUvloReport", enableUvloReport);
            bMsgRouted |= msgIN.route("/enableThermalStatusReport", enableThermalStatusReport);
            bMsgRouted |= msgIN.route("/enableOverCurrentReport", enableOverCurrentReport);
            bMsgRouted |= msgIN.route("/enableStallReport", enableStallReport);
            // bMsgRouted |= msgIN.route("/getLimitSw", getLimitSw);
            // bMsgRouted |= msgIN.route("/getLimitSwMode", getLimitSwMode);
            // bMsgRouted |= msgIN.route("/setLimitSwMode", setLimitSwMode);
            //bMsgRouted |= msgIN.route("/enableLimitSwReport", enableLimitSwReport);
            bMsgRouted |= msgIN.route("/enableElectromagnetBrake", enableElectromagnetBrake);
            bMsgRouted |= msgIN.route("/setBrakeTransitionDuration", setBrakeTransitionDuration);
            bMsgRouted |= msgIN.route("/getBrakeTransitionDuration", getBrakeTransitionDuration);
            bMsgRouted |= msgIN.route("/setMicrostepMode", setMicrostepMode);
            bMsgRouted |= msgIN.route("/getMicrostepMode", getMicrostepMode);
            bMsgRouted |= msgIN.route("/getHomeSwMode", getHomeSwMode);
            bMsgRouted |= msgIN.route("/setHomeSwMode", setHomeSwMode);
            bMsgRouted |= msgIN.route("/setStallThreshold", setStallThreshold);
            bMsgRouted |= msgIN.route("/getStallThreshold", getStallThreshold);
            bMsgRouted |= msgIN.route("/setOverCurrentThreshold", setOverCurrentThreshold);
            bMsgRouted |= msgIN.route("/getOverCurrentThreshold", getOverCurrentThreshold);
            bMsgRouted |= msgIN.route("/enableLowSpeedOptimize", enableLowSpeedOptimize);
            bMsgRouted |= msgIN.route("/setLowSpeedOptimizeThreshold", setLowSpeedOptimizeThreshold);
            bMsgRouted |= msgIN.route("/getLowSpeedOptimizeThreshold", getLowSpeedOptimizeThreshold);

            bMsgRouted |= msgIN.route("/setSpeedProfileRaw", setSpeedProfileRaw);
            bMsgRouted |= msgIN.route("/setMaxSpeedRaw", setMaxSpeedRaw);
            bMsgRouted |= msgIN.route("/setMinSpeedRaw", setMinSpeedRaw);
            bMsgRouted |= msgIN.route("/setFullstepSpeedRaw", setFullstepSpeedRaw);
            bMsgRouted |= msgIN.route("/setAccRaw", setAccRaw);
            bMsgRouted |= msgIN.route("/setDecRaw", setDecRaw);
            bMsgRouted |= msgIN.route("/getSpeedProfileRaw", getSpeedProfileRaw);

            // bMsgRouted |= msgIN.route("/setVoltageMode", setVoltageMode);
            // bMsgRouted |= msgIN.route("/setCurrentMode", setCurrentMode);
            bMsgRouted |= msgIN.route("/setBemfParam", setBemfParam);
            bMsgRouted |= msgIN.route("/getBemfParam", getBemfParam);
            // bMsgRouted |= msgIN.route("/setDecayModeParam", setDecayModeParam);
            // bMsgRouted |= msgIN.route("/getDecayModeParam", getDecayModeParam);
            // bMsgRouted |= msgIN.route("/getAdcVal", getAdcVal);
            bMsgRouted |= msgIN.route("/setGoUntilTimeout", setGoUntilTimeout);
            bMsgRouted |= msgIN.route("/getGoUntilTimeout", getGoUntilTimeout);
            bMsgRouted |= msgIN.route("/setReleaseSwTimeout", setReleaseSwTimeout);
            bMsgRouted |= msgIN.route("/getReleaseSwTimeout", getReleaseSwTimeout);
            bMsgRouted |= msgIN.route("/setHomingDirection", setHomingDirection);
            bMsgRouted |= msgIN.route("/getHomingDirection", getHomingDirection);
            bMsgRouted |= msgIN.route("/setHomingSpeed", setHomingSpeed);
            bMsgRouted |= msgIN.route("/getHomingSpeed", getHomingSpeed);
            bMsgRouted |= msgIN.route("/getHomingStatus", getHomingStatus);
            bMsgRouted |= msgIN.route("/setProhibitMotionOnHomeSw", setProhibitMotionOnHomeSw);
            bMsgRouted |= msgIN.route("/getProhibitMotionOnHomeSw", getProhibitMotionOnHomeSw);
            // bMsgRouted |= msgIN.route("/setProhibitMotionOnLimitSw", setProhibitMotionOnLimitSw);
            // bMsgRouted |= msgIN.route("/getProhibitMotionOnLimitSw", getProhibitMotionOnLimitSw);
            bMsgRouted |= msgIN.route("/getElPos", getElPos);
            bMsgRouted |= msgIN.route("/setElPos", setElPos);
            turnOnRXL();
            if ((!bMsgRouted) && reportErrors) {
                sendOneDatum("/error/osc", "MessageNotMatch");
            }
        }
        else if (reportErrors) {
            sendOneDatum("/error/osc", "OscSyntaxError");
        }
    }
}

bool isCorrectMotorId(uint8_t motorID) {
    bool bCorrectId = (MOTOR_ID_FIRST <= motorID) && (motorID <= MOTOR_ID_LAST);
    if ((!bCorrectId) && (motorID != MOTOR_ID_ALL)) {
        sendCommandError(motorID, ERROR_MOTORID_NOTMATCH);
    }
    return bCorrectId;
}

bool checkGoToDirection(uint8_t motorId, int32_t targetPos) {
    int32_t diff = stepper[motorId].getPos() - targetPos;
    bool dir = diff > 0;
    bool bLongPath = ((uint32_t)abs(diff))>>11 > 0;
    if (bLongPath) {
        dir = !dir;
    }
    return dir;
}

#pragma region config_commands_osc_listener
void setDestIp(OSCMessage& msg, int addrOffset) {
    bool bIpUpdated = false;
    OSCMessage newMes("/destIp");
    for (auto i = 0; i < 4; i++)
    {
        bIpUpdated |= (destIp[i] != Udp.remoteIP()[i]);
        newMes.add(Udp.remoteIP()[i]);
    }
    destIp = Udp.remoteIP();
    newMes.add(bIpUpdated);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    isDestIpSet = true;
    turnOnTXL();
}

void getVersion(OSCMessage& msg, int addrOffset) {
    String version = String(firmwareName) + String(" ") 
    + String(firmwareVersion[0]) + String(".")
    + String(firmwareVersion[1]) + String(".")
    + String(firmwareVersion[2]) + String(" ")
    + String(COMPILE_DATE) + String(" ")
    + String(COMPILE_TIME);
    sendOneDatum("/version", version.c_str());
}

void getConfigName(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/configName");
    newMes.add(configName.c_str()).add(sdInitializeSucceeded).add(configFileOpenSucceeded).add(configFileParseSucceeded);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void getConfigRegister(uint8_t deviceId) {
    sendTwoData("/configRegister", deviceId + MOTOR_ID_FIRST, stepper[deviceId].getParam(CONFIG));
}
void getConfigRegister(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        getConfigRegister(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getConfigRegister(i);
        }
    }
}

// reset the motor driver chip and setup it
void resetMotorDriver(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        resetMotorDriver(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            resetMotorDriver(i + MOTOR_ID_FIRST);
        }
    }
}

// void getAdcVal(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     if(isCorrectMotorId(motorID)) {
//         sendTwoData("/adcVal", motorID, stepper[motorID - MOTOR_ID_FIRST].getParam(ADC_OUT));
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             sendTwoData("/adcVal", i + MOTOR_ID_FIRST, stepper[i].getParam(ADC_OUT));
//         }
//     }
// }

// simply send reset command to the driverchip via SPI
void resetDev(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].hardHiZ();
        stepper[motorID].resetDev();
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].hardHiZ();
            stepper[i].resetDev();
        }
    }
}

void reportError(OSCMessage& msg, int addrOffset) {
    reportErrors = getBool(msg, 0);
}

void enableBusyReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportBUSY[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportBUSY[i] = bEnable;
        }
    }
}

void enableHizReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportHiZ[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportHiZ[i] = bEnable;
        }
    }
}
void enableHomeSwReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportHomeSwStatus[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportHomeSwStatus[i] = bEnable;
        }
    }
}
// void enableLimitSwReport(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     bool bEnable = getBool(msg, 1);
//     if(isCorrectMotorId(motorID)) {
//         reportLimitSwStatus[motorID - MOTOR_ID_FIRST] = bEnable;
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             reportLimitSwStatus[i] = bEnable;
//         }
//     }
// }
void enableDirReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportDir[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportDir[i] = bEnable;
        }
    }
}
void enableMotorStatusReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportMotorStatus[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportMotorStatus[i] = bEnable;
        }
    }
}
void enableSwEventReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportSwEvn[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportSwEvn[i] = bEnable;
        }
    }
}
void enableUvloReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportUVLO[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportUVLO[i] = bEnable;
        }
    }
}
void enableThermalStatusReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportThermalStatus[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportThermalStatus[i] = bEnable;
        }
    }
}
void enableOverCurrentReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportOCD[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportOCD[i] = bEnable;
        }
    }
}
void enableStallReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportStall[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportStall[i] = bEnable;
        }
    }
}

void getHomeSw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= motorID;
        getHomeSw(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getHomeSw(i);
        }
    }
}
void getHomeSw(uint8_t motorId) {
    sendThreeInt("/homeSw", motorId + MOTOR_ID_FIRST, homeSwState[motorId], dir[motorId]);
}
// void getLimitSw(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     if(isCorrectMotorId(motorID)) {
//         motorID -= MOTOR_ID_FIRST;
//         getLimitSw(motorID);
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             getLimitSw(i);
//         }
//     }
// }
// void getLimitSw(uint8_t motorId) {
//     sendThreeInt("limitSw", motorId + MOTOR_ID_FIRST, limitSwState[motorId], dir[motorId]);
// }

void getBusy(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/busy", motorID, busy[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/busy", i + MOTOR_ID_FIRST, busy[i]);
        }
    }
}
void getDir(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/dir", motorID, dir[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/dir", i + MOTOR_ID_FIRST, HiZ[i]);
        }
    }
}
void getHiZ(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/HiZ", motorID, HiZ[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/HiZ", i + MOTOR_ID_FIRST, HiZ[i]);
        }
    }
}
void getUvlo(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/uvlo", motorID, uvloStatus[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/uvlo", i + 1, uvloStatus[i]);
        }
    }
}

void getMotorStatus(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/motorStatus", motorID, motorStatus[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/motorStatus", i + 1, motorStatus[i]);
        }
    }
}

void getThermalStatus(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/thermalStatus", motorID, thermalStatus[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/thermalStatus", i + 1, thermalStatus[i]);
        }
    }
}

void getStatus(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/status", motorID, stepper[motorID - MOTOR_ID_FIRST].getStatus());
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/status", i + MOTOR_ID_FIRST, stepper[i].getStatus());
        }
    }
}

void getStatusList(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/statusList");
    for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
        newMes.add((int32_t)stepper[i].getStatus());
    }

    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void setMicrostepMode(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t value = getInt(msg, 1);
    value = constrain(value, STEP_FS, STEP_FS_128); // 0-7
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].configStepMode(value);
        microStepMode[motorID - MOTOR_ID_FIRST] = value;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].configStepMode(value);
            microStepMode[i] = value;
        }
    }
}

void getMicrostepMode(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/microstepMode", motorID, stepper[motorID - MOTOR_ID_FIRST].getStepMode());
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/microstepMode", i + MOTOR_ID_FIRST, stepper[i].getStepMode());
        }
    }
}

void getHomeSwMode(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/homeSwMode", motorID, stepper[motorID - MOTOR_ID_FIRST].getSwitchMode() > 0);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/homeSwMode", i + MOTOR_ID_FIRST, stepper[i].getSwitchMode() > 0);
        }
    }
}

void setHomeSwMode(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t value = (getBool(msg, 1)) ? SW_USER : SW_HARD_STOP;
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setSwitchMode(value);
        homeSwMode[motorID - MOTOR_ID_FIRST] = (value > 0);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setSwitchMode(value);
            homeSwMode[i] = (value > 0);
        }
    }
}
// void getLimitSwMode(OSCMessage& msg, int addrOffset) {
//     if (!isDestIpSet) { return; }
//     uint8_t motorID = getInt(msg, 0);
//     if(isCorrectMotorId(motorID)) {
//         sendTwoData("/limitSwMode", motorID, limitSwMode[motorID - MOTOR_ID_FIRST]);
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             sendTwoData("/limitSwMode", i + MOTOR_ID_FIRST, limitSwMode[i] > 0);
//         }
//     }
// }

// void setLimitSwMode(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     uint16_t switchMode = (getBool(msg, 1)) ? SW_USER : SW_HARD_STOP;
//     if(isCorrectMotorId(motorID)) {
//         limitSwMode[motorID - MOTOR_ID_FIRST] = switchMode > 0;
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             limitSwMode[i] = switchMode > 0;
//         }
//     }
// }

void getHomingStatus(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        sendTwoData("/homingStatus", motorID + MOTOR_ID_FIRST, homingStatus[motorID]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/homingStatus", i + MOTOR_ID_FIRST, homingStatus[i]);
        }
    }
}

// STALL_TH register is 5bit in PowerSTEP01, 7bit in L6470
void setStallThreshold(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    #ifdef L6470 
    uint8_t threshold = getInt(msg, 1) & 0x7F; // 7bit
    #else
    uint8_t threshold = getInt(msg, 1) & 0x1F; // 5bit
    #endif
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].setParam(STALL_TH, threshold);
        getStallThreshold(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setParam(STALL_TH, threshold);
            getStallThreshold(i);
        }
    }

}
void getStallThreshold(uint8_t motorId) {
    if (!isDestIpSet) { return; }
    #ifdef L6470
    uint8_t stall_th_raw = stepper[motorId].getParam(STALL_TH) & 0x7F;
    float threshold = (stall_th_raw + 1) * 31.25f;
    # else
    uint8_t stall_th_raw = stepper[motorId].getParam(STALL_TH) & 0x1F;
    float threshold = (stall_th_raw + 1) * 312.5f;
    #endif
    sendTwoData("/stallThreshold", motorId + MOTOR_ID_FIRST, threshold);
}
void getStallThreshold(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        getStallThreshold(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getStallThreshold(i);
        }
    }
}
// OCD_TH register is 5bit in PowerSTEP01, 4bit in L6470
void setOverCurrentThreshold(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    #ifdef L6470
    uint8_t threshold = getInt(msg, 1) & 0xF; // 4bit
    #else
    uint8_t threshold = getInt(msg, 1) & 0x1F; // 5bit
    #endif
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setParam(OCD_TH, threshold);
        getOverCurrentThreshold(motorID);
        overCurrentThreshold[motorID - MOTOR_ID_FIRST] = threshold;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setParam(OCD_TH, threshold);
            overCurrentThreshold[i] = threshold;
            getOverCurrentThreshold(i + MOTOR_ID_FIRST);
        }
    }
}
void getOverCurrentThreshold(uint8_t motorID) {
    if (!isDestIpSet) { return; }
    #ifdef L6470
    uint8_t ocd_th_raw = stepper[motorID - MOTOR_ID_FIRST].getParam(OCD_TH) & 0xF;
    float threshold = (ocd_th_raw + 1) * 375.0f;
    #else
    uint8_t ocd_th_raw = stepper[motorID - MOTOR_ID_FIRST].getParam(OCD_TH) & 0x1F;
    float threshold = (ocd_th_raw + 1) * 312.5f;
    #endif
    sendTwoData("/overCurrentThreshold", motorID, threshold);
}
void getOverCurrentThreshold(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getOverCurrentThreshold(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getOverCurrentThreshold(i + MOTOR_ID_FIRST);
        }
    }
}

void setLowSpeedOptimizeThreshold(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _lowSpdOptThreshold = getFloat(msg,1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        lowSpeedOptimizeThreshold[motorID] = _lowSpdOptThreshold;
        if (lowSpeedOptimizeEnable[motorID])
            stepper[motorID].setMinSpeed(_lowSpdOptThreshold);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            lowSpeedOptimizeThreshold[i] = _lowSpdOptThreshold;
            if (lowSpeedOptimizeEnable[i])
                stepper[i].setMinSpeed(_lowSpdOptThreshold);
        }
    }
}
void getLowSpeedOptimizeThreshold(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        getLowSpeedOptimizeThreshold(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getLowSpeedOptimizeThreshold(i);
        }
    }
}
void getLowSpeedOptimizeThreshold(uint8_t motorId) {
    if (!isDestIpSet) { return; }
    bool optimizationEnabled = (stepper[motorId].getParam(MIN_SPEED) & (1 << 12)) > 0;
    OSCMessage newMes("/lowSpeedOptimizeThreshold");
    newMes.add((int32_t)motorId + MOTOR_ID_FIRST);
    newMes.add(lowSpeedOptimizeEnable[motorId]);
    newMes.add(optimizationEnabled);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void enableLowSpeedOptimize(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool state = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].setLoSpdOpt(state);
        lowSpeedOptimizeEnable[motorID] = state;
        if (state) {
            stepper[motorID].setMinSpeed(lowSpeedOptimizeThreshold[motorID]);
        } else {
            stepper[motorID].setMinSpeed(minSpeed[motorID]);
        }
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setLoSpdOpt(state);
            lowSpeedOptimizeEnable[i] = state;
            if (state) {
                stepper[i].setMinSpeed(lowSpeedOptimizeThreshold[i]);
            } else {
                stepper[i].setMinSpeed(minSpeed[i]);
            }
        }
    }
}

void setBemfParam(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t intSpeed = constrain(getInt(msg, 1), 0, 0x3FFF);
    uint8_t
        stSlp = constrain(getInt(msg, 2), 0, 255),
        fnSlpAcc = constrain(getInt(msg, 3), 0, 255),
        fnSlpDec = constrain(getInt(msg, 4), 0, 255);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        intersectSpeed[motorID] = intSpeed;
        startSlope[motorID] = stSlp;
        accFinalSlope[motorID] = fnSlpAcc;
        decFinalSlope[motorID] = fnSlpDec;
        stepper[motorID].setParam(INT_SPD, intersectSpeed[motorID]);
        stepper[motorID].setParam(ST_SLP, startSlope[motorID]);
        stepper[motorID].setParam(FN_SLP_ACC, accFinalSlope[motorID]);
        stepper[motorID].setParam(FN_SLP_DEC, decFinalSlope[motorID]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            intersectSpeed[i] = intSpeed;
            startSlope[i] = stSlp;
            accFinalSlope[i] = fnSlpAcc;
            decFinalSlope[i] = fnSlpDec;
            stepper[i].setParam(INT_SPD, intersectSpeed[i]);
            stepper[i].setParam(ST_SLP, startSlope[i]);
            stepper[i].setParam(FN_SLP_ACC, accFinalSlope[i]);
            stepper[i].setParam(FN_SLP_DEC, decFinalSlope[i]);
        }
    }
}
void getBemfParam(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        getBemfParam(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getBemfParam(i);
        }
    }
}
void getBemfParam(uint8_t motorId) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/bemfParam");
    newMes.add((int32_t)motorId+MOTOR_ID_FIRST);
    newMes.add(intersectSpeed[motorId]).add(startSlope[motorId]).add(accFinalSlope[motorId]).add(decFinalSlope[motorId]);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

#ifdef POWERSTEP01
void setDecayModeParam(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t
        tFast = constrain(getInt(msg, 1), 0, 255),
        tOnMin = constrain(getInt(msg, 2), 0, 255),
        tOffMin = constrain(getInt(msg, 3), 0, 255);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        fastDecaySetting[motorID] = tFast;
        minOnTime[motorID] = tOnMin;
        minOffTime[motorID] = tOffMin;
        stepper[motorID].setParam(T_FAST, fastDecaySetting[motorID]);
        stepper[motorID].setParam(TON_MIN, minOnTime[motorID]);
        stepper[motorID].setParam(TOFF_MIN, minOffTime[motorID]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            fastDecaySetting[i] = tFast;
            minOnTime[i] = tOnMin;
            minOffTime[i] = tOffMin;
            stepper[i].setParam(T_FAST, fastDecaySetting[i]);
            stepper[i].setParam(TON_MIN, minOnTime[i]);
            stepper[i].setParam(TOFF_MIN, minOffTime[i]);
        }
    }
}
void getDecayModeParam(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        getDecayModeParam(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getDecayModeParam(i);
        }
    }
}
void getDecayModeParam(uint8_t motorId) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/decayModeParam");
    newMes.add((int32_t)motorId+MOTOR_ID_FIRST);
    newMes.add(fastDecaySetting[motorId]).add(minOnTime[motorId]).add(minOffTime[motorId]);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}
#endif

void enableElectromagnetBrake(uint8_t motorId, bool bEnable) {
    electromagnetBrakeEnable[motorId] = bEnable;
    if (bEnable) {
        //pinMode(brakePin[motorId], OUTPUT);
    } else {
        setBrake(motorId, false);
    }
}
void enableElectromagnetBrake(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        enableElectromagnetBrake(motorID, bEnable);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            enableElectromagnetBrake(i, bEnable);
        }
    }

}

void setBrakeTransitionDuration(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t duration = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        brakeTransitionDuration[motorID] = duration;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            brakeTransitionDuration[i] = duration;
        }
    }
}

void getBrakeTransitionDuration(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        sendTwoData("/brakeTransitionDuration", motorID + MOTOR_ID_FIRST, brakeTransitionDuration[motorID]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/brakeTransitionDuration", i + MOTOR_ID_FIRST, brakeTransitionDuration[i]);
        }
    }
}

void setGoUntilTimeout(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t timeout = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        goUntilTimeout[motorID] = timeout;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            goUntilTimeout[i] = timeout;
        }
    }
}
void getGoUntilTimeout(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/goUntilTimeout", motorID, goUntilTimeout[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/goUntilTimeout", i + MOTOR_ID_FIRST, goUntilTimeout[i]);
        }
    }
}
void setReleaseSwTimeout(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t timeout = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        releaseSwTimeout[motorID] = timeout;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            releaseSwTimeout[i] = timeout;
        }
    }
}
void getReleaseSwTimeout(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/releaseSwTimeout", motorID, releaseSwTimeout[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/releaseSwTimeout", i + MOTOR_ID_FIRST, releaseSwTimeout[i]);
        }
    }
}

void setHomingDirection(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool dir = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        homingDirection[motorID] = dir;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            homingDirection[i] = dir;
        }
    }
}
void getHomingDirection(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/homingDirection", motorID, homingDirection[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/homingDirection", i + MOTOR_ID_FIRST, homingDirection[i]);
        }
    }
}

void setHomingSpeed(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float spd = getFloat(msg, 1);
    spd = constrain(spd, 0.0, 15610.0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        homingSpeed[motorID] = spd;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            homingSpeed[i] = spd;
        }
    }
}
void getHomingSpeed(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/homingSpeed", motorID, homingSpeed[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/homingSpeed", i + MOTOR_ID_FIRST, homingSpeed[i]);
        }
    }
}

void setProhibitMotionOnHomeSw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool dir = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        bProhibitMotionOnHomeSw[motorID] = dir;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            bProhibitMotionOnHomeSw[i] = dir;
        }
    }
}
void getProhibitMotionOnHomeSw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/prohibitMotionOnHomeSw", motorID, bProhibitMotionOnHomeSw[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/prohibitMotionOnHomeSw", i + MOTOR_ID_FIRST, bProhibitMotionOnHomeSw[i]);
        }
    }
}
// void setProhibitMotionOnLimitSw(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     bool dir = getBool(msg, 1);
//     if(isCorrectMotorId(motorID)) {
//         motorID -= MOTOR_ID_FIRST;
//         bProhibitMotionOnLimitSw[motorID] = dir;
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             bProhibitMotionOnLimitSw[i] = dir;
//         }
//     }
// }
// void getProhibitMotionOnLimitSw(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     if(isCorrectMotorId(motorID)) {
//         sendTwoData("/prohibitMotionOnLimitSw", motorID, bProhibitMotionOnLimitSw[motorID - MOTOR_ID_FIRST]);
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             sendTwoData("/prohibitMotionOnLimitSw", i + MOTOR_ID_FIRST, bProhibitMotionOnLimitSw[i]);
//         }
//     }
// }

#pragma endregion config_commands_osc_listener

#pragma region kval_commands_osc_listener

void setKval(uint8_t motorId, uint8_t hold, uint8_t run, uint8_t acc, uint8_t dec) {
    // if (!isCurrentMode[motorId]) 
    {
        stepper[motorId].setHoldKVAL(hold);
        stepper[motorId].setRunKVAL(run);
        stepper[motorId].setAccKVAL(acc);
        stepper[motorId].setDecKVAL(dec);
    }
    kvalHold[motorId] = hold;
    kvalRun[motorId] = run;
    kvalAcc[motorId] = acc;
    kvalDec[motorId] = dec;
}

void setKval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int hold = getInt(msg, 1);
    hold = constrain(hold, 0, 255);
    int run = getInt(msg, 2);
    run = constrain(run, 0, 255);
    int acc = getInt(msg, 3);
    acc = constrain(acc, 0, 255);
    int dec = getInt(msg, 4);
    dec = constrain(dec, 0, 255);
    if (isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        setKval(motorID, hold, run, acc, dec);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            setKval(i, hold, run, acc, dec);
        }
    }
}

void setHoldKval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t kvalInput = constrain(getInt(msg, 1), 0, 255);
    if(isCorrectMotorId(motorID)) {
        // if (!isCurrentMode[motorID]) 
        {
            stepper[motorID - MOTOR_ID_FIRST].setHoldKVAL(kvalInput);
        }
        kvalHold[motorID - MOTOR_ID_FIRST] = kvalInput;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            // if (!isCurrentMode[i]) 
            {
                stepper[i].setHoldKVAL(kvalInput);
            }
            kvalHold[i] = kvalInput;
        }
    }
}
void setRunKval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t kvalInput = constrain(getInt(msg, 1), 0, 255);

    if(isCorrectMotorId(motorID)) {
        // if (!isCurrentMode[motorID]) 
        {
            stepper[motorID - MOTOR_ID_FIRST].setRunKVAL(kvalInput);
        }
        kvalRun[motorID - MOTOR_ID_FIRST] = kvalInput;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            // if (!isCurrentMode[i]) 
            {
                stepper[i].setRunKVAL(kvalInput);
            }
            kvalRun[i] = kvalInput;
        }
    }
}
void setAccKval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t kvalInput = constrain(getInt(msg, 1), 0, 255);
    if(isCorrectMotorId(motorID)) {
        // if (!isCurrentMode[motorID]) 
        {
            stepper[motorID - MOTOR_ID_FIRST].setAccKVAL(kvalInput);
        }
        kvalAcc[motorID - MOTOR_ID_FIRST] = kvalInput;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            // if (!isCurrentMode[i]) 
            {
                stepper[i].setAccKVAL(kvalInput);
            }
            kvalAcc[i] = kvalInput;
        }
    }
}
void setDecKval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t kvalInput = constrain(getInt(msg, 1), 0, 255);
    if(isCorrectMotorId(motorID)) {
        // if (!isCurrentMode[motorID]) 
        {
            stepper[motorID - MOTOR_ID_FIRST].setDecKVAL(kvalInput);
        }
        kvalDec[motorID - MOTOR_ID_FIRST] = kvalInput;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            // if (!isCurrentMode[i]) 
            {
                stepper[i].setDecKVAL(kvalInput);
            }
            kvalDec[i] = kvalInput;
        }
    }
}

void getKval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getKval(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getKval(i + MOTOR_ID_FIRST);
        }
    }
}
void getKval(uint8_t motorID) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/kval");
    newMes.add((int32_t)motorID);
    motorID -= MOTOR_ID_FIRST;
    newMes.add(kvalHold[motorID]).add(kvalRun[motorID]).add(kvalAcc[motorID]).add(kvalDec[motorID]);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}
#pragma endregion kval_commands_osc_listener

// #pragma region tval_commands_osc_listener
// void setTval(uint8_t motorId, uint8_t hold, uint8_t run, uint8_t acc, uint8_t dec) {
//     if (isCurrentMode[motorId]) {
//         stepper[motorId].setHoldTVAL(hold);
//         stepper[motorId].setRunTVAL(run);
//         stepper[motorId].setAccTVAL(acc);
//         stepper[motorId].setDecTVAL(dec);
//     }
//     tvalHold[motorId] = hold;
//     tvalRun[motorId] = run;
//     tvalAcc[motorId] = acc;
//     tvalDec[motorId] = dec;
// }
// void setTval(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     int hold = constrain(getInt(msg, 1), 0, TVAL_LIMIT_VAL);
//     int run = constrain(getInt(msg, 2), 0, TVAL_LIMIT_VAL);
//     int acc = constrain(getInt(msg, 3), 0, TVAL_LIMIT_VAL);
//     int dec = constrain(getInt(msg, 4), 0, TVAL_LIMIT_VAL);
//     if(isCorrectMotorId(motorID)) {
//         motorID -= MOTOR_ID_FIRST;
//         setTval(motorID, hold, run, acc, dec);
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             setTval(i, hold, run, acc, dec);
//         }
//     }
// }

// void setHoldTval(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     uint8_t tvalInput = constrain(getInt(msg, 1), 0, TVAL_LIMIT_VAL);
//     if(isCorrectMotorId(motorID)) {
//         motorID -= MOTOR_ID_FIRST;
//         if (isCurrentMode[motorID]) {
//             stepper[motorID].setHoldTVAL(tvalInput);
//         }
//         tvalHold[motorID] = tvalInput;
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             if (isCurrentMode[i]) {
//                 stepper[i].setHoldTVAL(tvalInput);
//             }
//             tvalHold[i] = tvalInput;
//         }
//     }
// }
// void setRunTval(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     uint8_t tvalInput = constrain(getInt(msg, 1), 0, TVAL_LIMIT_VAL);

//     if(isCorrectMotorId(motorID)) {
//         motorID -= MOTOR_ID_FIRST;
//         if (isCurrentMode[motorID]) {
//             stepper[motorID].setRunTVAL(tvalInput);
//         }
//         tvalRun[motorID] = tvalInput;
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             if (isCurrentMode[i]) {
//                 stepper[i].setRunTVAL(tvalInput);
//             }
//             tvalRun[i] = tvalInput;
//         }
//     }
// }
// void setAccTval(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     uint8_t tvalInput = constrain(getInt(msg, 1), 0, TVAL_LIMIT_VAL);
//     if(isCorrectMotorId(motorID)) {
//         motorID -= MOTOR_ID_FIRST;
//         if (isCurrentMode[motorID]) {
//             stepper[motorID].setAccTVAL(tvalInput);
//         }
//         tvalAcc[motorID] = tvalInput;
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             if (isCurrentMode[i]) {
//                 stepper[i].setAccTVAL(tvalInput);
//             }
//             tvalAcc[i] = tvalInput;
//         }
//     }
// }
// void setDecTval(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     uint8_t tvalInput = constrain(getInt(msg, 1), 0, TVAL_LIMIT_VAL);
//     if(isCorrectMotorId(motorID)) {
//         motorID -= MOTOR_ID_FIRST;
//         if (isCurrentMode[motorID]) {
//             stepper[motorID].setDecTVAL(tvalInput);
//         }
//         tvalDec[motorID] = tvalInput;
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             if (isCurrentMode[i]) {
//                 stepper[i].setDecTVAL(tvalInput);
//             }
//             tvalDec[i] = tvalInput;
//         }
//     }
// }

// void getTval(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     if(isCorrectMotorId(motorID)) {
//         getTval(motorID);
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             getTval(i + MOTOR_ID_FIRST);
//         }
//     }
// }
// void getTval(uint8_t motorID) {
//     if (!isDestIpSet) { return; }
//     OSCMessage newMes("/tval");
//     newMes.add((int32_t)motorID);
//     motorID -= MOTOR_ID_FIRST;
//     newMes.add(tvalHold[motorID]).add(tvalRun[motorID]).add(tvalAcc[motorID]).add(tvalDec[motorID]);
//     Udp.beginPacket(destIp, outPort);
//     newMes.send(Udp);
//     Udp.endPacket();
//     newMes.empty();
//     turnOnTXL();
// }
// float TvalToCurrent(uint8_t tval) {
//     return (tval + 1) * 78.125f;
// }
// void getTval_mA(uint8_t motorId) {
//     if (!isDestIpSet) { return; }
//     OSCMessage newMes("/tval_mA");
//     newMes.add((int32_t)motorId+MOTOR_ID_FIRST);
//     newMes.add(TvalToCurrent(tvalHold[motorId]));
//     newMes.add(TvalToCurrent(tvalRun[motorId]));
//     newMes.add(TvalToCurrent(tvalAcc[motorId]));
//     newMes.add(TvalToCurrent(tvalDec[motorId]));
//     Udp.beginPacket(destIp, outPort);
//     newMes.send(Udp);
//     Udp.endPacket();
//     newMes.empty();
//     turnOnTXL();
// }
// void getTval_mA(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     if(isCorrectMotorId(motorID)) {
//         motorID -= MOTOR_ID_FIRST;
//         getTval_mA(motorID);
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             getTval_mA(i);
//         }
//     }
// }
// #pragma endregion tval_commands_osc_listener

#pragma region speed_commands_osc_listener

void setSpeedProfile(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _acc = getFloat(msg, 1);
    float _dec = getFloat(msg, 2);
    float _maxSpeed = getFloat(msg, 3);

    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].setAcc(_acc);
        stepper[motorID].setDec(_dec);
        stepper[motorID].setMaxSpeed(_maxSpeed);
        acc[motorID] = _acc;
        dec[motorID] = _dec;
        maxSpeed[motorID] = _maxSpeed;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setAcc(_acc);
            stepper[i].setDec(_dec);
            stepper[i].setMaxSpeed(_maxSpeed);
            acc[i] = _acc;
            dec[i] = _dec;
            maxSpeed[i] = _maxSpeed;
        }
    }
}

void setMaxSpeed(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _maxSpeed = getFloat(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].setMaxSpeed(_maxSpeed);
        maxSpeed[motorID] = _maxSpeed;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setMaxSpeed(_maxSpeed);
            maxSpeed[i] = _maxSpeed;
        }
    }
}

void setMinSpeed(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _minSpeed = getFloat(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        minSpeed[motorID] = _minSpeed;
        if (!lowSpeedOptimizeEnable[motorID]) {
            stepper[motorID].setMinSpeed(_minSpeed);
        }
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            minSpeed[i] = _minSpeed;
            if (!lowSpeedOptimizeEnable[motorID]) {
                stepper[i].setMinSpeed(_minSpeed);
            }
        }
    }  
}

void getMinSpeed(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/minSpeed", motorID, minSpeed[motorID-MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/minSpeed", i + 1, minSpeed[i]);
        }
    }
}

void setFullstepSpeed(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _fullStepSpeed = getFloat(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].setFullSpeed(_fullStepSpeed);
        fullStepSpeed[motorID] = _fullStepSpeed;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setFullSpeed(_fullStepSpeed);
            fullStepSpeed[i] = _fullStepSpeed;
        }
    }
}
void getFullstepSpeed(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _fullStepSpeed;
    if(isCorrectMotorId(motorID)) {
        _fullStepSpeed = stepper[motorID - MOTOR_ID_FIRST].getFullSpeed();
        sendTwoData("/fullstepSpeed", motorID, _fullStepSpeed);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            _fullStepSpeed = stepper[i].getFullSpeed();
            sendTwoData("/fullstepSpeed", i + 1, _fullStepSpeed);
        }
    }
}
void setAcc(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _acc = getFloat(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].setAcc(_acc);
        acc[motorID] = _acc;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setAcc(_acc);
            acc[i] = _acc;
        }
    }
}
void setDec(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _dec = getFloat(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].setDec(_dec);
        dec[motorID] = _dec;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setDec(_dec);
            dec[i] = _dec;
        }
    }
}

void setSpeedProfileRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t _accRaw = getInt(msg, 1);
    uint16_t _decRaw = getInt(msg, 2);
    uint16_t _maxSpeedRaw = getInt(msg, 3);

    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setAccRaw(_accRaw);
        stepper[motorID - MOTOR_ID_FIRST].setDecRaw(_decRaw);
        stepper[motorID - MOTOR_ID_FIRST].setMaxSpeedRaw(_maxSpeedRaw);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setAccRaw(_accRaw);
            stepper[i].setDecRaw(_decRaw);
            stepper[i].setMaxSpeedRaw(_maxSpeedRaw);
        }
    }
}

void setMaxSpeedRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t t = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setMaxSpeedRaw(t);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setMaxSpeedRaw(t);
        }
    }
}
void setMinSpeedRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t t = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setMinSpeedRaw(t);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setMinSpeedRaw(t);
        }
    }
}

void setFullstepSpeedRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t t = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setFullSpeedRaw(t);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setFullSpeedRaw(t);
        }
    }
}

void setAccRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t t = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setAccRaw(t);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setAccRaw(t);
        }
    }
}
void setDecRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t t = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setDecRaw(t);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setDecRaw(t);
        }
    }
}

void getSpeed(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float s;
    if(isCorrectMotorId(motorID)) {
        s = stepper[motorID - MOTOR_ID_FIRST].getSpeed();
        if (dir[motorID - MOTOR_ID_FIRST] == REV) { s *= -1.0; }
        sendTwoData("/speed", motorID, s);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            s = stepper[i].getSpeed();
            if (dir[i] == REV) { s *= -1.0; }
            sendTwoData("/speed", i + MOTOR_ID_FIRST, s);
        }
    }
}

void getSpeedProfile(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        getSpeedProfile(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getSpeedProfile(i);
        }
    }
}
void getSpeedProfile(uint8_t motorId) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/speedProfile");
    newMes.add((int32_t)motorId+MOTOR_ID_FIRST);
    newMes.add((float)stepper[motorId].getAcc());
    newMes.add((float)stepper[motorId].getDec());
    newMes.add((float)stepper[motorId].getMaxSpeed());
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void getSpeedProfileRaw(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        getSpeedProfileRaw(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getSpeedProfileRaw(i);
        }
    }
}
void getSpeedProfileRaw(uint8_t motorId) {
    OSCMessage newMes("/speedProfileRaw");
    newMes.add((int32_t)motorId+MOTOR_ID_FIRST);
    newMes.add((int32_t)stepper[motorId].getAccRaw());
    newMes.add((int32_t)stepper[motorId].getDecRaw());
    newMes.add((int32_t)stepper[motorId].getMaxSpeedRaw());
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}
#pragma endregion speed_commands_osc_listener

#pragma region operational_commands_osc_listener

void getPosition(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/position", motorID, stepper[motorID - MOTOR_ID_FIRST].getPos());
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/position", i + MOTOR_ID_FIRST, stepper[i].getPos());
        }
    }
}
void getMark(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/mark", motorID, stepper[motorID - MOTOR_ID_FIRST].getMark());
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/mark", i + MOTOR_ID_FIRST, stepper[i].getMark());
        }
    }
}

void run(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float stepsPerSec = getFloat(msg, 1);
    float absSpeed = fabsf(stepsPerSec);
    boolean dir = stepsPerSec > 0;
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        if (checkMotionStartConditions(motorID, dir)) {
            stepper[motorID].run(dir, absSpeed);
        }
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (checkMotionStartConditions(i, dir)) { 
                stepper[i].run(dir, absSpeed); 
            }
        }
    }
}

void runRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int32_t speed = getInt(msg, 1);
    boolean dir = speed > 0;
    speed = abs(speed);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        if (checkMotionStartConditions(motorID, dir)) {
            stepper[motorID].runRaw(dir, speed);
        }
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (checkMotionStartConditions(i, dir)) {
                stepper[i].runRaw(dir, speed);
            }
        }
    }
}

void move(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int32_t steps = getInt(msg, 1);
    boolean dir = steps > 0;
    steps = abs(steps);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        if (checkMotionStartConditions(motorID, dir)) {
            stepper[motorID].move(dir, steps);
        }
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (checkMotionStartConditions(i, dir)) {
                stepper[i].move(dir, steps);
            }
        }
    }
}
void goTo(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int32_t pos = getInt(msg, 1);
    bool dir = 0;
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        dir = checkGoToDirection(motorID, pos);
        if (checkMotionStartConditions(motorID, dir)) {
            stepper[motorID].goTo(pos);
        }
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            dir = checkGoToDirection(i, pos);
            if (checkMotionStartConditions(i, dir)) {
                stepper[i].goTo(pos);
            }
        }
    }
}
void goToDir(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    boolean dir = getBool(msg, 1);
    int32_t pos = getInt(msg, 2);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        if (checkMotionStartConditions(motorID, dir)) {
            stepper[motorID].goToDir(dir, pos);
        }
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (checkMotionStartConditions(i, dir) )
                stepper[i].goToDir(dir, pos);   
        }
    }
}

void homing(uint8_t motorId) {
    if ( bHoming[motorId] ) {
        sendCommandError(motorId + MOTOR_ID_FIRST, ERROR_COMMAND_IGNORED);
    } else if ( isServoMode[motorId] ) {
        sendCommandError(motorId + MOTOR_ID_FIRST, ERROR_IN_SERVO_MODE);
    } else {
        bHoming[motorId] = true;
        if (homeSwState[motorId]) {
            releaseSw(motorId, 0, !homingDirection[motorId]);
            homingStatus[motorId] = HOMING_RELEASESW;
        } else {
            goUntil(motorId, 0, homingDirection[motorId], homingSpeed[motorId]);
            homingStatus[motorId] = HOMING_GOUNTIL;
        }
        sendTwoData("/homingStatus",motorId+MOTOR_ID_FIRST, homingStatus[motorId]);
    }
}
void homing(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if (isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        homing(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            homing(i);
        }
    }
}

void goUntil(uint8_t motorId, bool action, bool dir, float stepsPerSec) {
    if (isBrakeDisEngaged(motorId)) {
        if (homeSwState[motorId]) {
            sendTwoData("/error/command", "HomeSwActivated", motorId+MOTOR_ID_FIRST);
        } else {
            stepper[motorId].goUntil(action, dir, stepsPerSec);
            homingStatus[motorId] = HOMING_GOUNTIL;
            homingStartTime[motorId] = millis();
        }
    }
}
void goUntil(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool action = getBool(msg, 1);
    float stepsPerSec = getFloat(msg, 2);
    bool dir = stepsPerSec > 0;
    stepsPerSec = fabsf(stepsPerSec);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        goUntil(motorID, action, dir, stepsPerSec);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            goUntil(i, action, dir, stepsPerSec);
        }
    }
}
void goUntilRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool action = getBool(msg, 1);
    int32_t speed = getInt(msg, 2);
    bool dir = speed > 0;
    speed = abs(speed);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        if (isBrakeDisEngaged(motorID)) {
            if (homeSwState[motorID]) {
                sendTwoData("/error/command", "HomeSwActivated", motorID+MOTOR_ID_FIRST);
            } else {
                stepper[motorID].goUntilRaw(action, dir, speed);
                homingStatus[motorID] = HOMING_GOUNTIL;
                homingStartTime[motorID] = millis();
            }
        }
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (isBrakeDisEngaged(i)) {
                if (homeSwState[i]) {
                    sendTwoData("/error/command", "HomeSwActivated", i+MOTOR_ID_FIRST);
                } else {
                    stepper[i].goUntil(action, dir, speed);
                    homingStatus[i] = HOMING_GOUNTIL;
                    homingStartTime[i] = millis();
                }
            }
        }
    }
}

void releaseSw(uint8_t motorId, bool action, bool dir) {
    if (isBrakeDisEngaged(motorId)) {
        stepper[motorId].releaseSw(action, dir);
        homingStatus[motorId] = HOMING_RELEASESW;
        homingStartTime[motorId] = millis();
    }
}
void releaseSw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t action = getInt(msg, 1);
    bool dir = getBool(msg, 2);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        releaseSw(motorID, action, dir);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            releaseSw(i, action, dir);
        }
    }
}
void goHome(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool dir;
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        dir = checkGoToDirection(motorID, 0);
        if (checkMotionStartConditions(motorID, dir)) {
            stepper[motorID].goHome();
        }   
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            dir = checkGoToDirection(i, 0);
            if (checkMotionStartConditions(i, dir)) {
                stepper[i].goHome();
            }
        }
    }
}
void goMark(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool dir;
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        dir = checkGoToDirection(motorID, stepper[motorID].getMark());
        if (checkMotionStartConditions(motorID, dir)) {
            stepper[motorID].goMark();
        }
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            dir = checkGoToDirection(i, stepper[i].getMark());
            if (checkMotionStartConditions(i, dir)) {
                stepper[i].goMark();
            }
        }
    }
}
void setMark(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int32_t newMark = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setMark(newMark);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setMark(newMark);
        }
    }
}
void setPosition(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int32_t newPos = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setPos(newPos);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setPos(newPos);
        }
    }
}
void resetPos(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].resetPos();
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].resetPos();
        }
    }
}
void softStop(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        isServoMode[motorID - MOTOR_ID_FIRST] = false;
        stepper[motorID - MOTOR_ID_FIRST].softStop();
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            isServoMode[i] = false;
            stepper[i].softStop();
        }
    }
}
void hardStop(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        isServoMode[motorID - MOTOR_ID_FIRST] = false;
        stepper[motorID - MOTOR_ID_FIRST].hardStop();
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            isServoMode[i] = false;
            stepper[i].hardStop();
        }
    }
}

void softHiZ(uint8_t motorId) {
    isServoMode[motorId] = false;
    if (electromagnetBrakeEnable[motorId]) {
        if (motorStatus[motorId] == 0) { // motor stopped
            activate(motorId, false);
        } else {
            stepper[motorId].softStop();
            bBrakeDecWaiting[motorId] = true;
        }
    } else {
        stepper[motorId].softHiZ();
    }
}
void softHiZ(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        softHiZ(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            softHiZ(i);
        }
    }
}
void hardHiZ(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        isServoMode[motorID] = false;
        if (electromagnetBrakeEnable[motorID]) {
            activate(motorID, false);
        } else {
            stepper[motorID].hardHiZ();
        }
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            isServoMode[i] = false;
            if (electromagnetBrakeEnable[i]) {
              activate(i, false);
            } else {
                stepper[i].hardHiZ();
            }
        }
    }
}

void activate(uint8_t motorId, bool state) {
    if (electromagnetBrakeEnable[motorId]) {
        if (((brakeStatus[motorId] == BRAKE_ENGAGED) || (brakeStatus[motorId] == BRAKE_MOTORHIZ_WAITING)) && state) {
            // if (!isCurrentMode[motorId]) 
            {
                digitalWrite(ledPin, !digitalRead(ledPin));
                uint8_t t = kvalRun[motorId]>>1;
                if (kvalHold[motorId]< t) {
                    stepper[motorId].setHoldKVAL(t);
                    kvalHold[motorId] = t;
                }
            } 
            // else {
            //     uint8_t t = tvalRun[motorId]>>1;
            //     if (tvalHold[motorId]< t) {
            //         stepper[motorId].setHoldTVAL(t);
            //         tvalHold[motorId] = t;
            //     }
            // }
            stepper[motorId].hardStop();
            brakeStatus[motorId] = BRAKE_DISENGAGE_WAITING;
            brakeTransitionTrigTime[motorId] = millis();
        }
        else if ((brakeStatus[motorId] == BRAKE_DISENGAGED) || (brakeStatus[motorId] == BRAKE_DISENGAGE_WAITING)) {
            if (state) { // from /free state
                stepper[motorId].hardStop(); // to activate the motor current
            } else {
                setBrake(motorId, LOW);
                brakeStatus[motorId] = BRAKE_MOTORHIZ_WAITING;
                brakeTransitionTrigTime[motorId] = millis();
            }    
        }
    } else {
        sendCommandError(motorId + MOTOR_ID_FIRST, ERROR_COMMAND_IGNORED);
    }
}
void activate(OSCMessage& msg, int addrOffset) {    
    uint8_t motorID = getInt(msg, 0);
    bool state = getBool(msg,1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        activate(motorID, state);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            activate(i, state);
        }
    }
}
void free(uint8_t motorId) {
    if (electromagnetBrakeEnable[motorId]) {
        setBrake(motorId, HIGH);
        stepper[motorId].hardHiZ();
        brakeStatus[motorId] = BRAKE_DISENGAGED;
    } else {
        sendCommandError(motorId + MOTOR_ID_FIRST, ERROR_COMMAND_IGNORED);
    }
}
void free(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        free(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            free(i);
        }
    }
}
#pragma endregion operational_commands_osc_listener

#pragma region servo_commands_osc_listener

void setTargetPosition(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int32_t position = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        targetPosition[motorID - MOTOR_ID_FIRST] = position;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            targetPosition[i] = position;
        }
    }
}

void setTargetPositionList(OSCMessage& msg, int addrOffset) {
    for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
        targetPosition[i] = getInt(msg, i);
    }
}

void enableServoMode(uint8_t motorId, bool enable) {
    if (enable) {
        targetPosition[motorId] = stepper[motorId].getPos();
        reportBUSY[motorId] = false;
        reportMotorStatus[motorId] = false;
        reportDir[motorId] = false;
        stepper[motorId].hardStop();
    }
    else {
        stepper[motorId].softStop();
    }
    isServoMode[motorId] = enable;
}
void enableServoMode(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        enableServoMode(motorID, bEnable);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            enableServoMode(i, bEnable);
        }
    }
}

void setServoParam(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float 
        _kp = getFloat(msg, 1), 
        _ki = getFloat(msg, 2), 
        _kd = getFloat(msg, 3);
    if (_kp <= 0.0) _kp = 0;
    if (_ki <= 0.0) _ki = 0;
    if (_kd <= 0.0) _kd = 0;
    if(isCorrectMotorId(motorID)) {
        kP[motorID - MOTOR_ID_FIRST] = _kp;
        kI[motorID - MOTOR_ID_FIRST] = _ki;
        kD[motorID - MOTOR_ID_FIRST] = _kd;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            kP[i] = _kp;
            kI[i] = _ki;
            kD[i] = _kd;
        }
    }
}

void getServoParam(uint8_t motorId) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/servoParam");
    newMes.add(motorId+MOTOR_ID_FIRST);
    newMes.add(kP[motorId]).add(kI[motorId]).add(kD[motorId]);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void getServoParam(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        getServoParam(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getServoParam(i);
        }
    }
}

#pragma endregion servo_commands_osc_listener

// #pragma region PowerSTEP01_config_osc_listener

// void setVoltageMode(uint8_t motorId) {
//     //stepper[motorId].hardHiZ();
//     stepper[motorId].setPWMFreq(PWM_DIV_1, PWM_MUL_0_75);
//     stepper[motorId].setHoldKVAL(kvalHold[motorId]);
//     stepper[motorId].setRunKVAL(kvalRun[motorId]);
//     stepper[motorId].setAccKVAL(kvalAcc[motorId]);
//     stepper[motorId].setDecKVAL(kvalDec[motorId]);
//     stepper[motorId].setParam(ST_SLP, startSlope[motorId]);
//     stepper[motorId].setParam(FN_SLP_ACC, accFinalSlope[motorId]);
//     stepper[motorId].setParam(FN_SLP_DEC, decFinalSlope[motorId]);
//     stepper[motorId].setVoltageMode();
//     isCurrentMode[motorId] = false;
// }
// void setVoltageMode(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     if(isCorrectMotorId(motorID)) {
//         motorID -= MOTOR_ID_FIRST;
//         setVoltageMode(motorID);
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             setVoltageMode(i);
//         }
//     }
// }

// void setCurrentMode(uint8_t motorId) {
//     //stepper[motorId].hardHiZ();
//     stepper[motorId].setPredictiveControl(CONFIG_PRED_ENABLE);
//     stepper[motorId].setSwitchingPeriod(5);
//     if (stepper[motorId].getStepMode() > STEP_SEL_1_16)
//     {
//         stepper[motorId].configStepMode(STEP_SEL_1_16);
//         microStepMode[motorId] = STEP_SEL_1_16;
//     }
//     stepper[motorId].setHoldTVAL(tvalHold[motorId]);
//     stepper[motorId].setRunTVAL(tvalRun[motorId]);
//     stepper[motorId].setAccTVAL(tvalAcc[motorId]);
//     stepper[motorId].setDecTVAL(tvalDec[motorId]);
//     stepper[motorId].setParam(T_FAST, fastDecaySetting[motorId]);
//     stepper[motorId].setParam(TON_MIN, minOnTime[motorId]);
//     stepper[motorId].setParam(TOFF_MIN, minOffTime[motorId]);
//     stepper[motorId].setCurrentMode();
//     isCurrentMode[motorId] = true;
// }
// void setCurrentMode(OSCMessage& msg, int addrOffset) {
//     uint8_t motorID = getInt(msg, 0);
//     if(isCorrectMotorId(motorID)) {
//         motorID -= MOTOR_ID_FIRST;
//         setCurrentMode(motorID);
//     }
//     else if (motorID == MOTOR_ID_ALL) {
//         for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
//             setCurrentMode(i);
//         }
//     }
// }

void setElPos(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t newElPos = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setElPos(newElPos);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setElPos(newElPos);
        }
    }
}
void getElPos(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t elPos;
    uint8_t microStepPos, step;
    if(isCorrectMotorId(motorID)) {
        elPos = stepper[motorID - MOTOR_ID_FIRST].getElPos();
        microStepPos = elPos&0x7F;
        step = elPos>>7;
        sendThreeInt("/elPos", motorID, step, microStepPos);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            elPos = stepper[i].getElPos();
            microStepPos = elPos&0x7F;
            step = elPos>>7;
            sendThreeInt("/elPos", i + MOTOR_ID_FIRST, step, microStepPos);
        }
    }
}
// #pragma endregion PowerSTEP01_config_osc_listener
