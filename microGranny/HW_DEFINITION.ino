unsigned char buttonState, switchHash,justPressed, justReleased;
unsigned char dealRow;
unsigned char displayBuffer[4];
unsigned char knobHash;
int knobValues[2];


#define PITCH_INDEX 0
#define CRUSH_INDEX 1
#define START_INDEX 2
#define CUT_INDEX 3
#define SHIFT_SPEED_INDEX 4
#define LOOP_LEN_INDEX 5
#define LFO_RATE_INDEX 6
#define LFO_AMT_INDEX 7

const unsigned char knobMaxValue[8]={
  49,64,128,32,64,64,32,16};

byte doIt;
void UpdateUIInputs(){
  HandleMatrix(); 
  UpdateKnobUIInputs();
}

void InitUI(){

  pinMode(LATCH_PIN,OUTPUT);
  pinMode(CLOCK_PIN,OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
  for(int i=0;i<4;i++){
    pinMode(row[i],OUTPUT);
  }
  pinMode(row[4],INPUT);
  digitalWrite(LATCH_PIN,HIGH); 
  UpdateUIInputs();
  IsThereChangeInMidiChannel();
  ShouldIClearMemory();


}


void HandleMatrix(){
  for(int i=0;i<9;i++){
    JustReleased(i,false);
    JustPressed(i,false);
  }

  if(dealRow<=4) digitalWrite(row[dealRow],LOW);

  doIt++;
  if(doIt>10){

    doIt=0;
  }

  dealRow++;
  if(dealRow>=4){
    ReadButtonsRoutine();
  }
  if(dealRow>4){
    dealRow=0;
  }

  if(dealRow<4){
    digitalWrite(LATCH_PIN,LOW); 
    shiftOut(DATA_PIN,CLOCK_PIN,LSBFIRST,~displayBuffer[dealRow]);
    digitalWrite(LATCH_PIN,HIGH);
    digitalWrite(row[dealRow],HIGH);
  }

}

void ReadButtonsRoutine(){
  digitalWrite(LATCH_PIN,LOW); 
  shiftOut(DATA_PIN,CLOCK_PIN,LSBFIRST,255);
  digitalWrite(LATCH_PIN,HIGH);
  digitalWrite(row[3],LOW);
  pinMode(row[3],INPUT);
  delayMicroseconds(100);
  boolean newState=digitalRead(row[3]);

  boolean justRel = (ButtonState(8)!=newState && ButtonState(8))? true: false;
  JustReleased(8,justRel);

  boolean justPres = (ButtonState(8)!=newState && !ButtonState(8))? true: false;
  JustPressed(8,justPres);

  ButtonState(8,newState);

  /*
    if(justPressed(8)){
   setTime=millis(); 
   measureSet=true;
   }
   if(justRealeased(8)){
   measureSet=false; 
   }
   if(measureSet){
   if(ButtonState(8)){
   if(millis()-setTime>=200){
   measureSet=false;
   setPressed=true; 
   }
   } 
   }
   */

  pinMode(row[3],OUTPUT);
  digitalWrite(row[3],LOW);

  digitalWrite(LATCH_PIN,LOW); 
  shiftOut(DATA_PIN,CLOCK_PIN,LSBFIRST,0);
  digitalWrite(LATCH_PIN,HIGH);
  for(int i=0;i<8;i++){
    unsigned char whichButton=1<<i;
    digitalWrite(LATCH_PIN,LOW); 
    shiftOut(DATA_PIN,CLOCK_PIN,LSBFIRST,whichButton);
    digitalWrite(LATCH_PIN,HIGH);
    delayMicroseconds(100);////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    boolean newState=digitalRead(row[4]);

    boolean justRel = (ButtonState(i)!=newState && ButtonState(i))? true: false;
    JustReleased(i,justRel);

    boolean justPres = (ButtonState(i)!=newState && !ButtonState(i))? true: false;
    JustPressed(i,justPres);

    ButtonState(i,newState);
  }
}
void UpdateKnobUIInputs(){

  for(int knobRead=0;knobRead<NUMBER_OF_KNOBS;knobRead++){

    short newValue=analogRead(knobPin[knobRead]);
    KnobChanged(knobRead, false);
    short distance = abs(newValue - knobValues[knobRead]); 
    if (KnobFreezed(knobRead) == true) {
      /*
      if (distance > KNOB_FREEZE_DISTANCE) {
       // KnobFreezed(knobRead, false);
        KnobChanged(knobRead, true);
       // knobValues[knobRead] = newValue;
      }
     */
    if(CompareToMemory(newValue,knobRead)){
      KnobFreezed(knobRead, false);
      KnobChanged(knobRead, true);
      knobValues[knobRead] = newValue;
    };
    
      //if(newValue==
      
    } 
    else if (abs(newValue - knobValues[knobRead]) > KNOB_TOLERANCE) {
      knobValues[knobRead] = newValue;
      KnobChanged(knobRead, true);
    }
  }

}


//#################################### Under Functions ####################################//

unsigned int GetKnobValue(unsigned int index) {
  return knobValues[index]; //map(knobValues[index], 0, 1024, 0, 1024);
}

void FreezeKnobs(){
  for(int i=0;i<NUMBER_OF_KNOBS;i++) KnobFreezed(i,true);
}

boolean KnobFreezed(unsigned char _knob){
  boolean _knobFreezed;
  _knobFreezed=bitRead(knobHash,_knob);
  return _knobFreezed;
}

void KnobFreezed(unsigned char _knob, boolean _setState){
  bitWrite(knobHash,_knob,_setState);
}

boolean KnobChanged(unsigned char _knob){
  boolean _knobChanges;
  _knobChanges=bitRead(knobHash,_knob+NUMBER_OF_KNOBS);
  return _knobChanges;
}

void KnobChanged(unsigned char _knob, boolean _setState){
  bitWrite(knobHash,_knob+NUMBER_OF_KNOBS,_setState);
}




boolean ButtonState(unsigned char _button){
  boolean _buttonState;
  if(_button==8) _buttonState=bitRead(switchHash,0);
  else  _buttonState=bitRead(buttonState,_button);
  return _buttonState;
}

void ButtonState(unsigned char _button, boolean _setState){
  if(_button==8) bitWrite(switchHash,0,_setState);
  else bitWrite(buttonState,_button,_setState);
}

boolean JustPressed(unsigned char _button){
  boolean _buttonState;
  if(_button==8) _buttonState=bitRead(switchHash,1);
  else _buttonState=bitRead(justPressed,_button);
  return _buttonState;
}

void JustPressed(unsigned char _button, boolean _setState){
  if(_button==8) bitWrite(switchHash,1,_setState);
  else bitWrite(justPressed,_button,_setState);
}

boolean JustReleased(unsigned char _button){
  boolean _buttonState;
  if(_button==8) _buttonState=bitRead(switchHash,2);
  else _buttonState=bitRead(justReleased,_button);
  return _buttonState;
}

void JustReleased( unsigned char _button, boolean _setState){
  if(_button==8) bitWrite(switchHash,2,_setState);
  else bitWrite(justReleased,_button,_setState);
}

void DisplayText(char *text){
  for(int i=0;i<3;i++) DisplayChar(text[i],i);
}

void DisplayChar(char whichChar,unsigned char _digit) {
  if(whichChar==32)
  { 
    lightNumber(VOID,_digit);
  }
  else if(whichChar<65){
    lightNumber(whichChar-48,_digit);
  }
  else{
    lightNumber(whichChar-97+10,_digit);
  }
}


void lightNumber(int numberToDisplay, unsigned char _digit) {

  for(int i=0;i<7;i++){
    bitWrite(displayBuffer[_digit],segments[i],bitRead(pgm_read_word_near(typo+numberToDisplay),i)); 
  }

}
