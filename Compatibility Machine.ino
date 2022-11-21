// constants for the pins
const int ledPinred = 3;
const int ledPinblue = 2;
const int ledPinyellow = 4;
const int potPin = A0;
const int buttonPin = 5;

// other global variables
int buttonState = 0;
int answer;
unsigned long myTime;
bool start;


void setup() {
  // set the led pins as outputs
  pinMode(ledPinred, OUTPUT);
  pinMode(ledPinblue, OUTPUT);
  pinMode(ledPinyellow, OUTPUT);

   // set the button pins as input
  pinMode(buttonPin, INPUT);
  randomSeed(4087786);

  answer = random(2,5);
  start = false;
  
  // open the serial port for communication
  Serial.begin(9600);
  
  while(!Serial){
    ;; // do nothing until the serial port opens 
  }
  myTime = millis();
}


void loop() {
  
  // read the value of the pin and store it
  // this will be in a range of 0-85
  int potVal = analogRead(potPin);
  buttonState = digitalRead(buttonPin);

// if button state is high, program resets

  if (buttonState == HIGH) {
    myTime = millis();
    answer= random(2,5);
    delay(1000);
    Serial.print("press");
    start = true;

  }

if (start) {
  // map the value to the range of analogOut
  // store that in a new variable lovaVal
  int loveVal = map(potVal, 0, 85, 0, 60);
 
// compatibility machines takes 10 seconds to calculate the result during which users can wave their hands in front of it.

  if (millis() - myTime < 10000){

    if (loveVal < 20){
      analogWrite (ledPinblue, 60);
      analogWrite (ledPinred, 0);
      analogWrite (ledPinyellow, 0); 

    } else if (loveVal > 20 && loveVal < 40){
      analogWrite (ledPinyellow, 60);
      analogWrite (ledPinblue, 0); 
      analogWrite (ledPinred, 0);    

    } else if (loveVal > 40){
      analogWrite (ledPinred, 60);
      analogWrite (ledPinblue, 0);    
      analogWrite (ledPinyellow, 0);  
    }
  }

// after 10 seconds machine will give out result
else if (millis() - myTime > 10000){
 
//  the answer is actually random base on the answer variable

  if (answer == 2){
    analogWrite (ledPinblue, 60);
    analogWrite (ledPinred, 0);    
    analogWrite (ledPinyellow, 0); 
    // Serial.print("Love Compatibility = Breakup ASAP!!"); 

  } else if (answer == 3){
    analogWrite (ledPinyellow, 60);
    analogWrite (ledPinblue, 0);
    analogWrite (ledPinred, 0); 
    // Serial.print("Love Compatibility = Not Really Feeling It"); 

  }else if (answer == 4){
    analogWrite (ledPinred, 60);
    analogWrite (ledPinblue, 0);    
    analogWrite (ledPinyellow, 0);  
    // Serial.print("Love Compatibility = Forever in Love"); 

   
}
  delay(10);
}
}