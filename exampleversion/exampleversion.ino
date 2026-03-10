#include <QTRSensors.h>

QTRSensors qtr;

// Motor pins (localized, removed motor_interface.h)
const uint8_t L_F = 11;
const uint8_t L_B = 12;
const uint8_t R_F = 10;
const uint8_t R_B = 9;

// Sensor configuration (localized, removed sensor_interface.h)
const uint8_t SensorPins[] = {A0, A1, A2, A3, A4, A5, A7};
const uint8_t SensorCount = sizeof(SensorPins) / sizeof(SensorPins[0]);
const uint8_t EmitterPin = 7;

uint16_t sensorValues[SensorCount];

const int SPEED = 255;
const int GOAL = 1000;

int e = 0;
int e_past = 0;
int sigma = 0;
const int I_RANGE = GOAL;
int correction;

const float P = 1.0;
const float I = 0.0;
const float D = 0.0;

void setup()
{
  // Set motor output pins
  pinMode(L_F, OUTPUT);
  pinMode(L_B, OUTPUT);
  pinMode(R_F, OUTPUT);
  pinMode(R_B, OUTPUT);

  // Configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins(SensorPins, SensorCount);
  qtr.setEmitterPin(EmitterPin);
  delay(500);
  delay(5000);
  // begin calibration -- should take about 10 seconds
  digitalWrite(LED_BUILTIN, HIGH);
  analogWrite(L_F, 80);
  analogWrite(R_B, 80);
  digitalWrite(L_B, LOW);
  digitalWrite(R_F, LOW);
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(L_F, LOW);
  digitalWrite(R_F, LOW);
  digitalWrite(L_B, LOW);
  digitalWrite(R_B, LOW);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
}

void loop()
{
  // acquire position
  uint16_t position = qtr.readLineBlack(sensorValues);

  // print sensor readings
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.print(position);

  // PID
  e_past = e;
  e = GOAL - position;
  sigma = constrain(sigma + (I * e), -I_RANGE, I_RANGE);
  correction = map((P * e) + sigma + (D * (e - e_past)), -GOAL, GOAL, -SPEED, SPEED);

  Serial.print('\t');
  Serial.println(correction);

  analogWrite(L_F, constrain(SPEED - correction, 0, SPEED));
  analogWrite(R_F, constrain(SPEED + correction, 0, SPEED));
  digitalWrite(L_B, LOW);
  digitalWrite(R_B, LOW);
}