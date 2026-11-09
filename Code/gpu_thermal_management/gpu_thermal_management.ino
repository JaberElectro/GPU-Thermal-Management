/*
 * GPU Thermal Management System
 * -----------------------------
 * Reads temperature from a DHT11 and sets the speed of the DC cooling
 * fans with PWM through an IRF520 MOSFET driver module. The hotter the
 * enclosure, the faster the fans spin.
 *
 * Wiring:
 *   DHT11 DATA -> D2 (10k pull-up to 5V, usually on the module)
 *   IRF520 module SIG -> D9 (PWM), VCC -> 5V, GND -> GND
 *   IRF520 module VIN/GND <- fan power supply
 *   IRF520 module V+/V-   -> fans (+/-)
 *   Fan supply GND and Arduino GND are common through the module
 *
 * Libraries: "DHT sensor library" (Adafruit) + "Adafruit Unified Sensor".
 *
 * Serial output is CSV so a test run can be pasted straight into Data/.
 */

#include <DHT.h>

#define DHT_PIN  2
#define DHT_TYPE DHT11

const int FAN_PWM_PIN = 9;          // Timer1 PWM, ~490 Hz

// Temperature-to-speed curve. Illustrative values, tune for your enclosure.
const int TEMP_MIN = 30;            // below this: fans off
const int TEMP_MAX = 40;            // at/above this: full speed
const int PWM_MIN  = 90;            // ~35 % duty: lowest value that reliably starts the fans
const int PWM_MAX  = 255;

// The DHT11 must not be sampled faster than ~1 Hz.
const unsigned long SAMPLE_INTERVAL_MS = 2000;

DHT dht(DHT_PIN, DHT_TYPE);

// Map temperature to a PWM value.
//   T <  TEMP_MIN            -> 0 (off)
//   TEMP_MIN <= T < TEMP_MAX -> linear from PWM_MIN to PWM_MAX
//   T >= TEMP_MAX            -> PWM_MAX
int temperatureToPwm(float temperature) {
  if (temperature < TEMP_MIN)  return 0;
  if (temperature >= TEMP_MAX) return PWM_MAX;
  return map((long)temperature, TEMP_MIN, TEMP_MAX, PWM_MIN, PWM_MAX);
}

void setup() {
  Serial.begin(9600);

  pinMode(FAN_PWM_PIN, OUTPUT);
  analogWrite(FAN_PWM_PIN, 0);      // fans off at boot

  dht.begin();

  Serial.println(F("# GPU Thermal Management System"));
  Serial.println(F("time_s,temperature_c,pwm,duty_percent"));
}

void loop() {
  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    // Failed read: run the fans at full speed rather than leaving them
    // off while the temperature is unknown (fail-safe).
    analogWrite(FAN_PWM_PIN, PWM_MAX);
    Serial.println(F("# sensor read error: fans forced to full speed"));
    delay(SAMPLE_INTERVAL_MS);
    return;
  }

  int pwm = temperatureToPwm(temperature);
  analogWrite(FAN_PWM_PIN, pwm);

  // CSV: time_s, temperature_c, pwm, duty_percent
  Serial.print(millis() / 1000);
  Serial.print(',');
  Serial.print(temperature, 1);
  Serial.print(',');
  Serial.print(pwm);
  Serial.print(',');
  Serial.println((long)pwm * 100 / 255);

  delay(SAMPLE_INTERVAL_MS);
}
