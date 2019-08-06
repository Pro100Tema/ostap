#!/usr/bin/env python
# -*- coding: utf-8 -*-
# =============================================================================
# =============================================================================
__version__ = '$Revision$'
__author__  = 'Vanya BELYAEV Ivan.Belyaev@itep.ru'
__date__    = '2016-02-23'
__all__     = (
    'Task'        , ## the base class for task
    'TaskManager' , ## task manager 
    )
# =============================================================================
#from ostap.logger.logger import getLogger
#if '__main__' == __name__ : logger = getLogger ( 'pstap.paralllel.mp_pathos' )
#else                      : logger = getLogger ( __name__                    ) 
# =============================================================================
import sys, os, time, copy
excluded_varnames =  ( 'HOSTNAME', 'SSH_CLIENT', 'SSH_CONNECTION', 'DISPLAY' ) 

# =============================================================================
# PATHOS components 
# =============================================================================
import os
import sys
import pathos.core as core
import time, copy
import pathos

#==================================================================================
#At the input of the function given the desired remote server. The function copies
#the find_ppserver.py file to the server and runs it there.On exit we get the path
#to the ppserver file.
def ppserver(serv):
    k = pathos.core.copy('find_ppserv.py', destination = serv + ':~/find_ppserv.py')
    l = pathos.core.execute('python find_ppserv.py', host = serv)
    path = str(l.response())
    return path

#==================================================================================
#The function that copies and runs on a remote server the script.py files needed
#to set environment variables, starts the ppserver and the executable file on the
#remote server.After the file is executed, the results are transferred to localhost.
#since in the example 'sum_primes.py' a lot of information is returned,
#time.sleep(25) is supplied, otherwise nothing will be displayed
def send_to_serv(files):
        copy = pathos.core.copy('script.py', destination = server + ':~/script.py')
        start = pathos.core.execute('python script.py', host = server)
        print(start.response())

        pp = pathos.core.execute('python \t' + ppserver(server) + '\t' +'ppserver.py', host = server)

        copy = pathos.core.copy(file, destination = server + ':~/' + file)
        start = pathos.core.execute('python \t' + file, host = server)
        time.sleep(25)
        print(start.response())


def send_to_serv_2(file):
    copy = pathos.core.copy('script.py', destination = server_2 + ':~/script.py')
    start = pathos.core.execute('python script.py', host = server_2)
    print(start.response())

    pp = pathos.core.execute('python \t' + ppserver(server_2) + '\t' +'ppserver.py', host = server_2)

    copy = pathos.core.copy(file_2, destination = server_2 + ':~/' + file_2)
    start = pathos.core.execute('python \t' + file_2, host = server_2)
    time.sleep(25)
    print(start.response())

def send_to_serv_3(file):
    copy = pathos.core.copy('script.py', destination = server_3 + ':~/script.py')
    start = pathos.core.execute('python script.py', host = server_3)
    print(start.response())

    pp = pathos.core.execute('python \t' + ppserver(server_3) + '\t' +'ppserver.py', host = server_3)

    copy = pathos.core.copy(file_3, destination = server_3 + ':~/' + file_3)
    start = pathos.core.execute('python \t' + file_3, host = server_3)
    time.sleep(25)
    print(start.response())

#==================================================================================
#Using mp.Process (), the Parallel () function allows you to run multiple processes
#in parallel for computing. The function "send_to_serv" is written to the variable
#"target", and the variable "args" is the name of the file containing the calculated
# code
def Parallel():
    from pathos.helpers import mp
    process = [mp.Process(target = send_to_serv, args = (file,)),
               mp.Process(target = send_to_serv_2, args = (file_2,)), 
               mp.Process(target = send_to_serv_3, args = (file_3,))]
    r1 = map(lambda p: p.start(), process)
    r2 = map(lambda p: p.join(), process)
    r3 = map(lambda p: p.join(), process)
    r1 = list(r1); r1 = list(r2); r1 = list(r3)

#==================================================================================
def check_password(servers,passwords,password):
    try:
        for i in range(len(servers)):
            if password == passwords[i]:
                print("wrong password")
                exit()
            else:
                passwords.append(password)
                print(passwords)
                break
            return passwords
    except:
        return 0
    
#==================================================================================
#class Server 
# make ssh-tunnel between localhost and LHCb-server
# input data is LHCb-server,
# at the output we can get information about ssh-tunnel and PID
class Server(object):
    def __init__(self, host, **kwargs):
        sys.stdout.flush()
        sys.stdin.flush()
        self.tunnel = core.connect(host)
        rport = self.tunnel._rport
        
        link = (host, rport)

        self.session = core.execute(link,host)

        self.host = host
        self.local_server = 'localhost:%d' % self.tunnel._lport
        self.remote_server = '%s:%d' % (host, self.tunnel._rport)
        self.pid = core.getpid(host)

        password = str(self.tunnel._lport) + str(self.pid) #create secret code
        servers = [server, server_2, server_3] 
        passwords = ['']
        for i in range(len(servers)):
            passwords = check_password(servers,passwords,password)
                        
        sys.stdout.flush()
        sys.stdin.flush()
        print('SSH tunnel from:  %s -> to: %s,' % (self.local_server,self.remote_server))
        print('pid %d' % self.pid)

def __exit__(self):
    self.pid = None
    self.session = None
    self.tunnel = None

def __del__(self):
    self.__exit__()
    del self.session
    del self.tunnel

# =============================================================================
# The input to the program is the names of 3 remote servers, for example,
# 'lxplus701' 'lxplus741' 'lxplus779', and the names of the three files that need to
# be executed. I used 'nested.py', 'sum_primesX.py', which are standard pathos examples
# and file 'equation.py', which calculates the roots of a quadratic equation.
if '__main__' == __name__ :
   # server = input()
    server,server_2,server_3 = map(str,sys.stdin.readline().split())
   # file = input()
    file,file_2,file_3 = map(str,sys.stdin.readline().split())

    serv = Server(server)
    serv_2 = Server(server_2)
    serv_3 = Server(server_3)
    Parallel()
# =============================================================================
# The END 
# =============================================================================
