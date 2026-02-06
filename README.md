# ESP-Compressor-switch

This project implements a smart switch for an air compressor using an ESP32-C3 and ESP RainMaker. It integrates with Google Home and supports scheduling.

## Features

- **Remote Control**: Turn the compressor ON/OFF via the ESP RainMaker phone app.
- **Google Home Integration**: Link your RainMaker account to Google Home to use voice commands ("Hey Google, turn on the compressor").
- **Scheduling**: Set daily schedules (e.g., ON at 8:00 AM, OFF at 5:00 PM) via the app.
- **Safety**:
  - **Power Loss Recovery**: If power is lost, the device restarts in the **OFF** state to prevent unexpected operation.

## Hardware Setup

1.  **Microcontroller**: ESP32-C3 DevKit (or compatible).
2.  **Relay**: Connect a Solid State Relay (SSR) or Mechanical Relay Module to the ESP32-C3.
    - **Control Pin**: `GPIO 4` (connected to Relay Input).
    - **Ground**: Common ground.
    - **Power**: 3.3V or 5V as required by your relay module.

## Installation

1.  **Build and Flash**:
    - Open this project in VSCode with PlatformIO.
    - Connect your ESP32-C3 via USB.
    - Click "Upload".

2.  **Provisioning (First Time Setup)**:
    - Install the **ESP RainMaker** app on your phone (iOS/Android).
    - Open the app and sign in (or create an account).
    - Click "Add Device".
    - The app will search for the device via Bluetooth (ensure Bluetooth is on).
    - Follow the prompts to select your Wi-Fi network and enter the password.
    - Once claimed, the device will appear in your list.

3.  **Google Home Setup**:
    - Open the Google Home app.
    - Add a device -> Works with Google.
    - Search for "ESP RainMaker".
    - Log in with the same account used in the RainMaker app.
    - The "Compressor" switch will appear in your home.

## Usage

- **Manual**: Use the toggle in the RainMaker app or Google Home.
- **Schedule**: In the RainMaker app, go to the device settings -> "Schedules" to set automatic timers.
