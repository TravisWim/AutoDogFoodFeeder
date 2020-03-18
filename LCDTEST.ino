/*
  LiquidCrystal Library - Autoscroll

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch demonstrates the use of the autoscroll()
 and noAutoscroll() functions to make new text scroll or not.

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

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

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalAutoscroll

*/

// include the library code:
#include <LiquidCrystal.h>
#include <EEPROM.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
bool edit = false;
long timer;
int TankCups;
int LumiCups;
int TazCups;
int HoneyCups;
int editnumber = 1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String MainScreen[] = {"P","r","e","s","s"," ","A","n","y"," ","B","u","t","t","o","n","t","o"," ","P","o","u","r"," ","H","o","l","d"," ","T","a","n","k"," ","t","o"," ","E","d","i","t"};
String EditScreen[] ={"U","s","e"," ","T","a","z"," ","F","o","r"," ","L","e","f","t"," ","H","o","n","e","y"," ","F","o","r"," ","R","i","g","h","t"};
void EEPROM_Assign(int ID, double value){
  EEPROM.write(ID,value);
  }
void EEPROM_Read(int ID, double ItemRead){
  ItemRead = EEPROM.read(ID);
  }
void pourfood(int DogId){
    Serial.println("Pouring");
    Serial.print(DogId);
  }
void ButtonListen(){
  if(digitalRead(8) == LOW){
    delay(2000);
  if(digitalRead(8) == LOW and edit == false){
    Serial.println(digitalRead(8));
    edit = true;
    }else{
      pourfood(1);
      }
    }
    if (digitalRead(7) == LOW and edit == false){
      pourfood(2);
    }
    if (digitalRead(9) == LOW and edit == false){
      pourfood(3);
      }
    if (digitalRead(10) == LOW and edit == false){
      pourfood(4);
      }
  }
void ExitEdit(){
  if (digitalRead(8) == LOW){
    delay(1000);
    if (digitalRead(8) == LOW){
      lcd.clear();
      edit = false;
      }
    }
  }
void ButtonRead(){
  if(digitalRead(8) == LOW){
    if(editnumber == 1){
        TankCups +=1; 
        EEPROM.write(1,TankCups);
    }else if(editnumber == 2){
        TazCups +=1;
        EEPROM.write(2,TazCups);
    }else if(editnumber == 3){
        HoneyCups +=1;
        EEPROM.write(3,HoneyCups);
    }else if(editnumber == 4){
        LumiCups +=1;
        EEPROM.write(4,LumiCups);
    }
  }else if(digitalRead(7) == LOW){
    if(editnumber == 1){
        TankCups -=1; 
        EEPROM.write(1,TankCups);
    }else if(editnumber == 2){
        TazCups -=1;
        EEPROM.write(2,TazCups);
    }else if(editnumber == 3){
        HoneyCups -=1;
        EEPROM.write(3,HoneyCups);
    }else if(editnumber == 4){
        LumiCups -=1;
        EEPROM.write(4,LumiCups);
    }
    }
    Serial.println("8 Reads:");
    Serial.println(digitalRead(8));
    Serial.println("7 Reads:");
    Serial.println(digitalRead(7));
  }
void setup() {
   while (!Serial); // Wait for Serial port to initialize.
  Serial.begin(115200);
  // set up the LCD's number of columns and rows:
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  TankCups = EEPROM.read(1);
  Serial.println(TankCups);
  TazCups = EEPROM.read(2);
  HoneyCups = EEPROM.read(3);
  LumiCups = EEPROM.read(4);

}

void loop() {
  // set the cursor to (0,0):
  int num= 0;
  lcd.setCursor(0,0);
  while(num<16){
    lcd.print(MainScreen[num]);
    Serial.print(MainScreen[num]);
    num+=1;
    ButtonListen();
    if (edit){
      break;
      }
    delay(300);
    }
  Serial.println();
  num = 0;
  lcd.setCursor(0,1);
  while(num<13){
    lcd.print(MainScreen[num+16]);
    Serial.print(MainScreen[num+16]);
    num+=1;
    ButtonListen();
    if (edit){
      break;
      }
    delay(300);
    }
  Serial.println();
  // print from 0 to 9:
  lcd.clear();
  lcd.setCursor(0,0);
  num = 0;
  while(num<12){
    lcd.print(MainScreen[num+29]);
    Serial.print(MainScreen[num+29]);
    num+=1;
    ButtonListen();
    if (edit){
      break;
      }
    delay(300);
    }
  Serial.println();
  // turn off automatic scrolling
  if(edit){
    lcd.clear();
    lcd.setCursor(0,0);
    delay(200);
    lcd.print("Press Taz for Left");
    delay(500);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Honey for Right");
    delay(500);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Tank:" );
    while(edit){
      if(digitalRead(9) == LOW){
           if (editnumber<5){
               editnumber++;
               delay(300); 
            }else{
               editnumber= 1;
               delay(300);
              }
        }
      if(digitalRead(10) == LOW){
          if (editnumber>1){
               editnumber--;
               delay(300);
            }else{
               editnumber= 5;
               delay(300);
              }
        }
      if(editnumber == 1){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Tank:");
        lcd.print(TankCups);
        delay(10);
      }else if(editnumber == 2){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Taz:");
          lcd.print(TazCups);
          delay(10);
      }else if(editnumber == 3){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Honey:");
          lcd.print(HoneyCups);
          delay(10);
      }else if(editnumber == 4){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Lumi:");
          lcd.print(LumiCups);
          delay(10);
          ButtonRead();
          delay(500);
      }else if(editnumber == 5){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Hold Tank to exit");
        ExitEdit();
        Serial.println("ExitEdit Finished");
        Serial.println(edit);
        if (!edit){
          Serial.println("should be breaking");
          break;
          }
        delay(10);
      }
      }
     
   }
  
  Serial.println("About to clear");

  // clear screen for the next loop:
  lcd.clear();
  Serial.println("cleared");
}
