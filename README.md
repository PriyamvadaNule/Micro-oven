# 🔥 Smart Micro-Oven Simulation using PIC16F877A

A simulated embedded system project designed to replicate the functionality of a smart microwave oven with multiple cooking modes using the PIC16F877A microcontroller. Developed and tested during an internship using MPLAB X IDE, XC8 Compiler, and PICSimLab.

---

## 👩‍💻 Author

**Priyamvada Nule**  
Internship Project under the guidance of *Jayalaxmi N Dhanyal*
*Emertxe*

---

## 📌 Project Overview

This project simulates a micro-oven that allows users to:
- Select from 4 different cooking modes
- Set a cooking timer via keypad
- View status and time countdown on an LCD
- Control heating using relay and timer logic
- Get notified when cooking is complete using a buzzer

---

## 🚀 Features

- 🔘 **4 Cooking Modes**
  - Micro Mode (Low power)
  - Grill Mode (High heat)
  - Convection Mode (Hot air circulation)
  - Start Mode (Standard microwave)
  
- ⏱️ **Real-Time Timer** using interrupts  
- 🖥️ **LCD Display** for user interface  
- 🎛️ **Keypad Input** for mode and time selection  
- 🔁 **Relay & Heater Control** using microcontroller logic  
- 🔔 **Buzzer Alert** when cooking ends  

---

## 🛠️ Technologies Used

- **Microcontroller**: PIC16F877A  
- **Programming Language**: Embedded C  
- **IDE**: MPLAB X IDE  
- **Compiler**: XC8  
- **Simulation Tool**: PICSimLab  

---

## 🧰 Project Requirements

### Software
- [MPLAB X IDE](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)
- [XC8 Compiler](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers)
- [PICSimLab](https://github.com/lcgamboa/picsimlab)

### Hardware (for real implementation, not simulation)
- PIC16F877A microcontroller
- 4x4 Keypad
- 16x2 LCD
- Relay Module
- Heating Element (simulated)
- Buzzer
- Power Supply

---

## 📊 System Flow

```text
1. Display available cooking modes on LCD
2. Wait for user input via keypad
3. On valid mode, prompt for cooking time
4. Start cooking process: heater ON, timer ON
5. Use interrupts to countdown time
6. When time reaches 0, stop heater and activate buzzer
7. Return to main menu
