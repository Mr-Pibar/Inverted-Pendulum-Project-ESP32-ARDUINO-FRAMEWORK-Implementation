# Inverted Pendulum Project (ESP32 + Arduino Framework)

A personal embedded systems project focused on learning:

- ESP32 development
- Stepper motor control
- Encoder feedback
- Motion profiling
- Control system

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

# Feature Implementation

- HAL — encoders reading correctly, motor moving, homing working        (ongoing) // Stepper Done
- Control loop timing, velocity estimation, serial telemetry output     (ongoing)
- PD balance controller (manually swinging pendulum up, catch it)       (draft)
- LQR design in Python, implement on ESP32, compare to PD               (draft)
- Swing-up controller + automatic switch to LQR                         (draft)
- Tuning, Kalman filter, disturbance rejection experiments              (draft)

---

# Notes

ts fun yo
<br>-2255/Pibar

