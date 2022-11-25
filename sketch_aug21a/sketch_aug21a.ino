/*
   Blink
   Turns on an LED on for one second, then off for one second, repeatedly.
*/
 
// the setup function runs once when you press reset or power the board
 
void setup() {  // initialize digital pin 13 as an output.
   pinMode(13, OUTPUT);
}
 
// the loop function runs over and over again forever
 
void loop() {
  /*
   digitalWrite(13, HIGH); // turn the LED on (HIGH is the voltage level)
   delay(200); // wait for a second
   digitalWrite(13, LOW); // turn the LED off by making the voltage LOW
   delay(300); // wait for a second
   */
   showS();
   showO();
   showS();
   delay(1000);
}

int dot = 250;
int dash = 500;
int gap=100;

void showS(){
  showDot();
  showDot();
  showDot();
}

void showO(){
  showDash();
  showDash();
  showDash();
}

void showDot(){
  showDotDash(dot);
}

void showDash(){
  showDotDash(dash);
}

void showDotDash(int dotdash){
   digitalWrite(13, HIGH); // turn the LED on (HIGH is the voltage level)
   delay(dotdash); // wait for a second
   digitalWrite(13, LOW); // turn the LED off by making the voltage LOW
   delay(gap); 
}
