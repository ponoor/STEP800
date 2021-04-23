// 
// 
// 
#include "loadConfig.h"

void loadConfig() {
    uint8_t i;
    #ifdef PROTOTYPE_BLACK
    sdInitializeSucceeded = false;
    configFileOpenSucceeded = false;
    configFileParseSucceeded = false;
    DynamicJsonDocument doc(7200);
    #else
    if (digitalRead(SD_DETECT_PIN) == LOW)
    {
        sdInitializeSucceeded = SD.begin(SD_CS_PIN);
    }
    File file = SD.open(filename);
    configFileOpenSucceeded = (file != false);
    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/v6/assistant to compute the capacity.
    DynamicJsonDocument doc(7200); // 6144
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        p("Failed to read file: %s\nUsing default configuration.\n", error.f_str());
    }
    configFileParseSucceeded = (error == false);
    file.close();
    SD.end();
    #endif

    // Information
    JsonObject information = doc["information"];
    configName = information["configName"] | "Default";
    if (configFileOpenSucceeded) {
        for (i=0;i<2; i++) {
            loadedConfigVersion[i] = information["configVersion"][i] | 0;
        }
    }
    configTargetProduct = information["targetProduct"] | "---";

    // Network
    JsonObject network = doc["network"];
    JsonArray network_myIp = network["myIp"];
    JsonArray network_destIp = network["destIp"];
    JsonArray network_dns = network["dns"];
    JsonArray network_gateway = network["gateway"];
    JsonArray network_subnet = network["subnet"];
    for (i = 0; i < 4; i++) {
        myIp[i] = network_myIp[i] | myIp[i];
        destIp[i] = network_destIp[i] | destIp[i];
        dns[i] = network_dns[i] | dns[i];
        gateway[i] = network_gateway[i] | gateway[i];
        subnet[i] = network_subnet[i] | subnet[i];
    }
    isMyIpAddId = network["isMyIpAddId"] | true;
    inPort = network["inPort"] | 50000;
    outPort = network["outPort"] | 50100;
    isOutPortAddId = network["isOutPortAddId"] | true;
    JsonArray network_mac = network["mac"];
    for (i = 0; i < 6; i++) {
        mac[i] = network_mac[i] | mac[i];
    }
    isMacAddId = network["isMacAddId"] | true;
    bootedMsgEnable = network["bootedMsgEnable"] | true;
    isDestIpSet = network["canSendMsgBeforeDestIp"] | false;
    reportErrors = network["reportError"] | true;

    // Alarm and Report
    JsonObject alarmAndReport = doc["alarmAndReport"];
    JsonArray alarmAndReport_reportBUSY = alarmAndReport["reportBUSY"];
    JsonArray alarmAndReport_reportHiZ = alarmAndReport["reportHiZ"];
    JsonArray alarmAndReport_reportHomeSwStatus = alarmAndReport["reportHomeSwStatus"];
    JsonArray alarmAndReport_reportDir = alarmAndReport["reportDir"];
    JsonArray alarmAndReport_reportMotorStatus = alarmAndReport["reportMotorStatus"];
    JsonArray alarmAndReport_reportSwEvn = alarmAndReport["reportSwEvn"];
    //JsonArray alarmAndReport_reportCommandError = alarmAndReport["reportCommandError"];
    JsonArray alarmAndReport_reportUVLO = alarmAndReport["reportUVLO"];
    JsonArray alarmAndReport_reportThermalStatus = alarmAndReport["reportThermalStatus"];
    JsonArray alarmAndReport_reportOCD = alarmAndReport["reportOCD"];
    JsonArray alarmAndReport_reportStall = alarmAndReport["reportStall"];
    // JsonArray alarmAndReport_reportLimitSwStatus = alarmAndReport["reportLimitSwStatus"];
    JsonArray alarmAndReport_OCThreshold = alarmAndReport["OCThreshold"];
    for (i = 0; i < NUM_OF_MOTOR; i++)
    {
        reportBUSY[i] = alarmAndReport_reportBUSY[i] | false;
        reportHiZ[i] = alarmAndReport_reportHiZ[i] | false;
        reportHomeSwStatus[i] = alarmAndReport_reportHomeSwStatus[i] | false;
        //reportLimitSwStatus[i] = alarmAndReport_reportLimitSwStatus[i] | false;
        reportDir[i] = alarmAndReport_reportDir[i] | false;
        reportMotorStatus[i] = alarmAndReport_reportMotorStatus[i] | false;
        reportSwEvn[i] = alarmAndReport_reportSwEvn[i] | false;
        reportUVLO[i] = alarmAndReport_reportUVLO[i] | true;
        reportThermalStatus[i] = alarmAndReport_reportThermalStatus[i] | true;
        reportOCD[i] = alarmAndReport_reportOCD[i] | true;
        reportStall[i] = alarmAndReport_reportStall[i] | true;
        overCurrentThreshold[i] = alarmAndReport_OCThreshold[i] | 15;
    }

    // Driver settings
    JsonObject driverSettings = doc["driverSettings"];
    JsonArray driverSettings_homingAtStartup = driverSettings["homingAtStartup"];
    JsonArray driverSettings_homingDirection = driverSettings["homingDirection"];
    JsonArray driverSettings_homingSpeed = driverSettings["homingSpeed"];
    JsonArray driverSettings_homeSwMode = driverSettings["homeSwMode"];
    JsonArray driverSettings_prohibitMotionOnHomeSw = driverSettings["prohibitMotionOnHomeSw"];
    // JsonArray driverSettings_limitSwMode = driverSettings["limitSwMode"];
    // JsonArray driverSettings_prohibitMotionOnLimitSw = driverSettings["prohibitMotionOnLimitSw"];
    JsonArray driverSettings_goUnitlTimeout = driverSettings["goUnitlTimeout"];
    JsonArray driverSettings_releaseSwTimeout = driverSettings["releaseSwTimeout"];
    JsonArray driverSettings_stepMode = driverSettings["stepMode"];
    // JsonArray driverSettings_isCurrentMode = driverSettings["isCurrentMode"];
    JsonArray driverSettings_slewRate = driverSettings["slewRate"];
    JsonArray driverSettings_electromagnetBrakeEnable = driverSettings["electromagnetBrakeEnable"];
    JsonArray driverSettings_brakeTransitionDuration = driverSettings["brakeTransitionDuration"];
    uint16_t slewRateVal[3] = { SR_180V_us, SR_290V_us, SR_530V_us };
    for (i = 0; i < NUM_OF_MOTOR; i++) {
        bHomingAtStartup[i] = driverSettings_homingAtStartup[i] | false;
        homingDirection[i] = driverSettings_homingDirection[i] | REV;
        homingSpeed[i] = driverSettings_homingSpeed[i] | 50.0;
        homeSwMode[i] = driverSettings_homeSwMode[i] | true; // true: SW_USER, false: SW_HARDSTOP
        bProhibitMotionOnHomeSw[i] = driverSettings_prohibitMotionOnHomeSw[i] | false;
        // limitSwMode[i] = driverSettings_limitSwMode[i] | true;
        // bProhibitMotionOnLimitSw[i] = driverSettings_prohibitMotionOnLimitSw[i] | false;
        goUntilTimeout[i] = driverSettings_goUnitlTimeout[i] | 10000;
        releaseSwTimeout[i] = driverSettings_releaseSwTimeout[i] | 10000;
        microStepMode[i] = driverSettings_stepMode[i] | STEP_SEL_1_128;
        // isCurrentMode[i] = driverSettings_isCurrentMode[i] | false;
        slewRateNum[i] = constrain((driverSettings_slewRate[i] | 2), 0, 2); // default SR_530V_us
        slewRate[i] = slewRateVal[slewRateNum[i]];
#ifdef HAS_BRAKE
        electromagnetBrakeEnable[i] = driverSettings_electromagnetBrakeEnable[i] | false;
#else
        electromagnetBrakeEnable[i] = false;
#endif
        brakeTransitionDuration[i] = driverSettings_brakeTransitionDuration[i] | 100;
    }

    // Speed profile
    JsonObject speedProfile = doc["speedProfile"];
    JsonArray speedProfile_acc = speedProfile["acc"];
    JsonArray speedProfile_dec = speedProfile["dec"];
    JsonArray speedProfile_maxSpeed = speedProfile["maxSpeed"];
    JsonArray speedProfile_fullStepSpeed = speedProfile["fullStepSpeed"];
    for (i = 0; i < NUM_OF_MOTOR; i++) {
        acc[i] = speedProfile_acc[i] | 1000.;
        dec[i] = speedProfile_dec[i] | 1000.;
        maxSpeed[i] = speedProfile_maxSpeed[i] | 650.;
        fullStepSpeed[i] = speedProfile_fullStepSpeed[i] | 15610.;
    }

    // Voltage mode
    JsonObject voltageMode = doc["voltageMode"];
    JsonArray voltageMode_KVAL_HOLD = voltageMode["KVAL_HOLD"];
    JsonArray voltageMode_KVAL_RUN = voltageMode["KVAL_RUN"];
    JsonArray voltageMode_KVAL_ACC = voltageMode["KVAL_ACC"];
    JsonArray voltageMode_KVAL_DEC = voltageMode["KVAL_DEC"];
    JsonArray voltageMode_INT_SPEED = voltageMode["INT_SPEED"];
    JsonArray voltageMode_ST_SLP = voltageMode["ST_SLP"];
    JsonArray voltageMode_FN_SLP_ACC = voltageMode["FN_SLP_ACC"];
    JsonArray voltageMode_FN_SLP_DEC = voltageMode["FN_SLP_DEC"];
    JsonArray voltageMode_STALL_TH = voltageMode["STALL_TH"];
    JsonArray voltageMode_lowSpeedOptimize = voltageMode["lowSpeedOptimize"];
    for (i = 0; i < NUM_OF_MOTOR; i++) {
        kvalHold[i] = voltageMode_KVAL_HOLD[i] | 0;
        kvalRun[i] = voltageMode_KVAL_RUN[i] | 16;
        kvalAcc[i] = voltageMode_KVAL_ACC[i] | 16;
        kvalDec[i] = voltageMode_KVAL_DEC[i] | 16;
        intersectSpeed[i] = voltageMode_INT_SPEED[i] | 0x0408;
        startSlope[i] = voltageMode_ST_SLP[i] | 0x19;
        accFinalSlope[i] = voltageMode_FN_SLP_ACC[i] | 0x29;
        decFinalSlope[i] = voltageMode_FN_SLP_DEC[i] | 0x29;
        // stallThreshold[i] = voltageMode_STALL_TH[i] | 0x1F;
        stallThreshold[i] = voltageMode_STALL_TH[i] | 0x7F;
        lowSpeedOptimize[i] = voltageMode_lowSpeedOptimize[i] | 20.;
    }

    // Current mode
    // JsonObject currentMode = doc["currentMode"];
    // JsonArray currentMode_TVAL_HOLD = currentMode["TVAL_HOLD"];
    // JsonArray currentMode_TVAL_RUN = currentMode["TVAL_RUN"];
    // JsonArray currentMode_TVAL_ACC = currentMode["TVAL_ACC"];
    // JsonArray currentMode_TVAL_DEC = currentMode["TVAL_DEC"];
    // JsonArray currentMode_T_FAST = currentMode["T_FAST"];
    // JsonArray currentMode_TON_MIN = currentMode["TON_MIN"];
    // JsonArray currentMode_TOFF_MIN = currentMode["TOFF_MIN"];
    // for (i = 0; i < NUM_OF_MOTOR; i++) {
    //     tvalHold[i] = currentMode_TVAL_HOLD[i] | 0;
    //     tvalRun[i] = currentMode_TVAL_RUN[i] | 16;
    //     tvalAcc[i] = currentMode_TVAL_ACC[i] | 16;
    //     tvalDec[i] = currentMode_TVAL_DEC[i] | 16;
    //     fastDecaySetting[i] = currentMode_T_FAST[i] | 25;
    //     minOnTime[i] = currentMode_TON_MIN[i] | 41;
    //     minOffTime[i] = currentMode_TOFF_MIN[i] | 41;
    // }

    // Servo mode
    JsonObject servoMode = doc["servoMode"];
    JsonArray servoMode_kP = servoMode["kP"];
    JsonArray servoMode_kI = servoMode["kI"];
    JsonArray servoMode_kD = servoMode["kD"];
    for (i = 0; i < NUM_OF_MOTOR; i++) {
        kP[i] = servoMode_kP[i] | 0.06;
        kI[i] = servoMode_kI[i] | 0.0;
        kD[i] = servoMode_kD[i] | 0.0;
    }
}

uint8_t checkConfigVersion() {
    if (loadedConfigVersion[0] == -1) {
        return CONFIG_VERSION_NOTLOADED;
    } else if ((loadedConfigVersion[0] == 0) && (loadedConfigVersion[1] == 0)) {
        return CONFIG_VERSION_UNDEFINED;
    } else if (loadedConfigVersion[0] > applicableConfigVersion[0]) {
        return CONFIG_VERSION_NEW;
    } else if (loadedConfigVersion[0] < applicableConfigVersion[0]) {
        return CONFIG_VERSION_OLD;
    } else {
        if (loadedConfigVersion[1] > applicableConfigVersion[1]) {
            return CONFIG_VERSION_NEW;
        } else if (loadedConfigVersion[1] < applicableConfigVersion[1]) {
            return CONFIG_VERSION_OLD;
        } else {
            return CONFIG_VERSION_APPLICABLE;
        }
    }
}
