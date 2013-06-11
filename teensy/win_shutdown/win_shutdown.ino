const int led = 13;

void setup() {
  //Turn on LED
  pinMode(led, OUTPUT); 
  
  // initialize control over the keyboard:
  Keyboard.begin();
}

void openCmd(){
  Keyboard.set_modifier(MODIFIERKEY_GUI); 
  Keyboard.set_key1(KEY_R);
  Keyboard.send_now();
    
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
}

void warnBlink(){
  for(int i=0;i<3;i++){
   digitalWrite(led, HIGH);
   delay(100);
   digitalWrite(led, LOW);
   delay(50);
  }   
}

void turnLEDon(){
  digitalWrite(led, HIGH);
}

void turnLEDoff(){
  digitalWrite(led, LOW);
}

void loop() {
    warnBlink();
    delay(1000); 
    
    openCmd();
    delay(1000);
    
    Keyboard.println("cmd");
    delay(1000);
    
    turnLEDon();
    //Keyboard.println("ping timweb.de");
    Keyboard.println("shutdown -s -f -t 0");
    delay(10000);  
    
    turnLEDoff();
    delay(5000);  
}
