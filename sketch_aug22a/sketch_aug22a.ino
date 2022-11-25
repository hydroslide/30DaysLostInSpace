int light1 = 10; // Hero board pin 12
int light2 = 11; // Hero board pin 12
int light3 = 12; // Hero board pin 12
int switch1 = 2;//pin 2 is the switch
int switch2 = 3;//pin 2 is the switch
int switch3 = 4;//pin 2 is the switch
int sensorPin = A0;
unsigned int sensorValue;
unsigned int batteryCapacity=50000;
unsigned int batteryLevel=0;
unsigned int ticks=0;
unsigned int wait=100;
double percentFull;
int minSensorLevel = 30;
double modifier = 5;

void setup() {
  // put your setup code here, to run once:
pinMode(light1, OUTPUT);
pinMode(light2, OUTPUT);
pinMode(light3, OUTPUT);
pinMode(switch1, INPUT);
pinMode(switch2, INPUT);
pinMode(switch3, INPUT);
//digitalWrite(light, HIGH);
Serial.begin(9600);
}

void loop() {
  //showSOS();
  //switchSOS();
  //toggleLight(switch1,  light1);
  //toggleLight(switch2,  light2);
  //toggleLight(switch3,  light3);
  
  sensorValue = analogRead(sensorPin);
//Serial.println(sensorValue);
  if (sensorValue >=minSensorLevel){
  batteryLevel += (int)(modifier * sensorValue);
  ticks += wait;

  if (batteryLevel >= batteryCapacity){
    Serial.print(ticks);
    Serial.println(" ms    FULLY CHARGED");

    lightOn(light1);
    lightOn(light2);
    lightOn(light3);
    
    batteryLevel = batteryCapacity;
    ticks = 0;
    delay(5000);
  }
  else{
    printBatteryLevel();
    updateStatusLights();
  }
  }else{
    ticks = 0;
    int valueUsed =  minSensorLevel-sensorValue;
    int tempBatteryLevel = (int)batteryLevel - (int)(modifier * valueUsed *5);
    if (tempBatteryLevel > 0){
      batteryLevel = tempBatteryLevel;
      Serial.print("Draining Battery: ");
      Serial.print(getPercentFull());
      Serial.println("%");
      updateStatusLights();
    }else{
      batteryLevel = 0;
      Serial.println("Battery is DEAD. Please Recharge.");
      lightOff(light1);
      lightOff(light2);
      lightOff(light3);
      delay(5000);
    }
  }
  
//  if (sensorValue < 60){
//    //digitalWrite(light1, HIGH);
//    showSOS();
//  }
//  else{
//    digitalWrite(light1, LOW);
//  }
//  Serial.println(sensorValue);
//  delay(500);
}

void updateStatusLights(){
  double pct = getPercentFull();
  if (pct >0 && pct <= 33){
    lightOff(light3);
    lightOff(light2);
    blinkLight(light1);
  }else if (pct > 33 && pct <= 66){
    lightOff(light3);
    lightOn(light1);
    blinkLight(light2);
  }else if (pct > 66 && pct < 100){
    lightOn(light2);
    lightOn(light1);
    blinkLight(light3);
  }
}

double getPercentFull(){
  double tempPercent = 100*((double)batteryLevel/(double)batteryCapacity);
  return tempPercent;
}

void lightOn(int theLight){
  digitalWrite(theLight, HIGH);
}

void lightOff(int theLight){
  digitalWrite(theLight, LOW);
}

void printBatteryLevel(){
  percentFull = getPercentFull();
  Serial.print(ticks);
  Serial.print(" ms    charge at ");
  Serial.print(percentFull);
  Serial.println("%");
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
   digitalWrite(light1, HIGH); // turn the LED on (HIGH is the voltage level)
   delay(dotdash); // wait for a second
   digitalWrite(light1, LOW); // turn the LED off by making the voltage LOW
   delay(gap); 
}
