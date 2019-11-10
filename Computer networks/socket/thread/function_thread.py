#!/usr/bin/env python

# function_thread.py
#
# Ayoub Ouarrak
# 17-11-2014
# Il programma e' suddiviso in diverse unita' funzionali gestite da diversi thread.
# In questo esempio abbiamo un processo  interattivo e 2  unita' f1, f2.

from threading import Thread
from time import sleep
import sys;

def thread_f1(arg):
    print "Thread f1 started. Sleep for  " + str(arg) + " seconds"
    sleep(arg)
    print "Thread f1 finished"

def thread_f2(arg):
    print "Thread f2 started. Sleep for  " + str(arg) + " seconds"
    sleep(arg)  
    print "Thread f2 finished"                

def interactive():
  print "Interacive started (Press q to exit)"
  while True:
    cmd = raw_input(">> ")
    if cmd.strip() == '':
        continue
    if cmd.strip() == 'Q' or cmd.strip() == 'q':
        break
    print "command: " + cmd 


if __name__ == "__main__":
    t1 = 20
    t2 = 12

    if len(sys.argv) == 2:
        t1 = int(sys.argv[1])

    if len(sys.argv) == 3:
        t1 = int(sys.argv[1])
        t2 = int(sys.argv[2])

    if len(sys.argv) > 3:
        print "Usage: "
        print "python function_thread.py [t1 t2]"
        print "defaults value of t1 = 20, t2 = 12"
        SystemExit("too many arguments")

    thread1 = Thread(target = thread_f1, args = (t1, ))
    thread2 = Thread(target = thread_f2, args = (t2, ))

    thread1.start()
    thread2.start()

interactive()

# wait until the others thread has completed its work
thread1.join()
thread2.join()
print "Functional multithread finished, exiting...."

