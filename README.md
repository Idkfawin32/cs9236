# CS9236 Library

The CS9236 library provides an interface for working with the Crystal CS9236 Wavetable Synthesizer Chip. It allows you to control and communicate with the chip using an Arduino or compatible microcontroller. This library provides an easy-to-use API for sending MIDI messages and commands to the Crystal CS9236.

## Installation

To use this library in your Arduino project, follow these steps:

1. In the Arduino IDE, click on "Sketch" -> "Include Library" -> "Add .ZIP Library" and select the downloaded ZIP file of the CS9236 library.

2. Now, you can include the library in your Arduino sketch by adding the following line at the top of your sketch:
   #include <CS9236.h>

## Usage

To use the CS9236 library, you'll need to create an instance of the `CS9236` class and initialize it with the appropriate parameters. I've included an example project to help demonstrate this.

## API Reference

### Constructor

- `CS9236(uint8_t rs, Stream *comm)`: Initializes an instance of the CS9236 class with the specified reset pin (`rs`) and communication stream (`comm`).

### Basic MIDI Messages

- `NoteOn(uint8_t channel, uint8_t note_number, uint8_t velocity)`: Sends a Note On message.
- `NoteOff(uint8_t channel, uint8_t note_number)`: Sends a Note Off message.
- `ProgramChange(uint8_t channel, uint8_t program)`: Sends a Program Change message.
- `SetChannelPressure(uint8_t channel, uint8_t pressure)`: Sets the channel pressure.
- `SetPitchBend(uint8_t channel, uint16_t pitchbend)`: Sets the pitch bend.
- `SetModWheel(uint8_t channel, uint8_t depth)`: Sets the modulation wheel.
- `SetVolume(uint8_t channel, uint8_t volume)`: Sets the channel volume.
- `SetPan(uint8_t channel, uint8_t value)`: Sets the pan position.
- `SetExpression(uint8_t channel, uint8_t value)`: Sets the expression.
- `SetPedal(uint8_t channel, bool pedaldown)`: Sets the pedal.
- `SetReverb(uint8_t channel, uint8_t value)`: Sets the reverb level.
- `SetChorus(uint8_t channel, uint8_t value)`: Sets the chorus level.

### RPN Messages

- `SelectRPN(uint8_t channel, uint8_t rpn)`: Selects the RPN (Registered Parameter Number).
- `SetPitchBendSensitivity(uint8_t channel, uint16_t value)`: Sets the pitch bend sensitivity.
- `SetFineTuning(uint8_t channel, uint16_t value)`: Sets the fine tuning.
- `SetCoarseTuning(uint8_t channel, uint16_t value)`: Sets the coarse tuning.

### Channel Mode Messages

- `AllSoundsOff(uint8_t channel)`: Sends an All Sounds Off message.
- `ResetAll(uint8_t channel)`: Sends a Reset All Controllers message.
- `AllNotesOff(uint8_t channel)`: Sends an All Notes Off message.

### Special Functions

- `EnablePressureRecognition()`: Enables pressure recognition.
- `DisablePressureRecognition()`: Disables pressure recognition.
- `EnableTestTone()`: Enables the test tone.
- `DisableTestTone()`: Disables the test tone.

For detailed information on the usage of each function, please refer to the header file `CS9236.h`.

## License

This library is released under the BSD License. Please see the LICENSE file for more details.