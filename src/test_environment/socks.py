import socket
import os
import os.path

class Socket(object):
    def __init__(self, fn):
        self.sock = None
        self.fn = fn

    def closeSocket(self):
        self.sock.close()

class Server(Socket):
    def __init__(self, fn):
        Socket.__init__(self, fn)
        self.lsock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        self.lsock.bind(self.fn)
        self.lsock.listen(1)
        print self, "socket created: " + self.fn
        
    def createSocket(self):
        self.sock, addr = self.lsock.accept()

class Client(Socket):
    def __init__(self, fn):
        Socket.__init__(self, fn)

    def createSocket(self):
        s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        print self, "accessing socket: " + self.fn
        s.connect(self.fn)
        self.sock = s
