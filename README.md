# RATH 🤖

With blessings, we build.
With purpose, we progress.

RATH is an experimental robotics project inspired by the tradition of Rath Yatra of Lord Jagannath.

The project aims to build a modern, computationally driven RATH using readily available materials and open technologies.

The immediate goal is to build a wheeled robotic platform with motor control, telemetry, sensors, and network APIs. The long-term goal is to develop an intelligent control system capable of understanding telemetry, making decisions, correcting its own errors, and eventually completing a journey autonomously.

RATH is not intended to be completed in a single iteration.

Every Rath Yatra is an iteration.

---
 
## CONTEXT

The inspiration comes from the tradition of Rath Yatra of Lord Jagannath.

Every year, a new Rath is built from scratch, piece by piece, and then put to the ultimate test: carrying the traditionally immovable Lord on His journey to His aunt's abode.

I see a remarkable engineering idea in this tradition.

An immovable object is given wheels, a structure, a direction, and a tremendous task to accomplish.

And somehow, it moves.

That is the spirit behind RATH.

---

## PHILOSOPHY

This project is an attempt to carry that tradition forward with modern technology.

In medieval times, devotees relied on the best technology available to them, which was primarily mechanical, to accomplish this enormous task.

Today, we have another set of tools: computation, sensors, networks, control systems, machine learning, and artificial intelligence.

My tribute to Lord Jagannath is therefore to build a RATH that relies primarily on computational technology.

I do not expect to build it perfectly in the first iteration.

Instead, every Rath Yatra becomes a test, every test becomes data, and every iteration becomes an opportunity to improve.

The ultimate objective is simple:

«Build a RATH that can carry Lord Jagannath from Point A to Point B with progressively less human intervention.»

---

## THE ENGINEERING PRINCIPLE

Before making the RATH intelligent, we must first make it measurable.

The system should know what it is doing and report what is happening.

That means establishing reliable:

- Motor control
- Sensor feedback
- Telemetry
- Communication
- Battery monitoring
- Error detection
- Feedback loops
- Data collection

Only after the physical system can be measured and controlled reliably should higher-level intelligence be introduced.

The body comes before the brain.

---

## THE AIM

1. HARDWARE

Build a modular wheeled rover with:

- Network APIs for telemetry and control
- Motor control
- Sensors and feedback
- Battery monitoring
- Feedback loops for error correction
- A reliable communication layer
- The ability to operate safely without an AI controller

The hardware should be treated as a platform rather than a one-off machine.

---

2. SOFTWARE

Build a control system running on another node that can:

- Receive telemetry from RATH
- Interpret the state of the rover
- Make control decisions
- Send commands through the RATH API
- Record the results of those decisions
- Learn from previous runs

The intelligence layer should remain independent from the rover itself.

This allows the same RATH platform to be controlled by:

Human
   ↓
Manual Controller
   ↓
Python Controller
   ↓
Rule-Based Controller
   ↓
Machine Learning
   ↓
AI Controller

The rover becomes the body, while different controllers can become its brain.

---

## FIRST ITERATION

The first iteration is deliberately simple.

Phase 1: Build the Body

Build a working rover capable of:

- Motor control
- Battery monitoring
- Basic sensors
- Network communication
- Telemetry

Phase 2: Build the Interface

Create a Python wrapper around the RATH API so that a PC can:

- Connect to RATH
- Read telemetry
- Send commands
- Monitor the rover
- Record data

Phase 3: Introduce Intelligence

Integrate a 4-billion-parameter model and investigate using rover telemetry as an input to the control system.

The objective at this stage is not to claim autonomous intelligence.

It is to experiment.

Can a general-purpose model understand the state of a physical machine?

Can it choose appropriate actions?

Can those actions be evaluated?

Can the system improve over successive runs?

---

## MEASURING PROGRESS

Every iteration should produce measurable results.

Possible metrics include:

- Distance travelled autonomously
- Navigation error
- Average speed
- Battery consumption
- Communication reliability
- Number of human interventions
- Motor-control accuracy
- Recovery from failures
- Successful completion rate

For example:

RATH 2026

Distance:              50 m
Autonomous distance:   20 m
Human interventions:   4
Navigation error:      ±X m
Battery consumed:      X%
Successful runs:       X/X

The numbers will become the history of the project.

The goal is not merely to make the next RATH different.

The goal is to make it better.

---

## LONG-TERM VISION

The long-term vision is to build a RATH that can make a journey without being given every step of the way.

It should eventually be capable of:

1. Understanding where it is.
2. Understanding where it needs to go.
3. Observing its surroundings.
4. Understanding its own physical state.
5. Choosing an action.
6. Executing that action.
7. Measuring the result.
8. Correcting its behaviour.
9. Learning from previous journeys.

The final system may involve traditional control theory, robotics, machine learning, large language models, computer vision, reinforcement learning, or technologies that do not yet exist.

The architecture should remain open to all of them.

---

## THE ITERATION

RATH is not a single machine.

It is an ongoing experiment.

Every year provides another opportunity to build, test, measure, and improve.

Rath Yatra becomes the recurring field test.

The journey provides the problem.

Engineering provides the tools.

Data provides the measurement.

Iteration provides the progress.

And the ultimate objective remains the same:

«Build a RATH that moves with purpose.»

---

## CONTRIBUTE

Whether you are human or AI, if you can build, code, design, test, document, research, or simply suggest an idea, you are welcome to contribute.

You do not need to contribute a complete solution.

A better circuit, a piece of code, an algorithm, an experiment, a measurement, a mechanical design, or even a useful question can become part of the next iteration.

If you can help RATH move one step further, you are contributing to the journey.

---

## THANKS

Special thanks to:

1. Mr. Devashish Acharya for his keen insights and interest in the project.

And to everyone who contributes to the project, whether through code, hardware, ideas, experiments, or encouragement.

---

## RATH

With blessings, we build.
With purpose, we progress.
Iteration by iteration, we move.