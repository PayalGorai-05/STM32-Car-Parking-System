#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SENSOR1 PA0
#define SENSOR2 PA1

int totalSlots = 2;

void startupAnimation() {
    lcd.setCursor(0, 0);
    lcd.print(" SMART PARKING ");
    
    lcd.setCursor(0, 1);
    lcd.print(" Initializing ");
    
    for (int i = 0; i < 3; i++) {
        delay(500);
        lcd.print(".");
    }
    
    delay(1000);
    lcd.clear();
}

void setup() {
    Serial.begin(9600);

    lcd.init();
    lcd.backlight();

    startupAnimation();

    pinMode(SENSOR1, INPUT_PULLUP);
    pinMode(SENSOR2, INPUT_PULLUP);
}

void loop() {
    int L1 = digitalRead(SENSOR1);
    int L2 = digitalRead(SENSOR2);

    int available = 0;

    if (L1 == 1) available++;
    if (L2 == 1) available++;

    // Line 1 → Slot Summary
    lcd.setCursor(0, 0);
    lcd.print("Slots:");
    lcd.print(available);
    lcd.print("/");
    lcd.print(totalSlots);
    lcd.print("   ");

    // Line 2 → Sensor status
    lcd.setCursor(0, 1);

    if (L1 == 1)
        lcd.print("S1:EMP ");
    else
        lcd.print("S1:FULL ");

    if (L2 == 1)
        lcd.print("S2:EMP ");
    else
        lcd.print("S2:FULL ");

    Serial.print("Available: ");
    Serial.println(available);

    delay(500);
}