#!/usr/bin/env python

from socket import *
import sys
import optparse

parser = optparse.OptionParser()
parser.add_option('-i', '--inputfile', dest="filein", default="/etc/issue", help="nome del file di input" )
parser.add_option('-o', '--outputfile', dest="fileout", default="./temp", help="nome del file di output" )
parser.add_option('-t', '--timeout',  dest="timeout", default=2, help="tempo di timeout (sec)" )
parser.add_option('-s', '--server',   dest="server", default="localhost",help="nome del serv" )
parser.add_option('-p', '--port',     dest="port", default=9999,help="porta di ascolto del server" )
parser.add_option('-b', '--bufsize',   dest="bufsize", type=int, default=100,help="dimensione buffer di spedizione" )
options, remainder = parser.parse_args()

print "filein:", options.filein, " - server:", options.server, " - port:", options.port, " - buffer:", options.bufsize

addr = (options.server,options.port)
s = socket(AF_INET,SOCK_DGRAM)

fin=open(options.filein,"rb") 
s.sendto(options.fileout,addr)

while True:
        data = fin.read(options.bufsize)
        s.sendto(data,addr)
        print "sending ", len(data), " to:", addr
        if (data == ""):
            break

s.close()
fin.close()
