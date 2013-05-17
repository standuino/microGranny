unsigned char value[15][8];
unsigned char copyMemory[8];

unsigned char tempo, currentPreset,preset;
boolean blink;
#define NUMBER_OF_LETTER_1_BYTE 0
#define NUMBER_OF_LETTER_1_BITS 6
#define NUMBER_OF_LETTER_1_OFFSET 0

#define NUMBER_OF_LETTER_2_BYTE 1
#define NUMBER_OF_LETTER_2_BITS 6
#define NUMBER_OF_LETTER_2_OFFSET 0

#define NUMBER_OF_LOOP_LEN_BYTE 2
#define NUMBER_OF_LOOP_LEN_BITS 6
#define NUMBER_OF_LOOP_LEN_OFFSET 0



#define NUMBER_OF_PITCH_BYTE 4
#define NUMBER_OF_PITCH_BITS 6
#define NUMBER_OF_PITCH_OFFSET 0

#define NUMBER_OF_CRUSH_BYTE 5
#define NUMBER_OF_CRUSH_BITS 6
#define NUMBER_OF_CRUSH_OFFSET 0

#define NUMBER_OF_START_BYTE 6
#define NUMBER_OF_START_BITS 6
#define NUMBER_OF_START_OFFSET 0

#define NUMBER_OF_START_BYTE_2 2
#define NUMBER_OF_START_BITS_2 1
#define NUMBER_OF_START_OFFSET_2 6

#define NUMBER_OF_CUT_BYTE 7
#define NUMBER_OF_CUT_BITS 5
#define NUMBER_OF_CUT_OFFSET 0

#define NUMBER_OF_SHIFT_DIR_BYTE 0
#define NUMBER_OF_SHIFT_DIR_BITS 1
#define NUMBER_OF_SHIFT_DIR_OFFSET 6

#define NUMBER_OF_LFO_DEST_BYTE 1
#define NUMBER_OF_LFO_DEST_BITS 2
#define NUMBER_OF_LFO_DEST_OFFSET 6



#define NUMBER_OF_REPEAT_BYTE 2
#define NUMBER_OF_REPEAT_BITS 1
#define NUMBER_OF_REPEAT_OFFSET 7

#define NUMBER_OF_VOLUME_BYTE 3
#define NUMBER_OF_VOLUME_BITS 3
#define NUMBER_OF_VOLUME_OFFSET 5

#define NUMBER_OF_SHIFT_SPEED_BYTE_1 3
#define NUMBER_OF_SHIFT_SPEED_BITS_1 5
#define NUMBER_OF_SHIFT_SPEED_OFFSET_1 0

#define NUMBER_OF_SHIFT_SPEED_BYTE_2 0
#define NUMBER_OF_SHIFT_SPEED_BITS_2 1
#define NUMBER_OF_SHIFT_SPEED_OFFSET_2 7

#define NUMBER_OF_LFO_AMT_BYTE_1 4
#define NUMBER_OF_LFO_AMT_BYTE_2 5
#define NUMBER_OF_LFO_AMT_BITS_1 2
#define NUMBER_OF_LFO_AMT_BITS_2 2
#define NUMBER_OF_LFO_AMT_OFFSET_1 6
#define NUMBER_OF_LFO_AMT_OFFSET_2 6

#define NUMBER_OF_LFO_RATE_BYTE_1 6
#define NUMBER_OF_LFO_RATE_BYTE_2 7
#define NUMBER_OF_LFO_RATE_BITS_1 2
#define NUMBER_OF_LFO_RATE_BITS_2 3
#define NUMBER_OF_LFO_RATE_OFFSET_1 6
#define NUMBER_OF_LFO_RATE_OFFSET_2 5

#define LETTER_1 0
#define LETTER_2 1
#define SHIFT_DIR 2
#define LOOP 3
#define VOLUME 4
#define LFO_DEST 5
#define REPEAT 6

#define PITCH 7
#define CRUSH 8
#define SHIFT_SPEED 9
#define LOOP_LEN 10
#define START 11
#define CUT 12
#define LFO_RATE 13
#define LFO_AMT 14

void SetValue(unsigned char _VALUE_TYPE,unsigned char _SOUND, unsigned int _setValue){
  _SOUND--;
  switch(_VALUE_TYPE){
  case LETTER_1:
    for(int i=0;i<NUMBER_OF_LETTER_1_BITS;i++){
      bitWrite(value[_SOUND][NUMBER_OF_LETTER_1_BYTE],i+NUMBER_OF_LETTER_1_OFFSET,bitRead(_setValue,i));  
    }
    break;

  case LETTER_2:
    for(int i=0;i<NUMBER_OF_LETTER_2_BITS;i++){
      bitWrite(value[_SOUND][NUMBER_OF_LETTER_2_BYTE],i+NUMBER_OF_LETTER_2_OFFSET,bitRead(_setValue,i));  
    }
    break;

  case SHIFT_DIR:
    for(int i=0;i<NUMBER_OF_SHIFT_DIR_BITS;i++){
      bitWrite(value[_SOUND][NUMBER_OF_SHIFT_DIR_BYTE],i+NUMBER_OF_SHIFT_DIR_OFFSET,bitRead(_setValue,i));  
    }
    break;
    /*
  case LOOP:
     for(int i=0;i<NUMBER_OF_LOOP_BITS;i++){
     bitWrite(value[_SOUND][NUMBER_OF_LOOP_BYTE],i+NUMBER_OF_LOOP_OFFSET,bitRead(_setValue,i));  
     }
     break;
     */
  case VOLUME:
    for(int i=0;i<NUMBER_OF_VOLUME_BITS;i++){
      bitWrite(value[_SOUND][NUMBER_OF_VOLUME_BYTE],i+NUMBER_OF_VOLUME_OFFSET,bitRead(_setValue,i));  
    }
    break;

  case LFO_DEST:
    for(int i=0;i<NUMBER_OF_LFO_DEST_BITS;i++){
      bitWrite(value[_SOUND][NUMBER_OF_LFO_DEST_BYTE],i+NUMBER_OF_LFO_DEST_OFFSET,bitRead(_setValue,i));  
    }
    break;

  case REPEAT:
    for(int i=0;i<NUMBER_OF_REPEAT_BITS;i++){
      bitWrite(value[_SOUND][NUMBER_OF_REPEAT_BYTE],i+NUMBER_OF_REPEAT_OFFSET,bitRead(_setValue,i));  
    }
    break;

  case PITCH:
    for(int i=0;i<NUMBER_OF_PITCH_BITS;i++){
      bitWrite(value[_SOUND][NUMBER_OF_PITCH_BYTE],i+NUMBER_OF_PITCH_OFFSET,bitRead(_setValue,i));  
    }
    break;

  case CRUSH:
    for(int i=0;i<NUMBER_OF_CRUSH_BITS;i++){
      bitWrite(value[_SOUND][NUMBER_OF_CRUSH_BYTE],i+NUMBER_OF_CRUSH_OFFSET,bitRead(_setValue,i));  
    }
    break;

  

  case LOOP_LEN:
    for(int i=0;i<NUMBER_OF_LOOP_LEN_BITS;i++){
      bitWrite(value[_SOUND][NUMBER_OF_LOOP_LEN_BYTE],i+NUMBER_OF_LOOP_LEN_OFFSET,bitRead(_setValue,i));  
    }
    break;
    
    case SHIFT_SPEED:
    
    for(int i=0;i<NUMBER_OF_SHIFT_SPEED_BITS_1;i++){
      bitWrite(value[_SOUND][NUMBER_OF_SHIFT_SPEED_BYTE_1],i+NUMBER_OF_SHIFT_SPEED_OFFSET_1,bitRead(_setValue,i));  
    }
    for(int i=0;i<NUMBER_OF_SHIFT_SPEED_BITS_2;i++){
      bitWrite(value[_SOUND][NUMBER_OF_SHIFT_SPEED_BYTE_2],i+NUMBER_OF_SHIFT_SPEED_OFFSET_2,bitRead(_setValue,i+NUMBER_OF_SHIFT_SPEED_BITS_1));  
    }
    
    break;
    

  case START:
    for(int i=0;i<NUMBER_OF_START_BITS;i++){
      bitWrite(value[_SOUND][NUMBER_OF_START_BYTE],i+NUMBER_OF_START_OFFSET,bitRead(_setValue,i));  
    }
    for(int i=0;i<NUMBER_OF_START_BITS_2;i++){
      bitWrite(value[_SOUND][NUMBER_OF_START_BYTE_2],i+NUMBER_OF_START_OFFSET_2,bitRead(_setValue,i+NUMBER_OF_START_BITS));  
    }
    break;

  case CUT:
    for(int i=0;i<NUMBER_OF_CUT_BITS;i++){
      bitWrite(value[_SOUND][NUMBER_OF_CUT_BYTE],i+NUMBER_OF_CUT_OFFSET,bitRead(_setValue,i));  
    }
    break;

  case LFO_RATE:
    for(int i=0;i<NUMBER_OF_LFO_RATE_BITS_1;i++){
      bitWrite(value[_SOUND][NUMBER_OF_LFO_RATE_BYTE_1],i+NUMBER_OF_LFO_RATE_OFFSET_1,bitRead(_setValue,i));  
    }
    for(int i=0;i<NUMBER_OF_LFO_RATE_BITS_2;i++){
      bitWrite(value[_SOUND][NUMBER_OF_LFO_RATE_BYTE_2],i+NUMBER_OF_LFO_RATE_OFFSET_2,bitRead(_setValue,i+NUMBER_OF_LFO_RATE_BITS_1));  
    }
    break;

  case LFO_AMT:
    for(int i=0;i<NUMBER_OF_LFO_AMT_BITS_1;i++){
      bitWrite(value[_SOUND][NUMBER_OF_LFO_AMT_BYTE_1],i+NUMBER_OF_LFO_AMT_OFFSET_1,bitRead(_setValue,i));  
    }
    for(int i=0;i<NUMBER_OF_LFO_RATE_BITS_2;i++){
      bitWrite(value[_SOUND][NUMBER_OF_LFO_AMT_BYTE_2],i+NUMBER_OF_LFO_AMT_OFFSET_2,bitRead(_setValue,i+NUMBER_OF_LFO_AMT_BITS_1));  
    }
    break;

  }
}



unsigned char GetValue(unsigned char _VALUE_TYPE,unsigned char _SOUND){
  _SOUND--;

  unsigned char _returnValue=0; 

  switch(_VALUE_TYPE){
  case LETTER_1:
    for(int i=0;i<NUMBER_OF_LETTER_1_BITS;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_LETTER_1_BYTE],i+NUMBER_OF_LETTER_1_OFFSET)); 
    }
    break;

  case LETTER_2:
    for(int i=0;i<NUMBER_OF_LETTER_2_BITS;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_LETTER_2_BYTE],i+NUMBER_OF_LETTER_2_OFFSET)); 
    }
    break;

  case SHIFT_DIR:
    for(int i=0;i<NUMBER_OF_SHIFT_DIR_BITS;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_SHIFT_DIR_BYTE],i+NUMBER_OF_SHIFT_DIR_OFFSET)); 
    }
    break;
    /*
  case LOOP:
     for(int i=0;i<NUMBER_OF_LOOP_BITS;i++){
     bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_LOOP_BYTE],i+NUMBER_OF_LOOP_OFFSET)); 
     }
     break;
     */
  case VOLUME:
    for(int i=0;i<NUMBER_OF_VOLUME_BITS;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_VOLUME_BYTE],i+NUMBER_OF_VOLUME_OFFSET)); 
    }
    break;

  case LFO_DEST:
    for(int i=0;i<NUMBER_OF_LFO_DEST_BITS;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_LFO_DEST_BYTE],i+NUMBER_OF_LFO_DEST_OFFSET)); 
    }
    break;

  case REPEAT:
    for(int i=0;i<NUMBER_OF_REPEAT_BITS;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_REPEAT_BYTE],i+NUMBER_OF_REPEAT_OFFSET)); 
    }
    break;

  case PITCH:
    for(int i=0;i<NUMBER_OF_PITCH_BITS;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_PITCH_BYTE],i+NUMBER_OF_PITCH_OFFSET)); 
    }
    break;

  case CRUSH:
    for(int i=0;i<NUMBER_OF_CRUSH_BITS;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_CRUSH_BYTE],i+NUMBER_OF_CRUSH_OFFSET)); 
    }
    break;

  case LOOP_LEN:
    for(int i=0;i<NUMBER_OF_LOOP_LEN_BITS;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_LOOP_LEN_BYTE],i+NUMBER_OF_LOOP_LEN_OFFSET)); 
    }
    break;

  case START:
    for(int i=0;i<NUMBER_OF_START_BITS;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_START_BYTE],i+NUMBER_OF_START_OFFSET)); 
    }
    for(int i=0;i<NUMBER_OF_START_BITS_2;i++){
      bitWrite(_returnValue,i+NUMBER_OF_START_BITS,bitRead(value[_SOUND][NUMBER_OF_START_BYTE_2],i+NUMBER_OF_START_OFFSET_2)); 
    }
    break;

  case CUT:
    for(int i=0;i<NUMBER_OF_CUT_BITS;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_CUT_BYTE],i+NUMBER_OF_CUT_OFFSET)); 
    }
    break;

case SHIFT_SPEED:
    
     for(int i=0;i<NUMBER_OF_SHIFT_SPEED_BITS_1;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_SHIFT_SPEED_BYTE_1],i+NUMBER_OF_SHIFT_SPEED_OFFSET_1)); 
    }
    for(int i=0;i<NUMBER_OF_LFO_RATE_BITS_2;i++){
      bitWrite(_returnValue,i+NUMBER_OF_SHIFT_SPEED_BITS_1,bitRead(value[_SOUND][NUMBER_OF_SHIFT_SPEED_BYTE_2],i+NUMBER_OF_SHIFT_SPEED_OFFSET_2)); 
    }
    break;
    
  case LFO_RATE:
    for(int i=0;i<NUMBER_OF_LFO_RATE_BITS_1;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_LFO_RATE_BYTE_1],i+NUMBER_OF_LFO_RATE_OFFSET_1)); 
    }
    for(int i=0;i<NUMBER_OF_LFO_RATE_BITS_2;i++){
      bitWrite(_returnValue,i+NUMBER_OF_LFO_RATE_BITS_1,bitRead(value[_SOUND][NUMBER_OF_LFO_RATE_BYTE_2],i+NUMBER_OF_LFO_RATE_OFFSET_2)); 
    }
    break;

  case LFO_AMT:
    for(int i=0;i<NUMBER_OF_LFO_AMT_BITS_1;i++){
      bitWrite(_returnValue,i,bitRead(value[_SOUND][NUMBER_OF_LFO_AMT_BYTE_1],i+NUMBER_OF_LFO_AMT_OFFSET_1)); 
    }
    for(int i=0;i<NUMBER_OF_LFO_AMT_BITS_2;i++){
      bitWrite(_returnValue,i+NUMBER_OF_LFO_AMT_BITS_1,bitRead(value[_SOUND][NUMBER_OF_LFO_AMT_BYTE_2],i+NUMBER_OF_LFO_AMT_OFFSET_2)); 
    }

    break;

  }
  return _returnValue; 
}

char GetLetter(unsigned char _SOUND,unsigned char _letter){
  return GetValue(_letter,_SOUND);
}



void StorePreset(unsigned char index) {

  int offset = index * 128;

  for (int j = 0; j < 15; j++) {
    for (int k = 0; k < 8; k++) {
      EEPROM.write(offset + ((8 * j) + k), value[j][k]);
    }
  }
  //EEPROM.write(offset + 120,tempo);

}


void LoadPreset(unsigned char index) {  

  int offset = index * 128;
  for (int j = 0; j < 15; j++) {
    for (int k = 0; k < 8; k++) {
      value[j][k]=EEPROM.read(offset + ((8 * j) + k));
    }
  }

  //tempo=EEPROM.read(offset + 120);
  preset=index;
  FreezeKnobs();
  AllShouldBeIndexed();

}

void ClearMemmory(){

  DisplayPGMText(CLR);
  for(int j=0;j<8;j++){
    LoadPreset(j);
    currentPreset=j;

    for(int i=1;i<16;i++){

      UpdateUIInputs();
      UpdateUIInputs();
      UpdateUIInputs();

      SetValue(PITCH,i,36);
      SetValue(CRUSH,i,0);

      SetValue(START,i,0);
      SetValue(CUT,i,31);

      SetValue(LOOP_LEN,i,0);
      SetValue(SHIFT_SPEED,i,32);

      SetValue(LFO_AMT,i,0);
      SetValue(LFO_RATE,i,0);

      SetValue(LETTER_1,i,j+1);
      SetValue(LETTER_2,i,i-1);
      SetValue(LOOP,i,0);
      SetValue(SHIFT_DIR,i,0);

      SetValue(REPEAT,i,0);
      SetValue(LFO_DEST,i,0);
      SetValue(VOLUME,i,7);

    }

    tempo=120;
    StorePreset(j);
  }
}


unsigned char GetMIDIChannel() {
  return EEPROM.read(1023);
}

void SetMIDIChannel(unsigned char value) {
  EEPROM.write(1023, value);
}
void IsThereChangeInMidiChannel(){

  for(int i=0;i<4;i++){
    if(ButtonState(bigButtons[i]))
    { 
      channel=i;
    }
  }

}



void ShouldIClearMemory(){ 

  UpdateUIInputs();
  UpdateUIInputs();
  UpdateUIInputs();
  UpdateUIInputs();
  UpdateUIInputs();

  if(ButtonState(bigButtons[0]) && ButtonState(bigButtons[1]) && ButtonState(bigButtons[2]) && ButtonState(bigButtons[3])){
    ClearMemmory();
  }

}


















