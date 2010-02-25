class FunctionDeco(object):
    def __init__(self):
        self.freq = {}

    def getDecoName(self, function):
        if self.freq.has_key(function):
            self.freq[function] += 1
        else:
            self.freq[function] = 1
        
        freq = self.freq[function]
        if freq == 1:
            return function
        else:
            return function + "#" + str(freq)
