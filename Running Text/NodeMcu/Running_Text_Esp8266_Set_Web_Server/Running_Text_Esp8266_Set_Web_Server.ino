//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Set the Text via Web Server with EEPROM
/*
 * The original source code to "running Text" : https://github.com/busel7/DMDESP/blob/master/examples/TeksDiamdanJalan/TeksDiamdanJalan.ino by  busel7
 * Links to download the DMDESP library : https://github.com/busel7/DMDESP
 * Source code origin for writing and reading strings to / from EEPROM : https://circuits4you.com/2018/10/16/arduino-reading-and-writing-string-to-eeprom/
*/

//----------------------------------------Include Library
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <ESP8266WebServer.h>
#include <DMDESP.h>
#include <fonts/ElektronMart6x8.h>
#include <fonts/Arial_Black_16_ISO_8859_1.h>
#include <EEPROM.h>
//----------------------------------------

#include "PageIndex.h" //--> Include the contents of the User Interface Web page, stored in the same folder as the .ino file

//----------------------------------------Make a wifi name and password as access point
const char* ssid = "Wemos";
const char* password = "12345678";
//----------------------------------------

ESP8266WebServer server(80);  //--> Server on port 80

///----------------------------------------DMD Configuration (P10 Panel)
#define DISPLAYS_WIDE 1 //--> Panel Columns
#define DISPLAYS_HIGH 1 //--> Panel Rows
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);  //--> Number of Panels P10 used (Column, Row)
//----------------------------------------

char *Text[] = {"NodeMCU ESP8266"}; //--> Variable for scrolling Text. Don't leave this variable blank
String Incoming_Text = ""; //--> Variable to hold the text that is sent from a web server (web page)
String Text_To_EEPROM = ""; //--> Text variables stored in EEPROM
String Text_From_EEPROM = ""; //--> Variable to hold Text data read from EEPROM for display

//========================================================================This routine is executed when you open NodeMCU ESP8266 IP Address in browser
void handleRoot() {
  server.send(200, "text/html", MAIN_page); //--> Send web page
}
//========================================================================

//========================================================================Subroutines to handle incoming Text Data
void handle_Incoming_Text() {
  Incoming_Text = server.arg("TextContents");
  server.send(200, "text/plane", ""); //--> Send web page
  
  //----------------------------------------Save text data that has been set from the web server to EEPROM and read it for display
  // "ATTX:" is the keyword to set the text to be displayed.
  // So even if the IP of Nodemcu is known to other people, he can not immediately set the text.
  if (Incoming_Text.substring(0,5) /*== "ATTX:"*/) { 
    Text_To_EEPROM = Incoming_Text.substring(5, Incoming_Text.length());
    delay(10);
    write_String_to_EEPROM(0, Text_To_EEPROM); //--> Address "0" and String type data
    delay(10);
    Text_From_EEPROM = read_String_from_EEPROM(0);
    delay(100);
    Process_Incoming_Text(); 
  }
  //----------------------------------------
}
//========================================================================

//========================================================================Subroutines for processing incoming Text to be displayed in the P10 Panel
void Process_Incoming_Text() {
  delay(500);
  Serial.println("Incoming text : ");
  Serial.println(Incoming_Text);
  Serial.println();
  int str_len = Text_From_EEPROM.length() + 1;
  char char_array[str_len];
  Text_From_EEPROM.toCharArray(char_array, str_len);
  strcpy(Text[0], char_array);
  Incoming_Text = "";
  Text_To_EEPROM = "";
  Text_From_EEPROM = "";
}
//========================================================================

//========================================================================VOID SETUP()
void setup(){
  Serial.begin(115200);
  delay(500);

  EEPROM.begin(512);
  delay(500);

  //----------------------------------------DMDESP Setup
  Disp.start(); //--> Run the DMDESP library
  Disp.setBrightness(50); //--> Brightness level
  Disp.setFont(Arial_Black_16_ISO_8859_1); //--> Determine the font used
  //----------------------------------------
  
  WiFi.softAP(ssid, password);  //--> Start Making ESP8266 NodeMCU as an access point
  Serial.println("");
  
  IPAddress apip = WiFi.softAPIP(); //--> Get the IP server
  Serial.print("Connect your wifi laptop/mobile phone to this NodeMCU Access Point : ");
  Serial.println(ssid);
  Serial.print("Visit this IP : ");
  Serial.print(apip); //--> Prints the IP address of the server to be visited
  Serial.println(" in your browser.");
 
  server.on("/", handleRoot); //--> Routine to handle at root location. This is to display web page.
  server.on("/setText", handle_Incoming_Text);  //--> Routine to handle the call procedure handleLED
  
  server.begin(); //--> Start server
  Serial.println("HTTP server started");

  // "write_String_to_EEPROM" in void setup is used only once.
  // After the code has been uploaded, comment / disable "write_String_to_EEPROM" and upload the code again.
  // Then don't use "write_String_to_EEPROM" in void setup again.
//  write_String_to_EEPROM(0, Text_To_EEPROM); //--> Address "0" and String type data
//  delay(10);
  Text_From_EEPROM = read_String_from_EEPROM(0);
  delay(100);
  Process_Incoming_Text();
}
//========================================================================

//========================================================================VOID LOOP()
void loop(){
    server.handleClient();  //--> Handle client requests
//
    Disp.loop(); //--> Run "Disp.loop" to refresh the LED
//  Disp.drawText(5, 0, "IBOO"); //--> Display text "Disp.drawText(x position, y position, text)"
  Scrolling_Text(-1, 70); //--> Show running text "Scrolling_Text(y position, speed);"
}
//========================================================================

//========================================================================Subroutines for scrolling Text
void Scrolling_Text(int y, uint8_t scrolling_speed) {
  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  Disp.setFont(Arial_Black_16_ISO_8859_1);
  int fullScroll = Disp.textWidth(Text[0]) + width;
  if((millis() - pM) > scrolling_speed) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      return;
    }
    Disp.drawText(width - x, y, Text[0]);
  }  
}
//========================================================================

//========================================================================Subroutines for writing String to EEPROM
void write_String_to_EEPROM(char add,String data) {
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
}
//========================================================================

//========================================================================Subroutines to reading String from EEPROM
String read_String_from_EEPROM(char add) {
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}
//========================================================================
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
