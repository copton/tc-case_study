import parts
from logic import Logic

def run():
    tasks = parts.getTasks()

    for task in tasks.values()
        task.start()

    proc = application()

    for task in tasks.values():
        task.sync()

    logic = Logic(tasks)
    logic.wait()

    for task in tasks.values():
        task.join()

    proc.wait()

    logic.test()
