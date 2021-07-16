## Preparation
### Required tools
- PC which installed Arduino IDE software
- Atmel-ICE Basic https://www.microchip.com/DevelopmentTools/ProductDetails/ATATMEL-ICE
- Power Supply DC jack 24V 1A
- microSD or microSDHC card
- USB Type-C to Type-A cable
- Power Supply 24V 1A, with DC plug 5.5mm outer diameter, 2.1mm inter diameter, center plus
- Network Switch which support 100BASE-TX or faster.
- Ethernet cable CAT5 or higher.

### microSD card setup
1. Format the **microSD** or **microSDHC** card with FAT16 or FAT32.
    Note : microSDXC card will not work.
2. Download the test text data from here; https://raw.githubusercontent.com/kanta/STEP400_prototype/master/rev4/configTool/sample-setups/SM-42BYG011_24V/config.txt
3. Copy it to the top directory of the microSD card.
4. Remove the card from a PC and put into the microSD card slot on STEP800.
5. 
### Arduino IDE setup
1. Download and install latest Arduino IDE from https://www.arduino.cc/en/Main/Software
2. Install SAMD boards core. Procedure is explained here: https://www.arduino.cc/en/Guide/ArduinoZero
3. Specify the target board as `Arduino Zero (Native USB Port)`.
<img src="https://user-images.githubusercontent.com/1097902/125183587-aa763000-e252-11eb-8f3c-67a6195e0ffc.png" width = "600" />

#### Install Arduino Libraries for the test program

1. Open the IDE and click to the "Sketch" menu and then *Include Library*  > *Manage Libraries*.
2. Type "ponoor" to the search box located on the top right of the window. 
<img src="https://user-images.githubusercontent.com/1097902/125183637-2f614980-e253-11eb-8df9-8bcd8fce3c03.png" width = "600" />

3. You should be able to find "Ponoor L6470 Library". Select it and click the *Install* button.
4. Then install one another library “FlashStorage”. The procedure is same as above.

#### Download and Compile the test program

1. Download the program from [here](https://github.com/ponoor/STEP800/blob/master/step800_hardware_tests/Arduino/step800_hardware_tests/step800_hardware_tests.ino), and open it with the Arduino IDE software.
2. Specify the target board as `Arduino Zero (Native USB Port)` .
<img src="https://user-images.githubusercontent.com/1097902/125183641-37b98480-e253-11eb-9a5e-a9bc241dd2f0.png" width = "600" />
3. Press the “VERIFY” button. Then Arduino IDE starts the compile the program (which called “Sketch” in the IDE).

![](https://arduinotogo.com/wp-content/uploads/2016/07/ch3-buttons-labelled.png)

4. If the compiling process is done successfully, you will see a “Done compiling.” sign.
![image](https://user-images.githubusercontent.com/1097902/125183648-49029100-e253-11eb-86c9-38e77f9145b9.png)

## Programming the MCU
### 1. Apply the power supply
- Apply 24V DC to the PCB with DC input jack (5.5mm outer diameter, 2.1mm inter diameter, center plus). 
[ ] Check the green LED (designator `3.3V` )
### 2. Connect Atmel-ICE Basic
- Connect Atmel-ICE Basic with a PC with USB microB cable.
- Connect the programming cable to the “**SAM**” connector of the Atmel-ICE Basic
- For the cable, use the right connector in the following photo to the Atmel-ICE Basic, and the center connector to the PCB.  We won’t use the left connector.
<img src="https://user-images.githubusercontent.com/1097902/125184005-75b7a800-e255-11eb-8ed0-7846a7a99644.png" width = "300" /><img src="https://user-images.githubusercontent.com/1097902/125183995-659fc880-e255-11eb-8d24-a067c3d8cd0b.png" width = "300" />

- Remove the small plastic cover from `SWD` pin header on the PCB. Do not discard this cover, we will put this back to the connector later.
- Then connect a programming socket (the 1.27mm pitch 10pin connector in the middle of the cable) to `SWD` pinheader on the PCB. Be aware of the small circle marking which placed the pin no.1 of the `SWD` connector. The red line of the programming cable indicates the pin no.1 side of the programming header.
<img src="https://user-images.githubusercontent.com/1097902/125235340-45d3d780-e31d-11eb-8bce-7417e6088fea.png" width="600" />

- [ ] Green LED on Atmel-ICE Basic should be on.


### 3. Burn Arduino bootloader to the PCB
- Arduino bootloader can write from Arduino IDE. Select `Programmer` item from `Tools` menu,  then select `Atmel-ICE`.
    
![image](https://user-images.githubusercontent.com/1097902/125235519-8df2fa00-e31d-11eb-8c4e-d8952a9e9fbd.png)

- Then select `Burn Bootloader` item of `Tools` menu. 
    
![image](https://user-images.githubusercontent.com/1097902/125235534-93e8db00-e31d-11eb-9eda-bdcc99b7e92b.png)

- After programming process,
- [ ] Orange LED on the PCB (designator `L` ) will be fading in & out slowly.

### 4. Put the cover back to the SWD connector
Remove Atmel-ICE-Basic from the PCB and put the black plastic cover back to the SWD connector.

## Upload the test program
### Select a serial port from Arduino IDE
1. Connect the USB connector to a PC with an USB type-C cable. 
2. Open the IDE and click to the "Tools" menu and then *Port.* Then you should be able to find a serial port(s) and select one with information as `Arduino Zero (Native USB Port))` .
![image](https://user-images.githubusercontent.com/1097902/125291455-64a58e80-e35c-11eb-9130-723e42b0d35d.png)
3. If there is no serial port in the menu, probably the Arduino Zero bootloader isn’t programmed correctly. 
4. Click the upload button. The compile process will take a while. 
5. After the compile process is done, Arduino IDE will start upload it to STEP800. You will see the `TX` and `RX` LEDs on STEP800 are blinking during the upload process.

## Setups for the test
### Select the serial port again
Once the first sketch is uploaded to STEP800, the name of serial port will change from the original one. Select one with information as `Arduino Zero (Native USB Port))` again.

### Connect the Ethernet connector
Connect the Ethernet connector to a network switch with an Ethernet cable. This is used for check the ethernet link connection is established or not. 

## Test Procedure
Finally we are ready to start the test!

### Open a Serial Monitor
Click the lens button on the top right corner of the IDE window.
![image](https://user-images.githubusercontent.com/1097902/125292147-20ff5480-e35d-11eb-9c2d-bd06d57e2057.png)

Then you will see a new Serial Monitor window. You will find some settings in the bottom of the window but you can leave them as defaults.

### Send a test command
Select a transmission text form (see below) and type `t`  then return key.
![image](https://user-images.githubusercontent.com/1097902/125292308-4be9a880-e35d-11eb-92e4-6fa46b88a58d.png)

## Description of each tests
### microSD card slot

**Description**
This test checks the microSD card slot is working correctly or not.
The successful test result will look like this;

     -------------- SD card -------------- 
    SD card initialize: Ok
    SD_DETECT_PIN: 0 Ok
    
    Test result: Passed

**SD card initialize**
This item checks the connection with microSD card. If this test failed, please check followings;

- The microSD card is inserted
- Using a microSD or a microSDHC card, NOT microSDXC
- The microSD card is formatted with FAT16 or FAT32 formant, NOT exFAT 
- SPI wires for the microSD slot are wired correctly. 

**SD_DETECT_PIN**
This items checks the logical correctness of the microSD card detect pin.

**Related pins**

| MCU pin# | Function                             |
| -------- | ------------------------------------ |
| 13       | microSD SPI CS                       |
| 19       | microSD SPI MOSI (Shared with W5500) |
| 20       | microSD SPI SCK (Shared with W5500)  |
| 21       | microSD SPI MISO (Shared with W5500) |
| 10       | SD_DETECT_PIN                        |

### Auxiliary Pins

**Descriptions**
This test checks the auxiliary pad pins which exposed in the bottom side of the PCB.
The successful test result will look like this;

     -------------- Auxiliary Pins --------------
    Auxiliary Pins connection state: Ok
    
    Test result: Passed

This test confirms that each pin is not interfering with each other.

**Related pins**

| MCU pin# | Pad name (in Bottom side) |
| -------- | ------------------------- |
| 31       | SDA                       |
| 32       | SCL                       |
| 22       | D38                       |
|12|D9|
|11|D8|
|7|A1|
|15|D1|
|30|D7|

### Ethernet

**Descriptions**
This test the Ethernet controller chip and a physical connection of the network.
The successful test result will look like this;

     -------------- Ethernet --------------
    Ethernet hardware status: 3, -EthernetW5500 Ok
    Ethernet link status: 2 ..Ok
    
    Test result: Passed

**Ethernet hardware status**
This test checks the SPI communication with the Ethernet controller chip W5500 (`IC1`). If this test failed, please check the W5500 chip or wiring.

**Ethernet link status**
This test checks the physical connection of Ethernet. This test wait a few seconds to establish the connection. If the connection couldn’t establish within the waiting period, the test becomes failed. If so, please check the followings;

- Ethernet cable is connected with a network switch.
- Check the RJ45 connector `X3` and related components include; `C34, C35, C36, C37, R14, RN2, RN3`

**Related pins**

| MCU pin# | Function                             |
| -------- | ------------------------------------ |
| 9        | W5500 RESET                          |
| 27       | W5500 SPI CS                         |
| 19       | W5500 SPI MOSI (shared with microSD) |
| 20       | W5500 SPI SCK (shared with microSD)  |
| 21       | W5500 SPI MISO (shared with microSD) |

### L6470

**Description**
This test checks the motor driver chip L6470. 
The successful test result will look like this;

```
-------------- L6470 --------------     
L6470 SPI connection: Ok
L6470 ID#1
 STATUS: 0x7E30  Ok
 SW_F: 0 Ok
 BUSY: 0 Ok
L6470 ID#2
 STATUS: 0x7E30  Ok
 SW_F: 0 Ok
 BUSY: 0 Ok
L6470 ID#3
 STATUS: 0x7E30  Ok
 SW_F: 0 Ok
 BUSY: 0 Ok
L6470 ID#4
 STATUS: 0x7E30  Ok
 SW_F: 0 Ok
 BUSY: 0 Ok
L6470 ID#5
 STATUS: 0x7E30  Ok
 SW_F: 0 Ok
 BUSY: 0 Ok
L6470 ID#6
 STATUS: 0x7E30  Ok
 SW_F: 0 Ok
 BUSY: 0 Ok
L6470 ID#7
 STATUS: 0x7E30  Ok
 SW_F: 0 Ok
 BUSY: 0 Ok
L6470 ID#8
 STATUS: 0x7E30  Ok
 SW_F: 0 Ok
 BUSY: 0 Ok

Test result: Passed
```

**L6470 SPI connection**
This results shows the physical connection of the SPI daisy chain of 8 L6470s are working or not. All SPI pins of all L6470s and the MCU have to be connected properly to establish the SPI communication.
If this test failed, please check the connections of following pins;

| MCU pin# | L6470 pin# | Function             |
| -------- | ---------------- | -------------------- |
| 3        | 23               | L6470 SPI CS   |
| 8        | 3                | L6470 RESET    |
| 25       | 20               | L6470 SPI MOSI |
| 28       | 19               | L6470 SPI SCK  |
| 29       | 18               | L6470 SPI MISO |

**STATUS**
This item shows the status of each PowerSTEP01. There are several possible errors here.


- `OCD(Over Current) detected.` : This error indicates an overcurrent detection event. Probably something is wrong in following pins;

| L6470 pin#       | Function |
| ---------------------- | -------- |
| 1                      | OUT1A |
| 14                     | OUT1B |
| 15 | OUT2A |
| 28 | OUT2B |

- `UVLO(Under Voltage Lock Out) detected.`  : This error will happen then a VCC of the L6470 is too low.  Check the power supply is connected properly, and following pin connections;

| L6470 pin# | Function |
| ---------------- | -------- |
| 2, 26               | VSA       |
| 12, 16               | VSB    |
| 10               | CP      |
| 11               | VBOOT   |

- `OCD+UVLO detected.` : This error happens when the external clock source is not provided. Check the crystal oscillator `Q3` and external clock input and output pins of L6470. The external clock is daisy chained among L6470s, `Q3` → `U6` → `U7` → `U8` → `U9` → `U10` → `U11` → `U12` → `U13`.

| L6470 pin# | Function |
| ----------------- | -------- |
| 7                | OSCIN    |
| 8                | OSCOUT   |

**SW_F**
This item checks the state of SW pin of PowerSTEP01, which connected to HOME sensor connector. 

| L6470 pin# | Function |
| ---------------- | -------- |
| 4               | SW       |


### DIP Switch

**Descriptions**
This test checks the DIP switch (designator `ID`) and you need to move all digits of the switch by yourself to complete the test.
Initially you will see the following message.

```
-------------- DIP Switch --------------
Turn the digit #1 ON...
```
Move the specified digit of the switch. Then you will see a next message.
Eventually the test result will look something like this;

```
-------------- DIP Switch --------------
Turn the digit #1 ON....Done.
Turn the digit #1 OFF...Done.
Turn the digit #2 ON.Done.   
Turn the digit #2 OFF..Done.
Turn the digit #3 ON..Done. 
Turn the digit #3 OFF..Done.
Turn the digit #4 ON..Done. 
Turn the digit #4 OFF..Done.
Turn the digit #5 ON..Done. 
Turn the digit #5 OFF.Done.
Turn the digit #6 ON..Done.
Turn the digit #6 OFF..Done.
Turn the digit #7 ON...Done.
Turn the digit #7 OFF.Done. 
Turn the digit #8 ON..Done.
Turn the digit #8 OFF..Done.

Test result: Passed
```

You will see the message every time you moved the digit.
This test will be finished when all 8 digits are successfully moved.

If you need to cancel this DIP switch test you can type `b`.

### Test result

Finally you will see the result. The last line shows the total result.

```
-------------- Result of Hardware Test --------------
SD Card: Ok
Auxiliary Pins: Ok
Ethernet: Ok
L6470: Ok
DIP switch: Ok

Test result: Passed
```

