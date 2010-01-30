#! /usr/bin/env python 

from config import Config
from tasks import Task, Role
import logic

from threading import Lock
import struct
import socket
import os
import sys
import signal

class Flash(object):
    def __init__(self):
        self.lock = Lock()
        try:
            os.remove(Config.fn_flash)
        except OSError:
            pass

    def append(self, data):
        self.lock.acquire()
        f = open(Config.fn_flash, "a")
        self.lock.release()

    def reset(self):
        self.lock.acquire()
        if not os.path.exists(Config.fn_flash):
            self.lock.release()
            return []
        f = open(Config.fn_flash, "r")
        contents = f.read()
        f.close()
        os.remove(Config.fn_flash)
        self.lock.release()
        return contents

class Receive(Task):
    def __init__(self, flash):
        Task.__init__(self, Config.dt_receive, Config.fn_receive, Role.SERVER)
        self.flash = flash

    def action(self):
        value = self.socket.read(1024)
        self.flash.append(value)

class Collect(Task):
    def __init__(self, flash):
        Task.__init__(self, Config.dt_collect, Config.fn_collect, Role.SERVER)
        self.flash = flash

    def action(self):
        value = self.socket.read(1024)
        self.flash.append(value)

class Send(Task):
    def __init__(self, flash):
        Task.__init__(self, Config.dt_send, Config.fn_send, Role.CLIENT)
        self.flash = flash

    def action(self):
        def getValues():
            bytes = self.flash.reset()
            sizeofInt = struct.calcsize("!i")
            assert (len(bytes) % sizeofInt) == 0

            values = [struct.unpack("!i", bytes[i:i+sizeofInt]) for i in range(0, len(bytes), sizeofInt)]
            return values

        def sendResult(values):
            if values == []:
                min = max = 0
            else:
                min = reduce(min, values)
                max = reduce(max, values)
            bytes = struct.pack("!ii", min, max) 
            try:
                self.sock.send(bytes)
            except socket.error:
                self.shutdown.set()
            else:
                self.sock.flush()

        values = getValues()
        sendResult(values)

flash = Flash()

send = Send(flash)
receive = Receive(flash)
collect = Collect(flash)

receive.start()
collect.start()
send.start()

send.wait()

print "shutting down"
collect.join()
receive.join()
send.join()

print "exit"
