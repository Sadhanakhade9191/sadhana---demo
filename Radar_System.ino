// Includes the Servo library
#include <Servo.h>

// Includes the Wire library for I2C
#include <Wire.h>

// Includes the I2C LCD library
#include <LiquidCrystal_I2C.h>

// Initializes the I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Defines trigger and echo pins
const int trigPin = 10;
const int echoPin = 11;

// Variables for distance calculation
long duration;
int distance;

// Creates a servo object
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  // Initializes the LCD
  lcd.init();
  lcd.backlight();

  // Attaches the servo to pin 12
  myServo.attach(3);
}

void loop() {
  // Sweeps the servo from 15 to 165 degrees
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    delay(5);

    distance = calculateDistance();

    // Sends angle and distance to Processing
    Serial.print(i);
    Serial.print("°");
    Serial.println();
    Serial.print(distance);
    Serial.print("cm");
    Serial.println();
    Serial.println();

    // Displays angle on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Angle: ");
    lcd.print(i);
    lcd.print(" deg   ");

    // Displays distance on the LCD
    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm  ");

    delay(25);
  }

  // Sweeps the servo back from 165 to 15 degrees
  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    delay(5);

    distance = calculateDistance();

    // Sends angle and distance to Processing
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    // Displays angle on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Angle: ");
    lcd.print(i);
    lcd.print(" deg   ");

    // Displays distance on the LCD
    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm  ");

    delay(25);
  }
}

// Calculates distance using the ultrasonic sensor
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echo duration
  duration = pulseIn(echoPin, HIGH, 30000);

  // Checks whether an echo was received
  if (duration == 0) {
    return -1;
  }

  // Calculates distance in centimeters
  distance = duration * 0.034 / 2;

  return distance;
}