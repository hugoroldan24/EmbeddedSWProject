# Wireless Dual-Servo Controller

Hello! This is an embedded systems project built with two ATmega328P microcontrollers and nRF24L01+PA+LNA RF modules to wirelessly control two hobby servos using an analog joystick. All code is written in low-level C, without relying on any abstraction libraries. This project is helping me strengthen my skills in:

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
- **RF Module**: nRF24L01+PA+LNA(2.4 GHz) ×2  
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


## 🔌 Wiring Diagram

Below is a detailed overview of the connections between the ATmega328P microcontrollers and the nRF24L01 modules, as well as the connected peripherals (joystick and servos) on each side of the system.

###📤 Transmitter Side (Joystick → MCU → nRF24L01)

   | ATmega328P Pin | Connected To    | Description                          |
   | -------------- | --------------- | ------------------------------------ |
   | `PC0 (ADC0)`   | Joystick X-axis | Analog input (ADC)                   |
   | `PC1 (ADC1)`   | Joystick Y-axis | Analog input (ADC)                   |
   | `PB3 (MOSI)`   | nRF24L01+ MOSI  | SPI – Master Out                     |
   | `PB4 (MISO)`   | nRF24L01+ MISO  | SPI – Master In                      |
   | `PB5 (SCK)`    | nRF24L01+ SCK   | SPI Clock                            |
   | `PD7`          | nRF24L01+ CSN   | Chip Select (SPI)                    |
   | `PB0`          | nRF24L01+ CE    | Enables transmission                 |
   | `GND`          | nRF24L01+ GND   | Ground reference                     |
   | `3.3V`         | nRF24L01+ VCC   | Regulated power with 10 μF capacitor  |
   
---

###📥 Receiver Side (nRF24L01 → MCU → Servos)

   | ATmega328P Pin  | Connected To        | Description                         |
   | --------------  | ------------------- | ----------------------------------- |
   | `PB3 (MOSI)`    | nRF24L01+ MOSI      | SPI – Master Out                    |
   | `PB4 (MISO)`    | nRF24L01+ MISO      | SPI – Master In                     |
   | `PB5 (SCK)`     | nRF24L01+ SCK       | SPI Clock                           |
   | `PD7`           | nRF24L01+ CSN       | Chip Select (SPI)                   |
   | `PB0`           | nRF24L01+ CE        | Enables reception                   |
   | `PD2 (INT0)`    | nRF24L01+ IRQ       | Interrupt on received packet        |
   | `PB2 (OCR1A)`   | Servo Motor 1 (PWM) | PWM output                          |
   | `PB1 (OCR1B)`   | Servo Motor 2 (PWM) | PWM output                          |
   | `GND`           | nRF24L01+ & Servos  | Ground reference                    |
   | `5V`            | Servos VCC          | Power supply  			 |
   | `3.3V`          | nRF24L01+ VCC       | Regulated power with 10 μF capacitor |
   
---
   
   📌 **Note**: Make sure to power the nRF24L01 modules with a stable 3.3 V supply and place a decoupling capacitor (10 μF) close to the module to avoid voltage drops during transmission bursts.	



## ⚡ Getting Started

### ⚙️ Prerequisites
- **Toolchain**: avr-gcc, avr-libc, avrdude, make installed in your machine.
- Instalation commands:
   ```bash
  sudo apt update
  sudo apt install make gcc-avr binutils-avr avr-libc avrdude
   ```

### 💾 Build & Flash
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
    

