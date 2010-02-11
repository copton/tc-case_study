from config import Config

def verify(logs):
    def check_frequency():
        def _check_frequency(dt, log):
            last = logs.t0 + Config.first_dt
            for entry in log:
                assert entry[0] - last - dt < Config.max_dt_deviance
                last = entry[0]

        _check_frequency(Config.dt_receive, logs.receiveRead)
        _check_frequency(Config.dt_receive, logs.flashReceiveWritten)

        _check_frequency(Config.dt_send, logs.sendWritten)
        _check_frequency(Config.dt_send, logs.flashSendRead)
    
        _check_frequency(Config.dt_collect, logs.collectRead)
        _check_frequency(Config.dt_collect, logs.flashCollectWritten)

    def check_flow():
        def _check_flow(log1, log2):
            assert len(log1) == len(log2), (log1, log2)
            pairs = zip(log1, log2)
            for pair in pairs:
                assert pair[0][1] == pair[1][1], pair

        _check_flow(logs.receiveRead, logs.flashReceiveWritten)
        _check_flow(logs.collectRead, logs.flashCollectWritten)

    def check_result():
        def select(lst, idx):
            return [entry[idx] for entry in lst]

        assert len(logs.flashSendRead) == len(logs.sendWritten), (logs.flashSendRead, logs.sendWritten)

        vals_in = select(logs.flashSendRead, 1)
        vals_out = select(logs.sendWritten, 1)
        for pair in zip(vals_in, vals_out):
            result = [reduce(min, pair[0]), reduce(max, pair[0])]
            assert pair[1] == result, (pair[1], result)
            
    check_frequency()
    check_flow()
    check_result()
