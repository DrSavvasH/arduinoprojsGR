/*
  FLASHCARDS using SD-Card + OLED with ESP8266
  Savvas C.Hirides 2024

  Connections:
    MicroSD Card
    Card Module       ESP8266
    --------------------------------
     3V3 -------------------- 3V3 (5V for my module!!!!!!!!!!!!!!!!!!!!!!!!!)
     SCK -------- GPIO 14 --- D5
     MISO ------- GPIO 12 --- D6
     MOSI ------- GPIO 13 --- D7
     CS --------- GPIO 15 --- D8
     GND -------------------- GND
*/

#include <SPI.h>
#include <SD.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin). It was -1 in the demo
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
File Textfile;   
String z;
void setup() {
  Serial.begin(9600);
  Serial.println("Initializing SD card");
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
    }
  if (!SD.begin(15)) {  
    Serial.println("Initialization failed!");  
    return;}

  // Write to file
  //Textfile = SD.open("test.txt", FILE_WRITE);  
  //if (Textfile) {
    //Serial.println("Writing to Textfile...");  
   // Textfile.println("First line");    
   // Textfile.println("1, 2, 3, 4, 5");
  //  Textfile.println("a, b, c, d, e");
   // Textfile.println();
   // Textfile.close();     
   // Serial.println("Completed");       
   // Serial.println();
 // }
 // else {
  //  Serial.println("Text file could not be read");  
 // }

}

void loop()  {
  int counter =0;
  // READ TEXTFILE
  display.display();
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);
  delay (3000);
  display.clearDisplay();
  Textfile = SD.open("text.txt");      
  if (Textfile) {
    //Serial.println("text.txt:");    
    while (Textfile.available()) {
      //Serial.write(Textfile.read()); 
      z = char(Textfile.read());
      if (z == "|") {z="";}
      if (z == "#") {
                    delay(3000);
                    display.display();
                    display.clearDisplay();
                    display.setCursor(0, 0);
                    counter = 0;
                    z="";
                  }
      display.print(z);
      counter++;
      if (counter == 40) {
                     delay(3000);
                     display.display();
                     display.clearDisplay();
                     display.setCursor(0, 0);
                     counter = 0;
                   }
    }
    display.display();
    Textfile.close();    
  }
  else  {
    Serial.println("Text file could not be opened"); 
  }
}
