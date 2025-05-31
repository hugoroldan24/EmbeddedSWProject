# Wireless Dual-Servo Controller

An embedded project that uses two ATMega328P microcontrollers and nRF24L01 RF modules to drive two hobby servos from an analog joystick remotely. Through this project I’m deepening my skills in:

- **Low-level C & register programming** on AVR  
- **SPI & ADC setup** for efficient data exchange and analog sampling  
- **Interrupt-driven data flow** to guarantee real-time responsiveness  
- **Timer-based PWM generation** at 50 Hz for accurate servo control  
- **RF link configuration** and power-up sequencing per nRF24L01 datasheet  
- **Datasheet interpretation**, extracting register settings and timing constraints

---

## 📦 Hardware

- **Transmitter MCU**: ATMega328P  
- **Receiver MCU**: ATMega328P  
- **RF Module**: nRF24L01 (2.4 GHz) ×2  
- **Controls**: Dual analog joystick (2 axes)  
- **Actuators**: Two standard hobby servos (5 V)  
- **Power**: 5 V regulated (USB or external LiPo + buck)

---

## 🛠 Software

- **Bare-metal AVR C** (no Arduino libraries)  
- **AVR-GCC toolchain** (avr-gcc + avr-libc)  
- **Makefile** for build/flash automation  
- **SPI**, **ADC**, **Timer1**, **Timer0**, and **External Interrupt** drivers  

---

## 🚀 Work Flow

**1. Read Joystick Inputs**
     The transmitter MCU samples the two analog axes of the joystick via its ADC and converts those readings into digital values.

**2. Send Data to RF Module**
     The MCU packages the joystick values into a data packet and transfers it over SPI to the nRF24L01+ configured as a transmitter.

**3. Transmit Over the Air**
     The nRF24L01+ radio module sends the packet wirelessly to the paired receiver module.

**4. Receive and Forward Data**
     The nRF24L01+ receiver module captures the incoming packet and relays it over SPI to the receiver MCU.

**5. Generate PWM for Servos**
     The receiver MCU reads the joystick values, maps them to appropriate register settings, and drives two PWM outputs—one for each servo motor—to control speed and direction.
