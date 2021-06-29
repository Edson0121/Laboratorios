# Import serial model to connect with Arduino
import serial

# The port the Arduino is connected to
arduino_port = ""
# Serial connection
baud = 9600
# File name
fileName = "counterData.csv"

# Number of values to collect
samples = 10
line = 0
# Serial connection
serCon = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
# Open file
file = open(fileName, "a") # Append
print("Created file")

while(line <= samples):
    # Add data to file
    getData = str(serCon.readline()) # Read each line
    data = getData[0:][:-2]

    file = open(fileName, "a")
    # Write data with a new line
    file.write(data + "\n")
    line = line + 1

# Close file
print("Data collection complete.\n")
file.close()