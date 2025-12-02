# D1 Mini Drum Flash Project Status

## Current Status
Initial code written and ready for compilation/testing. This is a port of the ESP32 version adapted for D1 Mini (ESP8266).

## What We've Done
1. ✅ Ported code from ESP32 to D1 Mini (ESP8266)
2. ✅ Adapted PWM functions for ESP8266 (analogWrite with 10-bit resolution)
3. ✅ Updated pin definitions to use D1 Mini pin labels (D1, D2)
4. ✅ Adjusted brightness values for 10-bit PWM range (0-1023 vs 0-255)

## Next Steps
1. Compile the code for D1 Mini
2. Upload to D1 Mini board and test
3. Adjust brightness ramping parameters if needed
4. Set up Git repository
5. Push to GitHub

## Important Info

### Hardware
- WeMos D1 Mini (ESP8266 ESP-12F)
- D2 (GPIO4): PC817 optocoupler output (with INPUT_PULLUP)
- D1 (GPIO5): LED output
- PC817 input: 24V circuit → 1.2kΩ resistor → PC817 LED (19mA)

### Arduino Board Configuration
- Board: "LOLIN(WEMOS) D1 R2 & mini" or "Generic ESP8266 Module"
- Upload Speed: 921600
- CPU Frequency: 80 MHz
- Flash Size: 4MB (FS:2MB OTA:~1019KB)

### PWM Parameters (in code)
Located around lines 24-27 in d1-mini-drum-flash.ino:
- `PWM_FREQ`: 1000 Hz (ESP8266 standard)
- `PWM_RANGE`: 1023 (10-bit resolution)
- `MIN_BRIGHTNESS`: 80 (starting brightness, 0-1023)
- `MAX_BRIGHTNESS`: 1023 (peak brightness, 0-1023)
- `RAMP_TIME_MS`: 300 (milliseconds to reach max brightness)

These can be adjusted to change how the brightness ramping behaves.

## Problem We're Solving
Longer flashes from the 24V drum trigger circuit should appear brighter than short flashes. The PWM version gradually increases LED brightness based on how long the pulse has been active.

## Key Differences from ESP32 Version
- Uses `analogWrite()` instead of `ledcWrite()`
- 10-bit PWM (0-1023) instead of 8-bit (0-255)
- PWM frequency set to 1kHz (typical for ESP8266) instead of 5kHz
- Uses D1 Mini pin labels (D1, D2) for clarity
