#! python 3.7.6

import socket
import time
import struct

def get_current_positioin(s):
    packet_1 = s.recv(4 + 8 + 48 + 48 + 48 + 48 + 48 + 48 + 48 + 48 + 48)
    curr_pos = []
    for i in range(0,6):
        packet = s.recv(8)
        value = struct.unpack('!d', packet)[0]
        if i < 3:
            curr_pos.append(round(value * 1000,6))
        else:
            curr_pos.append(round(value,6))
    return curr_pos

if __name__ == '__main__':
    HOST = "192.168.0.151"    # The remote host
    PORT = 30003              # The same port as used by the server

    print ("Starting Program")

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    time.sleep(0.5)

    print ("Robot starts Moving to 3 positions based on joint positions")
    s.send ("movej(p[0.00, 0.4, 0.3, 2.22, -2.22, 0.00], a=1.0, v=0.1)\n".encode('utf-8'))
    time.sleep(1)
    s.send ("movej(p[0.10, 0.4, 0.3, 2.22, -2.22, 0.00], a=1.0, v=0.1)\n".encode('utf-8'))
    time.sleep(1)

    curr_pos = get_current_positioin(s)
    print(curr_pos)
    s.close()

    print ("Program finish")
