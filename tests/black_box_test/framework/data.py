import random
import time
from threading import Lock
from cStringIO import StringIO

class Source(object):
    def __init__(self, gen):
        self.log = []
        self.gen = gen

    def getNext(self):
        val = self.gen()
        self.log.append((time.time(), val))
        return val

    def getLog(self):
        return self.log

def randomGen():
    yield random.randint(-30, 70)

class NetSource(Source):
    def __init__(self):
        Source.__init__(self, randomGen())

class SensorSource(Source):
    def __init__(self):
        Source.__init__(self, randomGen())

class Sink(object):
    def __init__(self):
        self.log = []

    def setNext(self, val):
        self.log.append((time.time(), val))

    def getLog(self):
        return self.log

class NetSink(Sink):
    pass

class File(object):
    def __init__(self):
        self.log = {}
        self.contents = StringIO()
        self.lock = Lock()

    def _log(self, id, val):
        log = self.log.get(id, [])
        log.append((time.time(), id, val))
        self.log[id] = log

    def write(self, id, val):
        self.lock.acquire()
        self._log(id, val)
        self.contents.write(val)
        self.lock.release()

    def read(self, id, val):
        self.lock.acquire()
        self._log(id, val)
        self.contents.seek(0)
        contents = self.contents.read()
        self.contents.close()
        self.contents = StringIO()
        self.lock.release()
        return contents

class FileHandle(object):
    def __init__(self, file, id):
        self.file = file
        self.id = id

    def setNext(self, val):
        self.file.write(self.id, val)

    def getNext(self, val):
        return self.file.read(self.id, val)
