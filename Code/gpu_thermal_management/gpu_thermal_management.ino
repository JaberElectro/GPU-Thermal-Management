/*
 * GPU Thermal Management System
 * -----------------------------
 * Reads temperature from a DHT11 and switches 12 V cooling fans through a
 * logic-level N-MOSFET (low-side). Uses hysteresis to avoid fan chatter.
 *
 * Controller used in the reconstructed implementation: Arduino Uno.
 *
 * Wiring:
 *   DHT11 DATA -> D2 (10k pull-up to 5V)
 *   D9 -> 220R -> MOSFET gate, 10k gate pull-down to GND
 *   Fan(-) -> MOSFET drain, Fan(+) -> +12V, flyback diode across the fan
 *   12V supply GND tied to Arduino GND
 *
 * Libraries: "DHT sensor library" (Adafruit) + "Adafruit Unified Sensor".
 *
 * Serial output is CSV so a test run can be pasted straight into Data/.
 */

#include <DHT.h>

#define DHT_PIN  2
#define DHT_TYPE DHT11

const int   FAN_CONTROL_PIN = 9;

// Hysteresis band. Illustrative values, tune for your enclosure.
// The 5 °C gap is wider than the DHT11's ±2 °C accuracy, so sensor
// noise alone cannot toggle the fans.
const float FAN_ON_TEMP  = 35.0;
const float FAN_OFF_TEMP = 30.0;

// The DHT11 must not be sampled faster than ~1 Hz.
const unsigned long SAMPLE_INTERVAL_MS = 2000;

DHT dht(DHT_PIN, DHT_TYPE);
bool fanState = false;

void setup() {
  Serial.begin(9600);

  pinMode(FAN_CONTROL_PIN, OUTPUT);
  digitalWrite(FAN_CONTROL_PIN, LOW);   // fans off at boot

  dht.begin();

  Serial.println(F("# GPU Thermal Management System"));
  Serial.println(F("time_s,temperature_c,fan_state"));
}

void loop() {
  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    // A NaN would make every comparison below false and freeze the fan
    // in its last state. Report it instead of acting on it.
    Serial.println(F("# sensor read error"));
    delay(SAMPLE_INTERVAL_MS);
    return;
  }

  // --- Hysteresis control ---
  if (!fanState && temperature >= FAN_ON_TEMP) {
    fanState = true;                  // too hot: start cooling
  } else if (fanState && temperature <= FAN_OFF_TEMP) {
    fanState = false;                 // cooled enough: stop
  }
  // Between the two thresholds the state is intentionally left unchanged.

  digitalWrite(FAN_CONTROL_PIN, fanState ? HIGH : LOW);

  // CSV: time_s, temperature_c, fan_state
  Serial.print(millis() / 1000);
  Serial.print(',');
  Serial.print(temperature, 1);
  Serial.print(',');
  Serial.println(fanState ? 1 : 0);

  delay(SAMPLE_INTERVAL_MS);
}
