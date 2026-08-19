# System Design — IoT-Based Smart Security Door System

## 1. Introduction

The IoT-Based Smart Security Door System is a prototype designed to improve access control and provide remote monitoring of a security door.

The system uses an ESP32 microcontroller as the main controller. A keypad allows users to enter a security PIN, while a servo motor represents the physical locking mechanism. An LCD provides information to the user, while LEDs and a buzzer provide visual and audio feedback.

The system is enhanced using Blynk IoT, allowing important security information to be communicated over Wi-Fi and monitored remotely.

## 2. System Architecture

The system consists of five main sections:

1. User input
2. Security processing
3. Physical door control
4. Local status indicators
5. IoT monitoring


## 3. Hardware Components

### ESP32 DevKit

The ESP32 acts as the main controller. It processes keypad input, controls the servo, LEDs and buzzer, and provides Wi-Fi connectivity for communication with Blynk.

### 4x4 Keypad

The keypad provides the user interface for entering the security PIN.

The `#` key is used to submit the PIN and the `*` key is used to clear the entered PIN.

### Servo Motor

The servo motor represents the door locking mechanism.

Two positions are used:

* 0 degrees — locked
* 90 degrees — unlocked

After successful authentication, the servo moves to the unlocked position for five seconds before automatically returning to the locked position.

### LCD Display

The 16x2 I2C LCD provides local information to the user.

Examples include:

* `DOOR LOCKED`
* `ENTER PIN:`
* `ACCESS GRANTED`
* `ACCESS DENIED`
* `!!! ALARM !!!`

### LEDs

Two LEDs provide visual status information.

The green LED indicates successful access and an unlocked door.

The red LED indicates a locked door, denied access or an alarm condition.

### Buzzer

The buzzer provides an audible warning when an incorrect PIN is entered. It also provides repeated warning signals when the security alarm is activated.

## 4. Software Design

The system is programmed using Arduino C++.

The main software components are:

* Keypad input processing
* PIN validation
* Servo control
* LCD control
* LED control
* Buzzer control
* Failed-attempt tracking
* Alarm handling
* Wi-Fi communication
* Blynk communication

## 5. Security Logic

The PIN is:

`1234`

When the user enters four digits and presses `#`, the ESP32 compares the entered PIN with the stored PIN.

If the PIN is correct:

```text
ACCESS GRANTED
```

The failed-attempt counter is reset and the door is unlocked.

If the PIN is incorrect:

```text
ACCESS DENIED
```

The failed-attempt counter increases.

After three failed attempts, the alarm is activated.

## 6. System States

The system has several main operating states.

### Locked State

The system starts in the locked state.

* Servo: 0 degrees
* Red LED: ON
* Green LED: OFF
* Alarm: NORMAL
* LCD: `DOOR LOCKED`

### Unlocked State

When the correct PIN is entered:

* Servo: 90 degrees
* Red LED: OFF
* Green LED: ON
* LCD: `ACCESS GRANTED`

The door automatically locks again after five seconds.

### Access Denied State

When an incorrect PIN is entered:

* Red LED: ON
* Green LED: OFF
* Buzzer: ON temporarily
* Failed-attempt counter increases
* Blynk receives the access-denied event

### Alarm State

When three failed attempts occur:

* Buzzer activates repeatedly
* Red LED flashes
* LCD displays an alarm message
* Blynk receives the alarm status

## 7. ESP32 Pin Configuration

| Component | ESP32 GPIO |
| --------- | ---------: |
| Servo     |    GPIO 13 |
| Green LED |    GPIO 14 |
| Red LED   |    GPIO 27 |
| Buzzer    |    GPIO 26 |
| Keypad R1 |    GPIO 23 |
| Keypad R2 |    GPIO 19 |
| Keypad R3 |    GPIO 18 |
| Keypad R4 |    GPIO 17 |
| Keypad C1 |    GPIO 16 |
| Keypad C2 |     GPIO 4 |
| Keypad C3 |    GPIO 25 |
| Keypad C4 |    GPIO 33 |
| LCD SDA   |    GPIO 21 |
| LCD SCL   |    GPIO 22 |

## 8. IoT Enhancement

Blynk is used as the IoT platform for the project.

The ESP32 connects to Wi-Fi and communicates with Blynk Cloud.

Four virtual datastreams are used:

| Virtual Pin | Purpose         |
| ----------- | --------------- |
| V0          | Door Status     |
| V1          | Access Status   |
| V2          | Failed Attempts |
| V3          | Alarm Status    |

This allows the user to monitor the security system remotely.

For example, when an incorrect PIN is entered, Blynk can receive:

```text
Access Status: ACCESS DENIED
Failed Attempts: 1
```

When three failed attempts occur:

```text
Access Status: SECURITY ALARM
Failed Attempts: 3
Alarm Status: ALARM
```







Machine learning could analyse access patterns and identify behaviour that differs from normal usage.

