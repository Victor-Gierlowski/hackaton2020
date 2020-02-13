import serial
import time
'''
for i in range(15):
    try:
        arduino = serial.Serial("COM{0}".format(i),9600)
        time.sleep(2)
        print("Connection to " + "COM{0}".format(i) + " established succesfully!\n")
    except Exception as e:
        print(e)
'''
i=7
try:
    arduino = serial.Serial("COM{0}".format(i),9600)
    time.sleep(2)
    print("Connection to " + "COM{0}".format(i) + " established succesfully!\n")
except Exception as e:
    print(e)

#Note: for characters such as 'a' I set data = b'a' to convert the data in bytes
#However the same thing does not work with numbers...
data = 0
data = arduino.write(1)
time.sleep(2)
arduino.close()
