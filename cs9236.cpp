/*
 * Copyright (C) 2023 Trevor Hall
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
#include <Arduino.h>
#include "cs9236.h"

CS9236::CS9236(uint8_t rs, Stream * comm) {
  //constructor
  _rs = rs;
  _comm = comm;
}

void CS9236::Init(){
  digitalWrite(_rs, LOW);
  delay(1);
  digitalWrite(_rs, HIGH);
}
void CS9236::Shutdown(){
  digitalWrite(_rs, LOW);
}
void CS9236::SystemReset(){
  _comm->write(CS_SYSTEM_RESET);
}
void CS9236::Poll(){ //For active sensing, if Active Sensing is on, either a note/message, or this polling message must be sent no later than 372 ms, or else the All sounds off and reset all controllers function will be executed
  _comm->write(CS_ACTIVE_SENSE);
}
void CS9236::NoteOn(uint8_t channel, uint8_t note_number, uint8_t velocity){
  if(channel > 15) return; //only channels 0 through 15 are allowed
  uint8_t midipacket[3] = {CS_NOTE_ON | channel, note_number, velocity};;
  _comm->write(midipacket, 4);
}
void CS9236::NoteOff(uint8_t channel, uint8_t note_number){
  if(channel > 15) return;
  uint8_t midipacket[3] = {CS_NOTE_OFF | channel, note_number, 0x00};
  _comm->write(midipacket, 3);
}
void CS9236::ProgramChange(uint8_t channel, uint8_t program){  
  if(channel > 15) return;
  uint8_t midipacket[2] = {CS_PROGRAM_CHANGE | channel, program};
  _comm->write(midipacket, 2);
}
void CS9236::SetChannelPressure(uint8_t channel, uint8_t pressure){  
  if(channel > 15) return;
  uint8_t midipacket[2] = {CS_CHANNEL_PRESSURE | channel, pressure};
  _comm->write(midipacket, 2);
}
void CS9236::SetPitchBend(uint8_t channel, uint16_t pitchbend){  
  if(channel > 15) return;
  uint8_t midipacket[3] = {CS_PITCH_BEND | channel, (pitchbend >> 8) & 0xff, pitchbend & 0xff};
  _comm->write(midipacket, 3);
}
void CS9236::SetModWheel(uint8_t channel, uint8_t depth){
  if(channel > 15) return;
  uint8_t midipacket[3] = {0xB0 | channel, CS_CC_MODWHEEL, depth};
  _comm->write(midipacket, 3);
}
void CS9236::SetVolume(uint8_t channel, uint8_t volume){
  if(channel > 15) return;
  uint8_t midipacket[3] = {0xB0 | channel, CS_CC_VOLUME, volume};
  _comm->write(midipacket, 3);
}
void CS9236::SetPan(uint8_t channel, uint8_t value) {//0 - left, 64 - center, 127 - right
  if(channel > 15) return;
  uint8_t midipacket[3] = {0xB0 | channel, CS_CC_PAN, value};
  _comm->write(midipacket, 3);
}
void CS9236::SetExpression(uint8_t channel, uint8_t value){
  if(channel > 15) return;
  uint8_t midipacket[3] = {0xB0 | channel, CS_CC_EXPRESSION, value};
  _comm->write(midipacket, 3);
}
void CS9236::SetPedal(uint8_t channel, bool pedaldown){ // 0 through 63 = off, 64 through 127 =on | Sostenuto
  if(channel > 15) return;
  uint8_t midipacket[3] = {0xB0 | channel, CS_CC_PEDAL, pedaldown ? 0x7f : 0x00};
  _comm->write(midipacket, 3);
}
void CS9236::SetReverb(uint8_t channel, uint8_t value){
  if(channel > 15) return;
  uint8_t midipacket[3] = {0xB0 | channel, CS_CC_REVERB, value};
  _comm->write(midipacket, 3);
}
void CS9236::SetChorus(uint8_t channel, uint8_t value){
  if(channel > 15) return;
  uint8_t midipacket[3] = {0xB0 | channel, CS_CC_CHORUS, value};
  _comm->write(midipacket, 3);
}
 
//RPN messages
void CS9236::SelectRPN(uint8_t channel, uint8_t rpn){
  if(channel > 15) return;
  uint8_t msbpacket[3] = {0xB0 | channel, 0x65, 0x00};
  _comm->write(msbpacket, 3);
  uint8_t lsbpacket[3] = {0xB0 | channel, 0x64, rpn};
  _comm->write(lsbpacket, 3);
}
void CS9236::SetPitchBendSensitivity(uint8_t channel, uint16_t value){
  SelectRPN(channel, CS_RPN_PITCHBEND_SENSITIVITY);
  uint8_t msbpacket[3] = {0xB0 | channel, CS_CC_RPN_MSB, (value >> 8)};
  _comm->write(msbpacket, 3);
  uint8_t lsbpacket[3] = {0xB0 | channel, CS_CC_RPN_LSB, value & 0xff};
  _comm->write(lsbpacket, 3);
}
void CS9236::SetFineTuning(uint8_t channel, uint16_t value){
  SelectRPN(channel, CS_RPN_FINE_TUNING);
  uint8_t msbpacket[3] = {0xB0 | channel, CS_CC_RPN_MSB, (value >> 8)};
  _comm->write(msbpacket, 3);
  uint8_t lsbpacket[3] = {0xB0 | channel, CS_CC_RPN_LSB, value & 0xff};
  _comm->write(lsbpacket, 3);
}
void CS9236::SetCoarseTuning(uint8_t channel, uint16_t value){
  SelectRPN(channel, CS_RPN_COARSE_TUNING);
  uint8_t msbpacket[3] = {0xB0 | channel, CS_CC_RPN_MSB, (value >> 8)};
  _comm->write(msbpacket, 3);
  uint8_t lsbpacket[3] = {0xB0 | channel, CS_CC_RPN_LSB, value & 0xff};
  _comm->write(lsbpacket, 3);
}

//channel mode messages
void CS9236::AllSoundsOff(uint8_t channel){
  if(channel > 15) return;
  uint8_t midipacket[3] = {0xB0 | channel, CS_ALL_SOUNDS_OFF, 0x00};
  _comm->write(midipacket, 3);
}
void CS9236::ResetAll(uint8_t channel){
  if(channel > 15) return;
  uint8_t midipacket[3] = {0xB0 | channel, CS_RESET_ALL, 0x00};
  _comm->write(midipacket, 3);
}
void CS9236::AllNotesOff(uint8_t channel){
  if(channel > 15) return;
  uint8_t midipacket[3] = {0xB0 | channel, CS_ALL_NOTES_OFF, 0x00};
  _comm->write(midipacket, 3);
}
void CS9236::EnablePressureRecognition(){
  uint8_t midipacket[8] = {0xF0, 0x00, 0x01, 0x02, 0x01, 0x01, 0x01, 0xF7};
  _comm->write(midipacket, 8);
}
void CS9236::DisablePressureRecognition(){
  uint8_t midipacket[8] = {0xF0, 0x00, 0x01, 0x02, 0x01, 0x01, 0x02, 0xF7};
  _comm->write(midipacket, 8);
}
void CS9236::EnableTestTone(){
  uint8_t midipacket[8] = {0xF0, 0x00, 0x01, 0x02, 0x01, 0x01, 0x03, 0xF7};
  _comm->write(midipacket, 8);
}
void CS9236::DisableTestTone(){
  uint8_t midipacket[8] = {0xF0, 0x00, 0x01, 0x02, 0x01, 0x01, 0x04, 0xF7};
  _comm->write(midipacket, 8);
}