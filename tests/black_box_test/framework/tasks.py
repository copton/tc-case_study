from task imprt Task
from socks import Server, Client

class TestTask(Task, Server):
    def __init__(self, fn):
        Task.__init__(self)
        Server.__init__(self, fn)

    def threadSetup(self):
        self.createSocket()

class Source(TestTask):
    def __init__(self, fn, source):
        TestTask.__init__(self, fn)
        self.source = source

    def action(self):
        req = self.sock.recv(1024)
        assert req == "next"
        self.sock.send(self.source.next())
        self.sock.flush()

class Sink(TestTask):
    def __init__(self, fn, sink):
        TestTask.__init__(self, fn)
        self.sink = sink
        self.max = max

    def action(self):
        self.sink.next(self.sock.recv(1024))
        
class ControlSink(Sink):
    def __init__(self, fn, sink, max):
        Sink.__init__(self, fn, sink)
        self.max = max
        self.counter = 0

    def action(self):
        Sink.action(self)
        self.counter += 1
        if self.counter == self.max:
            self.shutdown.set()
