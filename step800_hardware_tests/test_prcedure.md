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

# Programming the MCU
## 1. Apply the power supply
- Apply 24V DC to the PCB with DC input jack (5.5mm outer diameter, 2.1mm inter diameter, center plus). 
[ ] Check the green LED (designator `3.3V` )
## 2. Connect Atmel-ICE Basic
- Connect Atmel-ICE Basic with a PC with USB microB cable.
- Connect the programming cable to the “**SAM**” connector of the Atmel-ICE Basic
- For the cable, use the right connector to the Atmel-ICE Basic, and the center connector to the PCB.  We won’t use the left connector.
<img src="https://media.digikey.com/Photos/Atmel%20Photos/MFG_ATATMEL-ICE-BASIC.jpg" width = "300" />
<img src="https://images-na.ssl-images-amazon.com/images/I/511stTQfqZL._AC_SL1440_.jpg" width = "300" />

- Remove the small plastic cover from `SWD` pin header on the PCB. Do not discard this cover, we will use it later.
- Then connect a programming socket (the 1.27mm pitch 10pin connector in the middle of the cable) to `SWD` pinheader on the PCB. Be aware of the small circle marking which placed the pin no.1 of the `SWD` connector. The red line of the programming cable indicates the pin no.1 side of the programming header.
![Pin no.1 is situated in the left bottom corner in this image. The red line of the programming cable should come to the same side of the SWD connector.](https://paper-attachments.dropbox.com/s_C4BFE802A808CAA525133E919C7A0A02329425BB61F7484D642CD4904227D66C_1611579199576_image.png)

[ ] Green LED on Atmel-ICE Basic should be on.


## 3. Burn Arduino bootloader to the PCB
- Arduino bootloader can write from Arduino IDE. Select `Programmer` item from `Tools` menu,  then select `Atmel-ICE`.
    
![](https://paper-attachments.dropbox.com/s_C4BFE802A808CAA525133E919C7A0A02329425BB61F7484D642CD4904227D66C_1609391577581_image.png)

- Then select `Burn Bootloader` item of `Tools` menu. 
    
![](https://paper-attachments.dropbox.com/s_C4BFE802A808CAA525133E919C7A0A02329425BB61F7484D642CD4904227D66C_1609391606908_image.png)

- After programming process,
[ ] Orange LED on the PCB (designator `L` ) will be fading in & out slowly.
