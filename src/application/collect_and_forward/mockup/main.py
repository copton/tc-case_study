#!/usr/bin/env python

from tasks import Collect, Receive, Send

import test_cases.collect_and_forward
from test_cases.collect_and_forward.config import Config

def run():
    tasks = {
        "receive" : Receive(Config.fn_receive, Config.fn_flash_receive_sink),
        "collect": Collect(Config.fn_collect, Config.fn_flash_collect_sink, Config.dt_collect),
        "send" : Send(Config.fn_flash_receive_source, Config.fn_flash_collect_source, Config.fn_send, Config.dt_send)
    }

    for task in tasks.values():
        task.start()

    for task in tasks.values():
        task.sync()

    for task in tasks.values():
        task.join()

run()
