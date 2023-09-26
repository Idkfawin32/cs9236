#include <Arduino.h>
#include <cs9236.h>

//The reset pin for the Wavetable Chip. I use pin 7 in my projects
#define wavetable_rs 7
#define rhythm_width 16

CS9236 wavetableChip(wavetable_rs, &Serial1);

//For the simple drum machine loop. 
const uint32_t rhythm_frames[rhythm_width] = {0x3c000030, 0x00000000, 0x00000010, 0x00000000, 0x00e00030, 0x00000000, 0x00000020, 0x0000002c, 0x00000034, 0x00000000, 0x34000024, 0x00000000, 0x00f00034, 0x00000000, 0x00000024, 0x2c000000};
byte master_volume = 127;
byte rhythm_ticks = 0;
uint32_t rhythm_waitmicros = 150000;
uint32_t last_sequencer_update = 0;
byte note_values[5] = {42,51,47,38,36};

//Updates the sequencer/drum machine, if percussion events are triggered for the current from it will send that information to the Wavetable chip
void updateSequencer(uint32_t microseconds){
  //Only increment the rhythm frame if enough time has passed
  if(microseconds - last_sequencer_update > rhythm_waitmicros){
    last_sequencer_update = microseconds;

    //Establish which frame we are on in the drum groove
    byte frameindex = rhythm_ticks++ % rhythm_width;
    uint32_t current_frame = rhythm_frames[frameindex] & 0x3fffffff; //clear top 2 bits

    // if a frame is 0, that means nothing happens at all, so we can skip it
    if(current_frame > 0){ 
      //I store my frames as 5 values with 6 bits each, this fits into a 32 bit unsigned integer leaving the most significant 2 bits blank, I currently do not use those bits for any purpose
      for(int i = 0; i < 5; i++){
        //extract the 6 bit value for this instrument, processing only non-zero values
        byte val6 = (current_frame >> (i * 6)) & 0x3f;
        if(val6 != 0) {
          float velo = ((float)val6) / 63.0; 
          byte midivelo = constrain(127.0 * (velo), 0, 127);

          //Trigger the percussion instrument with the specified velocity. We do not need a corresponding "NoteOff" call since this is percussion
          wavetableChip.NoteOn(0x09, note_values[i], midivelo);
        }
      }
    }
  }
}

void setup() {
  //Set the appropriate pinmode for the reset pin
  pinMode(wavetable_rs, OUTPUT);
  
  //Begin communication through Serial, I use Serial1 assuming we want Serial to be free and clear for debugging or other uses
  Serial1.begin(31250);
  while(!Serial1) delayMicroseconds(10);

  //Set up the wavetable chip
  wavetableChip.Init();
  //Reset all values on Midi Channel 10, please note that while this value is "9", since Midi Channel 1 is "0", Midi Channel 10 would be "9"
  wavetableChip.ResetAll(0x09);
  //Sets the volume of Channel 10 to master_volume, 0 is silent and 127 is maximum loudness
  wavetableChip.SetVolume(0x09, constrain(master_volume, 0, 127));
}

void loop() {
  //pumps the drum-machine loop
  updateSequencer(micros());
}
