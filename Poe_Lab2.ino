#include <Servo.h>

const int lightSensorPin = A0;
const int panServoPin = 11;
const int tiltServoPin = 10;

Servo panServo;
Servo tiltServo;

const int panRate = 1;
const int tiltRate = 10;
const int panRangeMaximum = 180;
const int tiltRangeMaximum = 180;

int panAngle = 0;
int tiltAngle = 0;

void setup()
{
  pinMode(lightSensorPin, INPUT);
  panServo.attach(panServoPin);
  tiltServo.attach(tiltServoPin);
  Serial.begin(9600);
}

void loop()
{
  updatePanServo(&panAngle);
  updateTiltServo(panAngle, &tiltAngle);
  moveToPosition(&panServo, panAngle);
  moveToPosition(&tiltServo, tiltAngle);
  
  int sensorReading = analogRead(lightSensorPin);
//  Serial.println("distance: ");
//  Serial.print(sensorToDistance(sensorReading));
//  Serial.print("angle: ");
//  Serial.print(panAngle);
  delay(15);
  
}

int sensorToDistance(int sensorReading)
{
  int distance = 11760/(sensorReading) + .4806;
  return distance;
}

void updatePanServo(int *panAngle)
{
  *panAngle = ((*panAngle)+panRate)%(panRangeMaximum+1);
}

void updateTiltServo(int panAngle, int *tiltAngle)
{
  Serial.println(panAngle);
  if (panAngle == panRangeMaximum)
  {
    *tiltAngle = ((*tiltAngle) + tiltRate)%(tiltRangeMaximum+1);
  }
}

void moveToPosition(Servo *servo, int angle)
{
  (*servo).write(angle);
}

