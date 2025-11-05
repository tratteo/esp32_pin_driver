#include <Arduino.h>
#include <map>
#include <vector>
#include "../include/defines.hpp"
enum class PinEntitlement
{
    adc,
    dac,
    touch,
    i2c,
    spi,
    uart,
    pwm,
    rtc
};
const std::vector<int> safePins = {4, 13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33, 34, 35, 36, 39};

std::map<PinEntitlement, const std::vector<int>> pinMappings = {
    {PinEntitlement::adc, {4, 13, 14, 25, 26, 27, 32, 33, 34, 35, 36, 39}},
    {PinEntitlement::dac, {25, 26}},
    {PinEntitlement::touch, {4, 13, 14, 25, 26, 27, 32, 33}},
    {PinEntitlement::i2c, {21, 22}},
    {PinEntitlement::spi, {13, 14, 18, 19, 23}},
    {PinEntitlement::uart, {16, 17}},
    {PinEntitlement::pwm, {4, 13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33}},
    {PinEntitlement::rtc, {4, 13, 14, 25, 26, 27, 32, 33, 34, 35, 36, 39}},
};

bool esp32GpioSafe(int pin, String operation)
{
    auto it = std::find(safePins.begin(), safePins.end(), pin);
    if (it == safePins.end())
        return false;
    if (operation == OP_WRITE)
    {
        return pin < 34;
    }
    return true;
}

bool esp32GpioEntitled(PinEntitlement function, int pin)
{
    auto vec = pinMappings[function];
    return std::find(vec.begin(), vec.end(), pin) != vec.end();
}