#define latchPin 8    //Store pin of shiftregister (pin 12)
#define dataPin 11    //Serial in of shift register (pin 14)
#define clockPin 12   // shift clock pin of shift register (pin 11)
byte data[][8] = {{0x00,0xe0,0x90,0x90,0xe0,0xa0,0x90,0x00},
                  {0x00,0x60,0x90,0x90,0x90,0x90,0x60,0x00},
                  {0x00,0x90,0x90,0xf0,0xf0,0x90,0x90,0x00},
                  {0x00,0xe0,0x40,0x40,0x40,0x40,0xe0,0x00},
                  {0x00,0xe0,0x40,0x40,0x40,0x40,0x40,0x00},
                  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};     // data to be displayed in matrix
const short n=2,                                                  // Number of shift registers in a row
            datalength=6;                                         // total number of characters in data
byte **registerState;                                             //starting address for registerStates
short b=0,r=0,c=0,s=0,dataLength=11;                              // index for bits,registers,characters,row
bool temp=0,rem=0;                                                // varialble for holding msb of byte
void setup(){
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);

  // Turn off the display
  registerState = new byte*[8];
  for(int row=0;row<8;row++){
    registerState[row] = new byte[n];
    for(int col=0;col<n;col++){
      registerState[row][col]=0;
    }
  }
}
void loop(){
  for(c=0; c<dataLength; c++){                                    // Iterating through eacch vharacter in data
      for(b=0;  b<8; b++){                                        // Iterating through each bit in character
            for(s=0; s<8; s++){                                   // Iterating through each row on the matrix
            for(r=0; r<n; r++){                                   // Iterating each register in a row
              if(r==0)
                rem = (data[c][s] >> (7-b)) & 1;                  // for first register msb is taken from data
              temp=rem;
              rem=(registerState[s][r] >> 7) & 1;                 // For successive registers msb is taken from previous registers
              registerState[s][r] = registerState[s][r] << 1;     // left shift the data
              registerState[s][r] = registerState[s][r] & 255;    // make sure data is a byte not exceeding 255
              registerState[s][r] = registerState[s][r] | temp;   // Appending msb of previous register to lsb of current regiser
              shiftOut(dataPin,clockPin,LSBFIRST,~registerState[s][r]); //Writing data on storage registers
            } 
              shiftOut(dataPin,clockPin,LSBFIRST,128>>s);         // Shifting through the rows top-bottom
              store();
              delay(6);
          }
          
      }
  }
}


void store(){
  digitalWrite(latchPin,HIGH);                                    // A pulse to latch the output the data in storage registers
  delayMicroseconds(10);
  digitalWrite(latchPin,LOW);
  delayMicroseconds(10);
}
