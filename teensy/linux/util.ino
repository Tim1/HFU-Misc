//================================================
//=============   Util functions  ================
//================================================

//makes console ready for new Command
void newCmd(){
  input = "";
  Serial.print("Teensy "); 
  printColored(pwd,"red");
  Serial.print(" > "); 
}

//Blinks LED
void blink(int times){
  if(led_on)
    return;

  for(int i = 0; i < times; i++){
    digitalWrite(LED, HIGH);
    delay(10);
    digitalWrite(LED, LOW);
    delay(5);
  } 
}

String splitString(String s, char parser,int index){
  String rs='\0';
  int parserIndex = index;
  int parserCnt=0;
  int rFromIndex=0, rToIndex=-1;

  while(index>=parserCnt){
    rFromIndex = rToIndex+1;
    rToIndex = s.indexOf(parser,rFromIndex);

    if(index == parserCnt){
      if(rToIndex == 0 || rToIndex == -1){
        return '\0';
      }
      return s.substring(rFromIndex,rToIndex);
    }
    else{
      parserCnt++;
    }

  }
  return rs;
}

String splitStringLast(String s, char parser,int index){
  String rs='\0';
  int parserIndex = index;
  int parserCnt=0;
  int rFromIndex=0, rToIndex=-1;

  while(index>=parserCnt){
    rFromIndex = rToIndex+1;
    rToIndex = s.indexOf(parser,rFromIndex);

    if(index == parserCnt){
      if(rToIndex == 0 || rToIndex == -1){
        return '\0';
      }
      return s.substring(rFromIndex,s.length());
    }
    else{
      parserCnt++;
    }

  }
  return rs;
}

char* toChar(String str){
  char charBuf[str.length()+1];
  for(int i=0;i<str.length();i++){
    if(str.substring(i,i+1) == "/")
      charBuf[i] = '/';
    else
      charBuf[i] = str.charAt(i);
  }
  charBuf[str.length()] = '\0';

  //tr.toCharArray(charBuf, sizeof(charBuf)); 
  return charBuf;
}

void printColored(String msg, String color){
  String colorCode = "[0;";
  if(color == "red")
    colorCode += "31";
  else if(color == "green")
    colorCode += "32";
  else if(color == "yellow")
    colorCode += "33";
  else if(color == "blue")
    colorCode += "34";
  else if(color == "magenta")
    colorCode += "35";
  else if(color == "cyan")
    colorCode += "36";
  else if(color == "white")
    colorCode += "37";
  else
    colorCode += "30";

  colorCode += ";40m";

  Serial.print(27,BYTE);  // ESC
  Serial.print(colorCode + msg);

  Serial.print(27,BYTE);  // ESC
  Serial.print("[0;37;40m");   

}
