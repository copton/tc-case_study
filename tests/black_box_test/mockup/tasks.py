from task import Task
from socks import Client
import codec
from time import sleep
import socket

class MockupTask(Task):
    def __init__(self, fn_source, fn_sink, dt):
        Task.__init__(self)
        self.source = Client(fn_source)
        self.sink = Client(fn_sink)
        self.dt = dt

    def threadSetup(self):
        self.source.createSocket()
        self.sink.createSocket()

    def threadShutdown(self):
        self.source.closeSocket()
        self.sink.closeSocket()

    def action(self):
        try:
            sleep(self.dt)
            vals = self.read()
            new_vals = self.map(vals)
            self.write(new_vals)
        except socket.error:
            Task.shutdown.set()

    def map(self, vals):
        return vals

    def read(self):
        self.source.sock.sendall("next")
        bytes = self.source.sock.recv(1024)
        return codec.decode(bytes)

    def write(self, vals):
        bytes = codec.encode(vals)
        self.sink.sock.sendall(bytes)

class Aggregator(MockupTask):
    def __init__(self, fn_source, fn_sink, dt):
        MockupTask.__init__(self, fn_source, fn_sink, dt)
        
    def map(self, vals):
        return [reduce(min, vals), reduce(max, vals)]
