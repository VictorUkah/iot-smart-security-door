# iot-smart-security-door
IoT-Based Smart Security Door System using ESP32, Keypad, Servo, LCD and Blynk

## Project Description

This project is an IoT-based smart security door system developed using an ESP32 and simulated using Wokwi.

The system requires a PIN code to unlock the door. Incorrect access attempts are recorded, and an alarm is activated after three consecutive failed attempts.

The system is enhanced using Blynk IoT technology, allowing security information to be monitored remotely.

## Main Components

- ESP32 DevKitC V4
- 4x4 Keypad
- Servo Motor
- 16x2 I2C LCD
- Red LED
- Green LED
- Buzzer

## IoT Technology

Blynk is used to monitor:

- Door status
- Access status
- Failed attempts
- Alarm status

## Security Features

- PIN authentication
- Automatic door locking
- Failed-attempt counter
- Three-attempt alarm
- Remote IoT monitoring

## Future Development

A future version could use machine learning to identify unusual access patterns based on factors such as access time, failed attempts and frequency of access.

## Simulation
https://wokwi.com/projects/472785715846566913
Wokwi simulation:

[Open Wokwi Simulation](YOUR_WOKWI_LINK)
