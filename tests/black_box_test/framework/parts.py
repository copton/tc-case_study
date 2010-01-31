import subprocess 
from config import Config
import data
import tasks

def application(command):
    config_values = [Config.dt_collect, Config.dt_receive, Config.dt_send, Config.fn_receive, Config.fn_send, Config.fn_collect, Config.fn_flash_receive, Config.fn_flash_collect, Config.fn_flash_send]
    config_options = map(lambda o: "-%d" % o, range(len(config_values)))
    assert len(config_values) == len(config_options)
    params = [str(t[i]) for t in zip(config_options, config_values) for i in range(2)]
    command_line = [command] + params
    print "starting application"
    proc = subprocess.Popen(command_line)
    return proc

def getTasks():
    file = data.File()
    return {
        "netSource" : tasks.Source(Config.fn_receive, data.Source(data.randomGen())),
        "sensorSource" : tasks.Source(Config.fn_collect, data.Source(data.randomGen())),
        "netSink" : tasks.ControlSink(Config.fn_send, data.Sink(), Config.testCount),
        "flashReceiveSink" : tasks.Sink(Config.fn_flash_receive, data.FileSink(file)),
        "flashCollectSink" : tasks.Sink(Config.fn_flash_collect, data.FileSink(file)),
        "flashSendSource" : tasks.Source(Config.fn_flash_send, data.FileSource(file)),
    }
