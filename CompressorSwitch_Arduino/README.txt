COMPRESSOR SWITCH - ARDUINO IDE SETUP
=======================================

This folder contains the Arduino sketch for the Compressor Switch using ESP RainMaker.

FILES:
------
1. CompressorSwitch_Arduino.ino : The main code file.
2. partitions.csv               : The custom partition table required for RainMaker.

PREREQUISITES:
--------------
1. Install Arduino IDE (v2.0+ recommended).
2. Install ESP32 Board Support:
   - Go to File > Preferences.
   - Add this URL to "Additional Boards Manager URLs":
     https://espressif.github.io/arduino-esp32/package_esp32_index.json
   - Go to Tools > Board > Boards Manager.
   - Search for "esp32" by Espressif Systems and install it.

3. Install ESP RainMaker Library:
   - Go to Sketch > Include Library > Manage Libraries.
   - Search for "ESP RainMaker" by Espressif and install the latest version.

BOARD CONFIGURATION:
--------------------
Select the following settings in the Tools menu:

1. Board: "ESP32C3 Dev Module" (or "ESP32-C3 SuperMini" if available)
2. USB CDC On Boot: "Enabled"
   (IMPORTANT: This allows Serial output over the USB port on the C3)
3. Flash Mode: "DIO" or "QIO" (usually DIO is safer)
4. Partition Scheme: "RainMaker" (if available).
   - If "RainMaker" is NOT available, select "Custom" or "Default 4MB with spiffs (1.2MB APP/1.5MB SPIFFS)" might work but RainMaker usually needs larger app partitions.
   - To use the provided `partitions.csv`:
     - Select "Huge APP (3MB No OTA/1MB SPIFFS)" if you don't need OTA updates.
     - OR if your board definition supports "Custom":
       Copy `partitions.csv` to the sketch folder (it's already here).
       Select "Partition Scheme: Custom".
       The IDE should pick up the csv file.

UPLOAD:
-------
1. Connect your ESP32-C3 via USB.
2. Select the correct Port in Tools > Port.
3. Click "Upload".
4. Open Serial Monitor (115200 baud) to see the QR code for provisioning.

USAGE:
------
1. Download the "ESP RainMaker" app on your phone.
2. Add a device and scan the QR code from the Serial Monitor.
3. Follow the prompts to connect the device to Wi-Fi.
