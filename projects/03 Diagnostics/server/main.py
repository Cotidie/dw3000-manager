from flask import Flask, request
from writer import FileWriter
import os

app = Flask(__name__)

SAVE_DIR = './_log/json'
FILE_WRITER = FileWriter(
    output_dir=SAVE_DIR,
    filename='frame',
    extension='json'
)

os.makedirs(SAVE_DIR, exist_ok=True)

@app.route('/json', methods=['POST'])
def receive_json():
    if not request.is_json:
        return "Request must be in JSON format", 400
    
    data = request.get_json()

    try:
        FILE_WRITER.write_json(data)
        return 'OK', 200
    except Exception as e:
        return f"error: {str(e)}", 500

@app.route('/text', methods=['POST'])
def receive_message():
    data = request.data.decode()
    print(f"Received: {data}")
    return 'OK', 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=20001)