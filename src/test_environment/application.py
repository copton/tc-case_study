import subprocess
from debug import debugout

class Application(object):
    def  __init__(self, command, params):
        self.command = command
        self.proc = None
        self.params = params
    
    def start(self):
        assert self.proc == None, "application already started"

        cmdline = [self.command]
        for k, v in self.params:
            cmdline.append("-" + k)
            cmdline.append(str(v))

        debugout("starting application", cmdline)
        self.proc = subprocess.Popen(cmdline)

    def wait(self):
        self.proc.wait()

    def kill(self):
        self.proc.kill()
