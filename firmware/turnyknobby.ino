/*
 * XIAO ESP32-S3 VOLUME CONTROLLER
 */

#include <Arduino.h>

// ---------- Hardware Pins Mappings ----------
#define ENC_A_PIN   2   
#define ENC_B_PIN   1   
#define ENC_SW_PIN  44 

const uint8_t LED_PINS[] = {8, 4, 43, 7, 3, 9, 5, 6}; 
const uint8_t NUM_LEDS = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

// ---------- SOFT-POWER LIMITING CONFIGURATION ----------
const uint8_t MAX_BRIGHTNESS = 30; 

// ---------- Core State Variables ----------
volatile int8_t  encoderDelta = 0;
volatile uint8_t lastEncoded  = 0;

int volume = 50;
const int VOLUME_STEP = 4;

void updateLEDs(bool slow);

void IRAM_ATTR encoderISR() {
  uint8_t MSB = digitalRead(ENC_A_PIN);
  uint8_t LSB = digitalRead(ENC_B_PIN);
  uint8_t encoded = (MSB << 1) | LSB;
  uint8_t sum = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderDelta++; 
  } else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderDelta--; 
  }
  lastEncoded = encoded;
}

void setup() {
  Serial.begin(115200);

  pinMode(ENC_A_PIN, INPUT_PULLUP);
  pinMode(ENC_B_PIN, INPUT_PULLUP);
  pinMode(ENC_SW_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENC_A_PIN), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B_PIN), encoderISR, CHANGE);

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    ledcAttach(LED_PINS[i], 5000, 8); 
    ledcWrite(LED_PINS[i], 0);
  }

  updateLEDs(true); 
  Serial.println("System active with safe reversed directional pins!");
}

void loop() {
  if (encoderDelta != 0) {
    noInterrupts();
    int8_t delta = encoderDelta;
    encoderDelta = 0;
    interrupts();

    volume = constrain(volume + (delta > 0 ? VOLUME_STEP : -VOLUME_STEP), 0, 100);
    updateLEDs(false);
  }

  delay(2);
}

void updateLEDs(bool slow) {
  uint8_t litCount = map(volume, 0, 100, 0, NUM_LEDS);

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    if (i < litCount) {
      if (slow) {
        for (int b = 0; b <= MAX_BRIGHTNESS; b += 2) {
          ledcWrite(LED_PINS[i], b);
          delay(8);
        }
      } else {
        ledcWrite(LED_PINS[i], MAX_BRIGHTNESS);
      }
    } else {
      ledcWrite(LED_PINS[i], 0);
    }
  }
}
