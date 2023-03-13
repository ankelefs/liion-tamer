/***************************************************
    Mainframe for Li-Ion Tamer project
***************************************************/
#include <LiquidCrystal.h>


// Constants
const int CHARGER_PIN = 13; // D13
const char CELL_VOLTAGE_PIN = A0;
const char CHARGE_INDICATOR_PIN = A1;
const int BUTTON_OUT_PIN = 2;
const int BUTTON_IN_PIN = 4;

const int INITIALIZING_BUFFER = 3500; // [ms]
const float CELL_VOLTAGE_THRESHOLD = 2.7; // [V]
const float CHARGE_INDICATOR_COMPLETED_VOLTAGE_THRESHOLD = 3.4; // [V]
const int CHARGER_ON = HIGH;
const int CHARGER_OFF = LOW;
bool charge_only = false;

const int LCD_REGISTER_SELECT = 5, LCD_ENABLE = 6, LCD_D4 = 9, LCD_D5 = 10, LCD_D6 = 11, LCD_D7 = 12;
LiquidCrystal lcd(LCD_REGISTER_SELECT, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);


// Function declarations
float get_cell_voltage() {
  int cell_voltage_binary = analogRead(CELL_VOLTAGE_PIN);
  float cell_voltage = cell_voltage_binary * (5.0/1023.0);

  return cell_voltage;
}


char get_charge_status() {
  char charge_status;
  int charge_indicator = analogRead(CHARGE_INDICATOR_PIN);
  float charge_indicator_voltage = charge_indicator * (5.0/1023.0);

  if(charge_indicator_voltage >= CHARGE_INDICATOR_COMPLETED_VOLTAGE_THRESHOLD) {
    charge_status = "completed";
  }

  return charge_status;
}


void update_lcd_charge_only() {
  lcd.setCursor(0, 0);
  lcd.print("Charging...");
  lcd.setCursor(0, 1);
  lcd.print("Voltage: ");
  lcd.setCursor(9, 1);
  lcd.print(get_cell_voltage());
  lcd.setCursor(12, 1);
  lcd.print("V");
}


// Setup
void setup() {
  pinMode(CELL_VOLTAGE_PIN, INPUT);
  pinMode(CHARGE_INDICATOR_PIN, INPUT);
  pinMode(BUTTON_IN_PIN, INPUT);     

  pinMode(CHARGER_PIN, OUTPUT); 
  pinMode(BUTTON_OUT_PIN, OUTPUT);  

  lcd.begin(16, 2);
  Serial.begin(9600);

  // Startup procedure
  digitalWrite(CHARGER_PIN, CHARGER_OFF);
  digitalWrite(BUTTON_OUT_PIN, HIGH);
}


// Main loop
void loop() {
  // User Action
  if(digitalRead(BUTTON_IN_PIN) == HIGH && get_cell_voltage() >= CELL_VOLTAGE_THRESHOLD) {
    charge_only = true;
  }

  // Charge Only (CO)
  if(charge_only == true) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Charge Only");
    lcd.setCursor(0, 1);
    lcd.print("Starting...");
    

    digitalWrite(CHARGER_PIN, CHARGER_ON);
    delay(INITIALIZING_BUFFER);

    lcd.clear();

    while(charge_only == true) {
      update_lcd_charge_only();
      
      char charge_status = "charging";
      charge_status = get_charge_status();
      if(charge_status == "completed") {
        charge_only = false;
        bool user_input = false;
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Charging done");
        lcd.setCursor(0, 1);
        lcd.print("Press to cont.");

        digitalWrite(CHARGER_PIN, CHARGER_OFF);

        while(user_input == false) {
          if(digitalRead(BUTTON_IN_PIN) == HIGH) {
            user_input = true;

            lcd.clear();
          }
        }
      }

      float cell_voltage = get_cell_voltage();
      if(cell_voltage <= CELL_VOLTAGE_THRESHOLD) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ERROR");
        lcd.setCursor(0, 1);
        lcd.print("Low cell voltage");
      }
    }
  }

  // Mode 2
  // ...
}

