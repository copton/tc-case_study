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
        
    def createSocket(self):
        s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        s.bind(self.fn)
        print self, "socket created: " + self.fn
        s.listen(1)
        self.sock, addr = s.accept()
        self.setup.set()

class Client(Socket):
    def __init__(self, fn):
        Socket.__init__(self, fn)

    def createSocket(self):
        s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        print self, "accessing socket: " + self.fn
        s.connect(self.fn)
        self.sock = s
