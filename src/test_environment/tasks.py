from socks import Server
from threading import Thread, Event
from time import sleep
from traceback import print_exc

class Task(Thread):
    shutdown = Event()
    def __init__(self):
        Thread.__init__(self)
        self.setup = Event()
        self.daemon = True

    def run(self):
        self.threadSetup()
        self.setup.set()
        try:
            while not Task.shutdown.isSet():
                self.action()
        except:
            print_exc()
            print self, "caught exception. Shutting down"
            Task.shutdown.set()
        self.threadShutdown()

    def start(self):
        print self, "starting..."
        Thread.start(self)
        print self, "started"

    def sync(self):
        print self, "syncing..."
        self.setup.wait()
        print self, "synced"

    def join(self):
        print self, "joining..."
        Thread.join(self)
        print self, "joined"

class ServerTask(Task, Server):
    def __init__(self, fn):
        Task.__init__(self)
        Server.__init__(self, fn)

    def threadSetup(self):
        self.createSocket()

    def threadShutdown(self):
        self.closeSocket()

class SourceTask(ServerTask):
    def __init__(self, fn, source):
        ServerTask.__init__(self, fn)
        self.source = source

    def action(self):
        req = self.sock.recv(1024)
        assert req == "next", req
        data = self.source.getNext()
        self.sock.sendall(data)

class SinkTask(ServerTask):
    def __init__(self, fn, sink):
        ServerTask.__init__(self, fn)
        self.sink = sink

    def action(self):
        data = self.sock.recv(1024)
        self.sink.setNext(data)

class PushTask(ServerTask):
    def __init__(self, fn, source, dt):
        ServerTask.__init__(self, fn)
        self.source = source
        self.dt = dt

    def action(self):
        sleep(self.dt)
        data = self.source.getNext()
        self.sock.sendall(data) 
        
class ControlSinkTask(SinkTask):
    def __init__(self, fn, sink, max):
        SinkTask.__init__(self, fn, sink)
        self.max = max
        self.counter = 0

    def action(self):
        SinkTask.action(self)
        self.counter += 1
        print self, "counter =", self.counter
        if self.counter == self.max:
            Task.shutdown.set()
