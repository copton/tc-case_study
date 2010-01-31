from config import Config
import time

class Logic(object):
    def __init__(self, netSource, sensorSource, netSink):
        self.t0 = time.time()
        self.netSource = netSource
        self.sensorSource = sensorSource
        self.netSink = netSink

    def test(self):
        return True
