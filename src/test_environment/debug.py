from threading import Lock, current_thread
import sys
from time import time

l = Lock()

def debugout(*what):
    id = current_thread().ident
    now = int(time())
    parts = [now, id] + list(what)
    out = ": ".join(map(str, parts)) + "\n"

    l.acquire()
    sys.stdout.write(out)
    l.release()
