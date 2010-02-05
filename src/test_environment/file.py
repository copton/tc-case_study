from time import time
from threading import Lock

class File(object):
    def __init__(self, codec):
        self.contents = []
        self.lock = Lock()
        self.codec = codec

    def write(self, bytes, log):
        vals = self.codec.decode(bytes)
        self.lock.acquire()
        log.append((time(), vals))
        self.contents += vals
        self.lock.release()

    def read(self, log):
        self.lock.acquire()
        log.append((time(), self.contents))
        bytes = self.codec.encode(self.contents)
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
