#include <Key.h>
#include <Keypad.h>
#include "frequencies.h"

 const byte rows =4;
 const byte cols =4;

 byte rowPins[rows] = {5,4,3,2};
 byte colPins[cols] = {6,7,8,9};

 int buzzer=10;

 char buttons[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
 };

  int scaleTones[rows][cols] = {
  {31,93,147,208},
  {247,311,370,440},
  {523,587,698,880},
  {1397,2637,3729,4978}
 };

   int chromaticScaleTones[rows][cols] = {
  {1046,554,622,0},
  {523,587,659,0},
  {0,740,831,932},
  {698,784,880,988}
 };

 int tones[rows][cols];

Keypad rainbowPad = Keypad(makeKeymap(buttons), rowPins, colPins, rows, cols);
//Keypad rainbowPad = Keypad(makeKeymap(scaleTones), rowPins, colPins, rows, cols);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  tones= *scaleTones;
  //tones=chromaticScaleTones;
}

int toneFreq = 0;
int toneTime = 50;

void loop() {
  
  // put your main code here, to run repeatedly:
  char result = rainbowPad.getKey();
  //int result = rainbowPad.getKey();
  int newToneFreq = 0;
  if (result != NULL){

    for (byte j=0; j<rows; j++) {
        for (byte i=0; i<cols; i++) {
            if (result == buttons[j][i]) {   // found it, get the corresponding tone
                toneFreq=chromaticScaleTones[j][i];
                break;
               }
           
        }  // end i loop
     }  // end j loop
    
    Serial.print("Key: ");     //   send the result to serial...
    Serial.print(result);
    Serial.print("   Freq: ");
    Serial.println(toneFreq);

   
  }else{
    if (rainbowPad.getState() == RELEASED)
      toneFreq = 0;
  }
    

    if (toneFreq !=0 ){
      //tone(buzzer, toneFreq, toneTime);  // ... and play the tone for a half second
      tone(buzzer, toneFreq);
      //delay(toneTime-2);
      //noTone(buzzer);
    }else
      noTone(buzzer);
  
}
