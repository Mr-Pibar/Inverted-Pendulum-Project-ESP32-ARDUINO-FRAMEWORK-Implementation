# Inverted Pendulum Project (ESP32 + Arduino Framework)

A personal embedded systems project focused on learning:

- ESP32 development
- Stepper motor control
- Encoder feedback
- MQTT communication
- Motion profiling
- PID control system

The long-term goal is to create a rail-based inverted pendulum system


---

# Hardware

Current hardware used:

- ESP32 DOIT DevKit V1
- TMC2209 stepper driver
- NEMA17 stepper motor
- Incremental rotary encoder (400 pulse)
- GT2 belt and pulley system 
- Linear rail system

(many thanks to Rayhan Arya for the metal parts and Satria Akhtari for helping design of the rail system)

---

# Features

Current implemented features (for now):

- Primitive stepper control
- Direction control (CW / CCW)
- Linear acceleration stepping
- Encoder pulse counting using interrupts
- WiFi connection
- MQTT communication
- MQTT-controlled motion commands

---

# MQTT Command Format

Example payload:

```text
1600,CW
```

Meaning:

- `1600` → number of steps
- `CW` → clockwise direction

Supported directions:

- `CW`
- `CCW`

---

# Project Structure

```text
src/
    main.cpp

lib/
    stepperControl/
    encoderControl/
    connectivity/

include/
    config.h
    wifiAndMQTT.h
```

---

# Platform

- Framework: Arduino
- Board: ESP32 DOIT DevKit V1
- IDE: PlatformIO

---

# Future Plans

Planned improvements:

```text
- Non-blocking step generation                  (on it)
- Timer interrupt based motion control          (I still need to learn ESP32 interrupts)
- PID balancing controller                      (idk where to start)
- Faster encoder processing                     (also need to learn ESP32 thread management and CPU cycles)
- Full inverted pendulum balancing              (bismillah)
```
---

# Notes

ts fun yo
<br>-2255/Pibar

