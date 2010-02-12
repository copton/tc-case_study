from test_environment.tasks import Task
from test_environment.socks import Client
from test_environment.debug import debugout

import test_cases.collect_and_forward.codec as codec

from time import sleep

class MockupTask(Task):
    def __init__(self, *fns):
        Task.__init__(self)
        self.clients = [Client(fn) for fn in fns]

    def threadSetup(self):
        for client in self.clients:
            client.createSocket()

    def threadShutdown(self):
        for client in self.clients:
            client.closeSocket()

class Collect(MockupTask):
    def __init__(self, fn_source, fn_sink, dt):
        MockupTask.__init__(self, fn_source, fn_sink)
        self.dt = dt

    def action(self):
        sleep(self.dt)
        self.clients[0].send("next")
        bytes = self.clients[0].recv()
        self.clients[1].send(bytes)
        
class Receive(MockupTask):
    def __init__(self, fn_source, fn_sink):
        MockupTask.__init__(self, fn_source, fn_sink)

    def action(self):
        bytes = self.clients[0].recv()
        self.clients[1].send(bytes) 

class Send(MockupTask):
    def __init__(self, fn_source1, fn_source2, fn_sink, dt):
        MockupTask.__init__(self, fn_source1, fn_source2, fn_sink)
        self.dt = dt

    def action(self):
        sleep(self.dt)
        vals = []
        for source in self.clients[:2]:
            source.send("next")
            vals += codec.decode(source.recv())
        
        new_vals = [reduce(min, vals), reduce(max, vals)]
        new_bytes = codec.encode(new_vals)
        self.clients[2].send(new_bytes)
