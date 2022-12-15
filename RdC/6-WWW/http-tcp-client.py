#!/usr/bin/python3

# Leonardo Davoli, 14/12/2022
# Summary : Example HTTP connection using TCP Sockets

from socket import *
import sys, time
import optparse

parser = optparse.OptionParser()
parser.add_option('-s', '--server',  dest="server",  default="localhost", help="server hostname")
parser.add_option('-p', '--port',    dest="port",    type=int,  default=80, help="server listening port")
options, remainder = parser.parse_args()

print("OPTIONS  server:", options.server, " - port:", options.port)

address = (options.server, options.port)
socket = socket(AF_INET, SOCK_STREAM)

socket.connect(address)
print("Connected to server:", address)

request = "GET /index.html HTTP/1.1\r\nHost:vps.davoleo.net\r\nConnection: Keep-Alive\r\n\r\n"
print("Request Line:", request)
socket.send(request.encode())
response = socket.recv(4096).decode()
print("Response", response)
print("-----")

request = "GET /cgi-bin/test.cgi HTTP/1.1\r\nHost:vps.davoleo.net\r\n\r\n"
print("Request Line:", request)
socket.send(request.encode())
response = socket.recv(4096).decode()
print("Response", response)
print("-----")
        
socket.close()

