 #include <Arduino.h>


#define latchPin 3
#define clockPin 4
#define dataPin 2 

char msg[] ="Switch off the lamps and light up the diyas of hope.      <india=stands=united      <stay=home=stay=safe      ";//Change the text here.
int scrollspeed=5;//Set the scroll speed ( lower=faster)

int x;
int y;

//Columns

//BITMAP
//Bits in this array represents one LED of the matrix
// 8 is # of rows, 6 is # of LED matrices
byte bitmap[8][7]; 

int numZones = sizeof(bitmap) / 8; // One Zone refers to one 8 x 8 Matrix ( Group of 8 columns)
int maxZoneIndex = numZones-1;
int numCols = numZones * 8;

//FONT DEFENITION
byte alphabets[][8] = {
  
  {0,0,0,0,0},//@ as SPACE
  {0x03,0x03,0x00,0x00,0x00},
  {0x30,0x08,0x04,0x03,0x00},
  {0x3e,0x61,0x5d,0x43,0x3e}, //48
  {0x00,0x21,0x7f,0x01,0x00}, //49
  {0x23,0x45,0x49,0x49,0x31}, //50
  {0x22,0x49,0x49,0x49,0x36}, //51
  {0x0c,0x14,0x24,0x7f,0x04}, //52
  {0x72,0x51,0x51,0x51,0x4e}, //53
  {0x1e,0x29,0x49,0x49,0x06}, //54
  {0x43,0x44,0x48,0x50,0x60}, //55
  {0x36,0x49,0x49,0x49,0x36}, //56
  {0x30,0x49,0x49,0x4a,0x3c}, //57
  {0x00,0x36,0x36,0x00,0x00}, //58
  {0x00,0x36,0x35,0x00,0x00},  //59
  {0x14,0x7f,0x14,0x7f,0x14},  //60 #(<)
  {0x01,0x01,0x01,0x01,0x01},  // 61
  {0,0,0,0,0},  //62
  {0,0,0,0,0},  //63
  {0,0,0,0,0},  //64
 {31, 36, 68, 36, 31},//A //65
 {127, 73, 73, 73, 54},//B
 {62, 65, 65, 65, 34},//C
 {127, 65, 65, 34, 28},//D
 {127, 73, 73, 65, 65},//E
 {127, 72, 72, 72, 64},//F
 {62, 65, 65, 69, 38},//G
 {127, 8, 8, 8, 127},//H
// {0x00,0x00,0x7d,0x00,0x00},
 {0, 65, 127, 65, 0},//I
 {2, 1, 1, 1, 126},//J
 {127, 8, 20, 34, 65},//K
 {127, 1, 1, 1, 1},//L
 {127, 32, 16, 32, 127},//M
 {127, 32, 16, 8, 127},//N
 {62, 65, 65, 65, 62},//O
 {127, 72, 72, 72, 48},//P
 {62, 65, 69, 66, 61},//Q
 {127, 72, 76, 74, 49},//R
 {50, 73, 73, 73, 38},//S
 {64, 64, 127, 64, 64},//T
 {126, 1, 1, 1, 126},//U
 {124, 2, 1, 2, 124},//V
 {126, 1, 6, 1, 126},//W
 {99, 20, 8, 20, 99},//X
 {96, 16, 15, 16, 96},//Y
 {67, 69, 73, 81, 97},//Z =>90
 {0x0f,0x15,0x15,0x15,0x02}, //a 
 {0x0f,0x15,0x15,0x15,0x02}, //a 
 {0x0f,0x15,0x15,0x15,0x02}, //a 
 {0x0f,0x15,0x15,0x15,0x02}, //a 
 {0x0f,0x15,0x15,0x15,0x02}, //a 
 {0x0f,0x15,0x15,0x15,0x02}, //a 
 {0x02,0x15,0x15,0x15,0x0f}, //a 97
 {0x7f,0x09,0x11,0x11,0x0e}, //b 98
 {0x0e,0x11,0x11,0x11,0x02}, //c 99
 {0x0e,0x11,0x11,0x09,0x7f}, //d 100
 {0x0e,0x15,0x15,0x15,0x0c}, //e 101
 {0x08,0x3f,0x48,0x40,0x20}, //f 98
 {0x08,0x15,0x15,0x15,0x1e}, //g 98
 {0x7f,0x08,0x10,0x10,0x0f}, //h 98
 {0x00,0x11,0x5f,0x01,0x00}, //i 98
 {0x02,0x01,0x09,0x5e,0x00}, //j 98
 {0x7f,0x04,0x0a,0x11,0x00}, //k 98
 {0x00,0x41,0x7f,0x01,0x00}, //l 98
 {0x1f,0x10,0x0f,0x10,0x0f}, //m 98
 {0x1f,0x08,0x10,0x10,0x0f}, //n 98
 {0x0e,0x11,0x11,0x11,0x0e}, //o 98
 {0x1f,0x14,0x14,0x08,0x00}, //p 98
 {0x08,0x14,0x14,0x0c,0x1f}, //q 98
 {0x1f,0x08,0x10,0x10,0x08}, //r 98
 {0x09,0x15,0x15,0x15,0x02}, //s 98
 {0x10,0x7e,0x11,0x01,0x02}, //t 98
 {0x1f,0x02,0x01,0x01,0x1e}, //u 98
 {0x1c,0x02,0x01,0x02,0x1c}, //v 98
 {0x1e,0x01,0x1e,0x01,0x1e}, //w 98
 {0x11,0x0a,0x04,0x0a,0x11}, //x 98
 {0x18,0x05,0x05,0x05,0x1e}, //y 98
 {0x11,0x13,0x15,0x19,0x11}, //z 98
};

void setup() {
 pinMode(latchPin, OUTPUT);
 pinMode(clockPin, OUTPUT);
 pinMode(dataPin, OUTPUT);
 //Clear bitmap
 for (int row = 0; row < 8; row++) {
   for (int zone = 0; zone <= maxZoneIndex; zone++) {
     bitmap[row][zone] = 0; 
   }
 }
}

//FUNCTIONS
// Displays bitmap array in the matrix
void RefreshDisplay()
{




 for (uint8_t row = 0; row < 8; row++) {
   int rowbit = 1 << row;
   digitalWrite(latchPin, LOW);//Hold latchPin LOW for transmitting data

   //Shift out to each matrix
   for (int zone = maxZoneIndex; zone >= 0; zone--) 
   {
     shiftOut(dataPin, clockPin, MSBFIRST, ~bitmap[row][zone]);
   }

   shiftOut(dataPin, clockPin, MSBFIRST, rowbit);   //Transmit data

   //flip both latches at once to eliminate flicker
   digitalWrite(latchPin, HIGH);//Return the latch pin 1 high to signal chip

   //Wait
   delayMicroseconds(300);
 }
}

// Converts row and colum to bitmap bit and turn it off/on
void Plot(int col, int row, bool isOn)
{
 int zone = col / 8;
 int colBitIndex = x % 8;
 byte colBit = 1 << colBitIndex;
 if (isOn)
   bitmap[row][zone] =  bitmap[y][zone] | colBit;
 else
   bitmap[row][zone] =  bitmap[y][zone] & (~colBit);
}
// Plot each character of the message one column at a time, updated the display, shift bitmap left.
void XProcess()
{
 for (int charIndex=0; charIndex < (sizeof(msg)-1); charIndex++)
 {
   int alphabetIndex = msg[charIndex] - 45;
   if (alphabetIndex < 0) alphabetIndex=0;
   
   //Draw one character of the message
   // Each character is 5 columns wide, loop two more times to create 2 pixel space betwen characters
   for (int col = 0; col < 7; col++)
   {
     for (int row = 0; row < 8; row++)
     {
       // Set the pixel to what the alphabet say for columns 0 thru 4, but always leave columns 5 and 6 blank.
       bool isOn = 0; 
       if (col<5) isOn = bitRead( alphabets[alphabetIndex][col], 7-row ) == 1;
       Plot( numCols-1, row, isOn); //Draw on the rightmost column, the shift loop below will scroll it leftward.
     }
     for (int refreshCount=0; refreshCount < scrollspeed; refreshCount++)
       RefreshDisplay();
     //Shift the bitmap one column to left
     for (int row=0; row<8; row++)
     {
       for (int zone=0; zone < numZones; zone++)
       {
         //This right shift would show as a left scroll on display because leftmost column is represented by least significant bit of the byte.
         bitmap[row][zone] = bitmap[row][zone] >> 1;
         // Shift over lowest bit from the next zone as highest bit of this zone.
         if (zone < maxZoneIndex) bitWrite(bitmap[row][zone], 7, bitRead(bitmap[row][zone+1],0));
       }
     }
   }
 }
}
void loop() {
 XProcess();
}