#!/usr/bin/env python

import data
import logic
import tasks
from config import Config
import sys
import subprocess
import threading
import signal
import os
import os.path

if len(sys.argv) != 2:
    sys.stderr.write("usage: %s executable" % sys.argv[0])
    sys.exit(1)


def prepare():
    def clean(fn):
        path, name = os.path.split(fn)
        try:
            os.makedirs(path)
        except OSError:
            pass
        try:
            os.remove(fn)
        except OSError:
            pass

    clean(Config.fn_receive)
    clean(Config.fn_send)
    clean(Config.fn_collect)

def sigHandler(signum, frame):
    print "signal handler"

def startApplication():
    signaled = threading.Event()
    signaled.clear() 
    signal.signal(signal.SIGUSR1, sigHandler)
        
    def getCommand():
        config_values = [Config.dt_collect, Config.dt_receive, Config.dt_send, Config.fn_receive, Config.fn_send, Config.fn_collect, Config.fn_flash]
        config_options = map(lambda o: "-"+o, "crsioef")
        assert len(config_values) == len(config_options)
        params = [str(t[i]) for t in zip(config_options, config_values) for i in range(2)]
        return [sys.argv[1]] + params

    command = getCommand()
    proc = subprocess.Popen(command)
    print "waiting for application"
    signaled.wait()
    print "signal received"
    return proc

prepare()

netSourceData = logic.GeneratorProxy(data.netSource())
sensorSourceData = logic.GeneratorProxy(data.sensorSource())
logic = logic.Logic(netSourceData, sensorSourceData)

netSink = tasks.NetSink(logic)
netSink.start()

proc = startApplication()

netSource = tasks.NetSource(netSourceData)
netSource.start()

sensorSource = tasks.SensorSource(sensorSourceData)
sensorSource.start()

logic.wait()

netSource.join()
sensorSource.join()
netSink.join()
proc.wait()
