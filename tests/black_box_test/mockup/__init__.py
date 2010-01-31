import parts
import tasks
from config import Config

def run():
    tasks = {
        "receive" : tasks.MockupTask(Config.fn_receive, Config.fn_flash_receive),
        "collect": tasks.MockupTask(Config.fn_collect, Config.fn_flash_collect),
        "send" : tasks.MockupTask(Config.fn_flash_send, Config.fn_send)
    }

    for task in tasks.values():
        task.start()

    for task in tasks.values():
        task.sync()

    for task in tasks.values():
        task.join()
