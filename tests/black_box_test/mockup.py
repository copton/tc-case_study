#! /usr/bin/env python 

from config import Config
from tasks import Task
import struct
import logic

flash=open(Config.fn_flash, "w")

class Receive(Task):
    def __init__(self):
        Task.__init__(self, Config.dt_receive, Config.fn_receive)

    def action(self):
        value = self.socket.read(1024)
        flash.write(value)

class Collect(Task):
    def __init__(self):
        Task.__init__(self, Config.dt_collect, Config.fn_collect)

    def action(self):
        value = self.socket.read(1024)
        flash.write(value)

class Send(Task):
    def __init__(self):
        Task.__init__(self, Config.dt_send, Config.fn_send)

    def action(self):
        bytes = flash.read(2048)
        sizeofInt = struct.calcsize("!i")
        assert (len(bytes) % sizeofInt) == 0

        values = [struct.unpack("!i", bytes[i:i+sizeofInt]) for i in range(0, len(bytes), sizeofInt)]
        result = logic.aggregate(values)
        
        self.socket.send(result)
