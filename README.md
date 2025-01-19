# ESP32 Thermal Imaging Display with AMG8831

This project demonstrates the use of an ESP32 microcontroller with an AMG8831 thermal sensor and a TFT display. The system reads temperature data from the sensor, displays the 8x8 thermal matrix on the screen, and highlights the minimum and maximum temperatures in real-time.

---

## Features
- Real-time thermal imaging with an 8x8 grid.
- Displays minimum and maximum temperatures dynamically.
- Intuitive visualization using a color palette to represent temperature variations.

---

## Requirements

### Hardware
- **ESP32-2432S028 CYD Board**
- **AMG8831 Thermal Sensor** (connected via I2C: SDA=IO27, SCL=IO22)
- **TFT Display** compatible with the ESP32 and configured via the `TFT_eSPI` library.

### Software
- [PlatformIO](https://platformio.org/) for development and upload.
- Libraries:
  - `TFT_eSPI` (Version 2.5.33 or compatible)
  - `Adafruit_AMG88xx` (directly included from GitHub)

---

## Project Structure
- **`src/main.cpp`**: Contains the implementation code for reading sensor data and displaying it on the TFT.
- **`platformio.ini`**: Defines the ESP32 environment, dependencies, and display configuration.
- **`.gitignore`**: Standard Git ignore file for excluding build and temporary files.

---

## Setup and Usage

### Step 1: Hardware Connections
1. Connect the AMG8831 sensor to the ESP32:
   - **SDA** -> IO27
   - **SCL** -> IO22
2. Attach the TFT display directly to the ESP32 board (ensure wiring matches the pin configurations in `platformio.ini`).

### Step 2: Install Dependencies
Make sure to install the required libraries using PlatformIO:
```bash
platformio lib install bodmer/TFT_eSPI@^2.5.33
platformio lib install https://github.com/adafruit/Adafruit_AMG88xx.git
```

### Step 3: Upload Firmware
1. Open the project in [Visual Studio Code](https://code.visualstudio.com/) with the PlatformIO plugin.
2. Configure the correct COM port for the ESP32.
3. Build and upload the firmware:
   ```bash
   platformio run --target upload
   ```

### Step 4: Monitor Output
Open the serial monitor in PlatformIO to debug or observe logs (default baud rate: `115200`).

---

## Display Details
- **Color Palette**: The display uses a gradient color scheme to represent temperature values. Blue indicates cooler areas, while red represents hotter areas.
- **Temperature Range**: Configurable between `MINTEMP` (10°C) and `MAXTEMP` (40°C).

---

## License
This project is open-source and distributed under the MIT license.

---

## Troubleshooting
- **"Sensor Error!" on Display**: Verify connections to the AMG8831 sensor and ensure it is powered correctly.
- **No Output on TFT**: Check the pin configurations in `platformio.ini` and ensure compatibility with your display module.

