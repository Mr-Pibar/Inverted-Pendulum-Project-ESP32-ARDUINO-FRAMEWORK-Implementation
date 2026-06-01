#include <Arduino.h>

#define ENCODER_A 34
#define ENCODER_B 35

volatile long encoderCount = 0;

void IRAM_ATTR encoderA_ISR(){
  if (digitalRead(ENCODER_B) == LOW){
        encoderCount++;
  } else {
        encoderCount--;
    }
}

void IRAM_ATTR encoderB_ISR() {
  if (digitalRead(ENCODER_A) == LOW){
      encoderCount--;
    } else {
       encoderCount++;
    }
}

long zeroOffset = 0;

void setup(){
    Serial.begin(9600);

    pinMode(ENCODER_A, INPUT);
    pinMode(ENCODER_B, INPUT);

    attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoderA_ISR, RISING);
    attachInterrupt(digitalPinToInterrupt(ENCODER_B), encoderB_ISR, RISING);

    delay(100);

    //Current position becomes 0°
    zeroOffset = encoderCount;

    Serial.println("Encoder Ready");
}

void loop() {
  long counts = encoderCount - zeroOffset;

  float angleRaw = counts * (360.0f / 800.0f);

  float angle = angleRaw;

while (angle > 180.0f){
  angle -= 360.0f;
}


  while (angle < -180.0f){
    angle += 360.0f;
  }


  //Velocity calculation
  static float prevAngleRaw = angleRaw;
  static uint32_t lastMicros = micros();

  uint32_t nowMicros = micros();
  float dt = (nowMicros - lastMicros) * 1e-6f;

  float angleVel = 0;

  if (dt > 0)
      angleVel = (angleRaw - prevAngleRaw) / dt;

  //Timestamp for logging
  uint32_t nowMillis = millis();

  Serial.print(nowMillis);
  Serial.print(",");
  Serial.print(angle);
  Serial.print(",");
  Serial.println(angleVel);

  prevAngleRaw = angleRaw;
  lastMicros = nowMicros;
}