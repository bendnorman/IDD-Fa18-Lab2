// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int delayTime = 200;


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  pinMode(A0, INPUT);
  
  
}

void loop() {
  // Turn off the display:
  lcd.noDisplay();
  delay(delayTime);
  lcd.print("Pin A0: ");
  lcd.print(analogRead(A0));
  // Turn on the display:
  lcd.display();
  
  delay(delayTime);
  lcd.clear();
}
