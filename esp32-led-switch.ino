/*
 * ESP32 LED Switch Control via PC817 Optocoupler with PWM Brightness Ramping
 *
 * This sketch detects fast pulses from a PC817 optocoupler and uses PWM
 * to gradually increase LED brightness based on pulse duration.
 * Longer pulses appear brighter!
 *
 * Hardware connections:
 * - GPIO4: PC817 output (Collector to GPIO4, Emitter to GND)
 * - GPIO5: LED output (LED with appropriate current-limiting resistor)
 *
 * PC817 Input: 24V circuit → 1.2kΩ → PC817 LED (19mA)
 *
 * Operation:
 * - When PC817 conducts (24V pulse active), GPIO4 reads LOW and LED brightness ramps up
 * - When PC817 is off, GPIO4 reads HIGH (pullup) and LED turns OFF
 * - Longer pulses reach higher brightness levels
 * - Optimized for fast pulse detection (50-200ms pulses at 0.5-2.5 Hz)
 */

// Define pin numbers
const int SWITCH_PIN = 4;  // GPIO4 for switch input
const int LED_PIN = 5;     // GPIO5 for LED output

// PWM configuration
const int PWM_FREQ = 5000;      // PWM frequency in Hz
const int PWM_RESOLUTION = 8;   // 8-bit resolution (0-255)

// Brightness ramping configuration
const int MIN_BRIGHTNESS = 20;   // Starting brightness (0-255)
const int MAX_BRIGHTNESS = 255;  // Maximum brightness (0-255)
const int RAMP_TIME_MS = 300;    // Time to reach max brightness (milliseconds)

// Tracking variables
unsigned long pulseStartTime = 0;
bool pulseActive = false;

void setup() {
  // Configure GPIO4 as input with internal pullup resistor enabled
  // The pullup resistor keeps the pin HIGH when PC817 is off
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  // Configure PWM for LED control (newer ESP32 core 3.x API)
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION);

  // Initialize LED to OFF state
  ledcWrite(LED_PIN, 0);
}

void loop() {
  // Read the current state of the PC817 optocoupler
  // When 24V pulse is active (PC817 conducts): reads LOW (0)
  // When 24V pulse is off (PC817 open): reads HIGH (1) due to pullup
  int switchState = digitalRead(SWITCH_PIN);

  if (switchState == LOW) {
    // Pulse is active
    if (!pulseActive) {
      // Pulse just started - record start time
      pulseStartTime = millis();
      pulseActive = true;
    }

    // Calculate how long the pulse has been active
    unsigned long pulseDuration = millis() - pulseStartTime;

    // Calculate brightness based on pulse duration (gradual ramp)
    int brightness;
    if (pulseDuration >= RAMP_TIME_MS) {
      // Pulse has been active long enough - use max brightness
      brightness = MAX_BRIGHTNESS;
    } else {
      // Ramp up brightness proportionally to pulse duration
      // brightness = MIN + (MAX - MIN) * (duration / rampTime)
      brightness = MIN_BRIGHTNESS +
                   ((MAX_BRIGHTNESS - MIN_BRIGHTNESS) * pulseDuration) / RAMP_TIME_MS;
    }

    // Set LED brightness using PWM
    ledcWrite(LED_PIN, brightness);

  } else {
    // Pulse is not active - turn LED off
    pulseActive = false;
    ledcWrite(LED_PIN, 0);
  }

  // No delay - loop runs as fast as possible to catch short pulses and provide smooth ramping
}
