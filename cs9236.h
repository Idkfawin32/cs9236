/*
 * Copyright (C) 2023 Trevor Hall
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
#include "Stream.h"
#ifndef CS9236_H_
#define CS9236_H_

#define CS_ACTIVE_SENSE 0xFE
#define CS_SYSTEM_RESET 0xFF

#define CS_NOTE_ON 0x90
#define CS_NOTE_OFF 0x80

#define CS_VOLUME 0xB0
#define CS_PROGRAM_CHANGE 0xC0
#define CS_CHANNEL_PRESSURE 0xD0
#define CS_PITCH_BEND 0xE0

#define CS_CC_MODWHEEL 0x01
#define CS_CC_RPN_MSB 0x06
#define CS_CC_RPN_LSB 0x26
#define CS_CC_VOLUME 0x07
#define CS_CC_PAN 0x0A
#define CS_CC_EXPRESSION 0x0B
#define CS_CC_PEDAL 0x40
#define CS_CC_REVERB 0x5B
#define CS_CC_CHORUS 0x5D

#define CS_RPN_PITCHBEND_SENSITIVITY 0x00
#define CS_RPN_FINE_TUNING 0x01
#define CS_RPN_COARSE_TUNING 0x02

#define CS_ALL_SOUNDS_OFF 0x78
#define CS_RESET_ALL 0x79
#define CS_ALL_NOTES_OFF 0x7B
#define CS_OMNI_MODE_OFF 0x7C
#define CS_OMNI_MODE_ON 0x7D
#define CS_MONO_MODE_ON 0x7E
#define CS_POLY_MODE_ON 0x7F


class CS9236 {
  public:
    CS9236(uint8_t rs, Stream * comm);

    void Init();
    void Shutdown();
    void SystemReset();
    void Poll();
    void NoteOn(uint8_t channel, uint8_t note_number, uint8_t velocity);
    void NoteOff(uint8_t channel, uint8_t note_number);
    void ProgramChange(uint8_t channel, uint8_t program);
    void SetChannelPressure(uint8_t channel, uint8_t pressure);
    void SetPitchBend(uint8_t channel, uint16_t pitchbend);
    void SetModWheel(uint8_t channel, uint8_t depth);
    void SetVolume(uint8_t channel, uint8_t volume);
    void SetPan(uint8_t channel, uint8_t value); //0 - left, 64 - center, 127 - right
    void SetExpression(uint8_t channel, uint8_t value);
    void SetPedal(uint8_t channel, bool pedaldown); // 0 through 63 = off, 64 through 127 =on | Sostenuto
    void SetReverb(uint8_t channel, uint8_t value);
    void SetChorus(uint8_t channel, uint8_t value);

    void SelectRPN(uint8_t channel, uint8_t rpn);
    void SetPitchBendSensitivity(uint8_t channel, uint16_t value); //RPN messages
    void SetFineTuning(uint8_t channel, uint16_t value);
    void SetCoarseTuning(uint8_t channel, uint16_t value);

    //channel mode messages
    void AllSoundsOff(uint8_t channel);
    void ResetAll(uint8_t channel);
    void AllNotesOff(uint8_t channel);

    void EnablePressureRecognition();//F0H 00H 01H 02H 01H 01H 01H F7H
    void DisablePressureRecognition();//F0H 00H 01H 02H 01H 01H 02H F7H

    void EnableTestTone();//F0H 00H 01H 02H 01H 01H 03H F7H
    void DisableTestTone();//F0H 00H 01H 02H 01H 01H 04H F7H
  private:
    uint8_t _rs;
    Stream * _comm; 
};
#endif