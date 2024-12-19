#include <LCD_I2C.h>
#include <stdio.h>

#define VOLTAGE        5.0
#define SUBMIT_BTN_PIN 4
#define POTENT_PIN     A0
#define MODE_LED_PIN   3
#define MODE_BTN_PIN   2
#define BTN_DELAY      300
#define BLINK_DELAY    300

LCD_I2C lcd(0x27, 20, 4);

int digits[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int correctDigits[9] = {2, 4, 3, 4, 5, 6, 7, 8, 9}; // can be whatever you want

int selection = 0;
int digit = 0;
bool evaluate = false;
char selectionArrowChars[3] = {'*', '|', '|'};

// true - digit editing mode
// false - digit selection mode
bool mode = false;

// boolean to blink mode LED when mode=true 
bool blink = false;
unsigned long lastBlinkTime = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(SUBMIT_BTN_PIN, INPUT);
  pinMode(MODE_LED_PIN, OUTPUT);
  pinMode(MODE_BTN_PIN, INPUT);

  // setup LCD
  lcd.begin();
  lcd.backlight();
  lcd.clear();
}

void updateLCD() {
  lcd.setCursor(0, 0);
  lcd.print(" ");
  for (int i = 0; i < 9; i++) {
    lcd.print(digits[i]);
    lcd.print(" ");
  }
  
  for (int j = 0; j < 3; j++) {
    lcd.setCursor(0, j+1);
    lcd.print(" ");
    for (int i = 1; i <= 9; i++) {
      if (i == selection) {
        lcd.print(selectionArrowChars[j]);
      } else {
        lcd.print(" ");
      }
      lcd.print(" ");
    }
  }
}

float getThreshold(int i) {
  return VOLTAGE * (i / 9.0);
}

void blinkModeLED() {
  if (mode) {
    // Non blocking LED blinking code
    if ((millis() - lastBlinkTime) > BLINK_DELAY) {
      lastBlinkTime = millis();
      if (blink) {
        digitalWrite(MODE_LED_PIN, HIGH);
      } else {
        digitalWrite(MODE_LED_PIN, LOW);
      }
      blink = !blink;
    }
  } else {
    digitalWrite(MODE_LED_PIN, HIGH);
  }
}

void toggleMode() {
  if (digitalRead(MODE_BTN_PIN)) {
    mode = !mode;
    delay(BTN_DELAY);
  }
}

void print_msg(char *msg) {
  for (int i = 0; i < strlen(msg); i++) {
    lcd.print(msg[i]);
    delay(BTN_DELAY / 2);
  }
}

void evaluate_password() {
  print_msg("EVALUATING... DONE");

  bool equivalent = true;
  for (int i = 0; i < 9; i++) {
    if (digits[i] != correctDigits[i]) {
      equivalent = false;
    }
  }
  
  lcd.setCursor(0, 2);
  if (!equivalent) {
    print_msg("ACCESS DENIED!");
  } else {
    print_msg("ACCESS GRANTED!");
  }
  lcd.setCursor(0, 3);
  print_msg("Reset to try again."); 
  
  // blocking loop - hit reset on arduino to restart program
  while (true) { } 
}

void loop() {
  float voltage = analogRead(POTENT_PIN) * (5.0 / 1023.0);
  
  for (int i = 1; i <= 9; i++) {
    // Implement "dead" zones so that arduino doesn't get confused with selecting digits if values are on borderline
    if (voltage <= getThreshold(i) + 0.2 && voltage >= getThreshold(i) - 0.2) { 
      if (!mode) {
        selection = i;
      } else {  
        digits[selection-1] = i;
      }
    }
  }

  if (!evaluate) {
    toggleMode();
    blinkModeLED();
    updateLCD();
  } else {
    evaluate_password();
  }

  if (digitalRead(SUBMIT_BTN_PIN) == HIGH) {
    if (!evaluate) {
      lcd.clear();
      lcd.setCursor(0, 0);
    }
    evaluate = true;
    delay(BTN_DELAY);
  }
}
