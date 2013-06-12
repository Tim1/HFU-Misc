// man pages: list information about command
void man(String arg1){
  String desc_clear = "clears the console";
  String desc_whoami = "prints Teensy";
  String desc_pwd = "prints the current directory";
  String desc_cd = "changes into directory";
  String desc_ls = "prints the current directory";
  String desc_mkdir = "creates a new directory in the current directory";
  String desc_touch = "creates a new file in the current directory";
  String desc_write = "writes a given string into a file (appending)";
  String desc_rm = "removes the given file/directory";
  String desc_cat = "prints a given file";
  String desc_led = "turn on/off the LED on the board";
   
  
  clearConsole();
  if(arg1 == ""){
    printColored("use: 'man <cmd>' for more infos and examples","yellow");
    Serial.println();
    Serial.println();
    Serial.println("following commands are available:");
    
    printColored("clear\t- ","green");
    Serial.println(desc_clear); 
    printColored("whoami\t- ","green");
    Serial.println(desc_whoami);
    printColored("pwd\t- ","green");
    Serial.println(desc_pwd);
    printColored("cd\t- ","green");
    Serial.println(desc_cd);
    printColored("ls\t- ","green");
    Serial.println(desc_ls);
    printColored("mkdir\t- ","green");
    Serial.println(desc_mkdir);
    printColored("touch\t- ","green");
    Serial.println(desc_write);
    printColored("rm\t- ","green");
    Serial.println(desc_rm);
    printColored("cat\t- ","green");
    Serial.println(desc_cat);
    printColored("led\t- ","green");
    Serial.println(desc_led);
  } 

}

