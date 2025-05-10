# Wireless Dual-Servo Controller

A work-in-progress embedded project that uses two ATMega328P microcontrollers and nRF24L01 RF modules to drive two hobby servos from an analog joystick remotely. Through this project I’m deepening my skills in:

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
