from flask import Flask, request

app = Flask(__name__)

@app.route('/message', methods=['POST'])
def receive_message():
    data = request.data.decode()
    print(f"Received: {data}")
    return 'OK', 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=20001)