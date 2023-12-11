# Smart Home System with ATmega32

## Overview

This project transforms the ATmega32 microcontrollers into a smart home system utilizing a combination of Serial Peripheral Interface (SPI) and I2C protocols. The master controller handles secure user authentication, door control, and acts as the central hub for remotely controlling devices connected to a slave controller. The system leverages SPI for communication between the master and slave controllers and utilizes I2C to store and retrieve user passwords securely on an external EEPROM.

## Components

### 1. ATmega32 Login System (Master)

This part of the project handles user authentication and door control.

- **Login.c**: Implements the user login and password management system. The user initializes a password, which is stored in external EEPROM using I2C protocol. After initialization, the user can log in by entering the correct password. Three unsuccessful login attempts result in a buzzer sound and system closure. Successful login opens a door using a DC fan controlled by Timer0 in fast PWM mode.

### 2. ATmega32 Remote Device Control (Master)

The master microcontroller allows the user to control devices remotely.

- **main.c**: After a successful login, the master microcontroller displays options for the user: cooler, heater, light on, and light off. The user's choice is sent to the slave microcontroller through the SPI protocol.

### 3. ATmega32 Remote Device (Slave)

This part receives commands from the master microcontroller and controls devices accordingly.

- **main.c**: Listens for commands sent by the master through SPI. Depending on the command received, it controls a cooler, a heater, or turns on/off lights.

## Hardware Setup

- **ATmega32 Microcontrollers**: Two microcontrollers used for the master and slave components.
- **LCD Display**: Used for user interface and displaying system messages.
- **Keypad (KPD)**: Used for user input during password initialization and device control.
- **EEPROM**: External EEPROM used for storing the user's password.
- **DC Fan**: Controlled by the master microcontroller to simulate door control.
- **LEDs**: Used to represent lights that can be controlled remotely.
- **Buzzer**: Used for sound feedback in case of unsuccessful login attempts.

## Dependencies

- **AVR Libc**: Standard C library for AVR microcontrollers.
- **util/delay.h**: Library for creating delays in the program.
- **avr/interrupt.h**: Library for handling interrupts.
- **SPI Driver**: Custom SPI driver for communication between master and slave microcontrollers.
- **DIO Driver**: Custom driver for digital I/O operations.
- **EEPROM Driver**: Custom driver for interfacing with external EEPROM.
- **LCD Driver**: Custom driver for interfacing with LCD display.
- **KPD Driver**: Custom driver for interfacing with the keypad.
- **TMR Driver**: Custom driver for Timer/Counter operations.
- **LM Sensor Driver**: Custom driver for interfacing with LM temperature sensor.

## Usage

1. Connect the hardware components according to the specified setup.
2. Upload the respective code to each ATmega32 microcontroller.
3. Power on the system and follow the login procedure.
4. After successful login, use the master microcontroller to control devices remotely.

## Contributing

If you find any issues or have improvements to suggest, feel free to open an issue or create a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
"# Smart-Home-System-Atmega32" 
