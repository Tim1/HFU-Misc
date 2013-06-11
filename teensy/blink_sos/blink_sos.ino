/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
// give it a name:
int led = 6;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);   
  Serial.begin(9600);  
}

void blink_short(){
  for(int i=0;i<3;i++){
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(50);
  }   
}

void blink_long(){
  for(int i=0;i<3;i++){
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    delay(50);
  }   
}

// the loop routine runs over and over again forever:
void loop() {
  blink_short();
  blink_long();
  blink_short();
  delay(200);
  Serial.println("Hello world");
}

