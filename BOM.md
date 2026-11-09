# Bill of Materials

| # | Qty | Part | Value / Model | Notes |
|---|---|---|---|---|
| 1 | 1 | Microcontroller board | Arduino Uno | Reconstructed implementation |
| 2 | 1 | Temperature / humidity sensor | DHT11 | 0–50 °C, ±2 °C. Module or bare sensor. |
| 3 | 1 | N-channel MOSFET | IRLZ44N (logic-level) | Recommended part. Any MOSFET with R<sub>DS(on)</sub> specified at V<sub>GS</sub> = 4.5 V works. |
| 4 | 1–2 | DC fan | 12 V, 80 mm / 120 mm | Total current well below the MOSFET rating |
| 5 | 1 | Schottky diode | 1N5819 | Flyback across the fan (1N4007 also works) |
| 6 | 1 | Resistor | 220 Ω | Gate series resistor |
| 7 | 1 | Resistor | 10 kΩ | Gate pull-down |
| 8 | 1 | Resistor | 10 kΩ | DHT11 data pull-up (skip if the module has one) |
| 9 | 1 | Power supply | 12 V DC, ≥ 1 A | Fan power |
| 10 | 1 | Breadboard / prototype board | | |
| 11 | 1 | Enclosure | Cardboard (prototype) | See README → Challenges |
| 12 | — | Jumper wires | | |
