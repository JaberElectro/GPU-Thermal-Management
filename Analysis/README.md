# Analysis

## Simulated response (`simulated-response.svg`)

This is a simple **first-order thermal model** used to check that the control logic behaves as intended before testing on hardware. It is **not measured data**.

$$
\frac{dT}{dt} = \frac{P}{C_{th}} - \left(k_{nat} + k_{fan}\,D\right)(T - T_{amb})
$$

The fan's cooling effect is modelled as proportional to its PWM duty cycle $D$.

| Symbol | Meaning | Value used |
|---|---|---|
| $T_{amb}$ | ambient temperature | 27 °C |
| $P/C_{th}$ | heating rate from the source | 0.05 °C/s |
| $k_{nat}$ | natural heat loss (fans off) | 0.0012 s⁻¹ |
| $k_{fan}$ | extra heat loss at 100 % duty | 0.02 s⁻¹ |
| $D$ | fan duty from the speed curve (30–40 °C, 35–100 %) | — |

What the model shows:

- **Fans disabled:** the temperature heads toward $T_{amb} + \frac{P/C_{th}}{k_{nat}} \approx 69$ °C.
- **PWM control:** the temperature settles just above 30 °C, with the fans running at partial speed (~45 %). The fans don't need full speed to hold the temperature, so they run quieter and use less power.
- **Design check:** at 100 % duty the equilibrium is $27 + \frac{0.05}{0.0212} \approx 29.4$ °C. If that number were **above** 40 °C (weak fans, or an enclosure that traps heat, which is the cardboard problem), the fans would sit at full speed and still lose.

## Plotting a real run

```bash
python plot_run.py ../Data/run-pwm-control.csv
```
