# Test Data

The sketch prints CSV over Serial:

```
time_s,temperature_c,pwm,duty_percent
0,27.0,0,0
2,27.0,0,0
...
```

## How to log a run

1. Open the Serial Monitor at 9600 baud, or use any serial logger (PuTTY, CoolTerm, `screen`).
2. Heat the enclosure and keep logging until the temperature stops changing.
3. Save the output as a `.csv` file in this folder.
4. Run `../Analysis/plot_run.py <file>.csv` to plot temperature and fan duty.

Suggested test runs:

| File | Condition |
|---|---|
| `run-fans-disabled.csv` | Same heat load with the fans unplugged (the baseline) |
| `run-pwm-control.csv` | Normal operation |

> Only measured data goes in this folder. The simulated curve in the README is labeled as a model.
