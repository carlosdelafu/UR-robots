# Echo client program
import socket
import time
import struct

HOST = "192.168.0.151"    # The remote host
PORT = 30003              # The same port as used by the server
print ("Starting Program")
count = 0

while (count < 1):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    time.sleep(0.5)
    print ("Set output 1 and 2 high")
    s.send (("set_digital_out(1,True)\n").encode('utf-8'))
    # print(bytes("set_digital_out(1,True)\n",encoding='utf-8'))
    time.sleep(0.1)

    s.send (("set_digital_out(2,True)\n").encode('utf-8'))
    #time.sleep(2)
    print ("Robot starts Moving to 3 positions based on joint positions")
    
    #movej([0.000000, -1.570796, -1.570796, 0.000000, 1.570796, -0.000000],1.200, 0.750,0,0)
    #movel(p[0.445139, -0.171816, 0.607850, -0.661258, 1.816791, -1.816791],3.000,0.300,0,0.001)
    #s.send ("movej([0.000000, -1.570796, -1.570796, 0.000000, 1.570796, -0.000000],1.200, 0.750,0,0)\n".encode('utf-8'))
    #s.send ("movel(p[0.445139, -0.171816, 0.607850, -0.661258, 1.816791, -1.816791],3.000,0.300,0,0.001)\n".encode('utf-8'))
    #time.sleep(10)
    
    print("test one over!")
    #exit()

    #s.send ("movej([-1.95, -1.66, 1.71, -1.62, -1.56, 1.19], a=1.0, v=0.1)\n".encode('utf-8'))
    #time.sleep(10)

    #s.send ("movej([-1.96, -1.53, 2.08, -2.12, -1.56, 1.19], a=1.0, v=0.1)\n".encode('utf-8'))
    #time.sleep(10)

    #print ("Robot starts Moving to 3 positions based on pose positions")

    # s.send ("movej(p[0.00, 0.03, 0.04, 2.22, -2.22, 0.00], a=1.0, v=0.1)\n".encode('utf-8'))
    # time.sleep(10)

    # meters 
    s.send ("movej(p[0.00, 0.4, 0.3, 2.22, -2.22, 0.00], a=1.0, v=0.1)\n".encode('utf-8'))
    time.sleep(1)

    s.send ("movej(p[0.10, 0.4, 0.3, 2.22, -2.22, 0.00], a=1.0, v=0.1)\n".encode('utf-8'))
    time.sleep(1)

    print ("Set output 1 and 2 low")

    s.send ("set_digital_out(1,False)\n".encode('utf-8'))

    time.sleep(0.1)

    s.send ("set_digital_out(2,False)\n".encode('utf-8'))
    time.sleep(0.1)

    count = count + 1
    print ("The count is:", count)

    print ("Program finish")

    time.sleep(1)
    # data = s.recv(1024)

    packet_1 = s.recv(4)
    packet_2 = s.recv(8)
    packet_3 = s.recv(48)
    packet_4 = s.recv(48)
    packet_5 = s.recv(48)
    packet_6 = s.recv(48)
    packet_7 = s.recv(48) 
    packet_8 = s.recv(48)
    packet_9 = s.recv(48)
    packet_10 = s.recv(48)
    packet_11 = s.recv(48)

    packet_12 = s.recv(8)
    packet_12 = packet_12.encode("hex") #convert the data from \x hex notation to plain hex
    x = str(packet_12)
    x = struct.unpack('!d', packet_12.decode('hex'))[0]
    print ("X = ", x * 1000)

    packet_13 = s.recv(8)
    packet_13 = packet_13.encode("hex") #convert the data from \x hex notation to plain hex
    y = str(packet_13)
    y = struct.unpack('!d', packet_13.decode('hex'))[0]
    print "Y = ", y * 1000

    packet_14 = s.recv(8)
    packet_14 = packet_14.encode("hex") #convert the data from \x hex notation to plain hex
    z = str(packet_14)
    z = struct.unpack('!d', packet_14.decode('hex'))[0]
    print "Z = ", z * 1000

    packet_15 = s.recv(8)
    packet_15 = packet_15.encode("hex") #convert the data from \x hex notation to plain hex
    Rx = str(packet_15)
    Rx = struct.unpack('!d', packet_15.decode('hex'))[0]
    print "Rx = ", Rx

    packet_16 = s.recv(8)
    packet_16 = packet_16.encode("hex") #convert the data from \x hex notation to plain hex
    Ry = str(packet_16)
    Ry = struct.unpack('!d', packet_16.decode('hex'))[0]
    print "Ry = ", Ry

    packet_17 = s.recv(8)
    packet_17 = packet_17.encode("hex") #convert the data from \x hex notation to plain hex
    Rz = str(packet_17)
    Rz = struct.unpack('!d', packet_17.decode('hex'))[0]
    print "Rz = ", Rz
    
    s.close()

    # dataDecodedA = binascii.b2a_base64(data)
    # print ("\n Received 64", dataDecodedA)
    
    # print ("\n Received hex", dataDecodedB)
    # dataDecodedC= binascii.b2a_hqx(data)
    # print ("\n Received hqx", dataDecodedC)
    
    # dataDecodedE = binascii.b2a_uu(data)
    # print ("\n Received uu", dataDecodedE)
  
    print ("Status data received from robot")