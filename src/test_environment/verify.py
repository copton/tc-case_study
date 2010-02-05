import pickle

def cmd(test):
    f = open(test.getLogfileName(), "r")
    log = pickle.load(f)
    test.verify(log)
