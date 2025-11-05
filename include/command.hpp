#include <Arduino.h>
#include "../include/esp32_gpio_mapping.hpp"
#include "../include/defines.hpp"

struct Command
{
    String operation;
    String mode;
    int pin;
    int value;
};

int clamp(int value, int min, int max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    else
    {
        return value;
    }
}

String executeCommand(Command &cmd)
{
    if (cmd.operation == OP_READ)
    {
        pinMode(cmd.pin, INPUT);
        int value;
        if (cmd.mode == OP_MODE_DIGITAL)
        {
            value = digitalRead(cmd.pin);
        }
        else if (cmd.mode == OP_MODE_ANALOG)
        {
            value = analogRead(cmd.pin);
        }
        return ("read:" + String(cmd.pin) + ":" + String(value));
    }
    else if (cmd.operation == OP_WRITE)
    {
        pinMode(cmd.pin, OUTPUT);
        if (cmd.mode == OP_MODE_DIGITAL)
        {
            cmd.value = cmd.value > 0 ? HIGH : LOW;
            digitalWrite(cmd.pin, cmd.value > 0 ? HIGH : LOW);
        }
        else if (cmd.mode == OP_MODE_ANALOG)
        {
            analogWrite(cmd.pin, cmd.value);
        }
        return ("write:" + String(cmd.pin) + ":" + String(cmd.value));
    }
    return "error:unrecognized command";
}

bool parseCommand(String input, Command &cmd)
{
    int firstColon = input.indexOf(':');
    int secondColon = input.indexOf(':', firstColon + 1);

    if (firstColon == -1 || secondColon == -1)
    {
        return false;
    }

    cmd.operation = input.substring(0, firstColon);
    cmd.mode = input.substring(firstColon + 1, secondColon);

    if ((cmd.operation != OP_READ && cmd.operation != OP_WRITE) || (cmd.mode != OP_MODE_DIGITAL && cmd.mode != OP_MODE_ANALOG))
    {
        return false;
    }

    String pinStr = input.substring(secondColon + 1);
    cmd.pin = pinStr.toInt();
    if (!esp32GpioSafe(cmd.pin, cmd.operation))
    {
        return false;
    }
    if (cmd.operation == OP_WRITE)
    {
        int valueIndex = pinStr.indexOf(':');
        if (valueIndex == -1)
        {
            return false;
        }
        cmd.pin = pinStr.substring(0, valueIndex).toInt();
        cmd.value = clamp(pinStr.substring(valueIndex + 1).toInt(), 0, 255);
    }

    if (cmd.operation == OP_WRITE && cmd.mode == OP_MODE_ANALOG && !esp32GpioEntitled(PinEntitlement::dac, cmd.pin))
    {
        return false;
    }

    if (cmd.operation == OP_READ && cmd.mode == OP_MODE_ANALOG && !esp32GpioEntitled(PinEntitlement::adc, cmd.pin))
    {
        return false;
    }

    return true;
}