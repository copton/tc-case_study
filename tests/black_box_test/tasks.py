from threading import Thread, Event
from time import sleep
from config import Config
import socket

class Role:
    CLIENT=0
    SERVER=1

class Task(Thread):
    def __init__(self, dt, fn, role):
        Thread.__init__(self)
        self.dt = dt
        self.fn = fn
        self.role = role

        self.setup = Event()
        self.setup.clear()

        self.shutdown = Event()
        self.shutdown.clear()

        self.sock = None

    def __del__(self):
        if self.sock != None:
            self.sock.close()

    def createSocket(self):
        s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        if self.role == Role.CLIENT:
            print self, "accessing socket: " + self.fn
            s.connect(self.fn)
            self.sock = s
            self.setup.set()
        elif self.role == Role.SERVER:
            s.bind(self.fn)
            print self, "socket created: " + self.fn
            self.setup.set()
            s.listen(1)
            self.sock, addr = s.accept()
            self.sock.settimeout(Config.sock_timeout)
        else:
            assert False, "role must be either SERVER or CLIENT: %d" % self.role

    def run(self):
        self.createSocket()
        while not self.shutdown.isSet():
            print self, "action"
            self.action()
            sleep(self.dt)

    def start(self):
        print self, "starting..."
        Thread.start(self)
        self.setup.wait()
        print self, "started"

    def join(self):
        self.shutdown.set()
        Thread.join(self)

    def wait(self):
        self.shutdown.wait()

class NetSource(Task):
    def __init__(self, source):
        Task.__init__(self, Config.dt_receive, Config.fn_receive, Role.CLIENT)
        self.source = source 

    def action(self):
        self.sock.send(self.source.next()) 
        self.sock.flush()

class SensorSource(Task):
    def __init__(self, source):
        Task.__init__(self, Config.dt_collect, Config.fn_collect, Role.CLIENT)
        self.source = source

    def action(self):
        self.sock.send(self.source.next())
        self.sock.flush()

class NetSink(Task):
    def __init__(self, sink):
        Task.__init__(self, Config.dt_send, Config.fn_send, Role.SERVER)
        self.sink = sink

    def action(self):
        self.sink.next(self.sock.recv(1024))

