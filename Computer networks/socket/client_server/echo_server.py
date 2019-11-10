#!/usr/bin/env python

# Nome Cognome, Data
# Summary: 

import sys, signal, os
#import select
import optparse
from socket import *

parser = optparse.OptionParser()
parser.add_option('-p', '--port',     dest="port",    default=25000, type=int )
parser.add_option('-s', '--server',   dest="server",  default="0.0.0.0", )
parser.add_option('-b', '--bufsize',  dest="bufsize", default=1024, type=int , help="dimensione buffer" )
options, remainder = parser.parse_args()

print"   port:", options.port, "  server:", options.server, "bufsize:",options.bufsize

s = socket(AF_INET,SOCK_DGRAM)
s.bind((options.server,options.port))

try: 
  while(1):
        data,addr = s.recvfrom(options.bufsize)
        print "from:",addr," data:", data
        Len = s.sendto(data,addr)
        print "to:",addr,"  data:", data
        print "----------------------------"
except (KeyboardInterrupt):
  print "Chiudi socket ed esci.."      
  s.close() 