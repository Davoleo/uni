#!/usr/bin/env python

# Nome Cognome, data
# Summary :

from socket import *
import sys, time
import optparse


parser = optparse.OptionParser()
parser.add_option('-s', '--server',  dest="server",  default="localhost", help="nome del server" )
parser.add_option('-p', '--port',    dest="port",    type=int,  default=25000, help="porta di ascolto del server" )
parser.add_option('-m', '--message', dest="message", default="hello from Nome Cognome, in python", help="messaggio  da spedire" )
options, remainder = parser.parse_args()
print("OPTIONS  server:", options.server, " - port:", options.port, " - message:", options.message)

addr = (options.server,options.port)
s = socket(AF_INET,SOCK_DGRAM)

ta=time.time()

Len = s.sendto(options.message.encode('utf-8'),addr)
print("to: ",addr,"  - data: ",options.message)

data,addr = s.recvfrom(1500)
print("from:",addr,"- data:", data)

tb=time.time()
print("tempo :", tb-ta)

s.close()

