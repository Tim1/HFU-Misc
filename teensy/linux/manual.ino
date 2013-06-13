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
  //------------
  String ex_cd = "goto root directory";
  String ex_mkdir = "create directory 'testdir'";
  String ex_touch = "create file 'test.txt'";
  String ex_write = "write 'abc 123 xyz' into file.txt";
  String ex_rm = "removes a file";
  String ex_cat = "prints the file: cat file.txt";
  String ex_led =  "turns led on ";
  String ex_led2 = "turns led off";


  clearConsole();
  if(arg1 == ""){
    printColored("use: 'man <cmd>' for more infos and examples","yellow");
    Serial.println();
    Serial.println();
    Serial.println("following commands are available:");

    printColored("write\t- ","green");
    Serial.println(desc_write); 
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
    Serial.println(desc_touch);
    printColored("rm\t- ","green");
    Serial.println(desc_rm);
    printColored("cat\t- ","green");
    Serial.println(desc_cat);
    printColored("led\t- ","green");
    Serial.println(desc_led);
  }
  else if(arg1 == "clear"){
    printMan(arg1,desc_clear,"","","","");
  }
  else if(arg1 == "whoami"){
    printMan(arg1,desc_whoami,"","","","");
  }
  else if(arg1 == "pwd"){
    printMan(arg1,desc_pwd,"","","","");
  }
  else if(arg1 == "cd"){
    printMan(arg1,desc_cd,ex_cd,"cd","","");
  }
  else if(arg1 == "mkdir"){
    printMan(arg1,desc_mkdir,ex_mkdir,"mkdir testdir","","");
  }
  else if(arg1 == "touch"){
    printMan(arg1,desc_touch,ex_touch,"touch file.txt","","");
  }
  else if(arg1 == "write"){
    printMan(arg1,desc_write,ex_write,"write file.txt abc 123 xyz","","");
  }
  else if(arg1 == "rm"){
    printMan(arg1,desc_rm,ex_rm,"rm file.txt","","");
  }
  else if(arg1 == "cat"){
    printMan(arg1,desc_cat,ex_cat,"cat file.txt","","");
  }
  else if(arg1 == "led"){
    printMan(arg1,desc_led,ex_led,"led on",ex_led2,"led off");
  }
  Serial.println();
  Serial.println();
}

//prints description and examples (if given) for a command
void printMan(String arg1,String desc,String ex_Desc_1,String ex_Code_1,String ex_Desc_2, String ex_Code_2){
  printColored(arg1+"\t- ","green");
  Serial.println(desc);
  Serial.println();

  if(ex_Desc_1 != ""){
    printColored("Example:","yellow");
    Serial.println();
    Serial.print(ex_Desc_1+": ");
    printColored(ex_Code_1,"green");
  }
  if(ex_Desc_2 != ""){
    Serial.println();
    Serial.print(ex_Desc_2+": ");
    printColored(ex_Code_2,"green");
  }


}



