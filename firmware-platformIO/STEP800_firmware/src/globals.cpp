// 
// 
// 

#include "globals.h"

// Tx, Rx LED
bool rxLedEnabled = false, txLedEnabled = false;
uint32_t RXL_blinkStartTime, TXL_blinkStartTime;

// Json configuration file
String configName;
String configTargetProduct;
bool sdInitializeSucceeded = false;
bool configFileOpenSucceeded = false;
bool configFileParseSucceeded = false;
int8_t loadedConfigVersion[2] = {-1,0};
bool configProductApplicable = false;

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
// Shift Register SPI
#ifndef PROTOTYPE_BLACK
SPIClass SPI3(&sercom2, MISO3, SCK3, MOSI3, SPI_PAD_2_SCK_3, SERCOM_RX_PAD_1);
#endif

// Network
uint8_t mac[] = { 0x60, 0x95, 0xCE, 0x10, 0x06, 0x00 },
mac_from_config[],
myId = 0;
IPAddress
    myIp(10, 0, 0, 100),
    myIp_from_config,
    destIp(10, 0, 0, 10),
    dns(10, 0, 0, 1),
    gateway(10, 0, 0, 1),
    subnet(255, 255, 255, 0);
unsigned int outPort, outPort_from_config;
unsigned int inPort;
EthernetUDP Udp;
boolean
    isDestIpSet,
    isMyIpAddId,
    isMacAddId,
    isOutPortAddId,
    bootedMsgEnable,
    reportErrors = true;
boolean isWaitingSendBootMsg = false;
#ifdef HAS_BRAKE
uint8_t brakeOut = 0;
#endif
uint8_t brakeStatus[NUM_OF_MOTOR] = { 0,0,0,0,0,0,0,0 }; 
uint32_t brakeTransitionTrigTime[NUM_OF_MOTOR];
bool bBrakeDecWaiting[NUM_OF_MOTOR] = { 0,0,0,0,0,0,0,0 };

// Homing
uint32_t homingStartTime[NUM_OF_MOTOR];
uint8_t homingStatus[NUM_OF_MOTOR] = { 0,0,0,0,0,0,0,0 };
bool bHoming[NUM_OF_MOTOR] = { 0,0,0,0,0,0,0,0 };
// Motor settings
bool 
    busy[NUM_OF_MOTOR],
    HiZ[NUM_OF_MOTOR],
    homeSwState[NUM_OF_MOTOR],
    dir[NUM_OF_MOTOR],
    uvloStatus[NUM_OF_MOTOR];
uint8_t
    motorStatus[NUM_OF_MOTOR],
    thermalStatus[NUM_OF_MOTOR];
bool
    reportBUSY[NUM_OF_MOTOR],
    reportHiZ[NUM_OF_MOTOR],
    reportHomeSwStatus[NUM_OF_MOTOR],
    reportDir[NUM_OF_MOTOR],
    reportMotorStatus[NUM_OF_MOTOR],
    reportSwEvn[NUM_OF_MOTOR],
    reportCommandError[NUM_OF_MOTOR],
    reportUVLO[NUM_OF_MOTOR],
    reportThermalStatus[NUM_OF_MOTOR],
    reportOCD[NUM_OF_MOTOR],
    reportStall[NUM_OF_MOTOR],
    // limitSwState[NUM_OF_MOTOR],
    // reportLimitSwStatus[NUM_OF_MOTOR],
    // limitSwMode[NUM_OF_MOTOR],
    homingDirection[NUM_OF_MOTOR],
    bProhibitMotionOnHomeSw[NUM_OF_MOTOR],
    // bProhibitMotionOnLimitSw[NUM_OF_MOTOR],
    bHomingAtStartup[NUM_OF_MOTOR];
float homingSpeed[NUM_OF_MOTOR];
uint16_t
    goUntilTimeout[NUM_OF_MOTOR],
    releaseSwTimeout[NUM_OF_MOTOR];
uint8_t kvalHold[NUM_OF_MOTOR], kvalRun[NUM_OF_MOTOR], kvalAcc[NUM_OF_MOTOR], kvalDec[NUM_OF_MOTOR];
// uint8_t tvalHold[NUM_OF_MOTOR], tvalRun[NUM_OF_MOTOR], tvalAcc[NUM_OF_MOTOR], tvalDec[NUM_OF_MOTOR];
// bool isCurrentMode[NUM_OF_MOTOR];
bool homeSwMode[NUM_OF_MOTOR];

uint16_t intersectSpeed[NUM_OF_MOTOR]; // INT_SPEED
uint8_t
    startSlope[NUM_OF_MOTOR], // ST_SLP
    accFinalSlope[NUM_OF_MOTOR], // FN_SLP_ACC
    decFinalSlope[NUM_OF_MOTOR], // FN_SLP_DEC
    stallThreshold[NUM_OF_MOTOR]; // STALL_TH
// uint8_t
//     fastDecaySetting[NUM_OF_MOTOR], // T_FAST
//     minOnTime[NUM_OF_MOTOR], // TON_MIN
//     minOffTime[NUM_OF_MOTOR]; // TOFF_MIN
uint8_t
    overCurrentThreshold[NUM_OF_MOTOR], // OCD
    microStepMode[NUM_OF_MOTOR]; // STEP_MODE
uint16_t slewRate[NUM_OF_MOTOR]; // GATECFG1
uint8_t slewRateNum[NUM_OF_MOTOR]; // [0]114, [1]220, [2]400, [3]520, [4]790, [5]980.
float lowSpeedOptimize[NUM_OF_MOTOR];
bool electromagnetBrakeEnable[NUM_OF_MOTOR];
uint16_t brakeTransitionDuration[NUM_OF_MOTOR];

float
    acc[NUM_OF_MOTOR],
    dec[NUM_OF_MOTOR],
    maxSpeed[NUM_OF_MOTOR],
    fullStepSpeed[NUM_OF_MOTOR];

// Servo mode
int32_t targetPosition[NUM_OF_MOTOR];
float kP[NUM_OF_MOTOR], kI[NUM_OF_MOTOR], kD[NUM_OF_MOTOR];
boolean isServoMode[NUM_OF_MOTOR];