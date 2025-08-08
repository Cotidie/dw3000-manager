import matplotlib.pyplot as plt
import os

FILENAME = "cir_8.txt"

if __name__ == "__main__":
    filepath = os.path.join('_log',FILENAME)
    indices = []
    reals = []
    with open(filepath, 'r') as f:
        for line in f:
            values = line.strip().split(",")
            indices.append(int(values[0]))
            reals.append(int(values[1]))

    plt.figure(figsize=(12, 5))
    plt.plot(indices, reals, linewidth=1)
    plt.title("CIRs")
    plt.xlabel("Index")
    plt.ylabel("CIR")
    plt.grid(True)
    plt.tight_layout()
    plt.show()