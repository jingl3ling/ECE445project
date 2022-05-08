#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <FastLED.h>
#include "pitches.h"

#define LED_PIN     7
#define NUM_LEDS    30
CRGB leds[NUM_LEDS];
int Contrast = 60;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial mySerial(13, 10); // RX, TX
int R = 255;
int G = 0;
int B = 0;
int color = 1;
int play = 0; //no song initially
int song = 1; 
bool pause = false;

int melody1[] = {

  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations1[] = {

  4, 8, 8, 4, 4, 4, 4, 4
};

int melody2[] = {

  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations2[] = {

  4, 4, 4, 4, 4, 4, 4, 4
};

int melody3[] = {

  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations3[] = {

  4, 4, 4, 4, 4, 4, 4, 4
};


String Pressed;
String Command;
bool default_screen = true;
bool check_pressed = false;
bool verti_screen = false;
bool hori_screen = false;
bool error_screen = false;
void setup()
{

  Serial.begin(9600);

  Serial.println("Goodnight moon!");

  mySerial.begin(9600);
  
  //lcd
  analogWrite(6, Contrast);
  lcd.begin(16, 4);

    //led
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

          for (int i = 0; i <= 29; i++) {
        leds[i] = CRGB ( R, G, B);
        FastLED.show();
      }

}

void loop()
{

  if(play == 1){
    if(song == 1){
      for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations1[thisNote];
    tone(8, melody1[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    }      
   }    
    if(song == 2){
      for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations2[thisNote];
    tone(8, melody2[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    }      
   } 
    if(song == 3){
      for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations3[thisNote];
    tone(8, melody3[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    }      
   }     
  
 }


    if(default_screen == true){
        lcd.setCursor(0, 0);
        lcd.print("Press the");
        lcd.setCursor(0, 1);
        lcd.print("button and");
        lcd.setCursor(0, 2);
        lcd.print("move arm to");
        lcd.setCursor(0, 3);
        lcd.print("send command");
    }

  // Feed any data from bluetooth to Terminal.
  if (mySerial.available()){
    Serial.write(mySerial.read());

    Pressed = mySerial.readString();
    Serial.println(Pressed);
    Serial.write("(print by press loop)");
    if( Pressed.startsWith("ressed"))
    {
      default_screen = false;

      lcd.clear();
      lcd.write("Button pressed");

      while (!mySerial.available()){
        Serial.println("Waiting for command");
      }
        
//      unsigned long pressed_time = millis();
//      while(millis() - pressed_time < 2000){
      Command = mySerial.readString();
//      }
      Serial.write("Command received:");
      Serial.println(Command);  

    if(Command.startsWith("H")){
      lcd.clear();
      lcd.write("Next song");
      
      song = song + 1;

      if (song == 4){
        song = 1;
      }
      
      delay(2000);
      lcd.clear();
      }
     else if(Command.startsWith("P")){
      if(pause == false){
         lcd.clear();
         lcd.write("Resume");
         play = 1;
         delay(2000);
         lcd.clear();
         pause = true;
      }
      else if(pause == true){
         lcd.clear();
         lcd.write("Pause");
         play = 0;
         delay(2000);
         lcd.clear();
         pause = false;        
      }
     }
    else if(Command.startsWith("V")){
      lcd.clear();
      lcd.write("Change light");
      color = color + 1;
//      R = random(210);
//      G = random(210);
//      B = random(210);

   if(color == 8){
    color = 1;
  }

   if(color == 1){
    R = 255;
    G = 0;
    B = 0;    
  }
  else if(color == 2){
    R = 255;
    G = 110;
    B = 0;   
  }
  else if(color == 3){
    R = 255;
    G = 255;
    B = 0;
  }
  else if(color == 4){
    R = 0;
    G = 255;
    B = 0;
  }
  else if(color == 5){
    R = 255;
    G = 10;
    B = 140;
  }
  else if(color == 6){
    R = 0;
    G = 255;
    B = 255;
  }
  else if(color == 7){
    R = 127;
    G = 0;
    B = 255;
  }

      for (int i = 0; i <= 29; i++) {
        leds[i] = CRGB ( R, G, B);
        FastLED.show();
      }
      delay(2000);
      lcd.clear();
    }
    else if(Command.startsWith("p")){
      lcd.clear();
      lcd.write("Error");
      delay(2000);
      lcd.clear();      
    }

    default_screen = true;
    }
  }
  // Feed all data from termial to bluetooth
  if (Serial.available()){
    mySerial.write(Serial.read());
  }
}
