// Basic serial communication with ESP8266
// Uses serial monitor for communication with ESP8266
//
//  Pins
//  Arduino pin 2 (RX) to ESP8266 TX
//  Arduino pin 3 to voltage divider then to ESP8266 RX
//  Connect GND from the Arduiono to GND on the ESP8266
//  Pull ESP8266 CH_PD HIGH
//
// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay it to the ESP8266
//localhost/add.php?vrijednost=x
//

#include <SoftwareSerial.h>

SoftwareSerial ESPserial(2, 3); // RX | TX
String server = "192.168.1.4";  //Server gdje je postavljena web stranica
String uri = "/add.php"; 
String data;
String x;

void setup() 
{
    Serial.begin(115200);
    ESPserial.begin(115200);
    reset(); // poziva funkciju void reset i resetira esp
    ESPserial.println("AT+CWMODE=1");// postavlja mod rada esp-a
    delay(2000);
    String cmd="AT+CWJAP=\""; //at naredba za spajanje na mrezu
    cmd+="mobilna_mreza";
    cmd+="\",\"";
    cmd+="11223344";
    cmd+="\"";
    ESPserial.println(cmd); //spajanje na wifi mrezu
    delay(5000);
    data = ""; 
}
 
void loop() 
{
//--------------AT KOMANDE---------------------------------------------------------------
//    // listen for communication from the ESP8266 and then write it to the serial monitor
//    if ( ESPserial.available() )   {  Serial.write( ESPserial.read() );  }
// 
//    // listen for user input and send it to the ESP8266
//    if ( Serial.available() )       {  ESPserial.write( Serial.read() );  }
//-----------UPISIVANJE VARIJABLE X U BAZU( iz nekog razloga ne radi)---------------------
     x=15;   // varijabla koja se pokušava upisat u bazu
     data = "vrijednost=" + x;
     httppost();
     Serial.println("\n");
     delay(5000);
}

void httppost () {
     ESPserial.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80"); // TCP
     if(ESPserial.find( (char*)"OK")) {
     Serial.println("TCP uspostavljen");
     }
     delay(1000);
     String postRequest = "POST /add.php HTTP/1.1\r\nHost: " + server + "\r\n" + 
     "Accept: *" + "/" + "*\r\n" + 
     "Content-Length: " + data.length() + "\r\n" + 
     "Content-Type: application/x-www-form-urlencoded;\r\n" + 
     "\r\n" + data;
     
     ESPserial.print("AT+CIPSEND=");
     ESPserial.println(postRequest.length() );
     if(ESPserial.find( (char*)"OK")) {
        Serial.println("CIPSEND prosao!");
     }
     delay(500);
     ESPserial.print(postRequest);
     Serial.print(postRequest);
     if(ESPserial.find( (char*)"OK")) {
        Serial.println("POST prosao!");
     }
     Serial.println("Slanje..");
     ESPserial.println("AT+CIPCLOSE");
}

void reset() {
    ESPserial.println("AT+RST");
    delay(1000);
    if(ESPserial.find( (char*)"OK") ) Serial.println("Modul je resetiran!");
}
