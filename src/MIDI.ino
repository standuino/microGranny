unsigned char incomingByte,note;
boolean noteOn,midiNoteOn,ignore, comandOff, setValuesInMidi, slaveMode, doSlaveStep, startPressed;
unsigned char state=0;
unsigned char channel=0,lastPlayedNote=1, lastNotePlayed, clockTick;
#define MIDI_CHANNEL 1023

void MidiBegin(){
  ShouldIChangeMidiChannel();
  ReadMidiChannel();
  Serial.begin(31250);
}
void ShouldIChangeMidiChannel(){
  for(int i=0;i<4;i++){
    if(ButtonState(bigButtons[i])) channel=i,EEPROM.write(MIDI_CHANNEL,channel);
  }



}

void ReadMidiChannel(){

  channel=EEPROM.read(MIDI_CHANNEL);
  long time;
  DisplayText("mdi");
  lightNumber(channel+1,2);
  time=millis();
  while((millis()-time)<400) UpdateUIInputs();

}

void MidiRead(){
  //channel=map(analogRead(4),0,1024,0,16);
  while(Serial.available() > 0){
    if (Serial.available() > 0) {

      // read the incoming byte:
      byte incomingByte = Serial.read();
      Serial.write(incomingByte);

      switch (state){
      case 0:
      
        if(incomingByte==0xF8){ //clock
          clockTick++;
          if(clockTick==6) doSlaveStep=true, clockTick=0;
          slaveMode=true;
        }
        else if(incomingByte==0xFA){ //start
          startPressed=true;
        }
        else if(incomingByte==0xFC){ //stop

        }


        else if(incomingByte < 128) { // if running status byte
          if(!ignore){ //
            note=incomingByte;
            state=2;
          }
        }

        if (incomingByte== (144 | channel)){  // look for as status-byte, our channel, note on
          state=1;
          ignore=false;
        }

        else if (incomingByte== (0x80 | channel)){ // look for as status-byte, our channel, note off
          state=1;
          ignore=false;
          comandOff=true;

        }
        else if(incomingByte>127){
          ignore=true; 
        }



        break;

      case 1:
        // get the note to play or stop
        if(incomingByte < 128) {
          note=incomingByte;
          state=2;
        }
        else{
          state = 0;  // reset state machine as this should be a note number
        }
        break;

      case 2: // get the velocity

        if(incomingByte < 128) {

          if(incomingByte!=0){ 
            if(comandOff){
              SetMIDINoteOff(note+1);
              //StopSound();

              comandOff=false;
            }
            else{
              // if(note<17){
              SetMIDINote(note+1), FreezeKnobs(),ResetCurrentLoop(); // PlaySound(note%12)
              //}
              // digitalWrite(13,HIGH);
              midiNoteOn=true;
            }
          }
          else{ 
            SetMIDINoteOff(note+1);
            //StopSound();
            // digitalWrite(13,LOW);
            midiNoteOn=false;
          }
        }
        state=0;
        break;
      } 
    }
  }
}


boolean midiMode;
unsigned char midiBuffer[16];
unsigned char midiBufferIndex;

void SetMIDIMode(boolean newMode) {
  midiMode = newMode;
}

void SetMIDINote(unsigned char note) {
  midiBuffer[midiBufferIndex] = note;
  if (midiBufferIndex < 5) {
    midiBufferIndex++;
  }
  DealMidiInEditMode();

  PlaySound(note);
}



void SetMIDINoteOff(unsigned char note) {
  int i = 0;
  boolean noteFound = false;
  for (i; i < 16; i++) {
    if (noteFound) {
      midiBuffer[i - 1] = midiBuffer[i];
    } 
    else if (midiBuffer[i] == note) {
      midiBuffer[i] = 0;
      noteFound = true;
    }
  }
  if (noteFound) {
    midiBufferIndex--;
  }
  if (midiBufferIndex == 0) {
    midiMode = false;
    setValuesInMidi=true;
    StopSound();
  }
  else{

    if(lastNotePlayed!=midiBuffer[midiBufferIndex-1]) PlaySound(midiBuffer[midiBufferIndex-1]);

  }
  /*
  for (int j; j <5; j++) {
   if(midiBuffer[j]!=0){
   PlaySound(midiBuffer([j]);
   }
   */

}






