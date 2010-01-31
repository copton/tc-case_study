import subprocess 
from config import Config
import data
import tasks

def application(command):
    config_values = [Config.dt_collect, Config.dt_receive, Config.dt_send, Config.fn_receive, Config.fn_send, Config.fn_collect, Config.fn_flash]
    config_options = map(lambda o: "-"+o, "crsioef")
    assert len(config_values) == len(config_options)
    params = [str(t[i]) for t in zip(config_options, config_values) for i in range(2)]
    command_line = [command] + params
    print "starting application"
    proc = subprocess.Popen(command_line)
    return proc

def netSource():
    return test_tasks.Source(Config.fn_receive, data.NetSource())

def sensorSource():
    return test_tasks.Source(Config.fn_collect, data.SensorSource())

def netSink():
    return test_tasks.ConrolSink(Confi.fn_send, data.NetSink(), Config.testCount)


def getTasks():
    return {

    }
