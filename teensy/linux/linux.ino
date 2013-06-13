#include <SD.h>

String input = "";         // a string to hold incoming data
String prevCMD = "";
const int LED = 6;
const int SDChip = 20;     //Teensy 2.0++ = 20 

boolean led_on = false;
String pwd = "/";

char ESC = (char)27;  //ASCII-Character for ESC
char ESC2 = (char)91; //ASCII-Character for [
int char_Escape = 0;

void setup() {

  Serial.begin(9600);// initialize serial
  pinMode(LED, OUTPUT);   

  input.reserve(300);// reserve 300 bytes for the input

  if (!SD.begin(SDChip)) {
    Serial.println("SD-Card initialization failed!");
    return;
  }

  while (!Serial); //Wait until Serial is connected
  newCmd();
}

void loop() {
  serialEvent();
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    if(inChar == '\t')
      continue;

    //CTRL+C: abort cmd and start with new cmd
    if(inChar == 3){
      Serial.println("^C");
      newCmd();
      return;
    }

    //Dont send ESC 
    if(inChar == ESC){
      char_Escape = 1;
      return;
    }
    if(char_Escape == 1 || inChar == ESC2){
      char_Escape = 2;
      return;
    }
    if(char_Escape == 2){
      //Arrow up: print last cmd
      if(inChar == 'A'){
        while(input.length() > 0){
          input = input.substring(0,input.length()-1);
          Serial.print((char)127); //ASCII Backspace 
        }
        Serial.print(prevCMD);
        input = prevCMD;
      }

      char_Escape = 0;
      return;
    }


    //Print the Character
    if(inChar != 127 && inChar != ESC){
      Serial.print(inChar);
    }

    //check for known Commands
    if(inChar == '\n' || inChar =='\r'){
      Serial.println();
      processCmd();
      newCmd();
    } 
    //Special Handling for Backspace (127)
    else if(inChar == 127){   
      if(input.length() > 0){
        input = input.substring(0,input.length()-1);
        Serial.print(inChar);
      }
    } 
    else{
      input += inChar;
    }

    blink(1);
  }
}

//Process the Command
void processCmd(){
  prevCMD = input;
  input += " ";

  String cmd = splitString(input,' ',0);
  String arg1 = splitString(input,' ',1);
  String arg2 = splitString(input,' ',2);
  String arg3 = splitString(input,' ',3);

  //Serial.println("split: "+cmd+" -- "+arg1+" -- "+arg2+" -- "+arg3);

  //switch between commands  
  if(cmd == "clear"){
    clearConsole();
  }
  else if(cmd == "man" || cmd == "help"){
    man(arg1);
  }
  else if(cmd == "color"){
    printColored("----====<<<< Color!!! >>>>====----","green");
    Serial.println();
    printColored("----====<<<< Color!!! >>>>====----","yellow");
    Serial.println();
    printColored("----====<<<< Color!!! >>>>====----","blue");
    Serial.println();
    printColored("----====<<<< Color!!! >>>>====----","red");
    Serial.println();
    printColored("----====<<<< Color!!! >>>>====----","magenta");
    Serial.println();
    printColored("----====<<<< Color!!! >>>>====----","cyan");
    Serial.println();
    printColored("----====<<<< Color!!! >>>>====----","white");
    Serial.println();
    printColored("----====<<<< Color!!! >>>>====----","black");
    Serial.println();
  }
  else if(cmd == "whoami"){
    printColored("Teensy","cyan");
    Serial.println();
  }
  else if(cmd == "pwd"){
    Serial.println(pwd);
  }
  else if(cmd == "cd"){
    if(arg1 != "" || arg1 != "\0"){
      pwd += arg1+"/";
    }
    else{
      pwd = "/";
    }
  }
  else if(cmd == "ls"){
    ls(SD.open(toChar(pwd)),0);
  }
  else if(cmd == "mkdir"){
    SD.mkdir(toChar(pwd + arg1));
  }
  else if(cmd == "touch"){
    File newFile = SD.open(toChar(pwd + arg1),FILE_WRITE);
    if(newFile)
      newFile.close();
    else{
      printColored("Failed to create file: "+(pwd+arg1),"red");
      Serial.println();
    }
  }
  else if(cmd == "write"){
    writeFile(arg1, arg2, input);
  }
  else if(cmd == "rm"){
    rm(arg1,arg2,arg3);
  }
  else if(cmd == "cat"){
    cat(arg1,arg2,arg3);
  }
  else if(cmd == "led"){
    if(arg1 == "on"){
      led_on = true;
      digitalWrite(LED, HIGH);
    }
    else if(arg1 == "off"){
      led_on = false;
      digitalWrite(LED, LOW);
    }
  }

  else{
    Serial.println("Unknown cmd: '"+ cmd + "'");
  }

}

//================================================
//==========  functions for commands   ===========
//================================================
void writeFile(String arg1, String arg2, String input){
  File file = SD.open(toChar(pwd + arg1),FILE_WRITE);
  if(!file){
    printColored("Failed to create file: "+(pwd+arg1),"red");
    Serial.println();
    return;
  }
  String text = splitStringLast(input,' ',2);

  Serial.print("Text: '");
  Serial.print(text);
  Serial.println("'");

  file.println(text);
  file.close();
}


void ls(File dir, int numTabs) {
  while(true) {
    File entry =  dir.openNextFile();
    if (!entry) {
      break;
    }
    for (int i=0; i<numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
    } 
    else {
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void clearConsole(){
  //Clears Console with special Commands
  Serial.print(27,BYTE);  // ESC
  Serial.print("[2J");    // clear window
  Serial.print(27, BYTE); // ESC
  Serial.print("[H");     // cursor to home (top)
}

void rm(String arg1, String arg2,String arg3){
  String toRemove = pwd + arg1;
  boolean success = false;

  success |= SD.remove(toChar(toRemove));
  success |= SD.rmdir(toChar(toRemove));

  if(success)
    Serial.println("removed: "+toRemove);
  else{
    printColored("failed to remove: "+toRemove,"red");
    Serial.println();
  }
}

void cat(String arg1, String arg2,String arg3){
  String toPrint = pwd + arg1;
  if(arg1 == ""){
    printColored("Failed to read file: "+toPrint,"red");
    Serial.println();
    return; 
  }


  File file = SD.open(toChar(toPrint),FILE_READ);
  if(file){
    while (file.available()) {
      Serial.write(file.read());
    }
    Serial.println();
    file.close();
  }
  else{
    printColored("Failed to read file: "+toPrint,"red");
    Serial.println();
  }

}






