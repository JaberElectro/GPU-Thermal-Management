# Analysis

## Simulated response (`simulated-response.svg`)

This is a simple **first-order thermal model** used to check that the control logic behaves as intended before testing on hardware. It is **not measured data**.

$$
\frac{dT}{dt} = \frac{P}{C_{th}} - k\,(T - T_{amb})
$$

| Symbol | Meaning | Value used |
|---|---|---|
| $T_{amb}$ | ambient temperature | 27 °C |
| $P/C_{th}$ | heating rate from the source | 0.05 °C/s |
| $k_{off}$ | heat loss, fans off | 0.0012 s⁻¹ |
| $k_{on}$ | heat loss, fans on | 0.02 s⁻¹ |

What the model shows:

- **Fans disabled:** the temperature heads toward the equilibrium $T_{amb} + \frac{P/C_{th}}{k_{off}} \approx 69$ °C.
- **Hysteresis control:** the temperature cycles between 30 and 35 °C.
- **Design check:** cooling only works if the fans-on equilibrium, $T_{amb} + \frac{P/C_{th}}{k_{on}} \approx 29.5$ °C, sits **below** the OFF threshold. If the fans are too weak, or the enclosure traps too much heat (the cardboard problem), that equilibrium rises above 30 °C and the fans never switch off.

## Plotting a real run

```bash
python plot_run.py ../Data/run-hysteresis.csv
```
