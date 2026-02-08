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

   **NOTE ON LIBRARY:**
   The "ESP RainMaker" library is BUILT-IN to the ESP32 Board package.
   You do NOT need to install it separately from the Library Manager.

BOARD CONFIGURATION (CRITICAL!):
--------------------------------
Select the following settings in the Tools menu:

1. Board: "ESP32C3 Dev Module" (or "ESP32-C3 SuperMini" if available)
2. USB CDC On Boot: "Enabled"
   *** THIS IS THE MOST IMPORTANT SETTING ***
   Since you are using the native USB port on the C3 Mini, this MUST be ENABLED
   to see any text (like the QR code) in the Serial Monitor.

3. Partition Scheme: "RainMaker" (if available).
   - IF YOU ARE USING "XIAO ESP32C3" OR SIMILAR:
     You MUST select a larger partition scheme. The "Default" one is too small.
     Select "Huge APP (3MB No OTA/1MB SPIFFS)" or "RainMaker" if listed.
     Alternatively, use "Partition Scheme: Custom" and the IDE should pick up `partitions.csv`.

4. Flash Mode: "DIO" or "QIO" (usually DIO is safer)

UPLOAD & TROUBLESHOOTING:
-------------------------
1. Connect your ESP32-C3 via USB.
2. Select the correct Port in Tools > Port.
3. Click "Upload".
4. IMMEDIATELY after upload, Open Serial Monitor (115200 baud).

**IF YOU SEE NOTHING IN SERIAL MONITOR:**
1. Make sure "USB CDC On Boot" is ENABLED in the Tools menu.
2. Press the RESET button on the ESP32-C3 board *while* the Serial Monitor is open.

**IF YOU SEE "No core dump partition found!" OR IT HANGS:**
1. This means your Partition Scheme is too small.
2. Go to Tools > Erase All Flash Before Sketch Upload > ENABLED.
3. Go to Tools > Partition Scheme > Select "Huge APP (3MB No OTA/1MB SPIFFS)".
4. Upload again.

USAGE:
------
1. Download the "ESP RainMaker" app on your phone.
2. Add a device and scan the QR code from the Serial Monitor.
3. Follow the prompts to connect the device to Wi-Fi.
