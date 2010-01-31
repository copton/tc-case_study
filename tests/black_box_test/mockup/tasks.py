from task import Task
from sock import Client
import codec

class MockupTask(Task):
    def __init__(self, fn_source, fn_sink, dt):
        Task.__init__(self)
        self.source = Client(fn_source)
        self.sink = Client(fn_sink)
        self.dt = dt

    def threadSetup(self):
        self.source.createSocket()
        self.sink.createSocket()

    def action(self):
        sleep(self.dt)
        vals = self.read()
        self.write(vals)

    def read(self):
        self.source.sock.write("next")
        self.source.sock.flush()
        bytes = self.source.sock.read(1024)
        return codec.decode(bytes)

    def write(self, vals):
        bytes = codec.encode(vals)
        self.sink.sock.write(bytes)
        self.sink.sock.flush()
