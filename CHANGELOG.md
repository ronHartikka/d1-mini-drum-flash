# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Initial D1 Mini (ESP8266) implementation
- PWM brightness ramping based on pulse duration
- PC817 optocoupler support for 24V drum trigger isolation
- Fast pulse detection (50-200ms pulses)
- Configurable brightness parameters (MIN_BRIGHTNESS, MAX_BRIGHTNESS, RAMP_TIME_MS)
- D1 Mini pin label definitions (D1, D2) for easier wiring
- Comprehensive README with wiring diagrams and troubleshooting
- STATUS.md for tracking development progress

### Technical Details
- 10-bit PWM resolution (0-1023 range)
- 1kHz PWM frequency
- ESP8266 analogWrite() implementation
- No delay in main loop for responsive detection

[Unreleased]: https://github.com/ronHartikka/d1-mini-drum-flash/compare/HEAD
