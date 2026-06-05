# Biometric Thermal Therapy Device
### Low-Cost Sauna Blanket with Automatic Skin Temperature Control

> Commercial sauna blankets cost ₹50,000. I built one for ₹2,000 that automatically adjusts to your skin temperature. This is how.

---

## The Problem

Thermal therapy (heat therapy) has well-documented wellness benefits â€” muscle recovery, circulation, relaxation, and detoxification. But commercial sauna blankets cost ₹40,000â€“₹80,000 in India, putting them out of reach for most people.

Existing low-cost alternatives use manual temperature controls â€” the user guesses how hot is too hot. That's not safe. That's not smart.

I built a device that reads your actual skin temperature in real time and adjusts automatically. No guessing. No manual control. Biometric feedback loop.

---

## What I Built

A portable full-body sauna blanket with:

- **Contactless IR skin temperature sensing** â€” MLX90614 medical-grade sensor reads skin temp without contact
- **Automatic relay control** â€” heating element turns ON/OFF based on real biometric data
- **Hysteresis logic** â€” prevents rapid switching, extends component life
- **Emergency safety cutoff** â€” dynamic lock engages if skin temp exceeds safe threshold, only releases when temp actually drops
- **Dual monitoring** â€” both skin temp and ambient temp logged in real time via Serial

**Version 1** â€” Built and functional. Self-designed circuit from scratch. Carbon fiber heating film. Cost: â‚¹2,000. Destroyed by accident.

**Version 2** â€” Fully engineered and documented. Awaiting component purchase (â‚¹3,500). Superior sensor, better safety architecture.

---

## Hardware (Version 2)

| Component | Model | Purpose |
|-----------|-------|---------|
| Microcontroller | Arduino Nano | Central processing and control logic |
| IR Temperature Sensor | MLX90614ESF-BAA | Contactless skin temperature reading |
| Solid State Relay | Fotek SSR-25DA | Safe 220V AC switching |
| Backup Thermistor | 10K NTC | Internal ambient safety backup |
| Heating Element | Carbon Fiber Heating Film | Full-body heat distribution |

---

## How It Works

```
[MLX90614 Sensor] â†’ reads skin temp every second
        â†“
[Arduino Nano] â†’ compares against target and safety thresholds
        â†“
[SSR-25DA Relay] â†’ switches 220V heating element ON or OFF
        â†“
[Serial Monitor] â†’ logs all readings for documentation
```

Emissivity is set to **0.98** â€” the scientifically accurate value for human skin. This is what makes the temperature reading medically meaningful rather than approximate.

---

## Code

The core control logic is in `/code/sauna_blanket.ino`

Biometric calibration parameters (target skin temperature, safety cutoff threshold, emissivity value) are withheld pending provisional patent filing at ipindia.gov.in.

The published code demonstrates:
- Sensor initialization and emissivity configuration
- Real-time dual temperature monitoring
- Hysteresis-based relay control logic
- Dynamic emergency cutoff with threshold lock

---

## Research

This project is the basis of an ongoing research paper:

**"Design and Development of a Low-Cost Thermal Therapy Device for Wellness Applications"**

Key differentiator from existing literature: existing devices (including Anyotoma et al., IEEE 2024) use manual app-based temperature control. This device uses contactless biometric skin sensing with fully automatic adjustment â€” no user input required during operation.

Paper in progress. Will be submitted to journal upon completion.

---

## IP Protection

PDF documentation of Version 2 design emailed to self for timestamp record â€” June 2026.

Provisional patent filing in progress at ipindia.gov.in.

Technical specifications and calibration parameters withheld from this repository until filing is complete.

---

## Project Status

| Milestone | Status |
|-----------|--------|
| Version 1 â€” Built and tested | âœ… Complete |
| Version 2 â€” Designed and documented | âœ… Complete |
| Arduino code â€” Written and tested (simulation) | âœ… Complete |
| GitHub documentation | ðŸ”„ In Progress |
| Component purchase for V2 | â³ Pending (â‚¹3,500) |
| Provisional patent filing | â³ Pending (â‚¹1,600) |
| Research paper | ðŸ”„ In Progress |
| Version 2 physical build | â³ Pending components |

---

## About

Built by **Vicky**, Class 12 student, Trichy, Tamil Nadu, India.

Self-taught in circuit design, Arduino programming, and hardware prototyping.

This device was designed, engineered, and documented independently â€” no institutional lab, no equipment budget, no team. Just a problem worth solving.

*Making wellness technology accessible to people who cannot afford commercial devices.*

---

## Contact

For research collaboration inquiries, reach out via GitHub.
