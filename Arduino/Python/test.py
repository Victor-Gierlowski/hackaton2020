import serial
ser = serial.Serial('COM7')  # open serial port
print(ser.name)         # check which port was really used
ser.write(b'B')     # write a string
ser.close()             # close port
