# Multi Sport Scoreboard

A real-time, wireless **Multi Sport Scoreboard System** designed to display and manage scores for multiple point-based sports using P10 LED display modules.

The system combines an **Android mobile application, Arduino UNO, Raspberry Pi, Huidu E63 LED controller, and P10 LED display panels** to provide a flexible and easy-to-operate digital scoreboard.

---

## 📌 Project Overview

Traditional sports scoreboards can be expensive, difficult to modify, and limited to a specific sport. This project develops a customizable scoreboard capable of supporting multiple sports through a single system.

The scoreboard is controlled wirelessly through an Android application. The user selects the sport and updates the score through the mobile application. Commands are transferred through Bluetooth and processed by the controller before being displayed on the large P10 LED screen.

### Supported Sports

* ⚽ Football
* ⚽ Futsal
* 🏀 Basketball
* 🏓 Table Tennis
* 🥋 Karate
* 🏑 Hockey
* 🥋 Taekwondo

> **Note:** The system is designed for point-based sports and does not currently support cricket.

---

## 🏗️ System Architecture

```text
┌──────────────────────┐
│    Android App       │
│   MIT App Inventor   │
└──────────┬───────────┘
           │
           │ Bluetooth
           ▼
┌──────────────────────┐
│      HC-05           │
│ Bluetooth Module     │
└──────────┬───────────┘
           │
           ▼
┌──────────────────────┐
│     Arduino UNO      │
│     ATmega328P       │
└──────────┬───────────┘
           │
           │ Data Communication
           ▼
┌──────────────────────┐
│    Raspberry Pi      │
│ Communication Layer  │
└──────────┬───────────┘
           │
           ▼
┌──────────────────────┐
│     Huidu E63        │
│   LED Controller     │
└──────────┬───────────┘
           │
           ▼
┌──────────────────────┐
│    P10 LED Panels    │
│   Digital Display    │
└──────────────────────┘
```

---

## 🔧 Hardware Components

| Component         | Purpose                                         |
| ----------------- | ----------------------------------------------- |
| Arduino UNO       | Main microcontroller and score-processing unit  |
| ATmega328P        | Microcontroller used by Arduino UNO             |
| HC-05 Bluetooth   | Wireless communication with Android application |
| Raspberry Pi      | Communication/middleware layer                  |
| Huidu E63         | LED display controller                          |
| P10 LED Modules   | Large-format scoreboard display                 |
| Power Supply      | Provides power to the electronic components     |
| Connecting Cables | Data and power connections                      |

---

## 💻 Software & Technologies

### Android Application

The Android application was developed using **MIT App Inventor**.

The application provides controls for:

* Selecting the sport
* Increasing scores
* Decreasing scores
* Resetting scores
* Managing game-related information
* Sending commands wirelessly

### Microcontroller Programming

The Arduino UNO is programmed to:

1. Receive commands from the communication interface.
2. Interpret the received data.
3. Update the scoreboard information.
4. Send the required information toward the display system.


## 📡 Communication

The system uses wireless communication to allow the scoreboard operator to control the display without directly interacting with the hardware.

### Communication Flow

```text
Android Application
        │
        │ Bluetooth
        ▼
      HC-05
        │
        ▼
    Arduino UNO
        │
        ▼
    P10 Display
```

The HC-05 module provides Bluetooth communication between the Android application and the hardware system.

The standard serial communication configuration used in the project includes a **9600 baud rate**.

---

## 🎮 How the System Works

### Step 1 — Select Sport

The operator opens the Android application and selects the required sport.

### Step 2 — Enter/Update Score

The operator uses the application controls to increase, decrease, or reset the score.

### Step 3 — Wireless Transmission

The application sends the selected command through Bluetooth using the HC-05 module.

### Step 4 — Command Processing

The Arduino UNO receives and processes the command.

### Step 5 — Communication

The processed scoreboard information is transferred through the Raspberry Pi communication layer.

### Step 6 — Display

The Huidu E63 controller receives the display information and drives the P10 LED modules.

### Step 7 — Real-Time Update

The updated score becomes visible on the scoreboard.

---

## ⭐ Key Features

* Multi-sport support
* Wireless scoreboard control
* Android-based user interface
* Large P10 LED display
* Real-time score updates
* Centralized scoreboard control
* Modular hardware design
* Easy-to-use interface
* Low-cost implementation compared with many commercial scoreboard systems
* Expandable architecture

---

## 🎯 Project Objectives

The main objectives of this project are:

1. To design and develop a digital scoreboard for multiple sports.
2. To provide wireless control through an Android application.
3. To display scores clearly on large P10 LED panels.
4. To reduce dependence on manually operated scoreboards.
5. To create a flexible system that can be adapted for different sports.
6. To integrate embedded systems, wireless communication, and LED display technologies into a single platform.

---

## 🧩 Technologies Used

```text
Hardware:
- Arduino UNO
- ATmega328P
- HC-05 Bluetooth
- Raspberry Pi
- Huidu E63
- P10 LED Modules

Software:
- Arduino IDE
- MIT App Inventor
- HD2018
- Huidu SDK
- C#
- Raspberry Pi Software

Communication:
- Bluetooth
- Serial Communication
- LED Display Data Communication
```

---

## 📂 Suggested Repository Structure

```text
Multi-Sport-Scoreboard/
│
├── Android-App/
│   └── MIT-App-Inventor/
│
├── Arduino/
│   ├── source-code/
│   └── libraries/
│
├── Raspberry-Pi/
│   └── communication/
│
├── Huidu/
│   └── configuration/
│
├── Hardware/
│   ├── circuit-diagram/
│   ├── PCB/
│   └── wiring/
│
├── Documentation/
│   ├── Final-Year-Project-Report/
│   ├── Presentation/
│   └── Poster/
│
├── Images/
│   └── project-images/
│
└── README.md
```

---

## 🚀 Future Improvements

The system can be further improved by adding:

* Automatic power-failure detection
* EEPROM-based state recovery
* 12V Li-ion battery backup
* Battery Management System (BMS)
* Solar charging capability
* Wi-Fi-based remote control
* Internet/cloud-based scoreboard management
* Tournament management functionality
* Automatic game timers
* Player/team name configuration
* Additional sports
* Web-based scoreboard control
* Statistics and match-history storage

---

## 📸 Project Demonstration

Add project photographs and demonstration videos to this section.

```text
/images
    ├── scoreboard.jpg
    ├── android-app.jpg
    ├── hardware.jpg
    ├── p10-display.jpg
    └── system-setup.jpg
```

---

## 👨‍💻 Project Team

**Final Year Project — Multi Sport Scoreboard**

Developed as a Bachelor of Computer Engineering Final Year Project.

### Team Members

* Muhammad Usman
* Subhan
* Saad

---

## 🎓 Academic Project

This project was developed as part of the **Bachelor of Computer Engineering** program.

**Project Type:** Final Year Project (FYP)
**Domain:** Embedded Systems / IoT / Digital Display Systems
**Application:** Sports Facilities & Indoor/Outdoor Sports Events

---

## 📜 License

This project is developed for academic and educational purposes.

If you want to use, modify, or distribute the project commercially, please contact the project authors.

---

## ⭐ Acknowledgements

We would like to thank our project supervisor, faculty members, and everyone who provided technical guidance and support throughout the development of this project.

---

## 📬 Contact

For questions, collaboration, or technical discussion regarding the project, please contact the project authors through GitHub or LinkedIn.
