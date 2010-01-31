import codec

import random
from time import time
from threading import Lock

class Source(object):
    def __init__(self, gen):
        self.log = []
        self.gen = gen

    def getNext(self):
        vals = self.gen.next()
        self.log.append((time(), vals))
        return codec.encode(vals)

    def getLog(self):
        return self.log

def randomGen():
    while True:
        yield [random.randint(-30, 70)]

class Sink(object):
    def __init__(self):
        self.log = []

    def setNext(self, vals):
        self.log.append((time(), codec.decode(vals)))

    def getLog(self):
        return self.log

class File(object):
    def __init__(self):
        self.readLog = {}
        self.writeLog = {}
        self.contents = []
        self.lock = Lock()

    def register(self, id):
        self.readLog[id] = []
        self.writeLog[id] = []

    def _log(self, id, vals):
        log = self.log.get(id, [])
        log.append((time(), id, vals))
        self.log[id] = log

    def write(self, id, bytes):
        vals = codec.decode(bytes)
        self.lock.acquire()
        self.writeLog[id].append((time(), vals))
        self.contents.append(vals)
        self.lock.release()

    def read(self, id):
        self.lock.acquire()
        vals = codec.decode(self.contents)
        self.readLog[id].append((time(), vals))
        self.contents = []
        self.lock.release()
        return vals

class FileHandle(object):
    def __init__(self, file, id):
        self.file = file
        self.id = id
        self.file.register(id)

    def setNext(self, vals):
        self.file.write(self.id, vals)

    def getNext(self):
        return self.file.read(self.id)
