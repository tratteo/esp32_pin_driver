import serial

ser = serial.Serial("COM4", 115200)

while True:
    try:

        user_input = input("> ")
        ser.write(user_input.encode())
        ser.write(b"\n")
        print(f"sent to esp_32: {user_input}")

        serial_response = ser.readline().decode().strip()
        print(f"received from esp_32: {serial_response}")
    except:
        exit(0)
