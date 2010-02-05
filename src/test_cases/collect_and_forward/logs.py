class Logs(object):
    def __init__(self, t0, tasks):
        self.t0 = t0
        self.receiveRead = tasks["netSource"].source.getLog()
        self.collectRead = tasks["sensorSource"].source.getLog()
        self.sendWritten = tasks["netSink"].sink.getLog()
        self.flashReceiveWritten = tasks["flashReceiveSink"].sink.getLog()
        self.flashCollectWritten = tasks["flashCollectSink"].sink.getLog()
        self.flashSendRead = tasks["flashSendSource"].source.getLog()


