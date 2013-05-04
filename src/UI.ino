boolean shift;
unsigned char scroll, potMode;
long setTime;
boolean hold,setLongPress,setMidLongPress;
unsigned char lastMode, editSound, lastEditSound, playSound,lastPlaySound;
unsigned char letter1, letter2, volume, shiftDirection;
boolean loopActive,repeat, lfoDest,doublePress;
unsigned char currentSoundVal[8];
uint32_t currentLoopStart,currentLoopEnd;
unsigned char currentLoopState;
boolean currentLoop;
unsigned char shouldBeIndexed[2];


void UpdateApplicationLayer(){

  ModeChange();
  if(mode!=0) ProceedEditMode();
  else ProceedPlayMode();

}

void ModeChange(){

  if(JustPressed(POT)) potMode++, FreezeKnobs();
  if(potMode>=4) potMode=0;

  lastMode=mode;

  if(JustPressed(SET)) setTime=millis();

  if(mode>=10) mode=0, StopSound();
  if(mode!=0 && lastMode==0) StopSound(), playSound=0,hold=false;

  if(wave.isplaying) setTime=millis();

  if(ButtonState(SET)){
    if(millis()-setTime>50) setMidLongPress=true;
    if(millis()-setTime>800) setMidLongPress=false, setLongPress=true, mode=0;
  } 
  else{
    setTime=millis(); 
  }

  if(ButtonState(SET) && JustPressed(UP) && mode<8) mode++,setTime=millis(),setMidLongPress=false,setLongPress=false,doublePress=true;  
  if(ButtonState(SET) && JustPressed(DOWN) && mode>0) mode--,mode--,setTime=millis(),setMidLongPress=false,setLongPress=false,doublePress=true;  

  if(lastMode!=0 && mode==0) SetValuesToMemory(editSound),IndexFiles(); //save
  if(lastMode==0 && mode!=0) SetValuesFromMemory(editSound);

  if(JustReleased(SET) && !wave.isplaying) {
    if(setMidLongPress) mode++, setLongPress=false;//mode=0, setLongPress=false;
    else if(setLongPress) mode=0, setLongPress=false;
    else if(doublePress) doublePress=false;
    // else mode++;              

  }

}


void DealMidiInEditMode(){
  if(note<=16){
    if (mode!=0) editSound=note+1, SetValuesToMemory(lastEditSound), SetValuesFromMemory(editSound), FreezeKnobs();
    else if(hold) playSound=note+1, FreezeKnobs(),ResetCurrentLoop(); 
  }
}

void ProceedEditMode(){

  if(JustPressed(PREW)) PlayAndMakeIndexIfNecessary(editSound);
  if(JustReleased(PREW)) StopSound();

  lastEditSound=editSound;

  for(int i=0;i<4;i++){
    if(JustPressed(bigButtons[i])) {
      bitWrite(editSound,i,!bitRead(editSound,i));
      SetValuesToMemory(lastEditSound);
      SetValuesFromMemory(editSound);
      FreezeKnobs();
    }
  }

  if(editSound!=0){
    if(!ButtonState(SET)){
      switch(mode){
      case 1:
        if(JustPressed(UP) && letter2<35) letter2++,SetValuesToMemory(editSound),SetIndexStatus(editSound,true);
        if(JustPressed(DOWN) && letter2>0) letter2--,SetValuesToMemory(editSound),SetIndexStatus(editSound,true);
        break;
      case 2:
        if(JustPressed(UP) && letter1<35) letter1++,SetValuesToMemory(editSound),SetIndexStatus(editSound,true);
        if(JustPressed(DOWN) && letter1>0) letter1--,SetValuesToMemory(editSound),SetIndexStatus(editSound,true);
        break; 
      case 3:
        if(JustPressed(UP) | JustPressed(DOWN)) repeat=!repeat;
        break;
      case 4:
        if(JustPressed(UP) && shiftDirection<1) shiftDirection++;
        if(JustPressed(DOWN) && shiftDirection>0) shiftDirection--;
        break;
      case 5:
        if(JustPressed(UP) | JustPressed(DOWN)) lfoDest=!lfoDest;
        break;
      case 6:
        if(JustPressed(UP) && volume<7) volume++;
        if(JustPressed(DOWN) && volume>0) volume--;
        break;
      case 7:
        if(JustPressed(UP)) Copy();
        if(JustPressed(DOWN)) Paste();
        break;
      case 8:
        if(JustPressed(UP)) StorePreset(preset), DisplayPGMText(SVD);
        if(JustPressed(DOWN)) StorePreset(preset),DisplayPGMText(SVD);
        break;
      case 9:
        if(JustPressed(UP) && preset<7) preset++,LoadPreset(preset),FreezeKnobs(),SetValuesFromMemory(editSound);
        if(JustPressed(DOWN) && preset>0) preset--,LoadPreset(preset),FreezeKnobs(),SetValuesFromMemory(editSound);
        break;
      } 
    }

    for(int i=0;i<2;i++){
      if(KnobChanged(i) && !KnobFreezed(i)) currentSoundVal[i+2*potMode]=map(GetKnobValue(i),0,1024,0,knobMaxValue[i+2*potMode]), SetValuesToMemory(editSound);
    }
  }

}


void ProceedPlayMode(){

  if(JustPressed(PREW)) hold=!hold;


  lastPlaySound=playSound;
  if(hold) { 
    for(int i=0;i<4;i++) { 
      if(JustPressed(bigButtons[i])) bitWrite(playSound,i,!bitRead(playSound,i));
    }
  }
  else{ 
    for(int i=0;i<4;i++) {
      bitWrite(playSound,i,ButtonState(bigButtons[i]));
    }
  }


  if(playSound!=lastPlaySound) PlaySound(playSound), FreezeKnobs(),ResetCurrentLoop(); // PLAY SOUND
  if(lastPlaySound!=0 && playSound==0) StopSound();

  SetValuesFromKnobs();

  if(JustPressed(UP)){
    if(wave.isplaying){
      switch(currentLoopState){
      case 0:
        currentLoopStart=wave.readPositionNow();
        DisplayPGMText(LPS);
        currentLoopState++;
        break;
      case 1:
        currentLoopEnd=wave.readPositionNow();
        currentLoop=true;
        DisplayPGMText(LPE);
        currentLoopState++;
        break;
      case 2:
        ResetCurrentLoop();
        break; 

      }

    }

  }

}

void ResetCurrentLoop(){

  DisplayPGMText(XXX);
  //currentLoopStart=0;
  //currentLoopEnd=0;
  currentLoopState=0;
  currentLoop=false;
}

unsigned char numberOfTap;
long lastTapTime;
int tapMemory[8];

void tap(){
  if(millis()-lastTapTime>3000){
    numberOfTap=0; 
  }
  if(numberOfTap==0){
    lastTapTime=millis();
    numberOfTap++;
  } 
  else{
    if(numberOfTap>8){
      for(int i=0;i<8;i++) {
        tapMemory[i]=tapMemory[i+1];
      }
      numberOfTap=8;
    }
    tapMemory[numberOfTap-1]= millis()-lastTapTime;
    lastTapTime=millis();
    int tapTogether;
    for(int i=0;i<numberOfTap;i++){
      tapTogether+=tapMemory[i]; 
    }
    tempo = 120000/(tapTogether/numberOfTap); // normaly 60000
  }
}



void SetValuesFromMemory(unsigned char _sound){
  if(_sound!=0){
    letter1=GetValue(LETTER_1,_sound);
    letter2=GetValue(LETTER_2,_sound);
    loopActive=GetValue(LOOP,_sound);
    shiftDirection=GetValue(SHIFT_DIR,_sound);

    repeat=GetValue(REPEAT,_sound);
    lfoDest=GetValue(LFO_DEST,_sound);
    volume=GetValue(VOLUME,_sound);


    currentSoundVal[PITCH_INDEX]=GetValue(PITCH,_sound);
    currentSoundVal[CRUSH_INDEX]=GetValue(CRUSH,_sound);
    currentSoundVal[START_INDEX]=GetValue(START,_sound);
    currentSoundVal[CUT_INDEX]=GetValue(CUT,_sound);

    currentSoundVal[SHIFT_SPEED_INDEX]=GetValue(SHIFT_SPEED,_sound);
    currentSoundVal[LOOP_LEN_INDEX]=GetValue(LOOP_LEN,_sound);
    currentSoundVal[LFO_RATE_INDEX]=GetValue(LFO_RATE,_sound);
    currentSoundVal[LFO_AMT_INDEX]=GetValue(LFO_AMT,_sound);
  }
}

void SetValuesToMemory(unsigned char _sound){

  if(_sound!=0){
    SetValue(LETTER_1,_sound,letter1);
    SetValue(LETTER_2,_sound,letter2);
    SetValue(LOOP,_sound,loopActive);
    SetValue(SHIFT_DIR,_sound,shiftDirection);

    SetValue(REPEAT,_sound,repeat);
    SetValue(LFO_DEST,_sound,lfoDest);
    SetValue(VOLUME,_sound,volume);

    SetValue(PITCH,_sound, currentSoundVal[PITCH_INDEX]);
    SetValue(CRUSH,_sound, currentSoundVal[CRUSH_INDEX]);
    SetValue(START,_sound, currentSoundVal[START_INDEX]);
    SetValue(CUT,_sound, currentSoundVal[CUT_INDEX]);

    SetValue(SHIFT_SPEED,_sound, currentSoundVal[SHIFT_SPEED_INDEX]);
    SetValue(LOOP_LEN,_sound, currentSoundVal[LOOP_LEN_INDEX]);
    SetValue(LFO_RATE,_sound, currentSoundVal[LFO_RATE_INDEX]);
    SetValue(LFO_AMT,_sound, currentSoundVal[LFO_AMT_INDEX]);
  }


}
void SetValuesFromKnobs(){
  if(playSound!=0){

    for(int i=0;i<2;i++){
      if(KnobChanged(i) && !KnobFreezed(i)) currentSoundVal[i+2*potMode]=map(GetKnobValue(i),0,1024,0,knobMaxValue[i+2*potMode]);
    }
  }

}


void Copy(){
  SetValuesToMemory(editSound);
  for(int i=0;i<8;i++) copyMemory[i]=value[editSound-1][i];
  DisplayPGMText(CPD);

}

void Paste(){
  for(int i=0;i<8;i++) value[editSound-1][i]=copyMemory[i];
  SetIndexStatus(editSound,true);
  SetValuesFromMemory(editSound);
  DisplayPGMText(PST);
}


boolean GetIndexStatus(unsigned char _SOUND){
  boolean val;
  val= bitRead(shouldBeIndexed[_SOUND/8],_SOUND%8); 
  return val;
}

void SetIndexStatus(unsigned char _SOUND,boolean _status){
  bitWrite(shouldBeIndexed[_SOUND/8],_SOUND%8,_status);
}

void AllShouldBeIndexed(){
  for(int i=0;i<16;i++) SetIndexStatus(i,true); 
}


void PlayAndMakeIndexIfNecessary(unsigned char _SOUND){
  if(GetIndexStatus(_SOUND)) IndexFile(_SOUND);
  if(editSound!=0) PlaySound(_SOUND);
}

boolean CompareToMemory(int _val,int _knob){ // unfreeze knobs
  boolean returnVal;
  if( currentSoundVal[_knob+2*potMode]==map(_val,0,1024,0,knobMaxValue[_knob+2*potMode])) returnVal=true;
  else returnVal=false;
  return returnVal;
}


