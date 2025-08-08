from serial import Serial
from typing import List

from entity import CIR

DELIM_START = "START OF CIR"
DELIM_END = "END OF CIR"

class Arduino:
    """Initializes a serial interface Arduino board"""

    def __init__(self, port: str, baud: int):
        """Initializes a serial interface Arduino board

        Arguments:
            port -- a serial port connected to Arduino board. 
                    For example, '/dev/ttyUSB0' for Linux, 'COM4' for Windows.

            baud -- a baudrate for which you chose for the Arduino's Serial class
        """
        self.port = port
        self.baud = baud
        self.serial = Serial(self.port, self.baud)

    def read_cirs(self) -> List[CIR]:
        """Read CIR values as a list of 1016 samples. The values should be wrapped with delimiters, 
        beginning with 'START OF CIR' and ending with 'END OF CIR'"""

        cirs = []
        while True:
            line = self.serial.readline().decode("utf-8").strip()
            if line == DELIM_END:
                break
            
            values = list(map(int, line.split(",")))
            cirs.append(CIR(
                index=values[0],
                real=values[1],
                imaginary=values[2]
            ))
        
        return cirs
    
    def detect_cirs(self) -> bool:
        line = self.serial.readline().decode("utf-8").strip()
        if line != DELIM_START:
            return False
        return True