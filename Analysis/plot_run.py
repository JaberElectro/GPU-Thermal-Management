"""Plot a logged test run: temperature and fan state versus time.

Usage:  python plot_run.py ../Data/run-hysteresis.csv
"""
import sys
import csv
import matplotlib.pyplot as plt

FAN_ON, FAN_OFF = 35.0, 30.0

t, temp, fan = [], [], []
with open(sys.argv[1]) as f:
    rows = (r for r in f if not r.startswith("#"))
    for row in csv.DictReader(rows):
        t.append(float(row["time_s"]) / 60)
        temp.append(float(row["temperature_c"]))
        fan.append(int(row["fan_state"]))

fig, (a1, a2) = plt.subplots(2, 1, sharex=True, figsize=(9, 5),
                             gridspec_kw={"height_ratios": [3, 1]})
a1.plot(t, temp, color="#cf222e", lw=2)
a1.axhline(FAN_ON, ls=":", color="#cf222e", label="ON threshold")
a1.axhline(FAN_OFF, ls=":", color="#0969da", label="OFF threshold")
a1.set_ylabel("Temperature (°C)")
a1.legend(frameon=False)
a1.grid(alpha=0.3)
a2.step(t, fan, where="post", color="#1a7f37")
a2.set_yticks([0, 1], ["OFF", "ON"])
a2.set_xlabel("Time (min)")
a2.grid(alpha=0.3)
fig.suptitle(sys.argv[1])
out = sys.argv[1].rsplit(".", 1)[0] + ".png"
fig.savefig(out, dpi=150, bbox_inches="tight")
print("saved", out)
