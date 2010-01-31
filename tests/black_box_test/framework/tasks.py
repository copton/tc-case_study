from task imprt Task
from socks import Server

class FrameworkTask(Task, Server):
    def __init__(self, fn):
        Task.__init__(self)
        Server.__init__(self, fn)

    def threadSetup(self):
        self.createSocket()

class Source(FrameworkTask):
    def __init__(self, fn, source):
        FrameworkTask.__init__(self, fn)
        self.source = source

    def action(self):
        req = self.sock.recv(1024)
        assert req == "next"
        data = self.source.getNext()
        self.sock.send(data)
        self.sock.flush()

class Sink(FrameworkTask):
    def __init__(self, fn, sink):
        FrameworkTask.__init__(self, fn)
        self.sink = sink

    def action(self):
        data = self.sock.recv(1024)
        self.sink.setNext(data)
        
class ControlSink(Sink):
    def __init__(self, fn, sink, max):
        Sink.__init__(self, fn, sink)
        self.max = max
        self.counter = 0

    def action(self):
        Sink.action(self)
        self.counter += 1
        if self.counter == self.max:
            Task.shutdown.set()
