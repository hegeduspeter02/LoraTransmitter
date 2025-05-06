# LoRa Transmitter

## Project setup

1. Install Make (through GnuWin): <https://gnuwin32.sourceforge.net/packages/make.htm>
2. Install Arduino CLI: <https://docs.arduino.cc/arduino-cli/installation/>\
*Optional:* Install Arduino IDE: <https://www.arduino.cc/en/software/>

3. Install the esp32 platform
    - Using CLI: `arduino-cli core install esp32:esp32`
    - Using Arduino IDE:
      - Open **Boards Manager** and search for "esp32" & install it

4. Install libraries
    - Using CLI:
      - LoRa: `arduino-cli lib install "LoRa"`
      - BME 280: `arduino-cli lib install "BME280"`
      - Battery Sense: `arduino-cli lib install "Battery Sense"`
      - Arduino JSON: `arduino-cli lib install "ArduinoJson"`
      - CayenneLPP: `arduino-cli lib install "CayenneLPP"`
    - Using Arduino IDE:
      - Open **Library Manager** and search for the libraries above & install them

5. Build the project
    - Using CLI: `make` or `make compile`
    - Using Arduino IDE: Use the Verify button

6. Upload the project to the MCU
    - Using CLI:
      - set the correct PORT in the Makefile
      - `make upload`
    - Using Arduino IDE:
      - Set the board to DOIT ESP32 DEVKIT V1 and select the correct COM port
      - Use the Upload button
