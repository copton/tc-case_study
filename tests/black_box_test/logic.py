from threading import Lock, Event
from config import Config
import struct

class GeneratorProxy(object):
    def __init__(self, generator):
        self.generator = generator
        self.values = []
        self.lock = Lock()

    def next(self):
        value = self.generator.next()
        self.lock.acquire()
        self.values.append(value)
        self.lock.release()
        bytes = struct.pack("!i", value)
        return bytes

    def getValues(self):
        self.lock.acquire()
        values = self.values
        self.values = []
        self.lock.release()
        return values

class Logic(object):
    def __init__(self, netSource, sensorSource):
        self.netSource = netSource
        self.sensorSource = sensorSource
        self.shutdown = Event()
        self.shutdown.clear()

        self.count = 0

    def next(self, bytes):
        assert self.count < Config.logic_maxCount, "control flow bug"

        values = self.netSource.getValues() + self.sensorSource.getValues()

        isResult = struct.unpack("!ii", bytes)
        shouldResult = (reduce(min, values), reduce(max, values))

        assert isResult == shouldResult, "result does not match: %s, %s" % (isResult, shouldResult) 
  
        self.count += 1
        if self.count == Config.logic_maxCount:
            self.shutdown.set()

    def wait(self):
        self.shutdown.wait()
