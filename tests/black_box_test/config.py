class Config(object):
    dt_collect = 0.5
    dt_receive = 1
    dt_send = 2
    fn_receive = "/tmp/tc/receive.sock"
    fn_send = "/tmp/tc/send.sock"
    fn_collect = "/tmp/tc/collect.sock"
    fn_flash = "/tmp/tc/flash.dat"

    sock_timeout = 5 / 1000.0
    logic_maxCount = 10

    @staticmethod
    def minTimeDelta():
        return min(dt_collect, dt_sent, dt_receive)
