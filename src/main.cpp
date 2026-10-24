#include <Arduino.h>

/**
 * Simulation only: generates synthetic power samples and prints telemetry.
 * No sensor, mains interface, Matter, or ESPHome implementation is present.
 */

constexpr int LED_PIN = 2;

float simulatedWatts = 120.0f;
double cumulativeWh = 0.0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  delay(500);
  Serial.println(F("OpenWatt Node simulation boot — synthetic telemetry"));
}

void loop() {
  // Simulate power sample jitter
  simulatedWatts += (float)(random(-30, 31));
  if (simulatedWatts < 0) simulatedWatts = 0;
  cumulativeWh += simulatedWatts / 3600.0; // per-second sample stand-in

  digitalWrite(LED_PIN, HIGH);
  Serial.printf(
      "{\"w\":%.1f,\"wh\":%.2f,\"mode\":\"local\"}\n",
      simulatedWatts,
      cumulativeWh);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(800);
}
