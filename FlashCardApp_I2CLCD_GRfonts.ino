//*
//* FlashCards study aid tool / for arduino MEGA with I2C LiquidCrystalDisplay (with Custom Greek Fonts) and SD Card reader - by Savvas Hirides (version 30,March 2024)
//* I2C PINS to 20 (SDA to SDA) and 21 (SCL to SCL). 5V and GRND.
//* CS to Pin 53,(MOSI to 51),(MISO to 50),(SCK to 52) dedicated to the SD reader / VCC (only 5V worked in my case) and GROUND connected accordingly
//*
// include the library code:
//needed for SD and LCD
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); 
const int chipSelect = 53;
// Missing Greek Character
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
// Variables
  int xx = 0;
  int yy = 0;
  int on4 = 0;
  int on7 = 0;
  int on8 = 0;
  int on9 = 0; 
String z ;
int GrMode = 0;
int cardnum = 0;
void setup() 
{
  //lcd.begin(20, 4);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.createChar(8, gamma);
  lcd.createChar(1, delta);
  lcd.createChar(2, theta);
  lcd.createChar(3, lamda);
  lcd.createChar(4, xi);
  lcd.createChar(5, ppi);
  lcd.createChar(6, sigma);
  lcd.createChar(7, fi);
  // Create Custom Characters
  //lcd.createChar(9, psi);
  //lcd.createChar(10, omega);
  lcd.setCursor(0, 0); //move along and down
  lcd.print("FLASHCARDS");
  lcd.setCursor(0, 1); //move along and down
  lcd.print("\x06");
  lcd.print("ABBA");
  lcd.print("\x06");
  lcd.print(" XEIPI");
  lcd.print("\x01");
  lcd.print("H");
  lcd.print("\x06");
  delay(2000);
    if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;}
 // Serial.println("card initialized.");
 // Serial.println("Press button to see each line");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
    lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reading File ...  ");
  File dataF = SD.open("text.txt");
  // if the file is available, raed it:
  if (dataF)
  {
    while (dataF.available())
    { 
    z = String(char(dataF.read()));
    if (z == "{") {cardnum++;}
    }
    dataF.close();
  }
    lcd.setCursor(0, 1);
      lcd.print("End Of File   ");
      delay (500);
      lcd.setCursor(0, 2);
      lcd.print("Flashcards found : ");
      delay (500);
      lcd.setCursor(0, 3);
      lcd.print(cardnum);
      delay(3000);
      lcd.clear();
}

void loop() { 
   File dataFile = SD.open("text.txt");
  // if the file is available, raed it:
  if (dataFile)
  {
    while (dataFile.available())
    { 
    z = String(char(dataFile.read()));
    
    if ((GrMode == 0) && (z !="~") && (z !="#") && (z !="{")) { 
                  lcd.setCursor(xx, yy);    
                  lcd.print(z);
                  xx++;
                  if (xx == 20) {xx = 0; yy++;}
                  if (yy > 4) {delay(100);lcd.clear();xx = 0; yy = 0;on4 = 0;on7 = 0;on8 = 0;on9 = 0;}
                  delay(150);
                  }
    if (GrMode == 1){
                                if (z == "G") {
                                lcd.setCursor(xx, yy);
                                lcd.print("\x08"); // worked with 20x4 screen
                                }

                                if (z == "D") {
                                lcd.setCursor(xx, yy);
                                lcd.print("\x01");
                                }

                                if (z == "U") {
                                lcd.setCursor(xx, yy);
                                lcd.print("\x02");
                                }

                                if ( z == "L") {
                                lcd.setCursor(xx, yy);
                                lcd.print("\x03");
                                }

                                if (z == "J") {
                                                      lcd.createChar(4, xi);
                                                      if (on8 == 1) {on4 = 0;on7 = 0;on8 = 0;on9 = 0;}
                                                      else {on4 = 1;}
                                                      lcd.setCursor(xx, yy);
                                                      lcd.print("\x04");
                                                      delay(100);
                                                    }

                                if (z == "P") {
                                lcd.setCursor(xx, yy);
                                lcd.print("\x05");
                                }

                                if (z == "S") {
                                lcd.setCursor(xx, yy);
                                lcd.print("\x06");
                                }

                                if (z == "F") {
                                lcd.createChar(7, fi);
                                if (on9 == 1) {on4 = 0;on7 = 0;on8 = 0;on9 = 0;}
                                                else {on7 = 1;}
                                                lcd.setCursor(xx, yy);
                                                lcd.print("\x07"); 
                                                delay(100);
                                }
                              
                                if (z == "C") {
                                lcd.createChar(4, psi);
                                if (on4 == 1) {on4 = 0;on7 = 0;on8 = 0;on9 = 0;}
                                              else {on8 = 1;}
                                              lcd.setCursor(xx, yy);
                                              lcd.print("\x04");
                                                delay(100);
                                }

                                if (z == "V") {
                                lcd.createChar(7, omega);
                                              if (on7 == 1) {on4 = 0;on7 = 0;on8 = 0;on9 = 0;}
                                              else {on9 = 1;}
                                              lcd.setCursor(xx, yy);
                                              lcd.print("\x07");
                                              delay(100);
                                }
                        GrMode = 0;
                        xx++;
                        if (xx == 20) {xx = 0; yy++;}
                        if (yy > 4) {delay(100);lcd.clear();xx = 0; yy = 0;on4 = 0;on7 = 0;on8 = 0;on9 = 0;}
                        delay(150);}
    if (z == "~") { 
                    GrMode = 1; }
  
    if ((z == "{") | (z == "#") | (z == "|")) { GrMode = 0;
                  xx=0;
                  yy=0;
                  z="";
                  delay(1000);
                  lcd.clear();
                  }
    }
    dataFile.close();
  } }
