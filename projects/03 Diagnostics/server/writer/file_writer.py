from flask import json
import os

class FileWriter:
    """
    A writer that saves data into sequentially numbered text files.
    """
    def __init__(self, output_dir: str, filename: str, extension: str="txt"):
        super().__init__()
        os.makedirs(output_dir, exist_ok=True)

        self.output_dir = output_dir
        self.filename = filename
        self.extension = extension
        self.suffix = self._get_suffix_num()

    def write(self, data: list):
        filename = self._get_filename(self.suffix)
        filepath = self._get_filepath(filename)
        with open(filepath, 'w') as f:
            for cir in data:
                f.write(str(cir) + '\n')

        self.suffix += 1

    def write_json(self, data:str):
        filename = self._get_filename(self.suffix)
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
    
    def _get_filename(self, suffix):
        return f"{self.filename}{suffix}.{self.extension}"
    
    def _get_filepath(self, filename: str):
        return os.path.join(self.output_dir, filename)
    
