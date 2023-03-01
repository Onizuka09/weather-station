from flask import Flask, render_template
from flask_socketio import SocketIO,emit 
import json 
import time 
app = Flask(__name__)
sio= SocketIO(app,cors_allowed_origins='*')



resp =  {'name': 'hello ESP8266 !'}

@app.route('/')
def route():
    return render_template('index2.html')

@sio.on('connect')
def test_connect():
    print("client connected")
    emit('response', resp)

@sio.on('message')
def handle_message(data):
    #str= json.dumps(data)
    print(data)
   # x=  {"data":data['name']}
    emit("data",data,broadcast=True)


sio.on('disconnect')
def test_disconnect():
    print('Client disconnected')



if __name__ =='__main__':
    sio.run(app,host='0.0.0.0',debug=True)    
