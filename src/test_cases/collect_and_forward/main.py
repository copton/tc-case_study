import test_environment
from test_environment.tasks import SourceTask, SinkTask, PushTask, ControlSinkTask
from test_environment.io import Source, Sink
from test_environment.file import File, FileSink, FileSource
import codec

from config import Config
from logs import Logs

import os
import os.path
import random
import sys
         
def getLogfileName():
    return Config.logfileName

def getApplicationCommand():
    try:
        return os.path.join(os.environ["ROOT"], "src", Config.applicationCommands[Args.application])
    except KeyError, e:
        sys.stderr.write("Application %s not found. Valid values for option -a are: " % e.args[0])
        sys.stderr.write(", ".join(Config.applicationCommands.keys()))
        sys.stderr.write("\n")
        sys.exit(1)

def getApplicationParameter():
    return {}

def getTmpDir():
    return Config.path

def _random():
    while True:
        yield [random.randint(-30, 70)]

def _random_tuple():
    while True:
        min = random.randint(-30, 70)
        max = random.randint(min, 70)
        yield [min, max]

def getTasks(notify):
    file_receive = File(codec)
    file_collect = File(codec)
    return {
        "netSource" : PushTask(Config.fn_receive, Source(codec, _random_tuple()), Config.dt_receive),
        "sensorSource" : SourceTask(Config.fn_collect, Source(codec, _random())),
        "netSink" : ControlSinkTask(Config.fn_send, Sink(codec), Config.testCount, notify),
        "flashReceiveSink" : SinkTask(Config.fn_flash_receive_sink, FileSink(file_receive)),
        "flashCollectSink" : SinkTask(Config.fn_flash_collect_sink, FileSink(file_collect)),
        "flashReceiveSource" : SourceTask(Config.fn_flash_receive_source, FileSource(file_receive)),
        "flashCollectSource" : SourceTask(Config.fn_flash_collect_source, FileSource(file_collect)),
    }
    
def createLog(t0, tasks):
    return Logs(t0, tasks) 

from verify import verify
from args import Args, setArgs

