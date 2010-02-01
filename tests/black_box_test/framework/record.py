import parts
from time import time

def record(command):
    tasks = parts.getTasks()

    for task in tasks.values():
        task.start()

    proc = parts.application(command)

    for task in tasks.values():
        task.sync()

    t0 = time()

    for task in tasks.values():
        task.join()

    proc.wait()

    log = parts.Log(t0, tasks) 
    return log
