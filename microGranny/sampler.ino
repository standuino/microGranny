char sampleName[]="00.WAV";
uint16_t fileIndex[16];
long startGranule, cutTime,cutLimit,loopTime,loopLimit,shiftNow, lfoTime;
unsigned char start,midiPitch;
int shiftSpeed;
boolean lfoUp=true,shiftUp;
int lfoStep;


void RenderSample(){
  // current loop
  if(currentLoop){
    if(wave.readPositionNow()>=currentLoopEnd){
      wave.stop();
      wave.seek(currentLoopStart);
      wave.play(); 
      if(midiMode) wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+midiPitch));
      else  wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+currentSoundVal[PITCH_INDEX]));

    } 
  }

  //REPEAT
  //if(wave.readPositionNow()>=wave.getSize()-50) wave.stop();

  if (!wave.isplaying){ 
    shiftNow=0;
    if(mode==0){
      if(repeat && playSound!=0) {

        wave.seek(startGranule*start);
        cutTime=millis();
        wave.play(); 
        if(midiMode) wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+midiPitch));
        else  wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+currentSoundVal[PITCH_INDEX]));

      }

      else wave.stop();
    }

    else{
      if(repeat && ButtonState(PREW)) {
        wave.seek(startGranule*start);
        cutTime=millis();
        wave.play(); 
        if(midiMode) wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+midiPitch));
        else  wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+currentSoundVal[PITCH_INDEX]));

      }
      else wave.stop();
    }

  }
  //REPEAT

  //CUT  //wave.readPosition(); //a wish
  if(currentSoundVal[CUT_INDEX]<31){
    if(millis()-cutTime>=cutLimit){
      wave.stop();
    }
  }
  //CUT

  //MICROSAMPLING
  if (wave.isplaying){
    if(currentSoundVal[LOOP_LEN_INDEX]!=0){
     

      if(millis()-loopTime>=loopLimit){    
        loopTime=millis();

        switch(shiftDirection){
        case 0:
        shiftNow+=shiftSpeed;
        /*
          if(shiftSpeed==32) shiftNow=shiftNow;
          else if(shiftSpeed>32) shiftNow+=(shiftSpeed-32);
          else if (shiftSpeed<32) shiftNow-=(32-shiftSpeed);
          */

          break;
        case 1:
          if(random(2)==0) shiftNow+=shiftSpeed;
          else shiftNow-=shiftSpeed;
          break;
          /*
          shiftNow-=shiftSpeed;
           break;
           case 2:
           
           break;
           case 3:
           if(random(4)==0) shiftUp=!shiftUp;
           if(shiftUp) shiftNow+=shiftSpeed;
           else shiftNow-=shiftSpeed;
           
           break; 
           */
        }

        wave.stop();
        wave.seek(startGranule*start+shiftNow);
        wave.play();
        if(midiMode) wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+midiPitch));
        else  wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+currentSoundVal[PITCH_INDEX]));

      }

    }
    else{
      shiftNow=wave.readPositionNow();
    }

  }
  //MICROSAMPLING

  //RENDER TWEAKING
  if(potMode==0 && KnobChanged(0) && !KnobFreezed(0)) if(!midiMode) wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+currentSoundVal[PITCH_INDEX]));  //UDELAT LADENOU TABULKU!!!
  if(potMode==0 && KnobChanged(1) && !KnobFreezed(1)) wave.crush= map(currentSoundVal[CRUSH_INDEX],0,64,0,255);

  if(potMode==1 && KnobChanged(0) && !KnobFreezed(0)) start=currentSoundVal[START_INDEX];
  if(potMode==1 && KnobChanged(1) && !KnobFreezed(1)) cutLimit=map(currentSoundVal[CUT_INDEX],0,31,1,1000);

  if(potMode==2 && KnobChanged(0) && !KnobFreezed(0)) shiftSpeed=map(currentSoundVal[SHIFT_SPEED_INDEX],0,64,-5000,5000);
  if(potMode==2 && KnobChanged(1) && !KnobFreezed(1)) loopLimit=map(currentSoundVal[LOOP_LEN_INDEX],0,64,1,500);
  //RENDER TWEAKING

  //RENDER LFO

  RenderLfo();

}

void RenderLfo(){

  if(currentSoundVal[LFO_AMT_INDEX]!=0){

    unsigned char lfoAmt=currentSoundVal[LFO_AMT_INDEX];
    unsigned char lfoRate=map(currentSoundVal[LFO_RATE_INDEX],0,31,50,1);

    if(millis()-lfoTime>=lfoRate){
      lfoTime=millis();

      if(lfoUp){
        lfoStep++;
        if(lfoStep>=16) lfoUp=false;
      }
      else{
        lfoStep--;
        if(lfoStep<=0) lfoUp=true;
      }

      switch(lfoDest){

      case 0:
        if(midiMode) wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+midiPitch)+lfoAmt*(lfoStep-8)*50);
        else  wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+currentSoundVal[PITCH_INDEX])+lfoAmt*(lfoStep-8)*50);

        // wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+currentSoundVal[PITCH_INDEX])+lfoAmt*(lfoStep-8)*50);
        break;
      case 1:
        wave.crush= map(currentSoundVal[CRUSH_INDEX],0,64,0,255)+lfoStep*lfoAmt;
        break; 
      }

    }
  }

}


void PlaySound(unsigned char _playSound){

  if(_playSound>16) midiMode = true;
  else {
    midiMode = false, lastPlayedNote=_playSound; 

  };

  unsigned char _playWhat;
  StopSound();


  if(mode!=0) _playWhat=editSound;
  else {
    if(midiMode){ 
      _playWhat=lastPlayedNote;
      if(setValuesInMidi) SetValuesFromMemory(lastPlayedNote),setValuesInMidi=false;
    }
    else  _playWhat=_playSound, SetValuesFromMemory(_playSound);
  }
  wave.crush= map(currentSoundVal[CRUSH_INDEX],0,64,0,255);
  playfile(_playWhat);
  if(currentSoundVal[START_INDEX]!=0){
    startGranule=wave.getSize()/128;
    start=currentSoundVal[START_INDEX];
    wave.seek(startGranule*start);
  }
  else{
    wave.seek(0);
  }

  cutLimit=map(currentSoundVal[CUT_INDEX],0,31,1,1000);
  cutTime=millis();
  shiftSpeed=map(currentSoundVal[SHIFT_SPEED_INDEX],0,64,-5000,5000);
  loopLimit=map(currentSoundVal[LOOP_LEN_INDEX],0,64,1,500);
  loopTime=millis();
  shiftNow=0;
  wave.play();
  wave.volume= 7-volume;
  if(midiMode) {
    if(_playSound<25) midiPitch=0;
    else if(_playSound>72) midiPitch=48;
    else midiPitch=_playSound-25;
    wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+midiPitch));
    lastNotePlayed=_playSound;
  }
  else  wave.setSampleRate(pgm_read_word_near(noteSampleRateTable+currentSoundVal[PITCH_INDEX])),lastNotePlayed=_playSound;



}




void StopSound(){
  wave.stop();
}


char* soundName(byte soundNumber){

  letter1=GetValue(LETTER_1,soundNumber);
  letter2=GetValue(LETTER_2,soundNumber);

  if(letter1>9) sampleName[0]=letter1+55;
  else sampleName[0]=letter1+48;
  if(letter2>9) sampleName[1]=letter2+55;
  else sampleName[1]=letter2+48;

  return sampleName;
}

char* soundName(){
  if(letter1>9) sampleName[0]=letter1+55;
  else sampleName[0]=letter1+48;
  if(letter2>9) sampleName[1]=letter2+55;
  else sampleName[1]=letter2+48;
  return sampleName;
}



void playfile(char *name) { //not indexed
  if (wave.isplaying) {
    wave.stop(); 
  }

  if (!file.open(root, name)) {
    //PgmPrint("Couldn't open file ");
    return;
  }

  if (!wave.create(file)) {
    //PgmPrintln("Not a valid WAV");
    return;
  }

  // wave.play();
}

void playfile(unsigned char soundNumber) { //INDEXED

  if (wave.isplaying) {
    wave.stop(); 
  }

  if (!file.open(root, fileIndex[soundNumber-1])) {
    //error("open by index");
    return;
  }

  if (!wave.create(file)) {
    //PgmPrintln("Not a valid WAV");
    return;
  }

  // wave.play();
}

void IndexFiles(void)
{
  wave.stop();
  DisplayPGMText(IND);
  for (int i = 0; i < 15; i++) {  
    UpdateUIInputs(); 
    if(GetIndexStatus(i+1)){
      if (!file.open(root, soundName(i+1))) ;
      fileIndex[i] = root.readPosition()/32 - 1;
    }   // Save file's index (byte offset of directory entry divided by entry size) // Current position is just after entry so subtract on
    SetIndexStatus(i+1,false);  
  } 

}

void IndexFile(unsigned char _sound)
{
  wave.stop();
  if (!file.open(root, soundName(_sound))) ;
  fileIndex[_sound-1] = root.readPosition()/32 - 1;   
  SetIndexStatus(_sound,false);


}


void Reboot(){
  for(int i=0;i<NUMBER_OF_BUTTONS;i++) if(ButtonState(i)) isError=false, SamplerInit(); 
};

void SamplerInit(){


  if (!card.init()) {
    //error("Card init. failed!");
    DisplayPGMText(INT);
    isError=true;
  }
  if (!vol.init(card)) {
    //error("No partition!");
    DisplayPGMText(PAR);
    isError=true;
  }
  if (!root.openRoot(vol)) {
    //error("Couldn't open dir");
    DisplayPGMText(DIR);
    isError=true;
  }

  while(isError){
    UpdateUIInputs();
    Reboot(); 
  }

}


void error_P(const char *str) {
  PgmPrint("Error: ");
  SerialPrint_P(str);
  sdErrorCheck();
  while(1);
}


void sdErrorCheck(void) {
  if (!card.errorCode()) return;
  //PgmPrint("\r\nSD I/O error: ");
  //Serial.print(card.errorCode(), HEX);
  //PgmPrint(", ");
  //Serial.println(card.errorData(), HEX);
  while(1);
}









































