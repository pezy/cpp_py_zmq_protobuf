import sys
import os
import zmq

sys.path.append(os.getcwd() + '/build')

from msg_pb2 import *
# Socket to talk to server
context = zmq.Context()
socket = context.socket(zmq.SUB)

print("Collecting updates from weather server...")
socket.connect ("tcp://localhost:5560")

# Subscribe to zipcode, default is NYC, 10001
socket.setsockopt_string(zmq.SUBSCRIBE, "")

msg = DataSet()

# Process 5 updates
total_value = 0
for update_nbr in range (5):
    string = socket.recv()
    print(string)
    msg.ParseFromString(string)
    print(str(msg))

