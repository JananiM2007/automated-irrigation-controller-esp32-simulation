#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SOIL_PIN 34
#define RELAY_PIN 26

#define GREEN_LED 18
#define YELLOW_LED 19
#define RED_LED 23

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ------------ Calibration ------------
// Change these after checking Serial Monitor
const int DRY_VALUE = 4095;
const int WET_VALUE = 0;

// ------------ EMA Filter ------------
const float alpha = 0.2;
float filteredADC = 0;

// ------------ Hysteresis ------------
const int ON_THRESHOLD = 30;
const int OFF_THRESHOLD = 45;

bool pumpState = false;

void setup()
{
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);

  lcd.init();
  lcd.backlight();

  filteredADC = analogRead(SOIL_PIN);
}

void loop()
{
  // -------- Oversampling --------
  long sum = 0;

  for(int i = 0; i < 10; i++)
  {
    sum += analogRead(SOIL_PIN);
    delay(5);
  }

  float rawADC = sum / 10.0;

  // -------- EMA Filter --------
  filteredADC = alpha * rawADC + (1 - alpha) * filteredADC;

  // -------- Convert to Moisture % --------
  int moisture = map(filteredADC, DRY_VALUE, WET_VALUE, 0, 100);
  moisture = constrain(moisture, 0, 100);

  // -------- Hysteresis --------
  if(!pumpState && moisture < ON_THRESHOLD)
      pumpState = true;

  if(pumpState && moisture > OFF_THRESHOLD)
      pumpState = false;

  digitalWrite(RELAY_PIN, pumpState);

  // -------- LEDs --------
  if(moisture > 60)
  {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
  else if(moisture >= 30)
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }
  else
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }

  // -------- LCD --------
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Moist:");
  lcd.print(moisture);
  lcd.print("%");

  lcd.setCursor(0,1);

  if(pumpState)
    lcd.print("Pump: ON ");
  else
    lcd.print("Pump: OFF");

  // -------- Serial Monitor --------
  Serial.print("Raw ADC: ");
  Serial.print(rawADC);

  Serial.print("  Filtered: ");
  Serial.print(filteredADC);

  Serial.print("  Moisture: ");
  Serial.print(moisture);
  Serial.print("%");

  Serial.print("  Pump: ");

  if(pumpState)
    Serial.println("ON");
  else
    Serial.println("OFF");

  delay(500);
}