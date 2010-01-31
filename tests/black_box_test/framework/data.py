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
        self.contents = []
        self.lock = Lock()

    def write(self, bytes, log):
        vals = codec.decode(bytes)
        self.lock.acquire()
        log.append((time(), vals))
        self.contents += vals
        self.lock.release()

    def read(self, log):
        self.lock.acquire()
        log.append((time(), self.contents))
        bytes = codec.encode(self.contents)
        self.contents = []
        self.lock.release()
        return bytes

class FileSource(object):
    def __init__(self, file):
        self.log = []
        self.file = file

    def getNext(self):
        return self.file.read(self.log) 

    def getLog(self):
        return self.log

class FileSink(object):
    def __init__(self, file):
        self.log = []
        self.file = file

    def setNext(self, bytes):
        self.file.write(bytes, self.log)

    def getLog(self):
        return self.log
