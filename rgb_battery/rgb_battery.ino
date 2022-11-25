//int rLight = 3;//11;
//int gLight = 5; //10;
//int bLight =6; //9;

int rLight = 11;
int gLight = 10;
int bLight =9;


void setup() {
  // put your setup code here, to run once:
pinMode(rLight, OUTPUT);
pinMode(gLight, OUTPUT);
pinMode(bLight, OUTPUT);

//Serial.begin(9600);
}

void loop() {
  //showSOS();
  //switchSOS();
  //toggleLight(switch1,  light1);
  //toggleLight(switch2,  light2);
  //toggleLight(switch3,  light3);

  /*
  setColor(195, 0, 255);
  delay(1001);
   setColor(13, 166, 255);
   delay(1001);
   */

  police();
  chunkyRainbow();
  smoothRainbow();
}

void police(){
    blinkColor(255,0,0,50,100,3);
     blinkColor(0,0,255,50,100,3);
}

void smoothRainbow(){
  int d = 3;
  int r=255;
  int g=0;
  int b=0;

  int stepValue = 1;

  
  for(g=0; g<255; g+= stepValue){
    setColor(r,g,b);
    delay(d);
  }
  for(r=255; r>0; r-= stepValue){
    setColor(r,g,b);
    delay(d);
  }
  for(b=0; b<255; b+= stepValue){
    setColor(r,g,b);
    delay(d);
  }
  for(g=255; g>0; g-= stepValue){
    setColor(r,g,b);
    delay(d);
  }
  for(r=0; r<255; r+= stepValue){
    setColor(r,g,b);
    delay(d);
  }
  for(b=255; b>0; b-= stepValue){
    setColor(r,g,b);
    delay(d);
  }
}

void chunkyRainbow(){
  showColor(255,0,0);
  showColor(255,136,0);
  showColor(255,247,0);
  showColor(157,255,0);
  showColor(0,255,204);
  showColor(0,81,255);
  showColor(106,0,255);
  showColor(255,0,247);
}

void showColor(int r, int g, int b){
  setColor(r,g,b);
  delay(500);
}

void setColor(int r, int g, int b){
  analogWrite(rLight, r);
  analogWrite(gLight, g);
  analogWrite(bLight, b);
}




void lightOn(int theLight){
  digitalWrite(theLight, HIGH);
}

void lightOff(int theLight){
  digitalWrite(theLight, LOW);
}



void toggleLight(int theSwitch, int theLight){
  if (digitalRead(theSwitch) == HIGH){
    digitalWrite(theLight, HIGH);
  }
  else{
    digitalWrite(theLight, LOW);
  }
  
}

void blinkLight(int theLight){
  digitalWrite(theLight, HIGH);
  delay(100);
  digitalWrite(theLight, LOW);
  delay(900);
}

void blinkColor(int r, int g, int b, int timeOn, int timeOff, int repeat){
  for (int i = 0; i< repeat; i++){
    setColor(r,g,b);
    delay(timeOn);
    setColor(0,0,0);
    delay(timeOff);
  }
}

/*
void switchSOS(){
  int switch1Value = digitalRead(switch1);
  if (switch1Value == HIGH){
    showSOS();
  }
  else{
    digitalWrite(light, HIGH);
  }
}
*/
void showSOS(){
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
  delay(gap);
}

void showO(){
  showDash();
  showDash();
  showDash();
  delay(gap);
}

void showDot(){
  showDotDash(dot);
}

void showDash(){
  showDotDash(dash);
}


void showDotDash(int dotdash){
  /*
   digitalWrite(light1, HIGH); // turn the LED on (HIGH is the voltage level)
   delay(dotdash); // wait for a second
   digitalWrite(light1, LOW); // turn the LED off by making the voltage LOW
   delay(gap); 
   */
}
