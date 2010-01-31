from time import time
from config import Config

class Logic(object):
    def __init__(self, tasks):
        self.t0 = time()
        self.tasks = tasks

    def _check_frequency(self, dt, log):
        last = self.t0 + Config.first_dt
        for entry in log:
            assert entry[0] - last - dt < Config.max_dt_deviance
            last = entry[0]

    def test(self):
        receiveRead = self.tasks["netSource"].source.getLog()
        collectRead = self.tasks["sensorSource"].source.getLog()
        sendWritten = self.tasks["netSink"].sink.getLog()
        flashReceiveWritten = self.tasks["flashReceiveSink"].sink.getLog()
        flashCollectWritten = self.tasks["flashCollectSink"].sink.getLog()
        flashSendRead = self.tasks["flashSendSource"].source.getLog()

        
        def check_frequency():
            self._check_frequency(Config.dt_receive, receiveRead)
            self._check_frequency(Config.dt_receive, flashReceiveWritten)

            self._check_frequency(Config.dt_send, sendWritten)
            self._check_frequency(Config.dt_send, flashSendRead)
        
            self._check_frequency(Config.dt_collect, collectRead)
            self._check_frequency(Config.dt_collect, flashCollectWritten)

        check_frequency()
