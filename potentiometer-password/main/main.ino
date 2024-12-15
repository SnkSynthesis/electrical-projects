#define VOLTAGE 5.0
int potent_pin = A0;
int prev = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

float get_threshold(int i) {
  return VOLTAGE * (i / 9.0);
}

void loop() {
  // put your main code here, to run repeatedly:
  float voltage = analogRead(A0) * (5.0 / 1023.0);
  
  for (int i = 1; i <= 9; i++) {
    // Implement "dead" zones so that arduino doesn't get confused with selecting digits if values are on borderline
    if (voltage <= get_threshold(i) + 0.2 && voltage >= get_threshold(i) - 0.2) {
      if (i != prev) {
        Serial.print("Number selected: ");
        Serial.print(i);
        Serial.print(", ");
        Serial.print(voltage);
        Serial.print(", ");
        Serial.println(get_threshold(i));
        // Serial.println(voltage);
        prev = i;
      }
    }
  }

  // if (VOLTAGE * (1 / 9))) {

  // }
  // Serial.println(voltage);
}
