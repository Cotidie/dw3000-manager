from dataclasses import dataclass

@dataclass
class CIR:
    """Class for CIR(Channel Impulse Response) which has real and imaginary values"""
    index: int
    real: int
    imaginary: int

    def __str__(self):
        return f"{self.index},{self.real},{self.imaginary}"