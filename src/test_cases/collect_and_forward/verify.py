from config import Config

def verify(logs):
    def check_frequency():
        def _check_frequency(dt, log):
            last = logs.t0 + Config.first_dt
            for entry in log:
                assert entry[0] - last - dt < Config.max_dt_deviance, (entry[0], last, entry[0] - last, dt, Config.max_dt_deviance)
                last = entry[0]

        _check_frequency(Config.dt_receive, logs.receiveRead)
        _check_frequency(Config.dt_receive, logs.flashReceiveWritten)

        _check_frequency(Config.dt_send, logs.sendWritten)
        _check_frequency(Config.dt_send, logs.flashReceiveRead)
        _check_frequency(Config.dt_send, logs.flashCollectRead)
    
        _check_frequency(Config.dt_collect, logs.collectRead)
        _check_frequency(Config.dt_collect, logs.flashCollectWritten)

    def check_flow():
        def _check_flow(log1, log2):
            if len(log1) == len(log2) + 1:
                log1.pop()
            assert len(log1) == len(log2), (len(log1), len(log2), log1, log2)
            pairs = zip(log1, log2)
            for pair in pairs:
                assert pair[0][1] == pair[1][1], pair

        _check_flow(logs.receiveRead, logs.flashReceiveWritten)
        _check_flow(logs.collectRead, logs.flashCollectWritten)

    def check_result():
        def select(lst, idx):
            return [entry[idx] for entry in lst]

        assert len(logs.flashReceiveRead) == len(logs.sendWritten)
        assert len(logs.flashCollectRead) == len(logs.sendWritten)

        vals_receive_in = select(logs.flashReceiveRead, 1)
        vals_collect_in = select(logs.flashCollectRead, 1)
        vals_out = select(logs.sendWritten, 1)

        for i in range(len(vals_out)):
            res_min = reduce(min, vals_receive_in[i] + vals_collect_in[i])
            res_max = reduce(max, vals_receive_in[i] + vals_collect_in[i])
            assert [res_min, res_max] == vals_out[i]
            
    check_frequency()
    check_flow()
    check_result()
