#include <ardPololuServoController.h>

ardPololuServoController<HardwareSerial> _servoController(&Serial1, 57000);
unsigned int minPosition = 300;
unsigned int maxPosition = 1500;

void setup()
{
}

void loop()
{
  for(int servo = 0; servo < 4; servo++)
  {
    _servoController.setPosition(servo, 608); 
  }
  delay(3000);
  for(int servo = 0; servo < 4; servo++)
  {
    _servoController.setPosition(servo, 2224); 
  }
  delay(3000);
}
