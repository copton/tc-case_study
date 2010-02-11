import socket
import os
import os.path
from debug import debugout

class Socket(object):
    def __init__(self, fn):
        self.sock = None
        self.fn = fn

    def closeSocket(self):
        self.sock.close()

    def send(self, data):
        self.sock.sendall(data)

class Server(Socket):
    def __init__(self, fn):
        Socket.__init__(self, fn)
        self.lsock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        self.lsock.bind(self.fn)
        self.lsock.listen(1)
        debugout(self, "socket created", self.fn)
        
    def createSocket(self):
        self.sock, addr = self.lsock.accept()
        self.sock.settimeout(0.5)

    def recv(self):
        try:
            return self.sock.recv(250)
        except socket.timeout:
            return None
        except socket.error, e:
            if e.errno == 104: #Connection reset by peer
                return None
            else:
                raise

class Client(Socket):
    def __init__(self, fn):
        Socket.__init__(self, fn)

    def createSocket(self):
        s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        debugout(self, "accessing socket", self.fn)
        s.connect(self.fn)
        self.sock = s

    def recv(self):
        return self.sock.recv(250)
