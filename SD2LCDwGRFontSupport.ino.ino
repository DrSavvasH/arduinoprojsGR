/*
  LiquidCrystal Library - Greek Enable for Arduino LCD - by Savvas Hirides

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  Careful! In order to accomodate both the SD and the LCD, the circuit has been changed:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 6
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 * Pins 10,11,12 dedicated to the SD reader / VCC (only 5V worked in my case) and GROUND connected accordingly

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 Part of this example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/
// include the library code:
//needed for SD
#include <SPI.h>
#include <SD.h>
//needed for LCD
#include <LiquidCrystal.h>
//#include <hd44780.h>
// include the SD library:
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>
// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;
const int rs=7, en=6, db4=5, db5=4, db6=3, db7=2; // lcd keypad shield pins
LiquidCrystal lcd(rs, en, db4, db5, db6, db7);
const int chipSelect = 10;
int strindx = 0;
int scrchar = 0;
int on4 = 0;
int on7 = 0;
int on8 = 0;
int on9 = 0;
int xx = 0;
int yy = 0;
// There is limitation in the characters to be processed (depends on type of arduino platform, but also on amount of greek symbols, which account for 2 characters)
String z ;
byte gamma[] = {
  B11111,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B00000
};

byte delta[] = {
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B11111,
  B00000
};

byte theta[] = {
  B01110,
  B10001,
  B10001,
  B11111,
  B10001,
  B10001,
  B01110,
  B00000
};

byte lamda[] = {
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B10001,
  B00000
};

byte xi[] = {
  B11111,
  B00000,
  B00000,
  B01110,
  B00000,
  B00000,
  B11111,
  B00000
};
byte ppi[] = {
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B00000
};
byte sigma[] = {
  B11111,
  B10000,
  B01000,
  B00100,
  B01000,
  B10000,
  B11111,
  B00000
};
byte fi[] = {
  B01110,
  B10101,
  B10101,
  B10101,
  B01110,
  B00100,
  B00100,
  B00000
};
byte psi[] = {
  B10101,
  B10101,
  B10101,
  B10101,
  B01110,
  B00100,
  B00100,
  B00000
};
byte omega[] = {
  B01110,
  B10001,
  B10001,
  B10001,
  B01010,
  B01010,
  B11011,
  B00000
};
void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.createChar(8, gamma);
  lcd.createChar(1, delta);
  lcd.createChar(2, theta);
  lcd.createChar(3, lamda);
  //lcd.createChar(4, xi);
  lcd.createChar(5, ppi);
  lcd.createChar(6, sigma);
  lcd.createChar(7, fi);
  //lcd.createChar(9, psi);
  //lcd.createChar(10, omega);
  lcd.begin(20, 4);
  lcd.home();
   // Open serial communications and wait for port to open:
  //Serial.begin(9600);
  //pinMode(thePin, INPUT_PULLUP);
  //while (!Serial)
 // {
  //  ; // wait for serial port to connect. Needed for native USB port only
 // }
  // initialize the LCD
  // Turn on the blacklight and print a message.
  //lcd.backlight();
  lcd.setCursor(7, 0); //move along and down
  lcd.print("LCD Text");
  lcd.setCursor(7, 1); //move along and down
  lcd.print("from SD");
  lcd.setCursor(7, 2);
  lcd.print("by");
  lcd.setCursor(1, 3);
  lcd.print(" Savas Hirides 2024");
  delay(1000);
  //Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;}
 // Serial.println("card initialized.");
 // Serial.println("Press button to see each line");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("text.txt");
  lcd.clear();
  lcd.print("  Reading File ...  ");
  delay (2000);
  // if the file is available, raed it:
  on4 = 0;
  on7 = 0;
  on8 = 0;
  on9 = 0;
  int GrMode = 0;
  if (dataFile)
      lcd.print(" End Of File   ");
      delay(500);
      lcd.clear();
  {
    while (dataFile.available())
    { 
    z = char(dataFile.read()); 
   
    if (z == "~") {GrMode = 1;}
    if (GrMode == 0){     
                  lcd.setCursor(xx, yy);
                  lcd.print (z);
                  xx++;
                  if (xx == 20) {xx = 0; yy++;}
                  if (yy > 3) {lcd.clear();xx = 0; yy = 0;on4 = 0;on7 = 0;on8 = 0;on9 = 0;}
                  delay (100);//}
                  }
                  //delay(150);
    //}//endwhile datafile available
 
    if ((GrMode == 1) && (z == "G")) {
     lcd.setCursor(xx, yy);
     lcd.print("\x08");
    }

    if ((GrMode == 1) && (z == "D")) {
    lcd.setCursor(xx, yy);
    lcd.print("\x01");
    }

    if ((GrMode == 1) && (z == "U")) {
    lcd.setCursor(xx, yy);
    lcd.print("\x02");
    }

    if ((GrMode == 1) && ( z == "L")) {
    lcd.setCursor(xx, yy);
    lcd.print("\x03");
    }

    if ((GrMode == 1) && (z == "J")) {
    lcd.createChar(4, xi);
    if (on8 == 1) {on4 = 0;on7 = 0;on8 = 0;on9 = 0;}
    else {on4 = 1;}
    lcd.setCursor(xx, yy);
    lcd.print("\x04");
    }

    if ((GrMode == 1) && (z == "P")) {
    lcd.setCursor(xx, yy);
    lcd.print("\x05");
    }

    if ((GrMode == 1) && (z == "S")) {
    lcd.setCursor(xx, yy);
     lcd.print("\x06");
    }

    if ((GrMode == 1) && (z == "F")) {
    lcd.createChar(7, fi);
    if (on9 == 1) {on4 = 0;on7 = 0;on8 = 0;on9 = 0;}
    else {on7 = 1;}
    lcd.setCursor(xx, yy);
    lcd.print("\x07"); 
    }
  
    if ((GrMode == 1) && (z == "C")) {
    lcd.createChar(4, psi);
    if (on4 == 1) {on4 = 0;on7 = 0;on8 = 0;on9 = 0;}
     else {on8 = 1;}
    lcd.setCursor(xx, yy);
     lcd.print("\x04");
    }

    if ((GrMode == 1) && (z == "V")) {
    lcd.createChar(7, omega);
    if (on7 == 1) {on4 = 0;on7 = 0;on8 = 0;on9 = 0;}
    else {on9 = 1;}
    lcd.setCursor(xx, yy);
    lcd.print("\x07");
    }

    if ((GrMode == 1) && !(z == "~")){xx++;GrMode = 0;}
    if (xx == 20) {xx = 0; yy++;}
    if (yy > 3) {lcd.clear();xx = 0; yy = 0;on4 = 0;on7 = 0;on8 = 0;on9 = 0;}
    }
    dataFile.close();
 //while (strindx < z.length());delay (1000);
  } 
//end of Setup
}
void loop() {}


