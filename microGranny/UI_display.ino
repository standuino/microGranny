unsigned char lastShowType, showType,lastKnobChanged;
long whileTime,blinkTime, knobDisplayTime;
boolean whileShow, modeDisplayed, knobDisplay;

#define WHILE 300

void ShowValue(){
  if(mode!=0){
    if(editSound!=0){
      if(mode==1 | mode==2){
        lightNumber(letter2,2);
        lightNumber(letter1,1);
        lightNumber(VOID,0);
      }
      switch(mode){
      case 3:
        if(repeat) DisplayPGMText(ONN),lightNumber(VOID,2);
        else DisplayPGMText(OFF);
        break; 
      case 4:
        switch(shiftDirection)
        {
        case 0:
          DisplayPGMText(FWD);
          break; 
        case 1:
          //DisplayPGMText(BCK);
          DisplayPGMText(RD1);
          break; 
        case 2:
          DisplayPGMText(RD1);
          break;
        case 3:
          DisplayPGMText(RD2);
          break;  
        }
        break;
      case 5:
        if(lfoDest) DisplayPGMText(CRS);
        else DisplayPGMText(PCH);
        break;
      case 6:
        DisplayNumber(volume);
        lightNumber(31,0);
        break;
      case 8:
        // DisplayText("sve");
        break;
      case 9:
        DisplayPGMText(PRE);
        lightNumber(preset,2);
        break;

      }
    }
    else{
   //    DisplayNumber(freeRam());
     DisplayPGMText(SEL);
    }
  }
  else{
    DisplayPGMText(XXX);

  }

}


void ReflectApplicationLayer(){

  //  for(int i=0;i<3;i++) displayBuffer[i]=0;
  if(millis()-blinkTime>80) blink=!blink, blinkTime=millis();
  if(millis()-knobDisplayTime>320) knobDisplay=false;

  if(whileShow){
    if(millis()-whileTime>WHILE) whileShow=false, ShowValue();
  }

  else {
    for(int i=0;i<NUMBER_OF_KNOBS;i++){ 
      if(KnobChanged(i) && !KnobFreezed(i)){ 
        if(i+2*potMode==0){
          if(currentSoundVal[0]>=36) DisplayNumber(currentSoundVal[i+2*potMode]-36),lightNumber(VOID,0);
          else DisplayNumber(36- currentSoundVal[i+2*potMode]),lightNumber(MINUS,0);
        }
        else if(i+2*potMode==4){
           if(currentSoundVal[4]>=32) DisplayNumber(currentSoundVal[i+2*potMode]-32),lightNumber(VOID,0);
          else DisplayNumber(32- currentSoundVal[i+2*potMode]),lightNumber(MINUS,0);
        }
        else DisplayNumber(currentSoundVal[i+2*potMode]);
        knobDisplay=true;
        knobDisplayTime=millis();
      }
    };
    if(!knobDisplay){
      switch(mode){
      case 0:
        break;
      case 1:
        ShowValue();
        if(blink) lightNumber(VOID,2);
        break;
      case 2:
        ShowValue();
        if(blink) lightNumber(VOID,1);
        break; 
      default:
        ShowValue();
        break;

      }
    }

  }


  lastShowType=showType;
  if(KnobChanged(0)) lastKnobChanged=0;
  if(KnobChanged(1)) lastKnobChanged=1;
  if(KnobChanged(0) | KnobChanged(1)) showType= 2*potMode+lastKnobChanged;


  if(lastShowType!=showType){
    modeDisplayed=false;
    switch(showType){ // nahradit textovym arrayem
    case PITCH_INDEX:
      ShowForAWhilePGM(PCH);
      break; 
    case CRUSH_INDEX:
      ShowForAWhilePGM(CRS);
      break; 
    case START_INDEX:
      ShowForAWhilePGM(STR);
      break; 
    case CUT_INDEX:
      ShowForAWhilePGM(CTT);
      break; 
    case SHIFT_SPEED_INDEX:
      ShowForAWhilePGM(SHF);
      break; 
    case LOOP_LEN_INDEX:
      ShowForAWhilePGM(LOP);
      break;
    case LFO_RATE_INDEX:
      ShowForAWhilePGM(RTE);
      break; 
    case LFO_AMT_INDEX:
      ShowForAWhilePGM(AMT);
      break; 
    }
  }

  bitWrite(displayBuffer[3],1,bitRead(potMode,1));
  bitWrite(displayBuffer[3],7,bitRead(potMode,0));


  if(mode==0){
    for(int i=0;i<4;i++)  bitWrite(displayBuffer[3],i+3,bitRead(playSound,i));
    bitWrite(displayBuffer[3],PREW,hold);
  }
  else{
    for(int i=0;i<4;i++) bitWrite(displayBuffer[3],i+3,bitRead(editSound,i));
    bitWrite(displayBuffer[3],PREW,ButtonState(PREW));
  }


  if(mode!=lastMode){  
    modeDisplayed=true;
    if(mode==0) ShowForAWhilePGM(XXX);
    else if(editSound!=0){
      switch(mode){  // nahradit textovym arrayem
      case 0:
        ShowForAWhilePGM(XXX);
        break;
      case 1:
        ShowForAWhilePGM(ND);
        break;
      case 2:
        ShowForAWhilePGM(ST);
        break;
      case 3:
        ShowForAWhilePGM(REP);
        break;
      case 4:
        ShowForAWhilePGM(DIR);
        break;
      case 5:
        ShowForAWhilePGM(LFO);
        break;
      case 6:
        ShowForAWhilePGM(VOL);
        break;
      case 7:
        ShowForAWhilePGM(COP);
        break;
      case 8:
        ShowForAWhilePGM(SVE);
        break;
      case 9:
        ShowForAWhilePGM(PRE);
        break;
      } 
    }
    else{
     //  DisplayNumber(freeRam());
      DisplayPGMText(SEL);
      // ShowForAWhile("sel");
    }
  }


  if(mode>2){
    for(int i=0;i<3;i++) bitWrite(displayBuffer[2-i],0,bitRead(mode-2,i)); 
  }
  else  for(int i=0;i<3;i++) bitWrite(displayBuffer[2-i],0,0); 

}


void ShowForAWhile(char* _charShow){
  //  showedChar=_charShow;
  whileShow=true;
  whileTime=millis();
  DisplayText(_charShow);
  
}

void ShowForAWhilePGM(int _charShow){
  //  showedChar=_charShow;
  whileShow=true;
  whileTime=millis();
  DisplayPGMText(_charShow);
  
}

void ShowForAWhile(int _charShow){

  //  showedChar=_charShow;
  whileShow=true;
  whileTime=millis();
  DisplayNumber(_charShow);

}


void DisplayNumber(int _number){

  lightNumber(_number/100,0);
  lightNumber((_number%100)/10,1);
  lightNumber(_number%10,2);

}

void InitialAnimation(){

  long time;  // nahradit textovym arrayem a forcyklem
  char temp[3];
  for(int j=0;j<7;j++){
    for(int i=0;i<3;i++) temp[i]=pgm_read_word_near(texts+i+j);

    DisplayText(temp);
    time=millis();
    while((millis()-time)<250) UpdateUIInputs();
  }
  /*
  DisplayNumber(freeRam());
  time=millis();
  while((millis()-time)<400) UpdateUIInputs();
  */
  DisplayPGMText(XXX);
}


int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void DisplayPGMText(unsigned char _whichText){
  char temp[3];
    for(int i=0;i<3;i++) temp[i]=pgm_read_word_near(texts+_whichText+i);
    DisplayText(temp);
}


















