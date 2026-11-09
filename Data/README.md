# Test Data

The sketch prints CSV over Serial:

```
time_s,temperature_c,fan_state
0,27.0,0
2,27.0,0
...
```

## How to log a run

1. Open the Serial Monitor at 9600 baud, or use any serial logger (PuTTY, CoolTerm, `screen`).
2. Heat the enclosure and let the controller go through at least two ON/OFF cycles.
3. Save the output as `run-YYYY-MM-DD.csv` in this folder.
4. Run `../Analysis/plot_run.py run-YYYY-MM-DD.csv` to get a temperature/fan-state plot.

Suggested test runs:

| File | Condition |
|---|---|
| `run-fans-disabled.csv` | Same heat load, fan pin forced LOW (the baseline) |
| `run-hysteresis.csv` | Normal operation |

> Only measured data goes in this folder. The simulated curve in the README is labeled as a model.
