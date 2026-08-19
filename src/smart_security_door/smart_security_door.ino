#define BLYNK_TEMPLATE_ID "TMPL4-9hb_uGq"
#define BLYNK_TEMPLATE_NAME "Smart security Door"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <Keypad.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>


// Pin configuration

const int servoPin = 13;
const int greenLED = 14;
const int redLED = 27;
const int buzzer = 26;

// LCD

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo

#include <ESP32Servo.h>

Servo doorServo;

// Keypad

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {23, 19, 18, 17};
byte colPins[COLS] = {16, 4, 25, 33};

Keypad keypad = Keypad(
  makeKeymap(keys),
  rowPins,
  colPins,
  ROWS,
  COLS
);

// Security settings

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

String correctPIN = "1234";
String enteredPIN = "";

int failedAttempts = 0;

const int maxAttempts = 3;

// Setup

void setup() {

  Serial.begin(115200);

Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  doorServo.setPeriodHertz(50);
doorServo.attach(servoPin, 500, 2400);

  // Start with door locked
  doorServo.write(0);

  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);
  digitalWrite(buzzer, LOW);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("SMART SECURITY");

  lcd.setCursor(0, 1);
  lcd.print("ENTER PIN:");

  delay(2000);

  showLockedScreen();
}

// Main program

void loop() {

  Blynk.run();

  char key = keypad.getKey();

  if (key) {

    Serial.print("Key pressed: ");
    Serial.println(key);

    // submit PIN
    if (key == '#') {

      checkPIN();

    }

    //clear PIN
    else if (key == '*') {

      enteredPIN = "";

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PIN CLEARED");

      delay(1000);

      showLockedScreen();
    }

    // Number entered
    else {

      if (enteredPIN.length() < 4) {

        enteredPIN += key;

        lcd.setCursor(0, 1);

        for (int i = 0; i < enteredPIN.length(); i++) {
          lcd.print("*");
        }
      }
    }
  }
}

// Check PIN

void checkPIN() {

  if (enteredPIN == correctPIN) {

    failedAttempts = 0;

    unlockDoor();

  } else {

    failedAttempts++;

    denyAccess();

  }

  enteredPIN = "";
}

// Unlock door

void unlockDoor() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("ACCESS GRANTED");

  lcd.setCursor(0, 1);
  lcd.print("DOOR UNLOCKED");

  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH);

  doorServo.write(90);

  Serial.println("Access granted");

  delay(5000);

  lockDoor();

  Blynk.virtualWrite(V0, "UNLOCKED");
  Blynk.virtualWrite(V1, "ACCESS GRANTED");
  Blynk.virtualWrite(V2, failedAttempts);
}

// Deny access

void denyAccess() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("ACCESS DENIED");

  lcd.setCursor(0, 1);
  lcd.print("Attempts: ");
  lcd.print(failedAttempts);

  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);

  tone(buzzer, 1000);
  delay(1000);
  noTone(buzzer);

  Serial.println("Access denied");

  // Alarm after 3 failed attempts
  if (failedAttempts >= maxAttempts) {

    alarm();

  } else {

    delay(1500);

    showLockedScreen();

    Blynk.virtualWrite(V1, "ACCESS DENIED");
    Blynk.virtualWrite(V2, failedAttempts);
  }
}

// Alarm

void alarm() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("!!! ALARM !!!");

  lcd.setCursor(0, 1);
  lcd.print("3 FAILED TRIES");

  Serial.println("SECURITY ALARM");

  for (int i = 0; i < 5; i++) {

    digitalWrite(redLED, HIGH);

    tone(buzzer, 1500);

    delay(300);

    digitalWrite(redLED, LOW);

    noTone(buzzer);

    delay(300);
  }

  failedAttempts = 0;

  showLockedScreen();

  Blynk.virtualWrite(V0, "LOCKED");
  Blynk.virtualWrite(V1, "SECURITY ALARM");
  Blynk.virtualWrite(V2, failedAttempts);
  Blynk.virtualWrite(V3, "ALARM");
}

// Lock door

void lockDoor() {

  doorServo.write(0);

  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);

  showLockedScreen();

  Serial.println("Door locked");
}

// Locked screen

void showLockedScreen() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("DOOR LOCKED");

  lcd.setCursor(0, 1);
  lcd.print("ENTER PIN:");

  Blynk.virtualWrite(V0, "LOCKED");
  Blynk.virtualWrite(V3, "NORMAL");
}
