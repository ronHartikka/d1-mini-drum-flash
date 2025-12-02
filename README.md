# D1 Mini Drum Flash

LED flash controller for drum triggers using a WeMos D1 Mini (ESP8266) and PC817 optocoupler. Converts 24V drum trigger pulses into LED flashes with **brightness proportional to pulse duration** - longer hits flash brighter!

## Features

- Fast pulse detection (50-200ms pulses at 0.5-2.5 Hz)
- PWM brightness ramping - longer pulses = brighter flashes
- Optocoupler isolation between 24V drum circuit and microcontroller
- No delay in main loop for responsive pulse detection
- Simple 2-wire connection to drum trigger circuit

## Hardware Requirements

### Components
- **WeMos D1 Mini** (or compatible ESP8266 ESP-12F board)
- **PC817 Optocoupler** (4-pin DIP)
- **1.2kΩ resistor** (for PC817 LED input, provides ~19mA at 24V)
- **LED + current-limiting resistor** (value depends on LED specs)
- **24V drum trigger circuit** (pulse output)

### Pin Connections

```
24V Drum Circuit:
  24V+ ──[1.2kΩ]──┬──> PC817 pin 1 (Anode)
                  │
  Trigger Pulse ──┘

  GND ────────────> PC817 pin 2 (Cathode)

D1 Mini Connections:
  D2 (GPIO4) ─────> PC817 pin 4 (Collector)
  GND ────────────> PC817 pin 3 (Emitter)
  D1 (GPIO5) ─────> LED + Resistor ──> GND
```

### PC817 Pinout (looking at top of chip)
```
  ┌───────┐
  │ ●     │
1─┤ A   C ├─4  (Pin 1: Anode, Pin 4: Collector)
2─┤ K   E ├─3  (Pin 2: Cathode, Pin 3: Emitter)
  └───────┘
```

## How It Works

1. **Drum trigger fires** → 24V pulse activates PC817 LED
2. **PC817 conducts** → D2 pin reads LOW (pulled to GND through optocoupler)
3. **PWM ramps up** → LED brightness increases gradually over 300ms
4. **Longer pulse = brighter flash** → Short hits are dimmer, hard hits are brighter
5. **Pulse ends** → LED immediately turns off

The internal pullup resistor on D2 keeps the pin HIGH when the optocoupler is off.

## Software Setup

### Requirements
- Arduino IDE or arduino-cli
- ESP8266 board support installed

### Arduino Board Manager Setup
1. Add ESP8266 board manager URL: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
2. Install "esp8266" boards package
3. Select board: **"LOLIN(WEMOS) D1 R2 & mini"** or **"Generic ESP8266 Module"**

### Configuration Options

In `d1-mini-drum-flash.ino`, adjust these constants to tune behavior:

```cpp
// Lines 24-27
const int PWM_FREQ = 1000;       // PWM frequency (Hz)
const int MIN_BRIGHTNESS = 80;   // Starting brightness (0-1023)
const int MAX_BRIGHTNESS = 1023; // Maximum brightness (0-1023)
const int RAMP_TIME_MS = 300;    // Time to reach max brightness (ms)
```

**Tuning Tips:**
- Increase `RAMP_TIME_MS` for slower, more gradual brightness changes
- Increase `MIN_BRIGHTNESS` to make short hits more visible
- Decrease `MAX_BRIGHTNESS` if LED is too bright at peak

### Upload Instructions

1. Connect D1 Mini via USB
2. Select the correct serial port
3. Click Upload or use arduino-cli:
   ```bash
   arduino-cli compile --fqbn esp8266:esp8266:d1_mini .
   arduino-cli upload -p /dev/ttyUSB0 --fqbn esp8266:esp8266:d1_mini .
   ```

## Technical Details

### PWM Configuration
- **Resolution**: 10-bit (0-1023 values)
- **Frequency**: 1000 Hz
- **Method**: ESP8266 `analogWrite()` function

### Pin Definitions
- **D2 (GPIO4)**: Input with internal pullup enabled
- **D1 (GPIO5)**: PWM output for LED control

### Key Differences from ESP32 Version
- Uses `analogWrite()` instead of ESP32's `ledcWrite()`
- 10-bit PWM range (0-1023) vs ESP32's 8-bit (0-255)
- Lower PWM frequency (1kHz vs 5kHz) - still flicker-free
- D1 Mini pin labels for easier wiring

## Troubleshooting

**LED doesn't light up:**
- Check LED polarity and current-limiting resistor
- Verify D1 (GPIO5) connection
- Test with a simple blink sketch first

**Pulses not detected:**
- Verify PC817 is conducting (check with multimeter)
- Ensure 1.2kΩ resistor is providing ~19mA to PC817 LED
- Check D2 (GPIO4) connection to pin 4 of PC817
- Verify GND connection between D1 Mini and PC817 pin 3

**LED flickers or behaves erratically:**
- Ensure common ground between drum circuit and D1 Mini (through PC817)
- Check for loose connections
- Verify 24V circuit provides clean pulses

**Upload fails:**
- Close Arduino IDE Serial Monitor if open
- Try different USB cable
- Press Reset button on D1 Mini before upload
- Check driver installation (CH340 or CP2102 depending on board)

## License

Open source - use freely for any purpose.

## Related Projects

- [esp32-led-switch](https://github.com/ronHartikka/esp32-led-switch) - ESP32 version of this project
