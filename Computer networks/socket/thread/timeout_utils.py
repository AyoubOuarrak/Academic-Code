# Nome Cognome - Data - versione

import signal, os, sys
import time         #sleep
import optparse

parser = optparse.OptionParser()
parser.add_option('-t', '--timeout', dest="timeout", default=2, )
parser.add_option('-s', '--sleeptime', dest="sleeptime", default=0.5, )
parser.add_option('-v', '--verbose',dest="verbose", default=False, action="store_true", )
parser.add_option('--version', dest="version", default=1.0, type="float", )
options, remainder = parser.parse_args()

N=0

def handler_alrm(signum, frame):
    print('Signal handler called with signal', signum)
    signal.alarm(options.timeout)
    global N
#    N=0

def handler_int(signum, frame):
    print('Signal handler called with signal', signum)
    sys.exit(0)

# Set the signal handler and a 5-second alarm
signal.signal(signal.SIGALRM, handler_alrm)
signal.signal(signal.SIGINT, handler_int)

signal.alarm(options.timeout)


ta=time.time()

while N<10:
        print N
        N=N+1
        time.sleep(options.sleeptime)

tb=time.time()

print "tempo :", tb-ta
