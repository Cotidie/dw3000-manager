from flask import json
import os

class FileWriter:
    """
    A writer that saves CIR (Channel Impulse Response) data into sequentially numbered text files.

    This class automatically creates a `_log` output directory if it does not exist,
    and writes CIR data to files named `cir_1.txt`, `cir_2.txt`, `cir_3.txt`, etc., avoiding overwrites.
    """
    def __init__(self, output_dir: str, filename: str, extension: str="txt"):
        super().__init__()
        os.makedirs(output_dir, exist_ok=True)

        self.output_dir = output_dir
        self.filename = filename
        self.extension = extension
        self.suffix = self._get_suffix_num()

    def write(self, data: list):
        filename = self._get_filename()
        filepath = self._get_filepath(filename)
        with open(filepath, 'w') as f:
            for cir in data:
                f.write(str(cir) + '\n')

        self.suffix += 1

    def write_json(self, data):
        filename = self._get_filename()
        filepath = self._get_filepath(filename)
        with open(filepath, 'w') as f:
            json.dump(data, f, indent=4, ensure_ascii=False)

        self.suffix += 1

    def _get_suffix_num(self):
        i = 1
        while True:
            suffix = f"_{i}" if i > 0 else ""
            filename = self._get_filename(suffix)
            filepath = self._get_filepath(filename)
            if not os.path.exists(filepath):
                break

            i += 1

        return i
    
    def _get_filename(self):
        return f"{self.filename}{self.suffix}.{self.extension}"
    
    def _get_filepath(self, filename: str):
        return os.path.join(self.output_dir, filename)
    
