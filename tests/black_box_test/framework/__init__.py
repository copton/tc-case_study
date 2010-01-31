import parts
from logic import Logic

def run(command):
    tasks = parts.getTasks()

    for task in tasks.values():
        task.start()

    proc = parts.application(command)

    for task in tasks.values():
        task.sync()

    logic = Logic(tasks)

    for task in tasks.values():
        task.join()

    proc.wait()

    logic.test()
