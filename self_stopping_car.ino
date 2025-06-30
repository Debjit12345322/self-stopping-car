#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup: lcd1 for front, lcd2 for back
LiquidCrystal_I2C lcd1 = LiquidCrystal_I2C(0x27, 16, 2);
LiquidCrystal_I2C lcd2 = LiquidCrystal_I2C(0x26, 16, 2);

// Ultrasonic pins
int trig1 = 6, echo1 = 7;    // Front sensor
int trig2 = 12, echo2 = 11;  // Back sensor

// Buzzer and motor pins
int buzz = 10;
int motor1 = 8, motor2 = 9;

float distance1, distance2;
int choice;

void setup() {
    pinMode(buzz, OUTPUT);
    pinMode(trig1, OUTPUT);
    pinMode(echo1, INPUT);
    pinMode(trig2, OUTPUT);
    pinMode(echo2, INPUT);
    pinMode(motor1, OUTPUT);
    pinMode(motor2, OUTPUT);

    Serial.begin(9600);
    lcd1.init();
    lcd1.backlight();
    lcd2.init();
    lcd2.backlight();

    // Mode selection
    do {
        Serial.println("Enter 1 for parking mode, and 2 for driving mode:");
        while (Serial.available() == 0);
        choice = Serial.parseInt();

        if (choice != 1 && choice != 2) {
            Serial.println("Wrong input");
        }
    } while (choice != 1 && choice != 2);
}

void loop() {
    // Read front distance
    digitalWrite(trig1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1, LOW);
    distance1 = 0.017 * pulseIn(echo1, HIGH);

    // Read back distance
    digitalWrite(trig2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2, LOW);
    distance2 = 0.017 * pulseIn(echo2, HIGH);

    switch (choice) {
        case 1: // Parking mode - backwards
            digitalWrite(motor1, HIGH);
            digitalWrite(motor2, LOW);

            if (distance1 < 4) {
                digitalWrite(buzz, HIGH);
                lcd2.setCursor(0, 0);
                lcd2.print("WARNING ");
                lcd2.print(distance1); lcd2.print("cm");
                digitalWrite(motor1, LOW);
                digitalWrite(motor2, LOW);
                delayMicroseconds(2000000);
                digitalWrite(buzz, LOW);
            }
            else if (distance1 < 10) {
                lcd2.setCursor(0, 0);
                lcd2.print("OBSTACLE ");
                lcd2.print(distance1); lcd2.print("cm");
            }
            else {
                lcd2.setCursor(0, 0);
                lcd2.print("Distance ");
                lcd2.print(distance1); lcd2.print("cm");
            }
            break;

        case 2: // Driving mode - forwards
            digitalWrite(motor2, HIGH);
            digitalWrite(motor1, LOW);

            if (distance2 < 4) {
                digitalWrite(buzz, HIGH);
                lcd2.setCursor(0, 0);
                lcd2.print("WARNING ");
                lcd2.print(distance2); lcd2.print("cm");
                digitalWrite(motor2, LOW);
                digitalWrite(motor1, LOW);
                delayMicroseconds(2000000);
                digitalWrite(buzz, LOW);
            }
            else if (distance2 < 10) {
                lcd2.setCursor(0, 0);
                lcd2.print("OBSTACLE ");
                lcd2.print(distance2); lcd2.print("cm");
            }
            else {
                lcd2.setCursor(0, 0);
                lcd2.print("Distance ");
                lcd2.print(distance2); lcd2.print("cm");
            }

            // Also show front distance (approaching vehicles)
            if (distance1 < 4) {
                digitalWrite(buzz, HIGH);
                lcd1.setCursor(0, 0);
                lcd1.print("WARNING ");
                lcd1.print(distance1); lcd1.print("cm");
                delayMicroseconds(2000000);
                digitalWrite(buzz, LOW);
            }
            else if (distance1 < 10) {
                lcd1.setCursor(0, 0);
                lcd1.print("SLOW DOWN ");
                lcd1.print(distance1); lcd1.print("cm");
            }
            else {
                lcd1.setCursor(0, 0);
                lcd1.print("Distance ");
                lcd1.print(distance1); lcd1.print("cm");
            }
            break;
    }
}
