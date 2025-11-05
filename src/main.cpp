#include <Arduino.h>
#include "../include/command.hpp"

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if (Serial.available())
  {
    String input = Serial.readStringUntil('\n');
    input.trim();
    input.toLowerCase();

    Command cmd;
    if (!parseCommand(input, cmd))
    {
      Serial.println("error:bad format");
    }
    else
    {
      String msg = executeCommand(cmd);
      Serial.println(msg);
    }
  }
}
