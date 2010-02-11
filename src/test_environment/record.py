from time import time
from application import Application
import pickle
import shutil
import os
import tasks

def cmd(test):
    shutil.rmtree(test.getTmpDir(), ignore_errors=True)
    os.makedirs(test.getTmpDir())

    app = Application(test.getApplicationCommand(), test.getApplicationParameter())
    tasks = test.getTasks(app.kill)

    t0 = run(tasks, app)

    log = test.createLog(t0, tasks)

    f = open(test.getLogfileName(), "w")
    pickle.dump(log, f)

def run(tasks, application):
    for task in tasks.values():
        task.start()

    application.start()

    for task in tasks.values():
        task.sync()

    t0 = time()

    application.wait()

    for task in tasks.values():
        task.join()

    return t0
