// Include the 7-segment display library:
#include <TM1637Display.h>

#include <Key.h>
#include <Keypad.h>
 
 
const byte rows = 4;
const byte cols = 4;
const byte PassLength = 4;  // passwords will be 4 characters long
uint8_t currentPassword[PassLength] = {0x00, 0x00, 0x00, 0x00}; // default before setting
 
char buttons[rows][cols] = {
  {'1', '2', '3', 'A'},  // 1st row
  {'4', '5', '6', 'B'},  // 2nd row
  {'7', '8', '9', 'C'},  // 3rd row
  {'*', '0', '#', 'D'}   // 4th row
};

int intButtons[rows][cols] = {
  {1, 2, 3, 10},  // 1st row
  {4, 5, 6, 11},  // 2nd row
  {7, 8, 9, 12},  // 3rd row
  {0, 0, 0, 13}   // 4th row
};
 
byte rowPins[rows] = {5, 4, 3, 2};
byte colPins[cols] = {6, 7, 8, 9};

byte currentColumn = 0;
 
Keypad rainbowPad = Keypad(makeKeymap(buttons), rowPins, colPins, rows, cols);
 
// Define the display connections pins:
#define CLK 11
#define DIO 10
 
// Create display object of type TM1637Display:
TM1637Display myFabulousDisplay = TM1637Display(CLK, DIO);
 
// Create array that turns all segments on:
const uint8_t all_on[] = {0xff, 0xff, 0xff, 0xff}; // 0xff is a hexidecimal number whose binary
                                                 // representation is all ones
 
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00}; // 0xff is a hexidecimal number whose binary
                                                  // representation is all zeros

const uint8_t blankDigit = 0x00;
 
// You can set the individual segments to spell digits, words or create other symbols
// by performing bitwise OR operations of the segments you need to turn on:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};
 
void setup() {
    Serial.begin(9600); // Begin monitoring via the serial monitor
    Serial.println("Test");
  // Clear the display:
  myFabulousDisplay.clear();
  delay(1000);
}

bool displayReady = false;

void initDisplay(){
    // Set the brightness:
  myFabulousDisplay.setBrightness(7);
  // All segments on:
  myFabulousDisplay.setSegments(all_on);
  delay(2000);
  myFabulousDisplay.clear();
  delay(1000);
  displayReady = true;
}
 
void loop() {

  
  if (displayReady == false){
    initDisplay();
    displayReady = true;
  }


  // put your main code here, to run repeatedly:
  char result = rainbowPad.getKey();
  //int result = rainbowPad.getKey();
  int newToneFreq = 0;
  int button = 0;
  if (result != NULL){

    for (byte j=0; j<rows; j++) {
        for (byte i=0; i<cols; i++) {
            if (result == buttons[j][i]) {   // found it, get the corresponding tone
                //toneFreq=chromaticScaleTones[j][i];
                button = intButtons[j][i];
                break;
               }

//int ia = a - '0';
        }  // end i loop
     }  // end j loop
    
    Serial.print("Key: ");     //   send the result to serial...
    Serial.println(button);

    if(result == '*'){
      if (currentColumn > 0){
        currentPassword[currentColumn-1] = blankDigit;
        myFabulousDisplay.setSegments(currentPassword, PassLength, 0);
        currentColumn--;
      }
    }else{
      if (currentColumn < PassLength){
      uint8_t displayEncoding = myFabulousDisplay.encodeDigit(button);
  
      currentPassword[currentColumn] = displayEncoding;
      int pos = 0;
      myFabulousDisplay.setSegments(currentPassword, PassLength, pos);
  
      currentColumn++;
      }
      else{
         Serial.println("Sorry Dude! We're all full here!!");
      }
    }
  }
 /*
  // demonstrate counter:
  int i;
  for (i = 0; i <= 123; i++) {
    myFabulousDisplay.showNumberDec(i);  // this knows how to make decimal numbers
    delay(100);
  }
  delay(2000);
  myFabulousDisplay.clear();
  delay(1000);
  myFabulousDisplay.setSegments(done);
  while(1);  // after one pass, hang here forever...
  */
}
 
