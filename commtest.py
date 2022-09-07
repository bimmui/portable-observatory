from sshkeyboard import listen_keyboard

import threading
import serial
import time
thestr = "none rn" # made a list as to keep the address when passed to other funcs

def press(key):
    global thestr
    if key == "up":
        thestr = 1
    elif key == "down":
        thestr = 2

    elif key == "w":
        thestr = 11
    elif key == "s":
        thestr = 22

    elif key == "left":
        print("left pressed")
        thestr = "left"
    elif key == "right":
        print("right pressed")
        thestr = "right"

def listenting():
    listen_keyboard(on_press=press)



if __name__ == '__main__':
    # Tries both possible connections for the Arduino
    try:
        ser = serial.Serial('/dev/ttyACM1', 9600, timeout=1)
    except:
        ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

    # Flushes any bytes that could already be in the input buffer
    ser.reset_input_buffer()

    # Starts the second thread to listen to keyboard input
    thread = threading.Thread(target=listenting, args=())
    thread.start()

    while True:
        # Prevents overloading the serial monitor
        if thestr == "none rn" or thestr == None:
            pass
        else:
            ser.write(f"{thestr}\n".encode('utf-8'))
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
        thestr = None
        time.sleep(.75)