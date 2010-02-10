#!/usr/bin/env python

from tasks import OnDemandTask, FrequentTask, Aggregator

import test_cases.collect_and_forward
from test_cases.collect_and_forward.config import Config

def run():
    tasks = {
        "receive" : OnDemandTask(Config.fn_receive, Config.fn_flash_receive),
        "collect": FrequentTask(Config.fn_collect, Config.fn_flash_collect, Config.dt_collect),
        "send" : Aggregator(Config.fn_flash_send, Config.fn_send, Config.dt_send)
    }

    for task in tasks.values():
        task.start()

    for task in tasks.values():
        task.sync()

    for task in tasks.values():
        task.join()

run()
