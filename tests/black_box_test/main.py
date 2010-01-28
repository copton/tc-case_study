#!/usr/bin/env python

import data
import logic
import tasks
from config import Config
import sys
import subprocess

if len(sys.argv) != 2:
    sys.stderr.write("usage: %s executable" % sys.argv[0])
    sys.exit(1)

netSourceData = logic.GeneratorProxy(data.netSource())
sensorSourceData = logic.GeneratorProxy(data.sensorSource())
logic = logic.Logic(netSourceData, sensorSourceData)

netSink = tasks.NetSink(logic)
netSink.start()

config_values = [Config.dt_collect, Config.dt_receive, Config.dt_send, Config.fn_receive, Config.fn_send, Config.fn_collect, Config.fn_flash]
config_options = map(lambda o: "-"+o, "crsioef")
assert len(config_values) == len(config_options)
params = [str(t[i]) for t in zip(config_options, config_values) for i in range(2)]

proc = subprocess.Popen([sys.argv[1]] + params)

netSource = tasks.NetSource(netSourceData)
netSource.start()
sensorSource = tasks.SensorSource(sensorSourceData)
sensorSource.start()

logic.wait()

netSource.join()
sensorSource.join()
netSink.join()
proc.wait()
