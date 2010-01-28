from threading import Lock, Event
from config import Config

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


def aggregate(lst):
    sum = reduce(lambda x, y: x + y, lst)
    return 1.0 * sum / len(lst)

class Logic(object):
    def __init__(self, netSource, sensorSource):
        self.netSource = netSource
        self.sensorSource = sensorSource
        self.shutdown = Event()
        self.shutdown.clear()

        self.count = 0

    def next(self, bytes):
        assert self.count < Config.logic_maxCount, "control flow bug"

        netSourceValues = self.netSource.getValues()
        sensorSourceValues = self.sensorSource.getValues()

        isResult = struct.unpack("!d", bytes)
        shouldResult = aggregate(netSourceValues + sensorSourceValues)

        assert isResult == shouldResult, "results do not match: %f, %f" % (isResult, shouldResult) 
  
        self.count += 1
        if self.count == Config.logic_maxCount:
            self.shutdown.set()

    def wait(self):
        self.shutdown.wait()
