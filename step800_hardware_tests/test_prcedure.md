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

1. Download the program from here. https://github.com/ponoor/STEP400/blob/master/hardwareTestSketch/hardwareTestSketch.ino
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
