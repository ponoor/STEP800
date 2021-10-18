# STEP800 LED test
## Preparation
### Connection
- Connect STEP800 to PC with an USB-C to Type-A cable
- Give a 24V power supply to STEP800

### Upload the test program
1. Download the test program from [here](https://github.com/ponoor/STEP800/tree/develop/step800_hardware_tests/step800_led_test), or unizip the attached file. 
2. Open the `step800_led_test.ino` with Arduino IDE.
3. Specify the IDE's target board as Arduino Zero (Native USB Port).
<img src="https://user-images.githubusercontent.com/1097902/125183587-aa763000-e252-11eb-8f3c-67a6195e0ffc.png" width = "600" />

4. Click to the "Tools" menu and then *Port*. Then you should be able to find a serial port(s) and select one with information as `Arduino Zero (Native USB Port))` .
<img src="https://user-images.githubusercontent.com/1097902/125291455-64a58e80-e35c-11eb-9130-723e42b0d35d.png" width = "600" />

5. Click the upload button. The compile process will take a while.
6. After the compile process is done, Arduino IDE will start upload it to STEP800. You will see the `TX` and `RX` LEDs on STEP800 are blinking during the upload process.
7. If the uploading process is done without problems, you will see the `L` led is turned on.

## Test
### Open the Serial Monitor
Click the lens button on the top right corner of the IDE window.
![image](https://user-images.githubusercontent.com/1097902/125292147-20ff5480-e35d-11eb-9c2d-bd06d57e2057.png)

Then you will see a new Serial Monitor window. You will find some settings in the bottom of the window but you can leave them as defaults.

### FLAG LEDs test
Select a transmission text form (see below) and type `f`  then return key.
This command turn all FLAG LEDs on.
![image](https://user-images.githubusercontent.com/1097902/125292308-4be9a880-e35d-11eb-92e4-6fa46b88a58d.png)

### BUSY LEDs test
Type `b` + return key should cause turning all BUSY LEDs on.

### Clear LEDs
Type `c` + return key will turn all LEDs off.

---

rev 2021-09-13-01, by kanta
