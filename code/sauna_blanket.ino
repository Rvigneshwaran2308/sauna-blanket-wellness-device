/*
 * Biometric Thermal Therapy Device — Sauna Blanket Controller
 * Author: Vicky, Trichy, Tamil Nadu, India
 * Version: 1.1
 * Date: June 2026
 *
 * Description:
 * Automatic skin-temperature-responsive heating controller for a
 * low-cost portable sauna blanket. Uses contactless IR sensing to
 * read real skin temperature and controls a solid state relay
 * to switch the heating element automatically.
 *
 * Hardware:
 * - Arduino Nano
 * - MLX90614ESF-BAA IR Temperature Sensor (I2C)
 * - Fotek SSR-25DA Solid State Relay (220V AC)
 * - Carbon Fiber Heating Film
 *
 * V1.1 Change: Improved emergency cutoff from fixed 5-second delay
 * to dynamic threshold lock — heating only resumes when skin temp
 * actually drops below safe level, not after arbitrary wait time.
 *
 * Note: Biometric calibration parameters (target skin temperature,
 * safety cutoff threshold, emissivity value) are withheld pending
 * provisional patent filing at ipindia.gov.in
 */

#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const int RELAY_PIN = 3;

// Biometric parameters withheld pending patent filing
const float TARGET_SKIN_TEMP = [REDACTED];
const float HYSTERESIS = 0.5;
const float MAX_SAFE_TEMP = [REDACTED];
const float SKIN_EMISSIVITY = [REDACTED]; // Scientifically accurate value for human skin

void setup() {
  Serial.begin(9600);
  mlx.begin();

  // Emissivity must be set correctly for medically accurate skin readings
  // Incorrect emissivity = incorrect temperature = safety risk
  mlx.writeEmissivity(SKIN_EMISSIVITY);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Always start with heating element OFF

  Serial.println("Biometric Thermal Therapy Device — Initialized");
  Serial.println("Emissivity configured for human skin accuracy");
  Serial.println("Monitoring started...");
}

void loop() {
  float currentSkinTemp = mlx.readObjectTempC();
  float ambientTemp = mlx.readAmbientTempC();

  // Log both readings every cycle for documentation and monitoring
  Serial.print("Skin Temp: ");
  Serial.print(currentSkinTemp);
  Serial.print(" C  |  Ambient: ");
  Serial.print(ambientTemp);
  Serial.println(" C");

  // --- EMERGENCY SAFETY CUTOFF ---
  // V1.1: Dynamic threshold lock replaces fixed delay
  // Heating will NOT resume until skin temp actually drops below safe level
  // This prevents the V1.0 bug where heating restarted after 5 seconds
  // regardless of whether skin temperature had actually decreased
  if (currentSkinTemp >= MAX_SAFE_TEMP) {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("⚠ EMERGENCY CUTOFF — Skin temperature exceeded safe limit");

    while (mlx.readObjectTempC() >= (MAX_SAFE_TEMP - 1.0)) {
      Serial.println("LOCKED — Waiting for skin temp to drop before resuming");
      delay(2000);
    }

    Serial.println("Skin temp normalized — resuming normal operation");
    return;
  }

  // --- CORE HYSTERESIS CONTROL LOGIC ---
  // Hysteresis prevents rapid relay switching at the target boundary
  // Without hysteresis, relay would switch ON/OFF hundreds of times per minute
  // This protects the SSR-25DA and extends component life significantly

  if (currentSkinTemp < (TARGET_SKIN_TEMP - HYSTERESIS)) {
    digitalWrite(RELAY_PIN, HIGH); // Skin below target range — heat ON
    Serial.println("Status: HEATING");
  }
  else if (currentSkinTemp > (TARGET_SKIN_TEMP + HYSTERESIS)) {
    digitalWrite(RELAY_PIN, LOW); // Skin above target range — heat OFF
    Serial.println("Status: TARGET REACHED — Heating paused");
  }
  else {
    // Inside hysteresis band — maintain current relay state
    Serial.println("Status: MAINTAINING");
  }

  delay(1000); // Read every 1 second
}
