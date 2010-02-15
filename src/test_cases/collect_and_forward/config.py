class Config(object):
    applicationCommand = "application/collect_and_forward/event-based/event-based"
#    applicationCommand = "application/collect_and_forward/mockup/main.py"

    logfileName = "/tmp/tc/log.pickle"
    
    path = "/tmp/tc/"

    fn_receive = path + "receive.sock"
    fn_send = path + "send.sock"
    fn_collect =path + "collect.sock"
    fn_flash_receive_source = path + "flash-receive-source.sock"
    fn_flash_collect_source = path + "flash-collect-source.sock"
    fn_flash_receive_sink = path + "flash-receive-sink.sock"
    fn_flash_collect_sink = path + "flash-collect-sink.sock"

    testCount = 3
    max_dt_deviance = 0.01
    first_dt = 0.1

    dt_collect = 0.5
    dt_receive = 1
    dt_send = 2
