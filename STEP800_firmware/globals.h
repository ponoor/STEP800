// globals.h

#ifndef _GLOBALS_h
#define _GLOBALS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <SPI.h>
#include <Ponoor_L6470Library.h>
#include <Ethernet.h>

// =============================================================================
// Board / Pin definitions
// =============================================================================
// #define PROTOTYPE_BLACK // First Black PCB prototype
// #define PROTOTYPE_R3 // Uncomment this line for the prototype r4 pcb.
// r3: revision anno lab 2020
// r4: with brake connector 2021 (production ver)


#ifdef PROTOTYPE_R3 // ----------------- Prototype r3 -----------------
    #define HAS_SD
    #define ledPin	13u
    // L6470
    #define L6470
    #define L6470_MISO	6u	// D6 /SERCOM3/PAD[2] miso
    #define L6470_MOSI	11u	// D11/SERCOM3/PAD[0] mosi
    #define L6470_SCK	12u	// D12/SERCOM3/PAD[3] sck

    #define L6470_CS_PIN A0
    #define L6470_RESET_PIN A2
    // Shift registers
    // 74HC165 shift register for dip switch and busy/flag input
    #define MISO3	3u // SERCOM2/PAD[1]
    #define MOSI3   2u // SERCOM2/PAD[2] // not in use
    #define SCK3	0u // SERCOM2/PAD[3]
    #define LATCH3	A5
    // Shift registers SPI
    extern SPIClass SPI3;

    // W5500
    #define W5500_RESET_PIN A3

    #define SETUP_SW_PIN	5u
#elif defined(PROTOTYPE_BLACK) // ----------------- Prototype D_L6470x8_black -----------------
    #define ledPin	4u
    // L6470
    #define L6470
    #define L6470_MISO	12u	// 
    #define L6470_MOSI	11u	// 
    #define L6470_SCK	13u	// 
    #define L6470_CS_PIN 9u
    #define L6470_RESET_PIN A5
    // Shift Registers
    #define MISO3   A3
    #define LATCH3  A1
    #define SCK3    A2
    // W5500
    #define W5500_RESET_PIN 8u
#else // ----------------- Product version -----------------
    #define HAS_SD
    #define HAS_BRAKE
    #define ledPin	13u
    // L6470
    #define L6470
    #define L6470_MISO	6u	// D6 /SERCOM3/PAD[2] miso
    #define L6470_MOSI	11u	// D11/SERCOM3/PAD[0] mosi
    #define L6470_SCK	12u	// D12/SERCOM3/PAD[3] sck

    #define L6470_CS_PIN A0
    #define L6470_RESET_PIN A2
    // Shift registers
    // 74HC165 +74HC595 for the dip sw input and the brake output
    #define MISO3	3u // SERCOM2/PAD[1]
    #define MOSI3   2u // SERCOM2/PAD[2]
    #define SCK3	0u // SERCOM2/PAD[3]
    #define LATCH3	A5
    // Shift registers SPI
    extern SPIClass SPI3;

    // W5500
    #define W5500_RESET_PIN A3

    #define SHIFTOUT_ENABLE_PIN 5u
#endif

// =============================================================================
// Pin definitions
// =============================================================================
#ifdef HAS_SD
#define SD_CS_PIN	4u
#define SD_DETECT_PIN   A4
#endif

// =============================================================================
// Constants and variables
// =============================================================================

// General
#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__
extern const char *firmwareName;
extern const uint8_t firmwareVersion[3]; // defined in the main Arduino sketch
extern int8_t loadedConfigVersion[2];
extern const uint8_t applicableConfigVersion[2];
#define STATUS_POLL_PERIOD   1 // [ms]


// Tx, Rx LED
extern bool rxLedEnabled, txLedEnabled;
extern uint32_t RXL_blinkStartTime, TXL_blinkStartTime;
#define RXL_TXL_BLINK_DURATION	30 // ms

// Json configuration file
constexpr char* filename = "/config.txt";
const String productName = "STEP800";
extern String configName;
extern String configTargetProduct;
extern bool sdInitializeSucceeded;
extern bool configFileOpenSucceeded;
extern bool configFileParseSucceeded;
extern bool configProductApplicable;

// L6470
#define NUM_OF_MOTOR   (8)
extern AutoDriver stepper[];
#define MOTOR_ID_ALL    255
#define MOTOR_ID_FIRST  1
#define MOTOR_ID_LAST   8

// Network
extern uint8_t mac[6], mac_from_config[6], myId;
extern IPAddress
    myIp,
    myIp_from_config,
    destIp,
    dns,
    gateway,
    subnet;
const IPAddress broadcastIp(255, 255, 255, 255);
extern unsigned int inPort, outPort, outPort_from_config;
extern EthernetUDP Udp;
extern bool
    isDestIpSet,
    isMyIpAddId,
    isMacAddId,
    isOutPortAddId,
    bootedMsgEnable,
    isWaitingSendBootMsg,
    reportErrors;
#define BOOT_MSG_WAIT_TIME  1000    //[ms], The waiting duration for sending a boot message after Ethernet has been linked

// Motor settings.
// #define TVAL_LIMIT_VAL  64 // approx. 5A

// Brake
#ifdef HAS_BRAKE
extern uint8_t brakeOut;
#endif
extern uint8_t brakeStatus[NUM_OF_MOTOR];
enum {
    BRAKE_ENGAGED = 0,
    BRAKE_DISENGAGE_WAITING, // motor excited
    BRAKE_DISENGAGED,
    BRAKE_MOTORHIZ_WAITING // brake closed
};
extern uint32_t brakeTransitionTrigTime[NUM_OF_MOTOR];
extern bool bBrakeDecWaiting[NUM_OF_MOTOR]; // Waiting deceleration for the brake engaging procedure

// Homing
extern uint32_t homingStartTime[NUM_OF_MOTOR];
extern uint8_t homingStatus[NUM_OF_MOTOR];
extern bool bHoming[NUM_OF_MOTOR];
extern float homingSpeed[NUM_OF_MOTOR];
enum {
    HOMING_UNDEFINED = 0,
    HOMING_GOUNTIL,
    HOMING_RELEASESW,
    HOMING_COMPLETED,
    HOMING_TIMEOUT
};

// Command errors
enum {
    ERROR_COMMAND_IGNORED = 0,
    ERROR_MOTORID_NOTMATCH,
    ERROR_BRAKE_ENGAGED,
    ERROR_HOMESW_ACTIVATING,
    //ERROR_LIMITSW_ACTIVATING,
    ERROR_GOUNTIL_TIMEOUT,
    ERROR_RELEASESW_TIMEOUT,
    ERROR_IN_SERVO_MODE
};
const String commandErrorText[8] = {
    F("CommandIgnored"),
    F("MotorIdNotMatch"),
    F("BrakeEngaged"),
    F("HomeSwActivating"),
    //F("LimitSwActivating"),
    F("GoUntilTimeout"),
    F("ReleaseSwTimeout"),
    F("InServoMode")
};
// These values will be initialized at loadConfig()
extern bool
    busy[NUM_OF_MOTOR],
    HiZ[NUM_OF_MOTOR],
    homeSwState[NUM_OF_MOTOR],
    dir[NUM_OF_MOTOR],
    uvloStatus[NUM_OF_MOTOR];
extern uint8_t
    motorStatus[NUM_OF_MOTOR],
    thermalStatus[NUM_OF_MOTOR];

extern bool
    reportBUSY[NUM_OF_MOTOR],
    reportHiZ[NUM_OF_MOTOR],
    reportHomeSwStatus[NUM_OF_MOTOR],
    reportDir[NUM_OF_MOTOR],
    reportMotorStatus[NUM_OF_MOTOR],
    reportSwEvn[NUM_OF_MOTOR],
    reportUVLO[NUM_OF_MOTOR],
    reportThermalStatus[NUM_OF_MOTOR],
    reportOCD[NUM_OF_MOTOR],
    reportStall[NUM_OF_MOTOR],
    reportPosition[NUM_OF_MOTOR],
    reportPositionList,
    //limitSwState[NUM_OF_MOTOR],
    //reportLimitSwStatus[NUM_OF_MOTOR],
    //limitSwMode[NUM_OF_MOTOR],
    homingDirection[NUM_OF_MOTOR],
    bProhibitMotionOnHomeSw[NUM_OF_MOTOR],
    //bProhibitMotionOnLimitSw[NUM_OF_MOTOR],
    bHomingAtStartup[NUM_OF_MOTOR];
extern uint16_t
    goUntilTimeout[NUM_OF_MOTOR],
    releaseSwTimeout[NUM_OF_MOTOR],
    reportPositionInterval[NUM_OF_MOTOR],
    reportPositionListInterval;
extern uint8_t kvalHold[NUM_OF_MOTOR], kvalRun[NUM_OF_MOTOR], kvalAcc[NUM_OF_MOTOR], kvalDec[NUM_OF_MOTOR];
//extern uint8_t tvalHold[NUM_OF_MOTOR], tvalRun[NUM_OF_MOTOR], tvalAcc[NUM_OF_MOTOR], tvalDec[NUM_OF_MOTOR];
//extern bool isCurrentMode[NUM_OF_MOTOR];
extern bool homeSwMode[NUM_OF_MOTOR];

extern uint16_t intersectSpeed[NUM_OF_MOTOR]; // INT_SPEED
extern uint8_t
    startSlope[NUM_OF_MOTOR], // ST_SLP
    accFinalSlope[NUM_OF_MOTOR], // FN_SLP_ACC
    decFinalSlope[NUM_OF_MOTOR], // FN_SLP_DEC
    stallThreshold[NUM_OF_MOTOR]; // STALL_TH
// extern uint8_t
//     fastDecaySetting[NUM_OF_MOTOR], // T_FAST
//     minOnTime[NUM_OF_MOTOR], // TON_MIN
//     minOffTime[NUM_OF_MOTOR]; // TOFF_MIN
extern uint8_t
    overCurrentThreshold[NUM_OF_MOTOR], // OCD
    microStepMode[NUM_OF_MOTOR]; // STEP_MODE
extern uint16_t slewRate[NUM_OF_MOTOR]; // GATECFG1
extern uint8_t slewRateNum[NUM_OF_MOTOR]; // [0]114, [1]220, [2]400, [3]520, [4]790, [5]980.
extern float lowSpeedOptimizeThreshold[NUM_OF_MOTOR];
extern bool lowSpeedOptimizeEnable[NUM_OF_MOTOR];
extern bool electromagnetBrakeEnable[NUM_OF_MOTOR];
extern uint16_t brakeTransitionDuration[NUM_OF_MOTOR];
extern float
    acc[NUM_OF_MOTOR],
    dec[NUM_OF_MOTOR],
    maxSpeed[NUM_OF_MOTOR],
    minSpeed[NUM_OF_MOTOR],
    fullStepSpeed[NUM_OF_MOTOR];

// Servo mode
extern int32_t targetPosition[NUM_OF_MOTOR];
extern float kP[NUM_OF_MOTOR], kI[NUM_OF_MOTOR], kD[NUM_OF_MOTOR];
extern boolean isServoMode[NUM_OF_MOTOR];
#endif

