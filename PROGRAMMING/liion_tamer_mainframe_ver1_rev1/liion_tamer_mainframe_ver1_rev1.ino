/***************************************************
    Mainframe for Li-Ion Tamer project

    Functionality:
    - Display
    - User interface
    - Different battery cell modi
    - Measurements
    - (Auditory response?)
***************************************************/
#include <LiquidCrystal.h>


const int CHARGER_PIN = 13; // D13
const char VOLTAGE_CHECK_PIN = A0;
const int BUTTON_OUT_PIN = 2;
const int BUTTON_IN_PIN = 4;

const int DELAY_LONG = 10000; // [ms]
const int DELAY_SHORT = 10000; // [ms]

const int CHARGER_ON = HIGH;
const int CHARGER_OFF = LOW;

const float VOLTAGE_THRESHOLD = 4.1;

bool charging = false;

int cell_voltage_binary;
float cell_voltage_value;

const int LCD_REGISTER_SELECT = 5, LCD_ENABLE = 6, LCD_D4 = 9, LCD_D5 = 10, LCD_D6 = 11, LCD_D7 = 12;
LiquidCrystal lcd(LCD_REGISTER_SELECT, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);


void setup() {
  pinMode(CHARGER_PIN, OUTPUT); 
  pinMode(VOLTAGE_CHECK_PIN, INPUT);
  pinMode(BUTTON_OUT_PIN, OUTPUT);   
  pinMode(BUTTON_IN_PIN, INPUT);     

  digitalWrite(CHARGER_PIN, CHARGER_OFF);
  digitalWrite(BUTTON_OUT_PIN, HIGH);

  lcd.begin(16, 2);

  Serial.begin(9600);
  Serial.println("Startup");
}


void print_cell_voltage(float cell_voltage_value) {
  Serial.print("Celle-spenning: ");
  Serial.print(cell_voltage_value);
  Serial.println(" V.");
}


float read_cell_voltage() {
  cell_voltage_binary = analogRead(VOLTAGE_CHECK_PIN);
  cell_voltage_value = cell_voltage_binary * (5.0/1023.0);

  return cell_voltage_value;
}


void loop() {
  if(digitalRead(BUTTON_IN_PIN) == HIGH) {
    Serial.println("Button pressed.");
    charging = true;
  }

  if(charging == true) {
    Serial.println("Charging...");
    digitalWrite(CHARGER_PIN, CHARGER_ON);

    if(read_cell_voltage() <= VOLTAGE_THRESHOLD) // CHANGE TO SIGNALS FROM TC4056
      print_cell_voltage(read_cell_voltage());

    digitalWrite(CHARGER_PIN, CHARGER_OFF);
    charging = false;
    
    Serial.println("Charging done.");
  }

  lcd.setCursor(0, 0); 
  lcd.print("Select mode: 1:CO 2:CCH 3:CT 4:SDT");
  lcd.setCursor(0, 1);
  lcd.print("Voltage: ");
  lcd.setCursor(9, 1);
  lcd.print(read_cell_voltage());
  lcd.setCursor(14, 1);
  lcd.print("V");

  print_cell_voltage(read_cell_voltage());
}

