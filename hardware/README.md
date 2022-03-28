# Diagram
```mermaid
flowchart LR
	MCU ---|SPI/SERCOM4| W5500 --- Ethernet
	MCU --- |SPI/SERCOM3|L6470 --> Motor
  MCU --> |SPI/SERCOM2|74HC165 --> 74HC595 --> MCU
	HomeSw -->|SW| L6470
	DIPSW --> 74HC165
	74HC595 --> Brake
  ```
  
  Check the [document](https://ponoor.com/en/docs/step-series/technical-information/hardware-step800/) for details.
  
