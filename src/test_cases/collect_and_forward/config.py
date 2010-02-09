class Config(object):
    applicationCommand = "application/collect_and_forward/event-based/event-based"
#    applicationCommand = "application/collect_and_forward/mockup/main.py"

    logfileName = "/tmp/tc/log.pickle"
    
    path = "/tmp/tc/"

    fn_receive = path + "receive.sock"
    fn_send = path + "send.sock"
    fn_collect =path + "collect.sock"
    fn_flash_receive = path + "flash-receive.sock"
    fn_flash_send = path + "flash-send.sock"
    fn_flash_collect = path + "flash-collect.sock"

    testCount = 3
    max_dt_deviance = 0.01
    first_dt = 0.1

    dt_collect = 0.5
    dt_receive = 1
    dt_send = 2
