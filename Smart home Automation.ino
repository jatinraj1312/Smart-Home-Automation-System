#include <LiquidCrystal.h>
#include <Servo.h>

#define TEMP_PIN A0       // TMP36 connected to analog pin A0
#define PIRPIN 13         // PIR signal wire connected to digital pin 13
#define RELAYPIN 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo door;

void setup() {
  pinMode(PIRPIN, INPUT);
  pinMode(RELAYPIN, OUTPUT);
  door.attach(9);
  lcd.begin(16, 2);
  lcd.print("Smart Home Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  int sensorValue = analogRead(TEMP_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  float tempC = (voltage - 0.5) * 100;  // TMP36 formula

  int motion = digitalRead(PIRPIN);

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC);
  lcd.print(" C");

  if (tempC > 30) {
    digitalWrite(RELAYPIN, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Fan: ON ");
  } else {
    digitalWrite(RELAYPIN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Fan: OFF");
  }

  if (motion == HIGH) {
    door.write(90);
  } else {
    door.write(0);
  }

  delay(1000);
}