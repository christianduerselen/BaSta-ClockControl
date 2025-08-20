# BaSta-ClockControl

BaSta-ClockControl is an Arduino program used to operate inside a clock control panel with buttons for various interactions within a basketball game.

- Start/Stop game clock switch state
- Horn button pressed
- Precision Time Status (PTS) control of game clock switch state
- Start/Stop shot clock switch state
- 24s shot clock reset button pressed
- 14s shot clock reset button pressed

## Wiring

The information from the states is read from digital inputs on the board

- D5 = Start/Stop game clock switch state (Start = High / Stop = Low)
- D6 = Horn button pressed
- D7 = Precision Time Status (PTS) control of game clock switch state
- D8 = 24s shot clock reset button pressed
- D9 = 14s shot clock reset button pressed
- D10 = Start/Stop shot clock switch state (Start = Low / Stop = High)

## Serial protocol

The information read from the digital inputs is transfered via serial port to a computer which can parse the following protocol to further use the button and switch state.
The protocol consists of 5 bytes that are sent periodically.

- Baudrate: 57600
- Byte 0 = 0x0D (Carriage Return)
- Byte 1 = 0x30 +
  - 0x01 if game clock is running
  - 0x02 if horn button is pressed
  - 0x04 if PTS game clock is running
- Byte 2 = 0x40 +
  - 0x01 if 24s shot clock reset button is pressed
  - 0x02 if 14s shot clock reset button is pressed
  - 0x04 if shot clock is running
- Byte 3 = 0x50
- Byte 4 = 0x60