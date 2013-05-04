/*
****************************************************
 -----STANDUINO-------MICRO GRANNY--SAMPLER---------
 ***************************************************
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 SAMPLER:
 -plays wave samples from SD card through 12 bit D/A converter
 -hackable in hardware (there is lot of free space to add features) and software (it is open source and re-programmable form Arduino)
 -intuitive interface with 4 perfect response big buttons, 2 pots, 5 small buttons and 3 digit 7-segment display
 -edit mode where you fully adjust the 15 different sound (each big button press combination makes different sound)
 -for each sound you can adjust: 
 -basic functions: sample,repeat,volume,pitch,bitCrush,start,cut
 -micro sampling features: loop length, shift speed, shift direction
 -lfo: rate, amt, destination
 -MIDI input
 -8 presets
 -3,5mm headphone output jack connector (directly to pwm pin) -can power stereo headphones (but instrument is in mono),
 -volume adjust pot
 -9-12V power supply from battery or adaptor
 
 software by: Vaclav Pelousek www.pelousek.eu
 developed by Standuino: www.standuino.eu
 
 uses hacked version of waveHC library
 uses parts of Audio project and MIDI library
 
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 */

/*

 to be fixed to DONE DONE
 -DONE - end of sample stop by readPosition-doesn affect bad samples
 -instant loop in microSampling...?
 
 future improovements
 -midi cc
 
 jako easter egg:
 -loop lenth násobek hodnoty tempo
 -tempo tapovací
 -tempo spocítat z délky tracku
 delka tracku v bytech
 samplovací frekvence.počet bytů za secundu
 f=b/t
 t=b/f
 t=size/22500
 tempo=beats/t
 64 32 16 8 4 2 1 2x 4x 8x
 
 */
 
#include <WaveHC.h>
#include <WaveUtil.h>
#include <pgmspace.h>
#include <EEPROM.h>

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the volumes root directory
FatReader file;   // This object represent the WAV file for a pi digit or period
WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time
#define error(msg) error_P(PSTR(msg))
boolean isError;
#define XXX 9

void setup() {
  
  InitUI();
  MidiBegin();
  SamplerInit();
  LoadPreset(0);
  InitialAnimation();
  IndexFiles();
  DisplayPGMText(XXX);

}


void loop() {

  MidiRead();
 // MidiRead();
  UpdateUIInputs();
  MidiRead();
 // MidiRead();
  UpdateApplicationLayer();
  MidiRead();
 // MidiRead();
  ReflectApplicationLayer();
  MidiRead();
 // MidiRead();
  RenderSample();

}













