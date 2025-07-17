# IC Tester and IV Curve Plotter

## Overview

A versatile embedded hardware project built using Arduino Mega 2560, designed to identify, verify, and test digital ICs (integrated circuits) and also plot IV characteristics of two-port devices such as diodes, thermistors, and LEDs. The system features a 2.4" TFT touchscreen interface, a 20-pin ZIF socket for IC placement, and an SD card for storing truth tables and test patterns.

---

## Key Features

### 1. **Digital IC Testing**

* **Functionality**: Automatically detects and tests digital ICs (e.g., 7400 series) using truth table logic patterns stored on an SD card.
* **Test Vector Format**: Each test case includes input/output states (e.g., `0000HHG000000V`) where:

  * `0`/`1`: Input low/high
  * `H`/`L`: Expected high/low output
  * `V`/`G`: Power and ground pins
* **Accuracy**: Over 95% reliable identification and fault detection of tested ICs.
* **IC Support**: Easily extendable by adding `.txt` files to the SD card. Supports >30 IC types.

### 2. **IV Curve Plotting (Analog Measurement Mode)**

* **Purpose**: Measures current-voltage (IV) characteristics of components like LEDs, diodes, thermistors.
* **PWM Filtering**: Uses Timer2 PWM (64kHz) filtered through RC (100Ω + 100μF) to generate smooth analog voltage.
* **Analog Readings**:

  * `A0`: Measures filtered PWM voltage (V\_in)
  * `A1`: Measures voltage across device under test (V\_out)
  * Current `I = (V_in - V_out) / R`
* **Processing App**: Desktop application plots I-V graph in real time, allowing colored overlays and adjustable ranges.
* **Auto-Protection**: Test stops if current exceeds max threshold (e.g., 10mA).

---

## Hardware Used

* Arduino Mega 2560
* 2.4" ILI9341 TFT LCD with Touch + SD Card
* 20-pin ZIF Socket
* 4GB MicroSDHC Card
* Female/Male Header Strips
* 2× WS2812B LEDs (optional)
* 2× 100nF Capacitors (optional)
* 1× 180Ω Resistor (optional)
* 100Ω resistor + 100μF capacitor (for RC filter)

---

## How it Works

### IC Tester Logic Flow:

1. Parse test file from SD card (IC number, name, pin count, test cases).
2. For each test case:

   * Set Vcc and GND pins.
   * Configure inputs as specified.
   * Trigger CLK pulse (if present).
   * Read outputs and compare against expected logic.
3. Mark IC as valid/defective based on test case results.

### IV Curve Plotter Flow:

1. Start PWM duty cycle at 0, increase to 100% in 256 steps.
2. At each step:

   * Wait for voltage to stabilize.
   * Read A0 and A1.
   * Compute current `I`, voltage `V`.
3. Plot I-V curve on Processing GUI.

---

## Software Components

* **Arduino Sketches**:

  * `main_tester.ino` – Contains `testCase()` and SD card logic.
  * `IVcurve_v1_0.ino` – Controls PWM generation and analog reading.
* **Processing App**:

  * `IVcurve_v1_0.pde` – Receives serial data and plots curves.

---

## Getting Started

1. Upload Arduino sketches to Mega.
2. Format SD card and add `.txt` IC definition files.
3. Power up device, insert IC into ZIF socket.
4. Use touchscreen to select and run test.
5. For IV measurement:

   * Connect component.
   * Run Processing app.
   * Click on color to begin measurement.

---

## Results

* **Detection Accuracy**: >95%
* **Supported ICs**: 30+ (Extensible)
* **PWM Ripple**: <1% with RC filter
* **Safe Current Limiting**: Yes, auto-stop on overcurrent
* **Resolution**: 8-bit (256-step PWM sweep)

---

## Future Improvements

* Add EEPROM storage for last tested IC.
* Touchscreen input for manual test editing.
* Wireless (BLE/WiFi) IC library updates.

---

## Author

Prasun Sharma

