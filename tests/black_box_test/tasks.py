from threading import Thread, Event
from time import sleep
from config import Config
import os
import os.path
import socket

class Task(Thread):
    def __init__(self, dt, fn, client):
        Thread.__init__(self)
        self.dt = dt
        self.fn = fn
        self.client = client

        self.running = Event()
        self.running.set()


    def createSocket(self):
        path, name = os.path.split(self.fn)
        try:
            os.makedirs(path)
        except OSError:
            pass

        s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        try:
            os.remove(self.fn)
        except OSError:
            pass
        
        if self.client:
            s.connect(self.fn)
            self.sock = s
        else:
            s.listen(1)
            self.sock, addr = s.accept()
            self.sock.settimeout(Config.sock_timeout)

    def run(self):
        self.createSocket()
        while self.running.isSet():
            self.action()
            sleep(self.dt)

    def join(self):
        self.running.clear()
        Thread.join(self)

class NetSource(Task):
    def __init__(self, source):
        Task.__init__(self, Config.dt_receive, Config.fn_receive, False)
        self.source = source 

    def action(self):
        self.socket.send(self.source.next()) 

class SensorSource(Task):
    def __init__(self, source):
        Task.__init__(self, Config.dt_collect, Config.fn_collect, False)
        self.source = source

    def action(self):
        self.socket.send(self.source.next())

class NetSink(Task):
    def __init__(self, sink):
        Task.__init__(self, Config.dt_send, Config.fn_send, True)
        self.sink = sink

    def action(self):
        sink.next(self.socket.recv(1024))

