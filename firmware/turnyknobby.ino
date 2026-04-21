#include <Arduino.h>
#include <BleKeyboard.h>

// ---------------- PIN MAPPING ----------------

// Encoder
#define ENC_A 1
#define ENC_B 2
#define ENC_SW 8

// LEDs in PHYSICAL ORDER (your PCB layout)
const int ledPins[8] = {
  6,   // D6
  5,   // D5
  11,  // D8
  3,   // D3
  9,   // D9
  7,   // D7
  4,   // D4
  10   // D1
};

// ---------------- CONFIG ----------------

#define ENCODER_STEPS_PER_NOTCH 2
#define VOL_MIN 0
#define VOL_MAX 100

BleKeyboard bleKeyboard("Volume Knob", "Custom", 100);

// ---------------- STATE ----------------

volatile int encoderValue = 0;
int lastEncoded = 0;

int volumeLevel = 50;
bool lastButtonState = HIGH;

// ---------------- ENCODER ISR ----------------

void IRAM_ATTR readEncoder() {
  int MSB = digitalRead(ENC_A);
  int LSB = digitalRead(ENC_B);

  int encoded = (MSB << 1) | LSB;
  int sum  = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    encoderValue++;

  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    encoderValue--;

  lastEncoded = encoded;
}

// ---------------- LED CONTROL ----------------

void updateLEDs(int volume) {
  int ledsToLight = map(volume, VOL_MIN, VOL_MAX, 0, 8);

  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], i < ledsToLight ? HIGH : LOW);
  }
}

// ---------------- BLE VOLUME ----------------

void sendVolumeChange(int steps) {
  if (!bleKeyboard.isConnected()) return;

  while (steps > 0) {
    bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
    steps--;
  }

  while (steps < 0) {
    bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
    steps++;
  }
}

// ---------------- SETUP ----------------

void setup() {
  Serial.begin(115200);

  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENC_A), readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), readEncoder, CHANGE);

  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  bleKeyboard.begin();
}

// ---------------- LOOP ----------------

void loop() {
  static int lastEncoderValue = 0;

  // ----- Encoder handling -----
  int delta = encoderValue - lastEncoderValue;

  if (abs(delta) >= ENCODER_STEPS_PER_NOTCH) {
    int steps = delta / ENCODER_STEPS_PER_NOTCH;

    volumeLevel += steps * 2; // sensitivity
    volumeLevel = constrain(volumeLevel, VOL_MIN, VOL_MAX);

    sendVolumeChange(steps);
    updateLEDs(volumeLevel);

    lastEncoderValue += steps * ENCODER_STEPS_PER_NOTCH;
  }

  // ----- Button (Mute) -----
  bool currentButton = digitalRead(ENC_SW);

  if (lastButtonState == HIGH && currentButton == LOW) {
    if (bleKeyboard.isConnected()) {
      bleKeyboard.write(KEY_MEDIA_MUTE);
    }
    delay(200); // debounce
  }

  lastButtonState = currentButton;

  delay(5);
}
