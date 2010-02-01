from tasks import MockupTask, Aggregator
from config import Config

def run():
    tasks = {
        "receive" : MockupTask(Config.fn_receive, Config.fn_flash_receive, Config.dt_receive),
        "collect": MockupTask(Config.fn_collect, Config.fn_flash_collect, Config.dt_collect),
        "send" : Aggregator(Config.fn_flash_send, Config.fn_send, Config.dt_send)
    }

    for task in tasks.values():
        task.start()

    for task in tasks.values():
        task.sync()

    for task in tasks.values():
        task.join()
