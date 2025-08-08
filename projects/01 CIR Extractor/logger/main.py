from arduino import Arduino
from writer import FileWriter

PORT = '/dev/ttyUSB1'
BAUD = 9600

OUTPUT_DIR = "_log"
FILENAME = "cir"

if __name__ == "__main__":
    arduino = Arduino(port=PORT, baud=BAUD)
    writer = FileWriter(output_dir=OUTPUT_DIR, filename=FILENAME)

    while True:
        if arduino.detect_cirs():
            cirs = arduino.read_cirs()
            writer.write(cirs)

        