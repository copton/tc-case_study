from socks import Server
from threading import Thread, Event
from time import sleep
from debug import debugout

class Task(Thread):
    shutdown = Event()
    def __init__(self):
        Thread.__init__(self)
        self.setup = Event()
        self.daemon = True

    def run(self):
        self.threadSetup()
        self.setup.set()
        while not Task.shutdown.isSet():
            self.action()
        self.threadShutdown()

    def start(self):
        debugout(self, "starting...")
        Thread.start(self)
        debugout(self, "started")

    def sync(self):
        debugout(self, "syncing...")
        self.setup.wait()
        debugout(self, "synced")

    def join(self):
        debugout(self, "joining...")
        Thread.join(self)
        debugout(self, "joined")

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
        req = self.recv()
        if req:
            assert req == "next", req
            data = self.source.getNext()
            self.send(data)

class SinkTask(ServerTask):
    def __init__(self, fn, sink):
        ServerTask.__init__(self, fn)
        self.sink = sink

    def action(self):
        data = self.recv()
        if data:
            self.sink.setNext(data)

class PushTask(ServerTask):
    def __init__(self, fn, source, dt):
        ServerTask.__init__(self, fn)
        self.source = source
        self.dt = dt

    def action(self):
        data = self.source.getNext()
        self.send(data)
        sleep(self.dt)
        
class ControlSinkTask(ServerTask):
    def __init__(self, fn, sink, max, notify):
        ServerTask.__init__(self, fn)
        self.sink = sink
        self.max = max
        self.counter = 0
        self.notify = notify

    def action(self):
        data = self.recv()
        if data:
            self.sink.setNext(data)
            self.counter += 1
            debugout(self, "counter", self.counter)
            if self.counter == self.max:
                Task.shutdown.set()
                self.notify()
