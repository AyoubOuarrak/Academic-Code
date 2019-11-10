#!/usr/bin/env python

# Nome Cognome
# data 
# summary

from socket import *
import sys, time
import optparse


parser = optparse.OptionParser()
parser.add_option('-s', '--server',   dest="server",  default="localhost", help="nome del server" )
parser.add_option('-p', '--port',     dest="port",    default=25028, type=int, help="porta di ascolto del server" )
parser.add_option('-b', '--bufsize',  dest="bufsize", default=100,  type=int, help="dimensione buffer di spedizione" )
options, remainder = parser.parse_args()
print "OPTIONS  server:", options.server, " - port:", options.port, " - bufsize:", options.bufsize

addr = (options.server,options.port)
s = socket(AF_INET,SOCK_DGRAM)

ta = time.time()

Len = s.sendto("hello from Nome Cognome, in python",addr)
print "sent ",Len," Bytes \n"

tb=time.time()
print "tempo :", tb-ta

s.close()
