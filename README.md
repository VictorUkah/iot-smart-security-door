# IoT-Based Smart Security Door System

## 1. Project Overview

The **IoT-Based Smart Security Door System** is an Arduino/ESP32-based security prototype designed to improve access control and monitoring.

The system requires a user to enter a correct PIN through a 4×4 keypad before the door can be unlocked. A servo motor represents the physical door lock, while LEDs and a buzzer provide visual and audio feedback.

The system has also been enhanced with **Blynk IoT**, allowing security information to be monitored remotely through an IoT dashboard.

---

## 2. Problem Statement

Traditional door security systems may provide physical protection but may not provide information about access attempts or suspicious activity.

The proposed system addresses this problem by providing:

* PIN-based authentication
* Automatic door locking
* Failed access attempt detection
* Security alarm functionality
* Remote IoT monitoring

---

## 3. Project Objectives

The main objectives are:

1. Develop a working smart security door prototype.
2. Implement PIN-based access control.
3. Control a simulated door lock using a servo motor.
4. Detect and record incorrect PIN attempts.
5. Activate an alarm after three failed attempts.
6. Display system information using an LCD.
7. Enhance the system using Blynk IoT.
8. Allow security events to be monitored remotely.
9. Evaluate the potential use of machine learning in future versions.

---

## 4. Hardware Components

The prototype uses the following components:

| Component        | Purpose                                 |
| ---------------- | --------------------------------------- |
| ESP32 DevKitC V4 | Main controller and Wi-Fi communication |
| 4×4 Keypad       | PIN entry                               |
| Servo Motor      | Simulates the door lock                 |
| 16×2 I2C LCD     | Displays system information             |
| Green LED        | Indicates successful access             |
| Red LED          | Indicates locked/denied status          |
| Buzzer           | Provides an audible warning             |

---

## 5. Software and Technologies

The project uses:

* Arduino C++
* ESP32
* Wokwi
* Blynk IoT
* GitHub

### Libraries

* Keypad
* ESP32Servo
* LiquidCrystal I2C
* Blynk

---

## 6. System Operation

The system starts in the locked state.

The user enters a four-digit PIN using the keypad.

### Correct PIN

If the entered PIN is correct:

1. Access is granted.
2. The green LED turns on.
3. The red LED turns off.
4. The servo moves to the unlocked position.
5. The Blynk dashboard reports that the door is unlocked.
6. After five seconds, the door automatically locks again.

### Incorrect PIN

If the PIN is incorrect:

1. Access is denied.
2. The red LED remains on.
3. The buzzer sounds.
4. The failed-attempt counter increases.
5. The failed-attempt information is sent to Blynk.

### Three Failed Attempts

After three incorrect PIN attempts:

1. The security alarm is activated.
2. The buzzer sounds repeatedly.
3. The red LED flashes.
4. The alarm status is sent to Blynk.
5. The failed-attempt counter is reset.

---

## 7. IoT Enhancement — Blynk

Blynk is used to provide remote monitoring of the security system.

The ESP32 connects to Wi-Fi and communicates with the Blynk cloud platform.

The following information is sent to Blynk:

| Virtual Pin | Data            |
| ----------- | --------------- |
| V0          | Door Status     |
| V1          | Access Status   |
| V2          | Failed Attempts |
| V3          | Alarm Status    |

Example dashboard information:

```text
Door Status: LOCKED
Access Status: ACCESS DENIED
Failed Attempts: 2
Alarm Status: NORMAL
```

When three failed attempts occur, the dashboard can display:

```text
Door Status: LOCKED
Access Status: SECURITY ALARM
Failed Attempts: 3
Alarm Status: ALARM
```

---

## 8. Security Features

The system includes several security features:

* Four-digit PIN authentication
* Automatic door locking
* Failed-attempt tracking
* Three-attempt alarm
* Visual LED indicators
* Audible buzzer warning
* Remote IoT monitoring

---

## 9. Testing

The system will be tested using several scenarios.

| Test                    | Input                | Expected Result        |
| ----------------------- | -------------------- | ---------------------- |
| Correct PIN             | `1234#`              | Door unlocks           |
| Incorrect PIN           | `1235#`              | Access denied          |
| Two failed attempts     | Two incorrect PINs   | Counter reaches 2      |
| Three failed attempts   | Three incorrect PINs | Alarm activates        |
| Clear PIN               | `*`                  | Entered PIN is cleared |
| Correct PIN after alarm | `1234#`              | Door unlocks           |

Testing evidence will be documented using screenshots from Wokwi and Blynk.

---

## 10. Machine Learning Potential

The current system uses rule-based security, where three failed attempts automatically activate the alarm.

A future version could incorporate machine learning to identify unusual access behaviour.

Potential data could include:

* Number of failed attempts
* Time of access
* Frequency of access attempts
* Duration of door openings
* Successful and unsuccessful access patterns

A machine-learning model could learn normal access behaviour and identify unusual activity.

For example, repeated access attempts at an unusual time could be classified as potentially suspicious.

Machine learning would therefore provide a more adaptive security system compared with the current fixed three-attempt rule.

---

## 11. Future Improvements

Possible future improvements include:

* Mobile push notifications
* fingerprint authentication
* Multiple authorised users
* Remote door-control functionality
* Cloud-based event history
* Real physical door sensors
* Camera integration
* Machine-learning-based anomaly detection
* Battery backup
* Tamper detection

---

## 12. Project Simulation

The project is simulated using Wokwi.

**Wokwi Simulation:**
(https://wokwi.com/projects/472785715846566913)

---

## 13. Repository Contents

```text
iot-smart-security-door/
│
├── README.md
│
├── src/
│   └── smart_security_door/
│       └── smart_security_door.ino
│
├── wokwi/
│   ├── diagram.json
│   └── libraries.txt
│
├── documentation/
│   ├── system-design.md
│   └── testing.md
│
└── screenshots/
    ├── wokwi-circuit.png
    └── blynk-dashboard.png
```

---





