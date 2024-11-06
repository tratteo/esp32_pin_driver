## ESP32 Universal pin driver 🌍

> [!IMPORTANT]
> Currently supporting only Serial (USB) communication.

### ⚡ Commands

```c
operation:mode:pin:value?
```

**Operation** `[write, read]`

**Mode** `[digital, analog]`

**Pin** `uint8_t`  
Safe GPIOs `[4, 13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33, 34, 35, 36, 39]`.  
Pin mapping [here](include/esp32_gpio_mapping.cpp).

**Value** `int`  
Value is automatically clamped to 8 bit:`[0, 255]`.

> [!NOTE]
> In digital write, pin is set to high if the value is greater than 0.

Examples:

```c
write:digital:13:0
write:analog:25:128

read:digital:19
read:analog:33
```

The ESP32 board available pins depend on the operation and mode used. Check out [esp32_gpio_mapping.cpp](include/esp32_gpio_mapping.cpp) for pin availability. For detailed information, check out the [ESP32 Pinout](https://lastminuteengineers.com/esp32-pinout-reference/).

### 🧪 Testing

To test program using the [Python utility](serial_test.py), install `pyserial`:

```sh
pip install pyserial
```

The run the script:

```sh
python serial_test.py
```

To edit the Serial port, edit the following line in the script:

```py
ser = serial.Serial("<your_port", 115200)
```
