"""Plot a logged test run: temperature and fan duty versus time.

Usage:  python plot_run.py ../Data/run-pwm-control.csv
"""
import sys
import csv
import matplotlib.pyplot as plt

TEMP_MIN, TEMP_MAX = 30, 40

t, temp, duty = [], [], []
with open(sys.argv[1]) as f:
    rows = (r for r in f if not r.startswith("#"))
    for row in csv.DictReader(rows):
        t.append(float(row["time_s"]) / 60)
        temp.append(float(row["temperature_c"]))
        duty.append(float(row["duty_percent"]))

fig, (a1, a2) = plt.subplots(2, 1, sharex=True, figsize=(9, 5),
                             gridspec_kw={"height_ratios": [3, 1.3]})
a1.plot(t, temp, color="#cf222e", lw=2)
a1.axhline(TEMP_MIN, ls=":", color="#0969da", label="fans start")
a1.axhline(TEMP_MAX, ls=":", color="#cf222e", label="full speed")
a1.set_ylabel("Temperature (°C)")
a1.legend(frameon=False)
a1.grid(alpha=0.3)
a2.step(t, duty, where="post", color="#1a7f37")
a2.set_ylabel("Fan duty (%)")
a2.set_xlabel("Time (min)")
a2.grid(alpha=0.3)
fig.suptitle(sys.argv[1])
out = sys.argv[1].rsplit(".", 1)[0] + ".png"
fig.savefig(out, dpi=150, bbox_inches="tight")
print("saved", out)
