
# Andrea Chiastra, Silvia Balzani, Andia Cecja
# 20 Dicembre 2014

from threading import Thread
import sys, signal, os
import select
import optparse
from socket import *

listaConn = []

parser = optparse.OptionParser()
parser.add_option('-p', '--port', dest = "port", default = 25011,  type = int)
parser.add_option('-b', '--bufsize',  dest = "bufsize", default = 1024,  type = int , help="dimensione buffer")
options, remainder = parser.parse_args()

def comunicationHandler(connection, addr):
	mex = 'a'
	while(True):
		try:
			mex = connection.recv(options.bufsize)
		except:
			break
		if(mex == '' or mex == 'quit'):
			break
		print "Address ", addr, " sent the following message: ", mex
		print "Sending such message back"
		connection.send(mex)
	print "Comunication with ", addr, " has ended"
	connection.close()

def connectionCloser(lista):
	for co in lista:
		try:
			co.close()
		except:
			pass

def sigIntHandler(signum, frame):
	print "Closing connections..."
	thr = Thread(target = connectionCloser, args = (listaConn, ))
	sys.exit()

sockConn = socket(AF_INET, SOCK_STREAM)
sockConn.bind(('0.0.0.0', options.port))
sockConn.listen(1)

signal.signal(signal.SIGINT, sigIntHandler)

while(True):
	print "Waiting for connections"
	connection, addr = sockConn.accept()
	listaConn = listaConn + [connection]
	thr = Thread(target = comunicationHandler, args = (connection, addr, ))
	thr.setDaemon(True)
	thr.start()
	print "Started comunication with ", addr
