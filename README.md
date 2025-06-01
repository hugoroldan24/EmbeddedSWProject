# Wireless Dual-Servo Controller

An embedded systems project using two ATmega328P microcontrollers and nRF24L01+ RF modules to wirelessly control two hobby servos via an analog joystick. This project is helping me strengthen my skills in:

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

## 🚀 Workflow

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

## 📐 Hardware Design

The schematics and PCB were designed using the EasyEDA platform.
Some components included in the design, such as a Bluetooth module, are not yet implemented — they are reserved for future development. This project is intended to evolve into a full drone system, where many additional features will be integrated.

![Transmitter Schematic](https://github.com/user-attachments/assets/d5b1afed-d974-4106-89cc-b38593cf12ae)

                         Transmitter Schematic
                         
![Transmitter PCB](https://github.com/user-attachments/assets/9e38f744-572a-4651-82d0-967a80ed147d)

                         Transmitter PCB Design
                         
![Receiver Schematic](https://github.com/user-attachments/assets/96c0bca4-1b79-4047-a7ad-08504e7d9587)

                         Receiver Schematic

![Receiver PCB](https://github.com/user-attachments/assets/0c9b6157-9341-489c-88f9-ee28fdbc4d49)

                         Receiver PCB Design


## ⚡ Getting Started

### Prerequisites
- **Toolchain**: avr-gcc, avr-libc, avrdude, make installed in your machine.
- Instalation commands:
   ```bash
  sudo apt update
  sudo apt install make gcc-avr binutils-avr avr-libc avrdude
   ```

### Build & Flash
1. Clone the repository:
   ```bash
   git clone https://github.com/hugoroldan24/EmbeddedSWProject.git
   cd EmbeddedSWProject
    ```
2. Compile and upload the code:
    ```bash
    cd transmitter/src      # cd receiver/src when compiling the code from the receiver 
    make all                # Compile the code and generate the .hex file
    make upload             # Flash the code into the MCU
    ```
