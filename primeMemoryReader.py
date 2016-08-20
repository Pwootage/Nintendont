# /bin/env python2

import struct
import socket

host = '192.168.1.210'
port = 43673

mapIP = "127.0.0.1"
mapPort = 43673

structfmt = ">BIH"  # type and code
structfmt += "3f"  # speed
structfmt += "3f"  # pos
structfmt += "If"  # room, health
structfmt += str(0x29 * 2) + "I"  # inventory
structfmt += "Q"  # timer

struct = struct.Struct(structfmt)

print structfmt
print str(struct.size)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((host, port))

mapSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # UDP

buff = ""
print "Connected"
while True:
    read = sock.recv(1024)
    if not read:
        break
    buff += read
    if len(buff) >= struct.size:
        packet = buff[:struct.size]
        buff = buff[struct.size:]
        mapSock.sendto(packet, (mapIP, mapPort))
        unpacked = struct.unpack(packet)
        # print unpacked
