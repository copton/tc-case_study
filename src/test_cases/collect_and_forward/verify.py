from config import Config
import sys

failed=0

def check(condition, what):
    global failed
    if not condition:
        sys.stdout.write("failed: " + what + "\n")
        failed=1
    else:
        sys.stdout.write("good: " + what + "\n")

def verify(logs):
    def check_frequency():
        def _check_frequency(dt, log, what):
            sys.stdout.write("checking frequency of " + what + "\n")
            last = logs.t0 + Config.first_dt
            for entry in log:
                check(entry[0] - last - dt < Config.max_dt_deviance, str((entry[0], last, entry[0] - last, dt, Config.max_dt_deviance)))
                last = entry[0]

        _check_frequency(Config.dt_receive, logs.receiveRead, "receiveRead")
        _check_frequency(Config.dt_receive, logs.flashReceiveWritten, "flashReceiveWritten")

        _check_frequency(Config.dt_send, logs.sendWritten, "sendWritten")
        _check_frequency(Config.dt_send, logs.flashReceiveRead, "flashReceiveRead")
        _check_frequency(Config.dt_send, logs.flashCollectRead, "flashCollectRead")
    
        _check_frequency(Config.dt_collect, logs.collectRead, "collectRead")
        _check_frequency(Config.dt_collect, logs.flashCollectWritten, "flashCollectWritten")

    def check_flow():
        def _check_flow(log1, log2, what):
            sys.stdout.write("checking flow of " + what + "\n")
            if len(log1) == len(log2) + 1:
                log1.pop()
            check(len(log1) == len(log2), "len: " + str((len(log1), len(log2))))
            pairs = zip(log1, log2)
            for pair in pairs:
                check(pair[0][1] == pair[1][1], "values: " + str(pair))

        _check_flow(logs.receiveRead, logs.flashReceiveWritten, "receiveRead <-> flashReceiveWritten")
        _check_flow(logs.collectRead, logs.flashCollectWritten, "collectRead <-> flashCollectWritten")

    def check_result():
        sys.stdout.write("checking result\n")
        def select(lst, idx):
            return [entry[idx] for entry in lst]

        check(len(logs.flashReceiveRead) == len(logs.sendWritten), "logs.flashReceiveRead")
        check(len(logs.flashCollectRead) == len(logs.sendWritten), "logs.flashCollectRead")

        vals_receive_in = select(logs.flashReceiveRead, 1)
        vals_collect_in = select(logs.flashCollectRead, 1)
        vals_out = select(logs.sendWritten, 1)

        for i in range(len(vals_out)):
            res_min = reduce(min, vals_receive_in[i] + vals_collect_in[i])
            res_max = reduce(max, vals_receive_in[i] + vals_collect_in[i])
            check([res_min, res_max] == vals_out[i], "values: " + str(([res_min, res_max], vals_out[i])))
            
    check_frequency()
    check_flow()
    check_result()

    if failed:
        sys.stdout.write("some checks failed\n")
