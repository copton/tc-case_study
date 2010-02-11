import test_environment
from test_environment.tasks import SourceTask, SinkTask, PushTask, ControlSinkTask
from test_environment.io import Source, Sink
from test_environment.file import File, FileSink, FileSource
import codec

from config import Config
from logs import Logs

from verify import verify

import os
import os.path
import random

def getLogfileName():
    return Config.logfileName

def getApplicationCommand():
    return os.path.join(os.environ["ROOT"], "src", Config.applicationCommand)

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

def getTasks():
    file = File(codec)
    return {
        "netSource" : PushTask(Config.fn_receive, Source(codec, _random_tuple()), Config.dt_receive),
        "sensorSource" : SourceTask(Config.fn_collect, Source(codec, _random())),
        "netSink" : ControlSinkTask(Config.fn_send, Sink(codec), Config.testCount),
        "flashReceiveSink" : SinkTask(Config.fn_flash_receive, FileSink(file)),
        "flashCollectSink" : SinkTask(Config.fn_flash_collect, FileSink(file)),
        "flashSendSource" : SourceTask(Config.fn_flash_send, FileSource(file)),
    }
    
def createLog(t0, tasks):
    return Logs(t0, tasks) 
