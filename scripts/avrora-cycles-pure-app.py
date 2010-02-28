#!/usr/bin/env python

import fileinput
import re
import sys

generated_funs = {
"ec_sub1_aggregate_from" : 0,
"ec_sub1_collect_run" : 0,
"ec_sub1_log_to" : 0,
"ec_sub1_receive_run" : 0,
"ec_sub1_send_run" : 0,
"ec_sub1_send_via" : 0,
"ec_sub2_aggregate_from" : 0,
"ec_sub2_collect_run" : 0,
"ec_sub2_log_to" : 0,
"ec_sub2_receive_run" : 0,
"ec_sub2_run_collect" : 0,
"ec_sub2_run_receive" : 0,
"ec_sub2_run_send" : 0,
"ec_sub2_send_run" : 0,
"ec_sub2_send_via" : 0,
"ec_sub3_collect_run" : 0,
"ec_sub3_receive_run" : 0,
"ec_sub3_send_run" : 0,
"ec_sub4_collect_run" : 0,
"ec_sub4_receive_run" : 0,
"ec_sub4_send_run" : 0,
"ec_sub5_collect_run" : 0,
"ec_sub5_receive_run" : 0,
"ec_sub5_send_run" : 0,
"ec_sub6_collect_run" : 0,
"ec_sub6_send_run" : 0,
"ec_sub7_send_run" : 0,
}

event_based_funs = {
"fired":0,
"readDone":0,
"appendDone":0,
"sendDone":0,
"receive":0,
}

class Process():
    def __init__(self, myfavors):
        self.cycles = 0
        self.region = 0
        self.t1 = 0
        self.favors = myfavors

    def _current_stack(self, line):
        stack = r'([a-zA-Z_][a-zA-Z0-9_]*)?:? @'
        if line.find(':') == -1:
            return ' '
        else:
            return re.search(stack, line).group(1)

    def _istate(self, line):
        assert line.find('>') > 0 or line.find('<') > 0

        isOnStack_p = None
        isFun_p = None
        cr = None

        parts = re.split("\s*", line)
        fname = parts[-2]
        time = int(parts[2])

        isFun_p = self.favors.has_key(fname)
        isOnStack_p = self.favors.has_key(self._current_stack(line))
        if line.find('>') > 0: 
            cr = '>'
        else:
            cr = '<'

        if isFun_p:
            if isOnStack_p:
                if cr == '<':
                    return 1 
                else:
                    return 2 
            else:
                if cr == '<':
                    return 3
                else:
                   return 4
        else:
            if isOnStack_p:
                if cr == '<':
                    return 5
                else:
                    return 6
                pass
            else:
                if cr == '<':
                   return 7
                else:
                   return 8

    def __call__(self, line):
        if line.find('>') > 0 or line.find('<') > 0:
            parts = re.split("\s*", line)
            time = int(parts[2])
            mystate = self._istate(line)

            if mystate == 4:
                self.t1 = time
            elif mystate == 5:
                self.t1 = time
            elif mystate == 3:
                self.cycles += time - self.t1
            elif mystate == 6:
                self.cycles += time - self.t1
            else:
                pass

        #print 'XXXXXXXXXXXXXXXX self.t1 ', self.t1, " time ", time
        #print '\033[1;38m' + line[:-1] + '\033[1;m'
   
    def dump_stats(self):
        sys.stdout.write(str(self.cycles) + "\n")


process = None
result_type = None
if len(sys.argv) > 2:
    if sys.argv[2] == '-evt':
        process = Process(event_based_funs)
        result_type = 'evt'
    elif sys.argv[2] == '-gen':
        process = Process(generated_funs)
        result_type = 'gen'

for line in fileinput.input(sys.argv[1]):
        process(line)

sys.stdout.write("total cycles of app " + result_type + ": ")
process.dump_stats()
