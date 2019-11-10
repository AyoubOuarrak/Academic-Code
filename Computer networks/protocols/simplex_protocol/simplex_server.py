#!/usr/bin/env python

# Author : Ayoub Ouarrak  
# Date : 3/12/2014  
# Version : 1.0

# Il receiver riceve una prima riga con il nome del file da scrivere
# poi riceve i dati che scrive sul file

from socket import *
import sys
import select
import optparse

parser = optparse.OptionParser()
parser.add_option('-t', '--timeout', dest="timeout", default=1024, )
parser.add_option('-p', '--port',    dest="port",    default=25028, )
parser.add_option('-b', '--bufsize', dest="bufsize", default=100, help = "dimensione buffer di spedizione" )

options, remainder = parser.parse_args()

print  "Port: ", options.port

host="0.0.0.0"
s = socket(AF_INET, SOCK_DGRAM)
s.bind((host,options.port))

addr = (host,options.port)

data, addr = s.recvfrom(options.bufsize)
filename = data.strip('\0')
print "file: ",filename

fout = open(filename,'wb')

i = 1
data, addr = s.recvfrom(options.bufsize)

print "data:", data
try:
    while(data):
        print "receiving ", i, "numbytes: ", len(data), " from: ", addr
        i=i+1
        fout.write(data)
        s.settimeout(options.timeout)
        data, addr = s.recvfrom(options.bufsize)
except timeout:
    fout.close()
    s.close()
   
 
print "File ", filename,"  received"
