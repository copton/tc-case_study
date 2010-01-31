from threading import Thread, Event

class Task(Thread):
    def __init__(self):
        Thread.__init__(self)

        self.shutdown = Event()
        self.shutdown.clear()

        self.setup = Event()
        self.setup.clear()

    def run(self):
        self.threadSetup()
        self.setup.set()
        while not self.shutdown.isSet():
            print self, "action"
            self.action()

    def start(self):
        print self, "starting..."
        Thread.start(self)
        print self, "started"

    def sync(self):
        self.setup.wait()

    def join(self, shutdown=False):
        self.shutdown.set()
        Thread.join(self)
