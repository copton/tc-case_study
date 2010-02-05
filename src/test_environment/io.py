from time import time

class Source(object):
    def __init__(self, codec, gen):
        self.log = []
        self.gen = gen
        self.codec = codec

    def getNext(self):
        vals = self.gen.next()
        self.log.append((time(), vals))
        return self.codec.encode(vals)

    def getLog(self):
        return self.log

class Sink(object):
    def __init__(self, codec):
        self.log = []
        self.codec = codec

    def setNext(self, vals):
        self.log.append((time(), self.codec.decode(vals)))

    def getLog(self):
        return self.log
