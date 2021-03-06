class Config(object):
    applicationCommands = {
        "hand-written": "application/collect_and_forward/hand-written/hand-written",
        "mockup": "application/collect_and_forward/mockup/main.py",
        "threads": "application/collect_and_forward/thread-based/thread-based",
        "generated": "application/collect_and_forward/generated/generated",
    }

    logfileName = "/tmp/tc/log.pickle"
    
    path = "/tmp/tc/"

    fn_receive = path + "receive.sock"
    fn_send = path + "send.sock"
    fn_collect =path + "collect.sock"
    fn_flash_receive_source = path + "flash-receive-source.sock"
    fn_flash_collect_source = path + "flash-collect-source.sock"
    fn_flash_receive_sink = path + "flash-receive-sink.sock"
    fn_flash_collect_sink = path + "flash-collect-sink.sock"

    testCount = 10
    max_dt_deviance = 0.02
    first_dt = 0.1

    dt_collect = 0.5
    dt_receive = 1
    dt_send = 2
