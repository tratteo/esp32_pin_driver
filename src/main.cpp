#include <Arduino.h>

const uint8_t OUT_PINS[] = {
    2, 4, 5, 12, 13, 14, 15,
    16, 17, 18, 19, 21, 22, 23,
    25, 26, 27, 32, 33};

const int OUT_PINS_COUNT = sizeof(OUT_PINS) / sizeof(uint8_t);

bool isPinSafe(uint8_t pin)
{
  for (int i = 0; i < OUT_PINS_COUNT; i++)
  {
    if (pin == OUT_PINS[i])
    {
      return true;
    }
  }
  return false;
}

void setup()
{
  Serial.begin(115200);

  for (int i = 0; i < OUT_PINS_COUNT; i++)
  {
    pinMode(OUT_PINS[i], OUTPUT);
  }
}
void loop()
{
  if (Serial.available())
  {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();

    if (command.length() < 2)
      return;

    char action = command[0];
    uint8_t pin = (uint8_t)command.substring(1).toInt();

    if (!isPinSafe(pin))
    {
      return;
    }
    if (action == 'h')
    {
      digitalWrite(pin, HIGH);
    }
    else if (action == 'l')
    {
      digitalWrite(pin, LOW);
    }
  }
}