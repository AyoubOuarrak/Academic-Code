#!/usr/bin/python

import socket
import sys

def isInt(str):
	try:
		int(str)
		return True
	except ValueError:
		return False


def dnsLookup(hostname):
	print "------- Hostname info -------"
	print ""

	if isInt(sys.argv[1][0]) == True:
		print "Name : " + socket.gethostbyaddr(hostname)[0]
		for als in socket.gethostbyaddr(hostname)[1]:
			print "Alias : " + als

		print "Address type : " + str(socket.getaddrinfo(hostname, 80)[0][1])
		for ips in socket.gethostbyaddr(hostname)[2]:
			print "Address : " + ips

	else:
		print "Name : " + socket.gethostbyname_ex(hostname)[0]
		for als in socket.gethostbyname_ex(hostname)[1]:
			print "Alias : " + als

		print "Address type : " + str(socket.getaddrinfo(hostname, 80)[0][1])
		for ips in socket.gethostbyname_ex(hostname)[2]:
			print "Address : " + ips

if len(sys.argv) == 1:
	dnsLookup("localhost")

if len(sys.argv) == 2:
	try:
		dnsLookup(sys.argv[1])
	except:
		print "unknow hostname"
		SystemExit("unknow argument")

if len(sys.argv) > 2:
	print "Usage : "
	print "python DNSLookup [hostname/IP]"
	SystemExit("1 argument requested, 2 given")

