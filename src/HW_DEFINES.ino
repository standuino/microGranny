#define LATCH_PIN 7
#define CLOCK_PIN 6
#define DATA_PIN 8

#define ROW_1_PIN 16
#define ROW_2_PIN 17
#define ROW_3_PIN 18
#define ROW_4_PIN 9
#define ROW_5_PIN 19

#define SET 8
#define PREW 2 
#define UP 1
#define DOWN 0
#define BIG_1 3
#define BIG_2 4
#define BIG_3 5
#define BIG_4 6
#define POT 7


#define KNOB_PIN_0 0
#define KNOB_PIN_1 1

#define KNOB_TOLERANCE 3
#define KNOB_FREEZE_DISTANCE 128
#define NUMBER_OF_KNOBS 2
#define NUMBER_OF_BUTTONS 9

#define SWITCH 4
unsigned char mode;
const unsigned char row[5]={ ROW_1_PIN,ROW_2_PIN,ROW_3_PIN,ROW_4_PIN,ROW_5_PIN };
const unsigned char bigButtons[4]={BIG_1,BIG_2,BIG_3,BIG_4};
const unsigned char knobPin[4]={KNOB_PIN_0,KNOB_PIN_1};

PROGMEM prog_uint16_t noteSampleRateTable[49]={/*0-C*/2772,2929,3103,3281,3495,3679,3910,4146,4392,4660,4924,5231,/*12-C*/5529,5863,6221,6579,6960,7355,7784,8278,8786,9333,9847,10420,/*24 C*/11025,11665,12402,13119,13898,14706,15606,16491,17550,18555,19677,20857,/*36-C*/22050,23420,24807,26197,27815,29480,31215,33070,35064,37119,39318,41709,/*48-C*/44100};
PROGMEM prog_char texts[]={"standuinoxxxindintpardirpchcrsstrcutshfloprteamtonnoffnorbckrndrd2presel2nd1strepdirlfovolcopsvesvdlpslpecpdpstclr"};
#define XXX 9
#define IND 12
#define INT 15
#define PAR 18
#define DIR 21
#define PCH 24
#define CRS 27
#define STR 30
#define CTT 33
#define SHF 36
#define LOP 39
#define RTE 42
#define AMT 45
#define ONN 48
#define OFF 51
#define FWD 54
#define BCK 57
#define RD1 60
#define RD2 63
#define PRE 66
#define SEL 69

#define ND 72
#define ST 75
#define REP 78
#define DIR 81
#define LFO 84
#define VOL 87
#define COP 90
#define SVE 93
#define SVD 96
#define LPS 99
#define LPE 102
#define CPD 105
#define PST 108
#define CLR 111


#define SEG_A 7 //Display pin 14
#define SEG_B 6 //Display pin 16
#define SEG_C 5 //Display pin 13
#define SEG_D 4 //Display pin 3
#define SEG_E 3 //Display pin 5
#define SEG_F 2 //Display pin 11
#define SEG_G 1 //Display pin 15
#define SEG_DOT 0


/*
Segments
 -  A
 F / / B
 -  G
 E / / C
 -  D
 */
 
const unsigned char segments[8]={
  SEG_A,SEG_B,SEG_C,SEG_D,SEG_E,SEG_F,SEG_G,SEG_DOT};


PROGMEM prog_uchar typo[38]={
  B00111111,  //0
  B00000110,  //1
  B01011011, //2
  B01001111, //3
  B01100110, //4
  B01101101, //5
  B01111101, //6
  B00000111, //7
  B01111111, //8
  B01101111, //9
  B01110111, //A 10
  B01111100, //b
  B01011000, //c
  B01011110, //d
  B01111001, //e
  B01110001, //f
  B00111101, //g
  B01110100, //h
  B00000100, //i
  B00011110, //j 
  B01110000, //k 20
  B00111000, //l
  B01010101, //m
  B01010100, //n
  B01011100, //o 
  B01110011, //p 25
  B01100111, //q
  B01010000, //r
  B01101101, //s //tu memit 
  B01111000, //t 
  B00011100, //u 30
  B00001100, //v 31
  B01101010, //w
  B01001001, //x 
  B01110010, //y 
  B01011011, //z tu menit 35
  B00000000, // void 36
  B01000000,
};

#define VOID 36
#define MINUS 37

/*
Segments
 -  A
 F / / B
 -  G
 E / / C
 -  D
 */
 
 

