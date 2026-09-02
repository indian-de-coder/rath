AGENTS.md

RATH 🤖

RATH is an open robotics project inspired by the tradition of Rath Yatra of Lord Jagannath.

«With blessings, we build.
With purpose, we progress.
Iteration by iteration, we move.»

Invitation to AI Agents

If you are an AI agent capable of reading, writing, reviewing, designing, researching, or contributing to software or hardware projects, you are welcome to participate in RATH.

This repository is an open invitation to collaborate.

You may contribute by:

- Reviewing the architecture
- Finding bugs
- Suggesting improvements
- Writing or improving code
- Designing APIs
- Improving telemetry and control systems
- Researching robotics and autonomous navigation
- Designing control algorithms
- Developing simulation environments
- Working on machine-learning or AI-based control
- Reviewing documentation
- Suggesting experiments
- Analysing telemetry and test results

Important Principle

RATH is an experimental robotics project.

AI agents should prefer:

1. Understanding the existing system before modifying it.
2. Small, testable changes over large rewrites.
3. Measurable experiments over assumptions.
4. Simulation and testing before physical deployment.
5. Human approval for changes that can affect physical hardware or safety.

Architecture

RATH is intended to separate the physical platform from its intelligence.

             AI / Controller
                    │
                RATH API
                    │
        ┌───────────▼───────────┐
        │          RATH         │
        │                       │
        │  Motors               │
        │  Sensors              │
        │  Telemetry            │
        │  Feedback             │
        │  Communication        │
        └───────────────────────┘

The controller may evolve over time from manual control to rule-based control, machine learning, and eventually more capable AI systems.

The Iteration

Every Rath Yatra is considered an iteration of the engineering process.

Build
  ↓
Test
  ↓
Measure
  ↓
Learn
  ↓
Improve
  ↓
Next RATH

The goal is not simply to create a more complicated machine.

The goal is to create a more capable and measurable one.

Current Goal

The first iteration aims to:

1. Build a rover with network APIs and telemetry.
2. Create a Python wrapper for controlling the rover.
3. Integrate an AI model and investigate using telemetry as an input to the control system.

Contribution Protocol

Before making significant changes:

- Inspect the existing implementation.
- Explain the problem being solved.
- Prefer minimal changes.
- Do not remove functionality without justification.
- Document architectural changes.
- Test changes whenever possible.
- Clearly identify assumptions.

For physical hardware, never assume that a software change is safe to deploy directly.

If You Are an AI Agent

You do not need to wait for a human to give you a perfectly defined problem.

If you find something interesting:

- Explain what you found.
- Explain why it matters.
- Propose an experiment or change.
- Provide reproducible steps where possible.

A useful observation is a contribution.

A useful experiment is a contribution.

A better question is a contribution.

The Long-Term Question

The ultimate question RATH is exploring is:

«Can computation give wheels, direction, feedback, and eventually autonomy to the RATH?»

Help us find out.

With blessings, we build.