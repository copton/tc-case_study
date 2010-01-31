from threading import Thread, Event

class Task(Thread):
    shutdown = Event()
    def __init__(self):
        Thread.__init__(self)
        self.setup = Event()

    def run(self):
        self.threadSetup()
        self.setup.set()
        while not Task.shutdown.isSet():
            self.action()
        self.threadShutdown()

    def start(self):
        print self, "starting..."
        Thread.start(self)
        print self, "started"

    def sync(self):
        self.setup.wait()
        print self, "synced"

    def join(self):
        print self, "joining..."
        Thread.join(self)
        print self, "joined"
