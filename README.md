Absolutely. I’d add it as a small **project philosophy** section, keeping the README technical rather than turning it into a manifesto.

# ROTH 🤖

> **With blessings, we build.**
> **With purpose, we progress.**

ROTH is an experimental robotics project built around a modified RC car platform. The goal is to turn a simple toy car into a programmable robotic vehicle with its own control system, motor control, networking, sensing, and eventually autonomous navigation.

## 🚗 Current Platform

The project started with a **360° stunt RC car** as the mechanical base.

Current mechanical direction:

* Original RC car chassis
* Two DC motors
* Acrylic sheet reinforcement / custom mounting
* Custom electronics mounted on the chassis

## 🧠 Controller

The main controller is an **ESP32** running **ESP-IDF**.

Current software components include:

* Wi-Fi
* TCP server / command shell
* Battery monitoring
* Motor PWM control
* Beacon / status LED
* FreeRTOS-based tasks

The ESP32 exposes a simple command interface for controlling ROTH.

Example:

```text
move 1 40 80 80
```

Where:

```text
move <channel> <power> <pulse> <duration>
```

## ⚙️ Motor Control

ROTH uses two DC motors controlled through a dual-channel motor driver.

The motor-control system currently supports:

* Forward / reverse control
* PWM speed control
* Four PWM outputs
* Minimum starting power compensation
* TCP-based motor commands
* Continuous throttle control from a gamepad

A major discovery during testing was **motor stiction / starting torque**.

The motor may not start at low PWM values when stationary, but once moving, it can continue running at a considerably lower PWM value.

This led to experimentation with:

* Starting pulses
* Minimum throttle
* PWM ramping
* PID-based control

## 🎮 Remote Control

A PC can currently act as the remote-control brain.

The controller input is read using Python and `evdev`, then translated into commands sent to ROTH.

```text
Gamepad
   │
   ▼
Python Controller
   │
   ▼
Network
   │
   ▼
ESP32
   │
   ▼
Motor Controller
   │
   ▼
DC Motors
```

## 🌐 Networking

ROTH currently uses **TCP** for reliable command and control communication.

The ESP32 runs a TCP server on:

```text
Port: 5000
```

Example:

```text
roth> move 1 40 80 80
```

UDP is also being considered for high-frequency gamepad control where low latency is more important than guaranteed delivery.

Potential architecture:

```text
TCP → configuration / commands / shell
UDP → continuous control / telemetry
```

## 🔋 Battery

ROTH includes battery-voltage monitoring using the ESP32 ADC.

Current voltage-divider arrangement:

```text
Battery
   │
  10kΩ
   │
   ├──── GPIO34 / ADC
   │
  10kΩ
   │
  GND
```

Battery information is exposed through the TCP shell:

```text
vbat
```

## 🖥️ Software Architecture

The firmware is gradually being separated into reusable components.

```text
ROTH
├── TCPShell
├── Battery
├── Beacon
├── Motor Control
├── Wi-Fi
└── FreeRTOS Tasks
```

The architecture is intentionally evolving from a simple motor controller into a small robotic control system.

## 📈 Development Path

ROTH is being developed incrementally:

```text
RC Car
  │
  ▼
ESP32 Motor Control
  │
  ▼
Network Control
  │
  ▼
Gamepad Control
  │
  ▼
Reliable Motion Control
  │
  ▼
Sensors
  │
  ▼
Localization
  │
  ▼
Navigation
  │
  ▼
Autonomous ROTH
```

## 🧭 Long-Term Goal

The larger goal is **Automated ROTH**.

The intended system will eventually be capable of travelling autonomously between two locations, remaining at the destination while charging, and returning automatically.

This will require progressively adding:

* Odometry
* Wheel-speed measurement
* IMU
* Heading estimation
* Distance sensing
* Obstacle detection
* Position estimation
* Navigation
* Autonomous motor control
* Battery management
* Charging detection
* Fail-safe behavior

## 🛠️ Current Focus

The immediate focus is building a reliable and controllable robotic platform before attempting autonomy.

### Current priorities

1. Reliable motor control
2. Smooth throttle control
3. Gamepad control
4. Battery monitoring
5. Chassis construction
6. Sensor integration

Autonomy comes later.

First, ROTH needs to learn how to drive. 🚗

## 🧭 Project Philosophy

ROTH is built one layer at a time.

Every subsystem is first tested, understood, and then integrated into the larger machine.

```text
Understand
    │
    ▼
Build
    │
    ▼
Test
    │
    ▼
Improve
    │
    ▼
Integrate
```

The philosophy behind the project is simple:

> **With blessings, we build.**
> **With purpose, we progress.**

The first gives the project its spirit.
The second gives it direction.

**Motor → Control → Network → Sensors → Intelligence → Autonomy**

And eventually:

> **ROTH drives itself.** 🤖
