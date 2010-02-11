from test_environment.tasks import Task
from test_environment.socks import Client
from test_environment.debug import debugout

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
        vals = self.read()
        new_vals = self.map(vals)
        self.write(new_vals)

    def map(self, vals):
        return vals

    def read(self):
        bytes = self.source.recv()
        return codec.decode(bytes)

    def write(self, vals):
        bytes = codec.encode(vals)
        self.sink.send(bytes)

class Collect(MockupTask):
    def __init__(self, fn_source, fn_sink, dt):
        MockupTask.__init__(self, fn_source, fn_sink)
        self.dt = dt

    def action(self):
        sleep(self.dt)
        return MockupTask.action(self)
        
    def read(self):
        self.source.send("next")
        return MockupTask.read(self)

class Receive(MockupTask):
    def __init__(self, fn_source, fn_sink):
        MockupTask.__init__(self, fn_source, fn_sink)

class Send(MockupTask):
    def __init__(self, fn_source, fn_sink, dt):
        MockupTask.__init__(self, fn_source, fn_sink)
        self.dt = dt

    def action(self):
        sleep(self.dt)
        return MockupTask.action(self)
        
    def read(self):
        self.source.send("next")
        return MockupTask.read(self)

    def map(self, vals):
        return [reduce(min, vals), reduce(max, vals)]
