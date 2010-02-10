from test_environment.tasks import Task
from test_environment.socks import Client

import test_cases.collect_and_forward.codec as codec

from time import sleep

class MockupTask(Task):
    def __init__(self, fn_source, fn_sink):
        Task.__init__(self)
        self.source = Client(fn_source)
        self.sink = Client(fn_sink)

    def threadSetup(self):
        self.source.createSocket()
        self.sink.createSocket()

    def threadShutdown(self):
        self.source.closeSocket()
        self.sink.closeSocket()

    def action(self):
        self.preAction()
        vals = self.read()
        new_vals = self.map(vals)
        self.write(new_vals)

    def map(self, vals):
        return vals

    def read(self):
        self.preRead()
        bytes = self.source.sock.recv(1024)
        return codec.decode(bytes)

    def write(self, vals):
        bytes = codec.encode(vals)
        self.sink.sock.sendall(bytes)

class FrequentTask(MockupTask):
    def __init__(self, fn_source, fn_sink, dt):
        MockupTask.__init__(self, fn_source, fn_sink)
        self.dt = dt

    def preAction(self):
        sleep(self.dt)
        
    def preRead(self):
        self.source.sock.sendall("next")

class OnDemandTask(MockupTask):
    def __init__(self, fn_source, fn_sink):
        MockupTask.__init__(self, fn_source, fn_sink)

    def preAction(self):
        pass

    def preRead(self):
        pass

class Aggregator(FrequentTask):
    def __init__(self, fn_source, fn_sink, dt):
        FrequentTask.__init__(self, fn_source, fn_sink, dt)
        
    def map(self, vals):
        return [reduce(min, vals), reduce(max, vals)]
