/******************************************************************************
   Flex_Sensor_Example.ino
   Example sketch for SparkFun's flex sensors
   (https://www.sparkfun.com/products/10264)
   Jim Lindblom @ SparkFun Electronics
   April 28, 2016

   Create a voltage divider circuit combining a flex sensor with a 47k resistor.
   - The resistor should connect from A0 to GND.
   - The flex sensor should connect from A0 to 3.3V
   As the resistance of the flex sensor increases (meaning it's being bent), the
   voltage at A0 should decrease.

   Development environment specifics:
   Arduino 1.6.7
******************************************************************************/
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int delayTime = 10;


const int player_one_pin = A0; // Pin connected to voltage divider output
int button_pin = 8;

int rest_voltage = 0;
int flick_voltage = 40;
int tolerance = 20;

int player_one_counter = 0;
int player_one_last_voltage = rest_voltage;

int game_state = 0;

int game_length_millis = 15000;
int count_down_millis = game_length_millis;


void setup()
{
        lcd.begin(16, 2);
        
        pinMode(button_pin, INPUT);

        Serial.begin(9600);
        pinMode(player_one_pin, INPUT);
        rest_voltage = analogRead(player_one_pin);
        Serial.println("Rest Voltage: " + String(rest_voltage));
}

void loop()
{

        if (game_state == 0) {
                lcd.print("Button to start!");
                lcd.display();
                int button_state = digitalRead(button_pin);
                if (button_state == 1) {
                    game_state = 1;
                    lcd.clear();
                }
        }
        if (game_state == 1) {
            player_one_counter = 0;
            count_down_millis = game_length_millis;
            rest_voltage = analogRead(player_one_pin);
            
            
            for (int i = 3; i > 0; i--) {
                
                lcd.print(i);
                delay(1000);
                lcd.clear();
            }
            lcd.print("GO!");
            delay(100);
            game_state = 2;
        }
        if (game_state == 2) {
            // lcd.noDisplay();
            lcd.setCursor(0, 0);
            lcd.print("Flicks: " + String(player_one_counter));
            lcd.display();

            int voltage_one = analogRead(player_one_pin);

            if (player_one_last_voltage > rest_voltage + flick_voltage && in_resting_position(voltage_one)) {
                    player_one_counter++;
                    Serial.println("Player One Counter: " + String(player_one_counter));
            }
            if (player_one_last_voltage < rest_voltage - flick_voltage && in_resting_position(voltage_one)) {
                    player_one_counter++;
                    Serial.println("Player One Counter: " + String(player_one_counter));
            }

            player_one_last_voltage = voltage_one;
            count_down_millis -= delayTime;
            lcd.setCursor(0, 1);
            int seconds = count_down_millis / 1000;
            lcd.print(seconds);
            if (seconds == 0) {
                game_state = 3;
            }
            
        }
        if (game_state == 3) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Final Score: " + String(player_one_counter));
            lcd.setCursor(0, 1);
            lcd.print("Button play again!");
            int button_state = digitalRead(button_pin);
            if (button_state == 1) {
                game_state = 1;
                lcd.clear();
            }
            
        }
        
        delay(delayTime);
        lcd.clear();
        

}

int in_resting_position(int voltage)
{
        int result = (voltage < rest_voltage + tolerance && voltage > rest_voltage - tolerance);
        return result;
}
