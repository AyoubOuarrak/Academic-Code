#Coded by Luca Cirani
#19-12-2013

#!usr/bin/python

#Config
ServerPort = 25
ServerAddress = 'lpr1.lpr.fis.unipr.it'
#End Config


import socket #For the connection
import os #For killing proc
import dns.resolver #For MX record

			
#Estabilish Connection			
Connection=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
try:
	Connection.connect((ServerAddress,ServerPort))
except:
	print "Unable to reach server. Aborting."
	os._exit(0)

	print "Connected to server "+str(ServerAddress)

def Send(Message):
	try:
		Connection.send(Message)
	except:
		print "Unable to send message. Aborting."
	        os._exit(0)
	
def Receive():
	try:
		Reply = Connection.recv(1024)
	except:
		print "Unable to receive reply. Aborting."
		os._exit(0)
	return Reply
	
MAIL_FROM = raw_input("Senders mail:").strip()
RCPT_TO = raw_input("Recipient's mail:").strip()

server = RCPT_TO[RCPT_TO.find("@")+1:]
user = RCPT_TO[:RCPT_TO.find("@")]

for x in dns.resolver.query(server, 'MX'):
	RCPT_TO=user+"@"+x.exchange.to_text()

FROM = raw_input("From:")
TO = raw_input("To:")
SUBJ = raw_input("Subject:")
DATA = raw_input("Message:")

Receive()
Send("MAIL FROM:" + MAIL_FROM + "\n")
Receive()
Send("RCPT TO:" + RCPT_TO + "\n")
Receive()
Send("DATA\n")
Receive()
Send("From:" + FROM + "\n")
Send("To:" + TO + "\n")
Send("Subject:" + SUBJ + "\n")
Send(DATA + "\n")

#while(DATA != "."):
#	DATA=raw_input().strip()
#	Send(DATA + "\n")

Receive()
Send("QUIT\n")
Connection.close()

